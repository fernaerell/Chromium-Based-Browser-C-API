#include <stdlib.h>
#include <string.h>

#include "cbbapi/browser/browser_version.h"

BrowserVersion* browser_version_create(
    const char* browser, const char* protocol_version, const char* user_agent, const char* v8_version,
    const char* webkit_version, const char* websocket_debugger_url)
{
    if(!browser || !protocol_version || !user_agent || !v8_version || !webkit_version || !websocket_debugger_url)
        return NULL;
    BrowserVersion* browser_version = malloc(sizeof(BrowserVersion));
    if(!browser_version) return NULL;
    browser_version->browser = strdup(browser);
    browser_version->protocol_version = strdup(protocol_version);
    browser_version->user_agent = strdup(user_agent);
    browser_version->v8_version = strdup(v8_version);
    browser_version->webkit_version = strdup(webkit_version);
    browser_version->websocket_debugger_url = strdup(websocket_debugger_url);
    return browser_version;
}

const char* browser_version_get_browser(BrowserVersion* browser_version)
{
    if(!browser_version) return NULL;
    return browser_version->browser;
}

const char* browser_version_get_protocol_version(BrowserVersion* browser_version)
{
    if(!browser_version) return NULL;
    return browser_version->protocol_version;
}

const char* browser_version_get_user_agent(BrowserVersion* browser_version)
{
    if(!browser_version) return NULL;
    return browser_version->user_agent;
}

const char* browser_version_get_v8_version(BrowserVersion* browser_version)
{
    if(!browser_version) return NULL;
    return browser_version->v8_version;
}

const char* browser_version_get_webkit_version(BrowserVersion* browser_version)
{
    if(!browser_version) return NULL;
    return browser_version->webkit_version;
}

const char* browser_version_get_websocket_debugger_url(BrowserVersion* browser_version)
{
    if(!browser_version) return NULL;
    return browser_version->websocket_debugger_url;
}

void browser_version_free(BrowserVersion* browser_version)
{
    if(!browser_version) return;
    if(browser_version->browser) free(browser_version->browser);
    if(browser_version->protocol_version) free(browser_version->protocol_version);
    if(browser_version->user_agent) free(browser_version->user_agent);
    if(browser_version->v8_version) free(browser_version->v8_version);
    if(browser_version->webkit_version) free(browser_version->webkit_version);
    if(browser_version->websocket_debugger_url) free(browser_version->websocket_debugger_url);
    free(browser_version);
}