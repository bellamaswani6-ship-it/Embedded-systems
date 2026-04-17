#include<bits/stdc++.h>
using namespace std;
int main()
{
shared_ptr<int>s=make_shared<int>(10);//there is no make_weak only should use make_shared for weak_ptr
//weak_ptr<int>wp=make_shared<int>(23);
weak_ptr<int>wp=s;
cout<<" at first weak count"<<wp.use_count()<<endl; // here it is 0 no memory for weak_ptr
cout<<"shared_ptr:"<<*s<<endl;
cout<<s.use_count()<<endl; //when we are using lock there must be valid data if no valid data it is nullptr
wp=s;
cout<<"weak count after intailisation:"<<wp.use_count()<<endl;
//cout<<"weak_ptr"<<*wp<<endl;// it is error because we cannot deference wp directly it is happend by lock()
if(auto p=wp.lock()) //as we creating another pointing to same memory loaction so count increases
cout<<"weak_ptr:"<<*p<<endl;//we can use either shared_ptr or auto for lock() 
else
cout<<"alredy destroyed"<<endl;
cout<<s.use_count()<<endl;
}
//generally for weak_ptr no ownership is given by shared_ptr but then can access and modify
