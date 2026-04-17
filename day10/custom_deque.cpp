#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class deque1
{
	int table_size=4;
	int block_size=4;
	int** block_table;
	int start_off,end_off,start_block,end_block,current_size;
	public:
	deque1()
	{
		block_table=new int*[table_size];
		int i;
		for(i=0;i<table_size;i++)
			block_table[i]=nullptr;
		start_block=end_block=table_size/2;//as discussed first we should insert at middle and then it is easy to insert front,back
		block_table[start_block]=new int[block_size];
		start_off=end_off=current_size=0;
	}
	void push_back(int x)
	{
		if(end_off==block_size)
		{
			if(end_block+1>=table_size)
				re_alloc();
			end_block++;
			block_table[end_block]=new int[block_size];
			end_off=0;
		}
		block_table[end_block][end_off++]=x;
		current_size++;
	}
	void push_front(int x)
	{
		if(start_off>0)
			start_off--;
		else
		{
			if(start_block - 1 < 0)
				re_alloc();
			start_block--;
			block_table[start_block]=new int[block_size];
			start_off=block_size-1;
		}
		block_table[start_block][start_off]=x;
		current_size++;
	}
	int operator [] (int index)
	{
		int total_off=start_off+index;
		int block=start_block+(total_off/block_size);
		int offset=total_off%block_size;
		return block_table[block][offset];
	}
	~deque1()
	{
		int i;
		for(i=0;i<table_size;i++)
			delete[] block_table[i];
		delete []block_table;
	}
	int size()
	{
		return current_size;
	}
	void re_alloc()
	{       cout<<"realloc is called"<<endl;
		int newsize=table_size*2;
		int old_start = start_block;
		int old_end   = end_block;
		int p_left,p_right;
		p_left= p_right=table_size/2;
		int**p,i,j,left,right;
		p=new int*[newsize]{nullptr};
		left=right=newsize/2;
		for(i=left-1,j=p_left-1;j>=0;i--,j--) 
			p[i]=block_table[j];
		for(i=right,j=p_right;j<table_size;i++,j++)
			p[i]=block_table[j];
		delete [] block_table;
		block_table=p;
		start_block = left;
		end_block = left + (old_end - old_start);
		table_size=newsize;
	}
};
int main()
{
	deque1 d;
	int i;
	for(i=0;i<15;i++)
		d.push_back(i+10);
//	for(i=0;i<8;i++)
//		d.push_back(i+20);
//	d.push_front(100);
//	cout<<d[2]<<endl;;
for(i=0;i<d.size();i++)
		cout<<d[i]<<" ";
	return 0;
}

