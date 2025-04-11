#include<iostream>
#include<thread>

int lock = 0;

class thread_object{
public:
     void operator()(int &x){
        for(int i=0;i< 10000000;i++){
            while(lock != 0);
            lock = 1;//lock acquired
            x += 1;
            lock = 0; //lock left
        }
     }
};
/*
for i < 10000 , x = 20000
for i < 10^7 , x = 15758112
*/

int main(){
    int x = 0;
    thread_object obj;
    std::thread t1(obj, std::ref(x)); //Process a
    std::thread t2(obj, std::ref(x)); //Process b

    t1.join();
    t2.join();

    std::cout<<"Final value of x:"<<x<<std::endl;

    return 0;
}