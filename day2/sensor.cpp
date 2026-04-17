#include<bits/stdc++.h>
using namespace std;
class sensor{     //make_unique is an utility function used from c++ 14 it is used to automatically 
                      //manages dma by avoiding memory leaks and exceptions in some situations
    public:                   // when new operator share same memory location error double deletion
    int d;
    sensor(int x)
    {
        d=x;
        cout<<"sensor is on"<<endl;
    }
    ~sensor()
    {
        cout<<"sensor is off"<<endl;
    }
    void display()
    {
        cout<<"temperature is:"<<d<<endl;
    }
    void calib()//most of API's 
{
  this->d=200;
}
};
void fun()
{
    unique_ptr<sensor>s1=make_unique<sensor>(20);//here i am allocating memory and initializex
    cout<<s1->d<<endl;
    
}
int main()
{
    fun();
    unique_ptr<sensor>s2=make_unique<sensor>(12);
    s2->display();
    unique_ptr<sensor>s3=move(s2);
    cout<<"after moving:"<<endl;
    s3->display();
    cout<<&s3<<endl;
    unique_ptr<sensor>s4(s3.release());
    s4->display();
    cout<<&s4<<endl;
      s2.reset(new sensor(4));
      sensor*raw=0;
       s3.swap(s2);
       raw=s3.get();//get method is used to copy data in unique pointer
      // raw=s2.get();//it just get data like to pass temperature calibration holding same address
     raw->calib();
     s3->display();
}
