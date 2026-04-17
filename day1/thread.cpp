#include<bits/stdc++.h>
using namespace std;
atomic<int>counter{0};
//int counter;
void increment()
{
    int i;
    for(i=0;i<1000;++i)
    counter++;
}
void decrement()        //why dynamic memory not in embedded
                    //thread,atomic operation(synchronizTION),memory segment,NON atomic
{
    int i;
    for(i=0;i<1000;++i)
    counter--;
}
int main()
{
    thread t1(decrement);
    thread t2(decrement);
    t1.join();
    t2.join();
    cout<<"counter:"<<counter;
}