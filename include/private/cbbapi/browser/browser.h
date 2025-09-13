#ifndef BROWSER_H
#define BROWSER_H

#include "cbbapi/browser/browser_version.h"
#include "cbbapi/browser/page/pages.h"

typedef struct Browser
{
    char* browser_path;
    unsigned short port;
    char* data_path;
} Browser;

void browser_init(void* java_vm);

Browser* browser_set_up(const char* browser_path, const unsigned short port, const char* data_path);

int browser_launch(Browser* browser);

int browser_has_launched(Browser* browser);

BrowserVersion* browser_get_browser_version(Browser* browser);

Pages* browser_get_pages(Browser* browser);

void browser_free(Browser* browser);

#endif