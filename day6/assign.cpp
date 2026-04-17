#include<bits/stdc++.h>
using namespace std;
int ref_count=0;
class weak_p
{
	int x;
   public:
//int ref_count=0;
 weak_p(const shared_ptr<int>&s ){
	ref_count++;
}
shared_ptr<int>& lock(shared_ptr<int>&p){
	if(!p) return p;
	*p=100;
        ref_count++;
	//cout<<ref_count<<endl;
    //    ref_count--;     
	return p;
}
};
int main()
{
shared_ptr<int>s=make_shared<int>(10);
weak_p wp=s;
cout<<ref_count<<endl;
//wp.lock(s);
//shared_ptr<int>p=s;
//cout<<"address:"<<&wp<<endl;
cout<<ref_count<<" "<<*s<<endl;
if(shared_ptr<int>p=wp.lock(s))
{
	cout<<ref_count<<endl;
	ref_count--;		
}
cout<<ref_count<<endl;
}

