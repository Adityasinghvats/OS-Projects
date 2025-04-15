#include<windows.h>
#include<stdio.h>

DWORD Sum; //DWORD is a unsigned 32-bit int
DWORD Fact;
DWORD WINAPI Summation(LPVOID Param)
{
    DWORD Upper = *(DWORD*)Param;
    for(DWORD i =0; i<=Upper; i++ )
    {
        Sum += 1;
    }
    return 0;
}

DWORD RecursiveFactorial(DWORD n){
    if(n == 0 || n == 1) return 1;
    return n * RecursiveFactorial(n-1);
}

DWORD WINAPI Factorial(LPVOID Param)
{
    DWORD Upper = *(DWORD*)Param;
    Fact = RecursiveFactorial(Upper);
    return 0;
}



int main(int argc, char *argv[])
{
    DWORD ThreadId;
    HANDLE ThreadHandle;
    int Param;
    //error check
    if(argc != 2){
        fprintf(stderr, "An integer parameter is required\n");
        return -1;
    }
    Param = atoi(argv[1]);
    if(Param<0){
        fprintf(stderr, "An integer >= 0 is required\n");
        return -1;
    }

    //create thread
    // ThreadHandle = CreateThread(
    //     NULL,
    //     0,
    //     Summation,
    //     &Param,
    //     0,
    //     &ThreadId
    // );
    ThreadHandle = CreateThread(
        NULL,
        0,
        Factorial,
        &Param,
        0,
        &ThreadId
    );
    if(ThreadHandle != NULL){
        //wait for thread to finish
        WaitForSingleObject(ThreadHandle, INFINITE);
        //close thread handle
        CloseHandle(ThreadHandle);

        printf("Factorial of %d: %d\n", Param, Fact);
    }
}

/*
PS D:\Dev\OS\winapi> ./thread 100000                                                                                                 
100001
PS D:\Dev\OS\winapi> ./thread 10
11
PS D:\Dev\OS\winapi> ./thread 10000000000
-2147483648
PS D:\Dev\OS\winapi> ./thread 100000000
100000001
*/
/*
PS D:\Dev\OS\winapi> ./thread 1
Factorial of 1: 1
PS D:\Dev\OS\winapi> ./thread 2
Factorial of 2: 2
PS D:\Dev\OS\winapi> ./thread 3
Factorial of 3: 6
PS D:\Dev\OS\winapi> ./thread 4
Factorial of 4: 24
PS D:\Dev\OS\winapi> ./thread 5
Factorial of 5: 120
PS D:\Dev\OS\winapi> ./thread 6
Factorial of 6: 720
PS D:\Dev\OS\winapi> ./thread 7
Factorial of 7: 5040
PS D:\Dev\OS\winapi> ./thread 8
Factorial of 8: 40320
PS D:\Dev\OS\winapi> ./thread 9
Factorial of 9: 362880
PS D:\Dev\OS\winapi> ./thread 10
Factorial of 10: 3628800
PS D:\Dev\OS\winapi> ./thread 11
Factorial of 11: 39916800
PS D:\Dev\OS\winapi> ./thread 12
Factorial of 12: 479001600
PS D:\Dev\OS\winapi> ./thread 13
Factorial of 13: 1932053504
PS D:\Dev\OS\winapi> ./thread 14
Factorial of 14: 1278945280
PS D:\Dev\OS\winapi> ./thread 15
Factorial of 15: 2004310016
PS D:\Dev\OS\winapi> ./thread 16
Factorial of 16: 2004189184
PS D:\Dev\OS\winapi> ./thread 17
Factorial of 17: -288522240
*/