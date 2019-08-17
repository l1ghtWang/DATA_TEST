//this is header file for  avl-lru
//the avl implementation must be wraped as internal function
//externally we should consider use same:
	//Item-look up -----this is from hash
	//if item exist in the hash->implies exist in the tree
	//once find item in the hash--> 
			//move item to the front of queue or left most of avl.
			//potential problem: 1. item deletion from location
								//  2. item insertion from left most posiyion
			//both operation required tree maintenece
			
			//the avl should be designed so that it is easy to insert at
			//left most possition, and also easy to delete given any node in the tree

//Todo:
	//utilized avl API
			//init
			//during insert (call insert left most)
				//the insertion can be done in o(1) if we maintain a pointer
				//otherwise traverse down from root
				//root should be track by avl structure
	

	//method
	//access(key)
		//check hash
		//	if yes, return node, caculate node distance, perform node delete
 		// perform left most insert. update histogram
		// if no, add to hash, update histogram, add to the tree
	//MRC construction

#ifndef JY_AVL_LRU_H
#define JY_AVL_LRU_H

#include "uthash.h"
#include <stdint.h>

#define COLDMISS -1

typedef struct Item_t {

	long long size;// size of the sub-tree rooted as x
	long long addrKey;
	int height;// height of the tree
	struct Item_t *left;
	struct Item_t *right;
	struct Item_t *parent;
	UT_hash_handle hh; /*make this structure hashable*/

} Item_t;

typedef struct LRU_Cache_t {

	long long totalKey;
	long long totalIns;
	//might not need these two pointer
	//Item_t *root; //might not needed
	Item_t *mostRecentItem; // this is need, left most element of avl

} LRU_Cache_t;

Item_t *HashItem = NULL;

typedef struct Hist_t {
	
	long long* rdHist; //contain first to last + coldmiss box
	int first;
	int size; 
	int interval;
	float* missRatio;

} Hist_t;

void cacheInit(LRU_Cache_t* cache);
void cacheFree(LRU_Cache_t* cache);
void createItem(LRU_Cache_t* cache, long long ikey);
//return the reuse distance of Item,
//iternally
//this function will handle
//hashfind
//avl deletion and insertion
//return get rd
long long findItem(LRU_Cache_t* cache, long long ikey);
//test only

void histInit(Hist_t *hist, int begin, int end, int interval);
void histFree(Hist_t* hist);
void addToHist(Hist_t* hist, long long ird);
void solveMRC(Hist_t* hist, LRU_Cache_t* cache);


void access(LRU_Cache_t* cache, Hist_t* hist, long long ikey);

void inOrder(Item_t *root);
#endif /*JY_AVL_LRU_H*/