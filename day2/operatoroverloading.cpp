/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
using namespace std;
class complex{
    int real,imaginary;
    public:
    complex(){}
    complex(int a,int b)
    {
        real=a;
        imaginary=b;
    }
    complex  operator +(complex&o1)
    {
        complex t;
        t.real=real+o1.real;
        t.imaginary=imaginary+o1.imaginary;
        return t;
    }
    void display()
    {
        cout<<real<<"+i"<<imaginary<<endl;
    }
};

int main()
{
     complex o1(2,5),o2(4,3),o3;
     o3=o1+o2;
     o3.display();
}