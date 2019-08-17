#include<stdio.h>
#include<stdint.h>
#include "MurmurHash3.cpp"
#include <iostream>
using namespace std;
int main()
{

  int seed = 998;
  long long ref1 = 0;
  uint32_t hash1;
  MurmurHash3_x86_32(&ref1, 8, seed, &hash1);





long long i = 0;
long long j =2;
long long a[10000];
for(; i < 10000; i++)
{
  a[i] = 0;
  }

i=0;
for(; i < 1000000; i++)
{
  
  MurmurHash3_x86_32(&j, 8, seed, &hash1);
  cout << hash1<<"\n";
  //cout << (hash1[1] % 10000)<<"\n";
  if(i>5000)
    j=i*123;
  else
    j=i;

}

// i=0;
// for(;i<10000; i++)
// {
//   cout << (hash1[1] % 10000)<<"\n";
// }

return 0;
}


