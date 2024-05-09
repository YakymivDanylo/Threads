#include <iostream>
#include <thread>
#include <string>
using namespace std;

int main() {
    int x=10;
    thread thr1([&x]{cout<<x*x;});
    cout<<endl;
    int y=5;
    thread thr2([&y]{cout<<y*y;});
    cout<<endl;
    int z=2;
    thread thr3([&z]{cout<<z*z;});
    cout<<endl;
    thr1.join();
    thr2.join();
    thr3.join();

    return 0;
}