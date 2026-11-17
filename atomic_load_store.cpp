// atomic_load_store.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <thread>
#include <atomic>


std::atomic<int> data{ 0 };
std::atomic<int> ready{ 0 };


int main()
{
    std::thread producer([] {
        data.store(42, std::memory_order_relaxed);
        ready.store(1, std::memory_order_release);
        });


    std::thread consumer([] {
        while (ready.load(std::memory_order_acquire) == 0) {};
        std::cout << "Consumer got the " << data.load(std::memory_order_relaxed) << " \n";
        });

    producer.join();
    consumer.join();
    std::cout << "Hello World!\n";
}
