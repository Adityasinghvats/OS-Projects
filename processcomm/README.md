- This repo is meant to be a code repo for the algorithms used for process synchronisation
- How to prevent deadlocks, mutexes and semaphores.
- consumer-producer is a buffer for producers to give info and consumer to take info, producer needs to know when to sleep and stop producing and consumer needs to know how to and when to stop consuming
- buffer is a shared resource so there should be context sync between both, to prevent a situation where consumer and procucer both sleep.
- CS - critical section.
- Semaphores , mutex are kind of locks, conditional variable , use TSL (Test and set lock instruction) under the hood to user kernel to manage processes.
- Conditional variable doesn't check for wakeup call continuously, thus saving clock cycles, and prevent busy waiting.
- When a semaphore is working it disables hardware interrupts, which means semaphores are atomic.
- A mutex (short for "mutual exclusion") is a synchronization primitive used to protect shared resources in a multithreaded environment. It ensures that only one thread can access a critical section of code or a shared resource at a time. Mutexes are commonly used to prevent race conditions, where multiple threads try to modify the same resource simultaneously, leading to unpredictable behavior.
How Mutex Works
- Locking: When a thread wants to access a shared resource, it locks the mutex.
- Critical Section: While the mutex is locked, no other thread can access the resource.
- Unlocking: Once the thread finishes its work, it unlocks the mutex, allowing other threads to proceed.

Semaphore vs. Mutex
While both semaphores and mutexes are used for synchronization, they serve different purposes:
- Mutex: Used for mutual exclusion, ensuring that only one thread accesses a resource at a time.
- Semaphore: Used for signaling and managing access to a pool of resources (e.g., multiple slots in a buffer).


How Mutex and Semaphore Work Together
In some scenarios, mutexes and semaphores are used together to achieve both mutual exclusion and signaling. For example:
- A mutex can protect the critical section where a shared resource (like a buffer) is modified.
- A semaphore can signal the availability of resources (e.g., empty or filled slots in a buffer).

Example: Producer-Consumer Problem
In the producer-consumer problem:
- A mutex ensures that only one thread (producer or consumer) modifies the buffer at a time.
- A semaphore tracks the number of empty slots (for producers) and filled slots (for consumers).

This combination ensures both thread safety and proper coordination between both.
