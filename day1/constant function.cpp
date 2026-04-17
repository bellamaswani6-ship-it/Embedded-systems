#include<bits/stdc++.h>
using namespace std;
class led
{
    bool status;
    int size;
    string colur;
    public:
    led(int a,bool c,string s)
    {
        size=a;
        status=c;
        s=colur;
    }
    void on()
    {
        status=true;
    }
    void off()
    {
        status=false;
    }
    void dispaly()const
    {
        if(status==true)
        cout<<"led is on"<<endl;
        else
        cout<<"led is off"<<endl;
    }
};
int main()
{
    led o1(2,false,"green");
    o1.on();
    o1.dispaly();
    led o2(4,true,"yellow");
    o2.off();
    o2.dispaly();
}