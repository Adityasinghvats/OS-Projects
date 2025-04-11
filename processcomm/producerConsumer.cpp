#include<iostream>
#include<queue>
#include<thread>
#include<mutex>
#include<condition_variable>

class Semaphore{
    private:
    std::mutex mutex_m;
    std::condition_variable condition_c;
    unsigned long count_c = 0; //Initilaized as lock
    public:
    Semaphore(int value){
        count_c = value;
    }
    void release(){ //one release is called it will run, without context switching, as it is atomic
        std::lock_guard<std::mutex> lock(mutex_m);
        ++count_c;
        //type mutex wrapper, automatically locks mutex and when it is out of scope releases it
        //ensure that mutex is released even if there is an error
        condition_c.notify_one();
    }
    void acquire(){
        std::unique_lock<std::mutex> lock(mutex_m);
        while(!count_c) condition_c.wait(lock);// handle spurious wake-ups
        --count_c;
    }
};

std::mutex mtx;
std::queue<int> buffer;
const unsigned int MAX_BUFFER_SIZE = 10;

Semaphore empty_slots(MAX_BUFFER_SIZE);//semaphore for empty slots
Semaphore filled_slots(0);//semaphore for filled slots

void producer(int value){
    empty_slots.acquire();//what if there is no empty slots

    {
        /*
        Inside this scope code will run using lock_guard
        ans destructed once scope is finished
        */
        std::lock_guard<std::mutex> lock(mtx);
        buffer.push(value); //as producer keeps on producing, fill the buffer for semaphore to know
        std::cout<<"Producing "<<value<<std::endl;
        std::cout<<"Buffer after producing: "<<buffer.size()<<std::endl<<std::endl;
    }
    filled_slots.release(); //signal thta a slot has been filled
}
void consumer(){
    filled_slots.acquire();//what if there is no filled slots
    int value;
    {
        /*
        Inside this scope code will run using lock_guard
        ans destructed once scope is finished
        */
        std::lock_guard<std::mutex> lock(mtx);
        value = buffer.front();
        buffer.pop(); //as producer keeps on producing, fill the buffer for semaphore to know
        std::cout<<"Consuming "<<value<<std::endl;
        std::cout<<"Buffer after Consuming: "<<buffer.size()<<std::endl<<std::endl;
    }
    empty_slots.release(); //signal that a slot has been emptied
}

int main(){
    std::thread producerThread([]{ //spwan 20 threads
        for(int i=1;i<=2000;++i){
            producer(i);
        }
    });
    // std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
    std::thread consumerThread([]{
        for(int i=1;i<=2000;++i){
            consumer();
        }
    });
    producerThread.join();
    consumerThread.join();
    
    return 0;
}
