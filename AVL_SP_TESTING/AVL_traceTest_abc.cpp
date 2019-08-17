#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/time.h>
#include <iostream>
#include "jy_avl_lru.c"

//#include <stdio.h>
//#include <string.h>
//#include "hyperloglog.h"
//using namespace std;

const int PGAP = 1024*1024/4096; //mrc output step
const int MAXL = 1000000; //number of bins in  reuse time histogram
const int MAXH = 9997; //size of hashvalue table
const int domain = 256; //reuse time histogram compression factor
const int STEP = 10000; // sampling rate



LRU_Cache_t cache;



FILE *fin,*fout;
long long *rd = new long long[MAXL];
 long long t;
long long n=0;
long long m=0;
long long loc = rand()%(STEP*2-1)+1;
long long node_cnt=0;
long long node_max = 0;
long long tott=0;

// AVL



//memset (rd,0,sizeof(long long)*MAXL);
long long domain_value_to_index(long long value)
{
    long long loc = 0,step = 1;
    int index = 0;
    while (loc+step*domain<value) {
        loc += step*domain;
        step *= 2;
        index += domain;
    }
    while (loc<value) index++,loc += step;
    return index;
}

long long domain_index_to_value(long long index)
{
    long long value = 0,step = 1;
    while (index>domain) {
        value += step*domain;
        step *= 2;
        index -= domain;
    }
    while (index>0) {
        value += step;
        index--;
    }
    return value;
}




void solve(long long addr)
{

    n++;
    
    //t = find(addr,now);
    long long cur_rd = findItem(&cache, addr);

    if (cur_rd == COLDMISS) 
    {
        createItem(&cache, addr);
    }


    else
    {
        if(cur_rd > MAXL)
        {   
            cur_rd = MAXL - 1;
            
        }
        rd[cur_rd]++;
        //std::cout << cur_rd << "\n";
    }
    

    
}


int main()
{

    int M = 2;
    int N = MAXL + 100;
    int ii,j,r = 0;
    LRU_Cache_t cache;

    for(ii = 0; ii<M; ii++)
    {
        for(j=0;j<N;j++)
        {
        
            solve(j);    
        } 
        for(j=N - 1;j> -1;j--)
        {
            //std::cout << " 11111";
            solve(j);    
        }   
     
    }   
    //std::cout << i;

    for(ii = MAXL -10; ii< MAXL; ii++)
    {
        std::cout <<"rd "<<ii<< ","<<rd[ii]<<"\n";
    }
    return 0;
}
