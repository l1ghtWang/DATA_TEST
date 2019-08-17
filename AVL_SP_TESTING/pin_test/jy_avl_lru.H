//this is c file for avl_lru 

//left right rotation

/*
 	avl insertion and avl deletion



 	*/


//reuse distance start from 1 ex: a a, rd = 1

//#include "jy_avl_lru_2.H"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "uthash.h"

//test debug
#include <assert.h>
#define COLDMISS -1



typedef struct Item_t {

	long long size;// size of the sub-tree rooted as x
	long long addrKey;
	long long height;// height of the tree
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

long long avlLD(Item_t* item);//done
Item_t* avlAncestor(Item_t *item); //done

//-------------------------higher level avl-------------------------
Item_t* avlRemove(LRU_Cache_t* cache, Item_t *item);
void avlLeftMostInsert(LRU_Cache_t* cache, Item_t *item); //done

//--------------------successor----------------------------------
Item_t* inorderSuccessor(Item_t *item);//done

//--------------------normal rotation helper---------------------------
long long getBalanceFactor(Item_t *item); //done
Item_t* maxHeightChild(Item_t* item); //done
long long totalChild(Item_t* item);//done
void rebalance(Item_t* item);//done
void rightRotate(Item_t *item);//done
void leftRotate(Item_t *item); //done
void updateHeight(Item_t * item);

//---------------------deletion helper---------------------
void leftLeftRotate(Item_t *item);//done
void leftRightRotate(Item_t *item);//done
void rightLeftRotate(Item_t *item);//done
void rightRightRotate(Item_t *item);//done
void updateHeightAndSize(Item_t* item);//done


//-----------------------lru function implementation--------------------

void cacheInit (LRU_Cache_t* cache)
{
	cache -> totalKey = 0;
	cache -> totalIns = 0;
	cache -> mostRecentItem = NULL;
}
//this will return null if not find
long long findItem(LRU_Cache_t* cache, long long ikey)
{
    Item_t *s;
    long long rd;
    HASH_FIND(hh, HashItem, &ikey, sizeof(long long), s);
  
    if(s != NULL)
    {
    	
    	rd = avlLD(s);



    	if(rd != 1)
    	{
    		//printf("rd = = =%d\n",rd );
	    	s = avlRemove(cache, s);
    		// //if(d == 3) exit(-1);

    		avlLeftMostInsert(cache, s);
    	}
    	return rd;
    	
    }

    //reuse distance
    return COLDMISS;
}

void createItem(LRU_Cache_t* cache, long long ikey)
{
	Item_t* newItem = (Item_t*)malloc(sizeof(Item_t));
	newItem->size = 1;
	newItem->addrKey = ikey;
	newItem->height = 1;
	newItem->left = NULL;
	newItem->right = NULL;
	newItem->parent = NULL;
	
	//cache->mostRecentItem = newItem;
	cache->totalKey++;

	avlLeftMostInsert(cache,newItem);

	HASH_ADD(hh, HashItem, addrKey, sizeof(long long), newItem);
	//cache->mostRecentItem = newItem;
}


/*

void access(LRU_Cache_t* cache, long long addr)
{
	cache -> totalIns++;

	long long rd = findItem(cache, addr);

	if (rd == COLDMISS) 
		createItem(cache, addr); 
	else
		rd--;

	addToHist(hist, rd);
}
*/

//------------------------lru functions implementation end-------------------

/***************Histogram Section  Start*************************/

/***************Histogram Section**************************
 Functions below are independent from Cache eviction policy
 Mainly used for generate MRC based on cache model



 ********************************************************/

/*
void histInit(Hist_t* hist, long long begin, long long end, long long interval)
{
	//consider edge case later
	long long slots = ((end - begin)/interval);
	hist -> first = begin;
	hist -> size = slots+2;
	hist -> interval = interval;
	hist -> rdHist = malloc(sizeof(long long)*(slots+2));
	hist -> missRatio = malloc(sizeof(float)*(slots+2));
	long long i;
	for(i = 0; i < slots+2; i++)
	{
		hist -> rdHist[i] = 0;
	}
}



void histFree(Hist_t* hist)
{
	free((void*)hist->rdHist);
	free((void*)hist->missRatio);
}


void addToHist(Hist_t* hist, long long ird)
{
	if(ird == COLDMISS || ird > (((hist->size)-2)*(hist->interval)+(hist->first)))
	{
		hist -> rdHist[hist->size-1]++; //cold miss bin++
	}else{
		if(ird - hist->first >= 0)
		{
			long long index = ((ird - hist->first) / (hist->interval)) + 1;
			hist->rdHist[index]++;
		}else{
			hist->rdHist[0]++;
		}
	}
}

void solveMRC(Hist_t* hist, LRU_Cache_t* cache)
{
	long long i;
	hist -> missRatio[hist->size-1] = (hist -> rdHist[hist->size-1])/((float)(cache -> totalIns));
	hist -> missRatio[hist->size-2] = hist -> missRatio[hist->size-1];
	for(i = hist->size-3; i >= 0; i--)
	{
		hist -> missRatio[i] = ((hist -> rdHist[i+1])/((float)(cache -> totalIns))) + hist->missRatio[i+1];
	}
}

*/

/***************Histogram Section  END*************************/
/***************Histogram Section  END*************************/
/***************Histogram Section  END*************************/
/***************Histogram Section  END*************************/
/***************Histogram Section  END*************************/
/***************Histogram Section  END*************************/


//-----------------helper implemtation------------------------------

long long getBalanceFactor(Item_t *item){
	long long lh = item->left == NULL ? 0 : (item->left)->height;
	long long rh = item->right == NULL ? 0 : (item->right)->height;

	return lh < rh ? (rh-lh) : (lh-rh);
}


Item_t* maxHeightChild(Item_t* item)  
{  
	long long a = 0;
	long long b = 0;
	if(item->left != NULL)
	{
		a = (item->left)->height;
	}
	if(item->right != NULL)
	{
		b = (item->right)->height;
	}
    return (a > b)? item->left : item->right;  
}  

long long totalChild(Item_t* item){
	long long leftSize = (item->left == NULL) ? 0 : (item->left)->size;
	long long rightSize = (item->right == NULL) ? 0 : (item->right)->size;

	return leftSize+rightSize;
}

void rightRotate(Item_t *item){
	

	Item_t* parent = item->parent;
	Item_t* leftChild = item->left;
	//Item_t* rightSub = item->right;
	Item_t* childRightSub = leftChild->right;

	if(parent != NULL)
	{
		if(parent->right == item)
		{
			parent->right = leftChild;
		}else{
			parent->left = leftChild;
		}
	}	
	item->parent = leftChild;

	if(childRightSub != NULL)
	{
		childRightSub->parent = item;
	}
	
		leftChild->parent = parent;
		leftChild->right = item;
	
	
		item->left = childRightSub;
		
	//size and height change
	Item_t *maxChild;
	maxChild = maxHeightChild(item);
	item->height = ((maxChild == NULL) ? 0 : maxChild->height)+1;
	item->size = totalChild(item)+1;

	maxChild = maxHeightChild(leftChild);
	leftChild->height = ((maxChild == NULL) ? 0 : maxChild->height)+1;
	leftChild->size = totalChild(leftChild)+1;


}



void leftRotate(Item_t *item){
	
	Item_t* parent = item->parent;
	Item_t* rightChild = item->right;
	//Item_t* leftSub = item->left;
	Item_t* childLeftSub = rightChild->left;


	if(parent != NULL)
	{
		if(parent->right == item)
		{
			parent->right = rightChild;
		}else{
			parent->left = rightChild;
		}
		
	}	

	item->parent = rightChild;

	if(childLeftSub != NULL)
	{
		childLeftSub->parent = item;
	}
	
		rightChild->parent = parent;
		rightChild->left = item;
	
	
		item->right = childLeftSub;

	Item_t *maxChild;
	maxChild = maxHeightChild(item);
	item->height =  ((maxChild == NULL) ? 0 : maxChild->height)+1;
	item->size = totalChild(item)+1;

	maxChild = maxHeightChild(rightChild);
	rightChild->height = ((maxChild == NULL) ? 0 : maxChild->height)+1;
	rightChild->size = totalChild(rightChild)+1;

	//maxChild = maxHeightChild(parent);
	//assert(parent->height == ((maxChild == NULL) ? 0 : maxChild->height)+1);
}


void leftLeftRotate(Item_t *item){
	assert(item != NULL);
	rightRotate(item);
}

void leftRightRotate(Item_t *item){
	assert(item != NULL && item->left != NULL);
	leftRotate(item->left);
	rightRotate(item);
}

void rightLeftRotate(Item_t *item){
	assert(item != NULL && item->right != NULL);
	rightRotate(item->right);
	leftRotate(item);
}

void rightRightRotate(Item_t *item){
	assert(item != NULL);
	leftRotate(item);
}


//***********not yet tested--------------------//
////
///
//
//return nil or the the nearest ancestor of x 
//such that x is in its right sub-tree
Item_t* avlAncestor(Item_t *item)
{
	Item_t* ancestor = NULL;
	Item_t* curr = item;
	Item_t* parent = item->parent;
	while(parent != NULL)
	{
		//if(parent->right != NULL)
		if((parent->right) == curr)
		{
			ancestor = parent;
			break;
		}
		curr = parent;
		parent = curr->parent;
	}

	return ancestor;
}


Item_t* inorderSuccessor(Item_t *item){

	Item_t* curr = NULL;

	if(item->right != NULL)
	{	
		curr = item->right;
		while(curr->left != NULL)
		{
			curr = curr->left;
		}
	}else if(item->parent != NULL){
		curr = item->parent;
		while(curr != NULL && item == curr->right)
		{
			item = curr;
			curr = curr->parent;
		}
	
	}
	return curr;

}



long long avlLD(Item_t* item){

	long long rd = 0;

	while(item != NULL)
	{
		if(item->left != NULL)
			rd += item->left->size;
		rd += 1; 

		item = avlAncestor(item);
	}

	return rd;

}

void rebalance(Item_t* item)
{

	Item_t* x = maxHeightChild(item);

	Item_t* y = maxHeightChild(x);

	if(item->left == x)
	{
		//leftxxxrotate
		if(x->left == y)
		{
			//leftleft case
			//printf("leftrotate: %d\n",item->addrKey );
			leftLeftRotate(item);
			
		}else{
			//leftright case
			//printf("leftRightrotate: %d\n",item->addrKey );
			leftRightRotate(item);
		}
	}else{
		if(x->left == y)
		{
			//rightleft case
			//printf("rightleftrotate: %d\n",item->addrKey );
			rightLeftRotate(item);
		}else{
			//rightright case
			//printf("rightrotate: %d\n",item->addrKey );
			rightRightRotate(item);
		}
	}



}

void updateHeightAndSize(Item_t* rbItem)
{
	Item_t* maxChild;
	while(rbItem != NULL)
	{
		maxChild = maxHeightChild(rbItem);
		rbItem->height = ((maxChild == NULL) ? 0 : maxChild->height)+1;
		rbItem->size = totalChild(rbItem)+1;

		if(getBalanceFactor(rbItem) == 2)
			rebalance(rbItem);
		
		rbItem = rbItem->parent;
	}
}

//insert to leftmost
//maintain balance
void avlLeftMostInsert(LRU_Cache_t* cache, Item_t *item)
{	

	Item_t *leftMost = cache->mostRecentItem;


	item->parent = leftMost;
	if(leftMost != NULL)
		leftMost->left = item;

	
	item->left = NULL;
	item->right = NULL;
	cache->mostRecentItem = item;
	//update height and size of all parent.
	//all parent must be updated (logn)
	
	updateHeightAndSize(item);
	
	
}

//rm one node from avl,
//return such node
//do not free this node
//maintain balance
Item_t* avlRemove(LRU_Cache_t* cache, Item_t *item)
{

	//assert(item != NULL);
	Item_t* rbItem;
	Item_t* succ;

	succ = inorderSuccessor(item);


	if (succ != NULL)//curr node have right sub tree or right parent
	{
		
		if(item->right != NULL)
		{
			if(succ->parent->left == succ)
			{
				succ->parent->left = succ->right;
				if(succ->right != NULL)
					succ->right->parent = succ->parent;

				succ->right = item->right;
				item->right->parent = succ;
			}

			rbItem = succ->parent;

			
			succ->parent = item->parent;
			succ->left = item->left;	
			if(item->left != NULL)
				item->left->parent = succ;
			if(item->parent != NULL)
			{
				if(item->parent->left == item)
					item->parent->left = succ;
				else
					item->parent->right = succ;
			}

		}else //succ is its parent
		{
			if(item->parent->left == item)
				item->parent->left = item->left;
			else
				item->parent->right = item->left;
			

			if(item->left != NULL)
				item->left->parent = item->parent;
			rbItem = item->parent;
		}

	}else//curr node does not have any successor
	{

		if(item->parent != NULL)
			item->parent->right = item->left;
		if(item->left != NULL)
			item->left->parent = item->parent;

		rbItem = item->parent;
	}


	if(item == cache->mostRecentItem)
		cache->mostRecentItem = succ;

	item->parent = NULL;
	item->left = NULL;
	item->right = NULL;

	updateHeightAndSize(rbItem);

	
	return item;
}

	void updateHeight(Item_t * item)
	{

		Item_t* maxChild;
		Item_t *curr = item;
		while(curr != NULL)
		{
	
			maxChild =maxHeightChild(curr);
			curr->height = ((maxChild == NULL) ? 0 : maxChild->height)+1;
			curr->size = totalChild(curr)+1;

			//printf("here 1111\n");
			if(getBalanceFactor(curr) == 2)
			{	
		//		printf("item height with 2: %d\n", parent->addrKey );
				rebalance(curr);
				//break;
			}
		//	printf("heree1111111\n");
			curr = curr->parent;
		}
	}
	

