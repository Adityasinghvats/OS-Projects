#include<iostream>
#include<thread>

int turn = 0;

class thread1{
    public:
    void non_critical_section(){
        int a = 0;
        while(++a < 10);
    }
    void operator()(int &x){
        while(true){
            while(turn != 0); // loop and wait
            x += 1;
            std::cout<<"Thread 1"<<x<<std::endl;
            turn = 1;
            non_critical_section();
        }
    }
};
// this proves that if non_critical_section of a process is large 
// it can delay and slow down other process in waitTurn
class thread2{
    public:
    void non_critical_section(){
        int a = 0;
        while(++a < 1000000000);
    }
    void operator()(int &x){
        while(true){
            while(turn != 1); // loop and wait
            x += 1;
            std::cout<<"Thread 2"<<x<<std::endl;
            turn = 0;
            non_critical_section();
        }
    }
};
int main(){
    int x = 0;
    thread1 obj1;
    thread2 obj2;
    std::thread t1(obj1, std::ref(x)); //Process a
    std::thread t2(obj2, std::ref(x)); //Process b

    t1.join();
    t2.join();

    return 0;
}