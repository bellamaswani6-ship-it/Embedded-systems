#include<bits/stdc++.h>
using namespace std;
class led
{
unique_ptr<int>o1;
public:
led(int n):o1(make_unique<int>(n)){
  cout<<"pin"<<*o1<<"is initializesd"<<endl;
}
void show()
{
cout<<"pin value:"<<*o1<<endl;
}
};
int main()
{
led o1(12);
o1.show();
//led o2=o1;  error becoz exclusive ownership
led o2=move(o1);
o2.show();
}

