// C++ Program to demonstrate 
// static_cast char* to int*
#include <iostream>
using namespace std;

// Driver code
int main()
{
  int a = 10;
  char c = 'a';
  
  // Pass at compile time, 
  // may fail at run time
  int* q = (int*)&c;
  int p = static_cast<int>(c);
  return 0;
}
