#ifndef PAGE_H
#define PAGE_H

typedef struct Page
{
    char* description;
    char* devtools_frontend_url;
    char* favicon_url;
    char* id;
    char* title;
    char* type;
    char* url;
    char* websocket_debugger_url;
} Page;

Page* page_create(
    const char* description, const char* devtools_frontend_url, const char* favicon_url, const char* id,
    const char* title, const char* type, const char* url, const char* websocket_debugger_url);

const char* page_get_description(Page* page);

const char* page_get_devtools_frontend_url(Page* page);

const char* page_get_favicon_url(Page* page);

const char* page_get_id(Page* page);

const char* page_get_title(Page* page);

const char* page_get_type(Page* page);

const char* page_get_url(Page* page);

const char* page_get_websocket_debugger_url(Page* page);

void page_free(Page* page);

#endif