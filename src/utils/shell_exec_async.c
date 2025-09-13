#include <stdio.h>

#include "cbbapi/utils/shell_exec_async.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <stdlib.h>
#endif

int shell_exec_async(const char* args[])
{
#ifdef _WIN32
    char cmdline[1024];
    size_t pos = 0;
    for(int i = 0; args[i]; i++)
    {
        int n = snprintf(cmdline + pos, sizeof(cmdline) - pos, "%s ", args[i]);
        if(n < 0 || n >= (int)(sizeof(cmdline) - pos)) break;
        pos += n;
    }

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if(!CreateProcessA(NULL, cmdline, NULL, NULL, FALSE, DETACHED_PROCESS, NULL, NULL, &si, &pi))
    {
        return 0;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 1;
#else
    pid_t pid = fork();
    if(pid == 0)
    {
        setsid();
        execvp(args[0], (char* const*)args);
        perror("execvp");
        exit(127);
    }
    else if(pid < 0)
    {
        perror("fork");
        return 0;
    }
    return 1;
#endif
}