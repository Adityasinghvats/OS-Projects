#include<iostream>
#include<unistd.h>

using namespace std;

void pipeline(const char *process1,const char *arg1, const char *process2, const char *arg2){
    // taking input params 
    int fd[2]; //file descriptor array , each with 2 ends
    pipe(fd);
    int id = fork();
    if(id != 0){//parent fork() returns an int value 1 for parent , 0 for child
        close(fd[0]);//close read end of pipe
        dup2(fd[1], STDOUT_FILENO);//standard output redirected to output end of pipe
        close(fd[1]);

        execlp("/usr/bin/cat", process1, arg1, nullptr);//use `which cat` to find path
        cerr<< "Failed to execute" << process1 << endl;
    }else if(id != 1){
        close(fd[1]);//close the write end of the pipe
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        execlp("/usr/bin/grep", process2, arg2, nullptr);
        cerr<< "Failed to execute" << process2 << endl;
    }
}

int main(int argc, char* argv[]){
    string filename;
    string word;
    if(argc>2){
        filename = argv[1];
        word = argv[2];
    }

    pipeline("cat",filename.c_str(), "grep", word.c_str());
    return 0;
}