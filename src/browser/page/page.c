#include <stdlib.h>
#include <string.h>

#include "cbbapi/browser/page/page.h"

Page* page_create(
    const char* description, const char* devtools_frontend_url, const char* favicon_url, const char* id,
    const char* title, const char* type, const char* url, const char* websocket_debugger_url)
{
    if(!description || !devtools_frontend_url || !favicon_url || !id || !title || !type || !url ||
       !websocket_debugger_url)
        return NULL;
    Page* page = malloc(sizeof(Page));
    if(!page) return NULL;
    page->description = strdup(description);
    page->devtools_frontend_url = strdup(devtools_frontend_url);
    page->favicon_url = strdup(favicon_url);
    page->id = strdup(id);
    page->title = strdup(title);
    page->type = strdup(type);
    page->url = strdup(url);
    page->websocket_debugger_url = strdup(websocket_debugger_url);
    return page;
}

const char* page_get_description(Page* page)
{
    if(!page) return NULL;
    return page->description;
}

const char* page_get_devtools_frontend_url(Page* page)
{
    if(!page) return NULL;
    return page->devtools_frontend_url;
}

const char* page_get_favicon_url(Page* page)
{
    if(!page) return NULL;
    return page->favicon_url;
}

const char* page_get_id(Page* page)
{
    if(!page) return NULL;
    return page->id;
}

const char* page_get_title(Page* page)
{
    if(!page) return NULL;
    return page->title;
}

const char* page_get_type(Page* page)
{
    if(!page) return NULL;
    return page->type;
}

const char* page_get_url(Page* page)
{
    if(!page) return NULL;
    return page->url;
}

const char* page_get_websocket_debugger_url(Page* page)
{
    if(!page) return NULL;
    return page->websocket_debugger_url;
}

void page_free(Page* page)
{
    if(!page) return;
    if(page->description) free(page->description);
    if(page->devtools_frontend_url) free(page->devtools_frontend_url);
    if(page->favicon_url) free(page->favicon_url);
    if(page->id) free(page->id);
    if(page->title) free(page->title);
    if(page->type) free(page->type);
    if(page->url) free(page->url);
    if(page->websocket_debugger_url) free(page->websocket_debugger_url);
    free(page);
}