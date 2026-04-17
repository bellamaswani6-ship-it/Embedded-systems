#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<cstring>
using namespace std;
class File
{
    int fd;
    public:
    File()
    {
        fd=open("data",O_WRONLY|O_CREAT|O_TRUNC|0644);
        cout<<"file gets opened"<<endl;
    }
    ~File()
    {
        if(fd)
        {
        cout<<"file gets closed"<<endl;
        close(fd);
        }
    }
    void writedata(const char*data)
    {
        write(fd,data,strlen(data));
    }
};
int main()
{
    File f;
    f.writedata("hello i am aswani");
    File f2;
    f2.writedata("it is my second file");
}