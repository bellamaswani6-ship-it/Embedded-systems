#include<bits/stdc++.h>
using namespace std;
int main()
{
    unique_ptr<int>p1=make_unique<int>(20);
    cout<<*p1<<endl;
    cout<<&p1<<endl;
    //unique_ptr<int>p2=p1;//as copying not possible in unique_ptr becoz of exclusive ownership
    unique_ptr<int>p2=move(p1);
     cout<<*p2<<endl;
    cout<<&p2<<endl;
}