#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/time.h>
#include <iostream>
#include "jy_avl_lru.H"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//#include <stdio.h>
//#include <string.h>
//#include "hyperloglog.h"
//using namespace std;

const int PGAP = 1024*1024/4096; //mrc output step
const int MAXL = 100000; //number of bins in  reuse time histogram
const int MAXH = 9997; //size of hashvalue table
const int domain = 256; //reuse time histogram compression factor
const int STEP = 10000; // sampling rate
const int rdInterval = 1024;



LRU_Cache_t cache;



FILE *fin,*fout;
long long *rd = new long long[MAXL];
double *mrc = new double[MAXL];
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
    //if(n%10000 == 0)std::cout << n<<0 << "\n";
    long long cur_rd = findItem(&cache, addr);
    int index = 0;

    //if(n%10000 == 0)std::cout << n<<1 << "\n";
    if (cur_rd == COLDMISS) 
    {
        createItem(&cache, addr);
        rd[MAXL-1]++;
    }
    else
    {
        cur_rd--;
        index = cur_rd/rdInterval;
        if(index > MAXL-2 )
        {   
            index = MAXL-1;
            
        }
        rd[index]++;
        //std::cout << cur_rd << "\n";
    }
    

    
}

void solveMRC(long long *rd)
{
    int i;
    mrc[MAXL-1] = (rd[MAXL-1])/(double)n;
    mrc[MAXL-2] = mrc[MAXL-1];
    for(i = MAXL-3; i >= 0; i--)
    {
        mrc[i] = ((rd[i+1])/((double)n)) + mrc[i+1];
    }
}


int main(int argc, char const *argv[])
{

    /*
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

    */

    FILE*       rfd = NULL;
    char*   linePtr = NULL;
    size_t linelen = 0;
    cacheInit(&cache);

    if((rfd = fopen(argv[1],"r")) == NULL)
    {
        perror("open error for read");
        return -1; 
    }


    getline(&linePtr, &linelen, rfd);   
    int iii = 0;
    while ( getline(&linePtr, &linelen, rfd) != -1)
    {

        solve(strtoll(linePtr,NULL,10));   
        
      
        //iii++;
        //if(iii == 3000) break;
    }

    //solveMRC(rd);
    
    std::cout << "reuse_dist,counts";

    int i = 0;
    for(i = 0; i< MAXL; i++)
    {
        std::cout << (i)*rdInterval << "," << rd[i] << "\n";
    }
    

    free((void*)linePtr);
    fclose(rfd);

    return 0;
}