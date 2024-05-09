#include <iostream>
#include <thread>
using namespace std;
int counter = 0;
void increas_counter(int thread_id){
    for (int i = 0; i < 10; ++i) {
        counter+=thread_id;
        cout<<"Thread id: "<<thread_id<<" counter: "<<counter<<endl;
    }
}

int main() {
    thread thr1(increas_counter,1);
    cout<<endl;
    thread thr2(increas_counter,2);
    cout<<endl;
    thread thr3(increas_counter,3);
    cout<<endl;
    thr1.join();
    thr2.join();
    thr3.join();
    return 0;
}
