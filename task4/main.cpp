#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;
mutex mut1, mut2;
void funcA() {
    std::cout << "Thread1::Trying to lock mut1: " << std::endl;
    std::lock_guard<std::mutex> lockGuard1(mut1);
    std::cout << "Thread1::Mut1 was locked " << std::endl;
    std::this_thread::sleep_for(20ms);
    std::cout << "Thread1::Trying to lock mut2: " << std::endl;
    std::lock_guard<std::mutex> lockGuard2(mut2);
    std::cout << "Thread1::Mut2 was locked " << std::endl;
    std::this_thread::sleep_for(100ms);
    std::cout <<"Thread1::Thread 1 releases locks" << std::endl;
}
void funcB() {
    std::cout << "Thread2::Trying to lock mut2: " << std::endl;
    std::lock_guard<std::mutex> lockGuard2(mut2);
    std::cout << "Thread2::Mut2 was locked " << std::endl;
    std::this_thread::sleep_for(10ms);
    std::cout << "Thread2::Trying to lock mut1: " << std::endl;
    std::lock_guard<std::mutex> lockGuard1(mut1);
    std::cout << "Thread2::Mut1 was locked " << std::endl;
    std::this_thread::sleep_for(100ms);
    std::cout <<"Thread2::Thread 2 releases locks" << std::endl;
}

int main() {
    thread t1(funcA);
    thread t2(funcB);

    t1.join();
    t2.join();

    return 0;
}