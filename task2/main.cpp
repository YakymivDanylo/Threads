#include <iostream>
#include <thread>
using namespace std;
int counter = 0;
void increas_counter(int thread_id){
    for (int i = 0; i < 5; ++i) {
        counter+=thread_id;
        cout<<"Thread id: "<<thread_id<<" counter: "<<counter<<" "<<endl;
    }
}

int main() {
    thread thr1(increas_counter,1);
    thread thr2(increas_counter,2);
    thread thr3(increas_counter,3);
    thr1.join();
    thr2.join();
    thr3.join();
    cout<<"Final value of counter: "<<counter<<endl;

    return 0;
}
