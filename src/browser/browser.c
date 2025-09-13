#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "naett.h"
#include "json.h"

#include "cbbapi/browser/browser.h"
#include "cbbapi/utils/port_in_use.h"
#include "cbbapi/utils/shell_exec_async.h"
#include "cbbapi/browser/page/page.h"

void browser_init(void* java_vm) { naettInit(java_vm); }

Browser* browser_set_up(const char* browser_path, const unsigned short port, const char* data_path)
{
    if(!browser_path || !data_path) return NULL;
    Browser* browser = malloc(sizeof(Browser));
    if(!browser) return NULL;
    browser->browser_path = strdup(browser_path);
    browser->port = port;
    browser->data_path = strdup(data_path);
    return browser;
}

int browser_launch(Browser* browser)
{
    if(!browser || !browser->browser_path || !browser->data_path || browser_has_launched(browser)) return 0;

    size_t port_arg_len = snprintf(NULL, 0, "--remote-debugging-port=%hu", browser->port);
    char port_arg[port_arg_len + 1];
    snprintf(port_arg, port_arg_len + 1, "--remote-debugging-port=%hu", browser->port);

    size_t data_arg_len = snprintf(NULL, 0, "--user-data-dir=%s", browser->data_path);
    char data_arg[data_arg_len + 1];
    snprintf(data_arg, data_arg_len + 1, "--user-data-dir=%s", browser->data_path);

    const char* args[] = {browser->browser_path, port_arg, data_arg, "--no-first-run", "--disable-extensions", NULL};

    return shell_exec_async(args);
}

int browser_has_launched(Browser* browser)
{
    if(!browser) return 0;
    return port_in_use(browser->port);
}

BrowserVersion* browser_get_browser_version(Browser* browser)
{
    if(!browser) return NULL;

    char url[64];
    snprintf(url, sizeof(url), "http://localhost:%hu/json/version", browser->port);

    naettReq* req = naettRequest(url, naettMethod("GET"), naettHeader("accept", "application/json"));
    if(!req) return NULL;

    naettRes* res = naettMake(req);
    if(!res)
    {
        naettFree(req);
        return NULL;
    }

    while(!naettComplete(res)) usleep(100 * 1000); // 100ms

    if(naettGetStatus(res) < 0)
    {
        naettFree(req);
        return NULL;
    }

    int bodyLength = 0;
    const char* body = naettGetBody(res, &bodyLength);
    if(!body || bodyLength <= 0)
    {
        naettFree(req);
        return NULL;
    }

    json_object* json = json_tokener_parse(body);

    naettFree(req);

    json_object* browser_field = json_object_object_get(json, "Browser");
    json_object* protocol_version_field = json_object_object_get(json, "Protocol-Version");
    json_object* user_agent_field = json_object_object_get(json, "User-Agent");
    json_object* v8_version_field = json_object_object_get(json, "V8-Version");
    json_object* webkit_version_field = json_object_object_get(json, "WebKit-Version");
    json_object* websocket_debugger_url_field = json_object_object_get(json, "webSocketDebuggerUrl");

    BrowserVersion* browser_version = browser_version_create(
        json_object_get_string(browser_field), json_object_get_string(protocol_version_field),
        json_object_get_string(user_agent_field), json_object_get_string(v8_version_field),
        json_object_get_string(webkit_version_field), json_object_get_string(websocket_debugger_url_field));

    json_object_put(json);

    return browser_version;
}

Pages* browser_get_pages(Browser* browser)
{
    if(!browser) return NULL;

    char url[64];
    snprintf(url, sizeof(url), "http://localhost:%hu/json/list", browser->port);

    naettReq* req = naettRequest(url, naettMethod("GET"), naettHeader("accept", "application/json"));
    if(!req) return NULL;

    naettRes* res = naettMake(req);
    if(!res)
    {
        naettFree(req);
        return NULL;
    }

    while(!naettComplete(res)) usleep(100 * 1000); // 100ms

    if(naettGetStatus(res) < 0)
    {
        naettFree(req);
        return NULL;
    }

    int bodyLength = 0;
    const char* body = naettGetBody(res, &bodyLength);
    if(!body || bodyLength <= 0)
    {
        naettFree(req);
        return NULL;
    }

    json_object* jsons = json_tokener_parse(body);

    naettFree(req);

    Pages* pages = pages_create();

    size_t jsons_len = json_object_array_length(jsons);
    for(size_t i = 0; i < jsons_len; i++)
    {
        struct json_object* json = json_object_array_get_idx(jsons, i);
        json_object* type_field = json_object_object_get(json, "type");
        const char* type_field_str = json_object_get_string(type_field);
        if(strcmp(type_field_str, "page") != 0) continue;
        json_object* description_field = json_object_object_get(json, "description");
        json_object* devtools_frontend_url_field = json_object_object_get(json, "devtoolsFrontendUrl");
        json_object* favicon_url_field = json_object_object_get(json, "faviconUrl");
        json_object* id_field = json_object_object_get(json, "id");
        json_object* title_field = json_object_object_get(json, "title");
        json_object* url_field = json_object_object_get(json, "url");
        json_object* websocket_debugger_url_field = json_object_object_get(json, "webSocketDebuggerUrl");

        Page* page = page_create(
            json_object_get_string(description_field), json_object_get_string(devtools_frontend_url_field),
            json_object_get_string(favicon_url_field), json_object_get_string(id_field),
            json_object_get_string(title_field), type_field_str, json_object_get_string(url_field),
            json_object_get_string(websocket_debugger_url_field));

        pages_add(pages, page);
    }

    json_object_put(jsons);

    pages_shrink(pages);

    return pages;
}

void browser_free(Browser* browser)
{
    if(!browser) return;
    if(browser->browser_path) free(browser->browser_path);
    if(browser->data_path) free(browser->data_path);
    free(browser);
}