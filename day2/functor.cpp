#include<bits/stdc++.h>
using namespace std;
class led
{
    public:
    bool state;
      led(bool r)
      {
         state=r; 
      }
    void operator()(bool r)const{
        
        if(r==true)
        {
            if(state==true)
        cout<<"invalid action"<<endl;
        else
        {
            r=true;
            cout<<"led is on"<<endl;
        }
        }
        else
        {
            r=false;
            cout<<"led is off"<<endl;
        }
        
    }
};
int main()
{
    unique_ptr<led,deleter>o1(new led(true),deleter{});
    o1(true);
    o1(true);
    o1(false);
}



