#include<iostream>
using namespace std;
template<typename t>
class A{
    t *p;
    public:
     explicit A(t *ptr){
         p=ptr;
         cout<<"unique_ptr is created"<<endl;
     }
     ~A()
     {
           cout<<"unique_ptr gets deleted"<<endl;
         delete[]p;
     }
     A(const A&o){}
    t* operator -> () const
    {
        return p;
    }
    t& operator *()
    {
        return *p;
    }
   void reset(t *q=nullptr)  //it is reset means we take a nwe ptr and copy previous ptr to it
   {
       cout<<"reset function is working"<<endl;
       delete p;
       p=q;
   }
   void release() //relese is used when it is in middle we dont want
   {
       t *temp=p;
       p=nullptr;
   }
   
 };
 class B{
     public:
     B()
     {
         cout<<"B object created"<<endl;
     }
     ~B()
     {
         cout<<"B object destroyed"<<endl;
     }
     void display()
     {
         cout<<"hello from B"<<endl;
     }
 };
int main()
{
    A<B>o(new B());
    o->display();
    A<B>o1(new B());
    o1->display();
    cout<<&o1<<endl;
}