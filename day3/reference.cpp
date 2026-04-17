#include<bits/stdc++.h>
using namespace std;
int main()
{
	int x=10;
	int &rv=x;
        const int &v=x;
	int &y=transform(x);
	cout<<y<<endl;
	int&& k=5;
	int&& z=sum(k);
	cout<<z<<endl;
}
int& transform(int x)
{
	return x*x;
}
int sum(int x)
{
    return x+5;
}
