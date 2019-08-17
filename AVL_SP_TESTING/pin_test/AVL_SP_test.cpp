#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/time.h>
#include <iostream>
#include "jy_avl_lru.H"


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
        cur_rd--;
        if(cur_rd > MAXL-1 )
        {   
            cur_rd = MAXL-1;
            
        }
        rd[cur_rd]++;
        //std::cout << cur_rd << "\n";
    }
    

    
}


int main(int argc, char const *argv[])
{

    int r = 5, s = 10;

    if(argc == 3)
    {
        r = atoi(argv[1]);
        s = atoi(argv[2]);
    }

    int i,j;
    for(j=0; j<s; j++)
    {
        for(i = 0; i<r; i++)
        {
            solve(i);
        }
        for(i = 0; i<r; i++)
        {
            solve(r-i-1);
        }
    }

    for(i = 0; i< r; i++)
    {
        std::cout << i << "," << rd[i] << "\n";
    }
    return 0;
}