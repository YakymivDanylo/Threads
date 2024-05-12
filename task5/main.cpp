#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>

using namespace std;

template<typename T>
class Queue {

    int size;
    int max_size;
    list <T> thelist;

public:
    Queue(T data, int new_max_size) {
        list<T> temp(data);
        thelist = temp;
        size = 1;
        max_size = new_max_size;
    }
    void enqueue(T data) {
        if (!this->isFull()) {
            thelist.push_back(data);
            size++;
        } else {
            throw overflow_error("Queue is full.");
        }
    }
    T dequeue() {
        if (!this->isEmpty()) {
            T data = thelist.front();
            thelist.pop_back();
            --size;
            return data;
        } else {
            throw out_of_range("Queue is empty!");
        }
    }

    bool isEmpty() {
        if (size == 0) {
            return true;
        }
        return false;
    }
    bool isFull() {
        if (size == max_size) {
            return true;
        }
        return false;
    }
    [[nodiscard]]int getMaxSize() {
        return max_size;
    }
};

mutex mute;
condition_variable cond_var;
bool flag = false;

Queue sharedData(1, 10);
[[maybe_unused]] int deleted = sharedData.dequeue();

void writer() {
    {
        lock_guard<mutex> guard_lock(mute);
        cout << "Mutex was locked for writing data." << endl;
        for (int i = 0; i < sharedData.getMaxSize(); i++) {
            sharedData.enqueue(3);
        }
        flag = true;
    }
    cond_var.notify_one();
}
void reader() {
    unique_lock<mutex> uniqueLock(mute);
    cout << "Mutex was locked for reading data." << endl;
    cond_var.wait(uniqueLock, []{return flag;});
    for (int i = 0; i < sharedData.getMaxSize(); i++) {
        cout << sharedData.dequeue() << " ";
    }
    cout << endl;
    cout << "Data was read." << endl;
}
void task() {
    thread thr1(writer);
    thread thr2(reader);

    thr1.join();
    thr2.join();
}

int main() {
    task();

    return 0;
}