#ifndef BROWSER_VERSION_H
#define BROWSER_VERSION_H

typedef struct BrowserVersion
{
    char* browser;
    char* protocol_version;
    char* user_agent;
    char* v8_version;
    char* webkit_version;
    char* websocket_debugger_url;
} BrowserVersion;

BrowserVersion* browser_version_create(
    const char* browser, const char* protocol_version, const char* user_agent, const char* v8_version,
    const char* webkit_version, const char* websocket_debugger_url);

const char* browser_version_get_browser(BrowserVersion* browser_version);

const char* browser_version_get_protocol_version(BrowserVersion* browser_version);

const char* browser_version_get_user_agent(BrowserVersion* browser_version);

const char* browser_version_get_v8_version(BrowserVersion* browser_version);

const char* browser_version_get_webkit_version(BrowserVersion* browser_version);

const char* browser_version_get_websocket_debugger_url(BrowserVersion* browser_version);

void browser_version_free(BrowserVersion* browser_version);

#endif