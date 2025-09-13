#ifndef CBBAPI_H
#define CBBAPI_H

#include <stddef.h>
typedef struct Browser Browser;

typedef struct BrowserVersion BrowserVersion;

typedef struct Pages Pages;

typedef struct Page Page;

void browser_init(void* java_vm);

Browser* browser_set_up(const char* browser_path, const unsigned short port, const char* data_path);

int browser_launch(Browser* browser);

int browser_has_launched(Browser* browser);

BrowserVersion* browser_get_browser_version(Browser* browser);

const char* browser_version_get_browser(BrowserVersion* browser_version);

const char* browser_version_get_protocol_version(BrowserVersion* browser_version);

const char* browser_version_get_user_agent(BrowserVersion* browser_version);

const char* browser_version_get_v8_version(BrowserVersion* browser_version);

const char* browser_version_get_webkit_version(BrowserVersion* browser_version);

const char* browser_version_get_websocket_debugger_url(BrowserVersion* browser_version);

Pages* browser_get_pages(Browser* browser);

size_t pages_get_length(Pages* pages);

Page* pages_get_page(Pages* pages, size_t index);

const char* page_get_description(Page* page);

const char* page_get_devtools_frontend_url(Page* page);

const char* page_get_favicon_url(Page* page);

const char* page_get_id(Page* page);

const char* page_get_title(Page* page);

const char* page_get_type(Page* page);

const char* page_get_url(Page* page);

const char* page_get_websocket_debugger_url(Page* page);

void browser_free(Browser* browser);

void browser_version_free(BrowserVersion* browser_version);

void pages_free(Pages* pages);

#endif