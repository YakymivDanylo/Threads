#include <iostream>
#include <thread>
#include <string>
using namespace std;

int main() {

    thread thr1([](int x){cout<<x*x<<endl;},5);
    cout<<endl;
    thread thr2([](int x){cout<<x*x;},4);
    cout<<endl;
    thread thr3([](int x){cout<<x*x;},3);
    cout<<endl;
    thr1.join();
    thr2.join();
    thr3.join();

    return 0;
}