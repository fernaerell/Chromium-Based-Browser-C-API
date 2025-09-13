#include <stdio.h>

#include <cbbapi/cbbapi.h>

#define BROWSER_PATH "C:/Program Files (x86)/Microsoft/Edge/Application/msedge.exe"
#define DATA_PATH "C:/Projects/Chromium-Based-Browser-API/data"
#define PORT 8080
#define URL "https://www.youtube.com/watch?v=xvFZjo5PgG0"

int main()
{
    browser_init(NULL);

    Browser* browser = browser_set_up(BROWSER_PATH, PORT, DATA_PATH);

    if(!browser_launch(browser)) printf("Failed to launch browser.\n");

    printf("Browser launched: %i\n", browser_has_launched(browser));

    BrowserVersion* browser_version = browser_get_browser_version(browser);

    printf("Browser: %s\n", browser_version_get_browser(browser_version));
    printf("Protocol Version: %s\n", browser_version_get_protocol_version(browser_version));
    printf("User Agent: %s\n", browser_version_get_user_agent(browser_version));
    printf("V8 Version: %s\n", browser_version_get_v8_version(browser_version));
    printf("Webkit Version: %s\n", browser_version_get_webkit_version(browser_version));
    printf("Websocket Debugger URL: %s\n", browser_version_get_websocket_debugger_url(browser_version));

    Pages* pages = browser_get_pages(browser);

    size_t pages_length = pages_get_length(pages);
    printf("Page amount: %zu\n", pages_get_length(pages));

    for(size_t i = 0; i < pages_length; i++)
    {
        Page* page = pages_get_page(pages, i);
        printf("page_index: %zu\n", i);
        printf("description: %s\n", page_get_description(page));
        printf("devtools_frontend_url: %s\n", page_get_devtools_frontend_url(page));
        printf("favicon_url: %s\n", page_get_favicon_url(page));
        printf("id: %s\n", page_get_id(page));
        printf("title: %s\n", page_get_title(page));
        printf("type: %s\n", page_get_type(page));
        printf("url: %s\n", page_get_url(page));
        printf("websocket_debugger_url: %s\n", page_get_websocket_debugger_url(page));
    }

    browser_free(browser);
    browser_version_free(browser_version);
    pages_free(pages);
    return 0;
}