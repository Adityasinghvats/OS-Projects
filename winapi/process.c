#include<stdio.h>
#include<windows.h>
#include<tchar.h>

int main(VOID){
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    //allocate memory
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    //create child process
    /*
    Application name
        NULL,                      // Command line args
        NULL,                      // Process handle not inheritable
        NULL,                      // Thread handle not inheritable
        FALSE,                     // Set handle inheritance to FALSE
        0,                         // No creation flags
        NULL,                      // Use parent's environment block
        NULL,                      // Use parent's starting directory 
        &si,                       // Pointer to STARTUPINFO structure
        &pi                        // Pointer to PROCESS_INFORMATION structure
    
    The second parameter (lpCommandLine) must be a writable buffer, 
    not a string literal. You're passing a string literal directly.

    The command line argument should be the first parameter
     (lpApplicationName) when using a full path.
    */
    TCHAR szCmdline[] = _T("C:\\Windows\\System32\\notepad.exe");
    if(!CreateProcess(NULL,
    szCmdline,
    NULL,
    NULL,
    FALSE,
    0,
    NULL,
    NULL,
    &si,
    &pi
     )){
        DWORD error = GetLastError();
        fprintf(stderr, "Create process failed with error %lu\n", error);
        return -1;
     }
    WaitForSingleObject(pi.hProcess, INFINITE);
    printf("Child complete");

    //close handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}