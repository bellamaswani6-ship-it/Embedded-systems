#include<bits/stdc++.h>
using namespace std;
/*class deleter
{
    public:
    void operator()(FILE*file) const //as it is a file to avoid resource leak we had gone through custom deleter
                                      //when it is gone out of scope it will deallocate properly
    {
          if(file)
          {
              cout<<"file is closed"<<endl;
              fclose(file);
          }
    }
};*/
class deleter
{
    public:
    template<typename T>
    void operator() (T*p)const{
        cout<<"memory is deallocated"<<endl;
        delete[]p;
    }
};
int main()
{
    /*unique_ptr<FILE,deleter>fileptr(fopen("data","w"));
    if(fileptr)
    cout<<"file opened successfully"<<endl;*/
    unique_ptr<int[],deleter>p(new int[10]);
     cout<<"memory is allocated for 10 integers"<<endl;
}