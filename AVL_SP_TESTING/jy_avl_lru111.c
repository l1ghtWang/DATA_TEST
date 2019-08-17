//this is c file for avl_lru 

//left right rotation

/*
 	avl insertion and avl deletion



 	*/


//reuse distance start from 1 ex: a a, rd = 1

#include "jy_avl_lru.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//test debug
#include <assert.h>
int d = 0;

//-------------------LRU helper----------------------------------
//LRU distance finder
long long avlLD(Item_t* item);//done


/**************AVL helper Function*****************************/
 
//-----------avl lru helper---------------------------------
//return nil or the the nearest ancestor of x 
//such that x is in its right sub-tree
Item_t* avlAncestor(Item_t *item); //done

//-------------------------higher level avl-------------------------
Item_t* avlRemove(Item_t *item);
void avlLeftMostInsert(LRU_Cache_t* cache, Item_t *item); //done

//--------------------successor----------------------------------
Item_t* inorderSuccessor(Item_t *item);//done

//--------------------normal rotation helper---------------------------
int getBalanceFactor(Item_t *item); //done
Item_t* maxHeightChild(Item_t* item); //done
int totalChild(Item_t* item);//done
void rebalance(Item_t* item);//done
void rightRotate(Item_t *item);//done
void leftRotate(Item_t *item); //done

//---------------------deletion helper---------------------
void leftLeftRotate(Item_t *item);//done
void leftRightRotate(Item_t *item);//done
void rightLeftRotate(Item_t *item);//done
void rightRightRotate(Item_t *item);//done


/*********************avl helper end*****************************/



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
    	s = avlRemove(s);
    	// //if(d == 3) exit(-1);

    	avlLeftMostInsert(cache, s);
    	return rd;
    	
    }

    //reuse distance
    return COLDMISS;
}

void createItem(LRU_Cache_t* cache, long long ikey)
{
	Item_t* newItem = (Item_t*) malloc(sizeof(Item_t));
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




void access(LRU_Cache_t* cache, Hist_t* hist, long long ikey)
{
	cache -> totalIns++;

	long long rd = findItem(cache, ikey);

	if (rd == COLDMISS) {createItem(cache, ikey); }
	else{rd--;}

	addToHist(hist, rd);
}


//------------------------lru functions implementation end-------------------

/***************Histogram Section  Start*************************/

/***************Histogram Section**************************
 Functions below are independent from Cache eviction policy
 Mainly used for generate MRC based on cache model



 ********************************************************/


void histInit(Hist_t* hist, int begin, int end, int interval)
{
	//consider edge case later
	int slots = ((end - begin)/interval);
	hist -> first = begin;
	hist -> size = slots+2;
	hist -> interval = interval;
	hist -> rdHist = (long long*) malloc(sizeof(long long)*(slots+2));
	hist -> missRatio = (float *)malloc(sizeof(float)*(slots+2));
	int i;
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
			int index = ((ird - hist->first) / (hist->interval)) + 1;
			hist->rdHist[index]++;
		}else{
			hist->rdHist[0]++;
		}
	}
}

void solveMRC(Hist_t* hist, LRU_Cache_t* cache)
{
	int i;
	hist -> missRatio[hist->size-1] = (hist -> rdHist[hist->size-1])/((float)(cache -> totalIns));
	hist -> missRatio[hist->size-2] = hist -> missRatio[hist->size-1];
	for(i = hist->size-3; i >= 0; i--)
	{
		hist -> missRatio[i] = ((hist -> rdHist[i+1])/((float)(cache -> totalIns))) + hist->missRatio[i+1];
	}
}

/***************Histogram Section  END*************************/
/***************Histogram Section  END*************************/
/***************Histogram Section  END*************************/
/***************Histogram Section  END*************************/
/***************Histogram Section  END*************************/
/***************Histogram Section  END*************************/

/*
int main(int argc, char const *argv[])
{
	char buf[128];

	//open file for read key value
	FILE*       rfd = NULL;
	FILE*       wfd = NULL;
	char*   linePtr = NULL;
	ssize_t linelen = 0;

	LRU_Cache_t cache;
	Hist_t hist;

	//cache init
	cacheInit(&cache);
	histInit(&hist,atoi(argv[2]),atoi(argv[3]), atoi(argv[4]));

	//hist init

	if((rfd = fopen(argv[1],"r")) == NULL)
	{
		perror("open error for read");
		return -1; 
	}
	
	strcpy(buf, argv[1]);
	strcat(buf, "_lru.mrc");
	if((wfd = fopen(buf ,"w")) == NULL)
	{
		perror("open error for write");
		return -1; 
	}

	char *keyStr;
	long long key;
	
	while ( getline(&linePtr, &linelen, rfd) != -1)
	{

		keyStr = strtok(linePtr, " ");
		 keyStr = strtok(NULL, " ");
		 keyStr = strtok(NULL, " ");
		key = strtoul(keyStr, NULL, 16);
		//printf("%d\n",key );
		d++;
		if(d % 1000000 == 0)
		printf("%d\n",d );
		access(&cache, &hist, key);
		
	}


	solveMRC(&hist, &cache);
	int i;

	//printf("%d\n", cache.totalIns );
	 for(i = 0; i < hist.size; i++)
	 {
	 	printf("%d\n",hist.rdHist[i] );
	 }

	for(i = 0; i < hist.size-1; i++)
	{
		fprintf(wfd, "%d,%f\n", hist.first+i*(hist.interval), hist.missRatio[i]);
	}
	
	//loop for end of file
	//construct histogram
	//listCacheFree(&cache);
	histFree(&hist);
	free((void*)linePtr);
	fclose(wfd);
	fclose(rfd);
	return 0;
}

*/


//-----------------helper implemtation------------------------------

int getBalanceFactor(Item_t *item){
	int lh = item->left == NULL ? 0 : (item->left)->height;
	int rh = item->right == NULL ? 0 : (item->right)->height;

	return lh < rh ? (rh-lh) : (lh-rh);
}


Item_t* maxHeightChild(Item_t* item)  
{  
	int a = 0;
	int b = 0;
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

int totalChild(Item_t* item){
	int leftSize = (item->left == NULL) ? 0 : (item->left)->size;
	int rightSize = (item->right == NULL) ? 0 : (item->right)->size;

	return leftSize+rightSize;
}

void rightRotate(Item_t *item){
	
	assert(item->left != NULL);

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

//size??????
void leftRotate(Item_t *item){
	assert(item->right != NULL);
	//assert(getBalanceFactor(item) == 2);

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
		
	}
	else if(item->parent != NULL){
	
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

	//assert(item != NULL);
	if(item == NULL) return 0;


	//modified

	if(item->left == NULL)
	{
		return avlLD(avlAncestor(item)) + 1; 
	}else{

		return avlLD(avlAncestor(item)) + (item->left)->size + 1;
	}

	//iterative version:

}

void rebalance(Item_t* item)
{
	//identify the 3 pivot point
	//first is item;
	assert(item->left != NULL || item->right != NULL);
	Item_t* x = maxHeightChild(item);
	assert(x->left != NULL || x->right != NULL);
	Item_t* y = maxHeightChild(x);
//if(d==7)
//assert(item->right != NULL );
//printf("item: %d, getBalanceFactor: %d\n", item->addrKey, getBalanceFactor(item));
	//determine rotation pattern
	//x is not null!
	//y is not null!
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

//insert to leftmost
//maintain balance
void avlLeftMostInsert(LRU_Cache_t* cache, Item_t *item)
{
	Item_t *leftMost = cache->mostRecentItem;
	//item->parent = NULL;
	if(leftMost != item)
	{
		item->parent = leftMost;
		if(leftMost != NULL)
		leftMost->left = item;
	}
	
	item->left = NULL;
	item->right = NULL;
	cache->mostRecentItem = item;
	//update height and size of all parent.
	//all parent must be updated (logn)
	Item_t* maxChild;
	//printf("%ld\n",item->parent );
	
	//printf("in\n");

	while(item != NULL)
	{
	//	if (d % 10000 == 0)
	//printf("see avlinsert\n");
		maxChild = maxHeightChild(item);
		item->height = ((maxChild == NULL) ? 0 : maxChild->height)+1;
		item->size = totalChild(item)+1;
		//printf("avlinsert before bal, %ld\n", item);
		if(getBalanceFactor(item) == 2)
		{
			rebalance(item);
		//	break;
		}
		//printf("out%d\n", item->addrKey);
		item = item->parent;
	}
	
	
}

//rm one node from avl,
//return such node
//do not free this node
//maintain balance
Item_t* avlRemove(Item_t *item){

	assert(item != NULL);
	Item_t* parent;
	Item_t* succ;
	
	// parent = item->parent;

 //    if(item->left == NULL && item->right == NULL)
 //    {
 //    	if(parent != NULL)
 //    	{
	//     	if(parent->left == item) 
	//     		parent->left = NULL;
	//     	else					 
	//     		parent->right = NULL;
	//     }
 //    }
 //    else if(item->left == NULL)
	// {
	// 	if(parent != NULL)
	// 	{
	// 		if(parent->left == item) 
	//     		parent->left = item-> right;
	//     	else					 
	//     		parent->right = item-> right;	
	// 	}

	// 	(item->right)->parent = parent;

	// }else if(item->right == NULL)
	// {
	// 	if(parent != NULL)
	// 	{
	// 		if(parent->left == item) 
	//     		parent->left = item-> left;
	//     	else					 
	//     		parent->right = item-> left;	
	// 	}
		
	// 	(item->left)->parent = parent;

	// }else{

	// 	succ = item->right;
	// 	while(succ->left != NULL)
	// 	{
	// 		succ = succ->left;
	// 	}
		
	// }



	succ = inorderSuccessor(item);
	if(succ == NULL)
	{
		parent = item->parent;
		if(item->left != NULL)
		{	
			item -> left->parent = parent;
		}
		if(parent != NULL){
			parent->right = item->left;
		}	
		Item_t* maxChild;
		while(parent != NULL)
		{
		//	if (d % 10000 == 0)
		//	printf("see nosucc updata\n");
		//	printf("parent: %d\n",parent->addrKey );
			maxChild =maxHeightChild(parent);
			parent->height = ((maxChild == NULL) ? 0 : maxChild->height)+1;
			parent->size = totalChild(parent)+1;

			if(getBalanceFactor(parent) == 2)
			{	
		//		printf("item height with 2: %d\n", parent->addrKey );
				rebalance(parent);
				//break;
			}
			parent = parent->parent;
		}

		return item;

	}else{
		//assert(succ != NULL);
		Item_t* curr;
		curr = item;
		while(succ != NULL)
		{
			HASH_DELETE(hh,HashItem, curr);
			HASH_DELETE(hh,HashItem, succ);
		//	printf("hey\n");
			long long tempKey = curr->addrKey;
			curr->addrKey = succ->addrKey;
			succ->addrKey = tempKey;
			HASH_ADD(hh, HashItem, addrKey, sizeof(long long), curr);
			HASH_ADD(hh, HashItem, addrKey, sizeof(long long), succ);
			curr = succ;
			if(succ->left == NULL && succ->right == NULL)
				break;
			succ = inorderSuccessor(curr);
			
		}

		parent = curr->parent;
		if(curr->parent != NULL)
		{
			if(parent->left == curr)
				parent->left = NULL;
			else
				parent->right = NULL;
		}else{
			if(curr->left != NULL)
				curr->left->parent = NULL;
		}

		Item_t* maxChild;
		while(parent != NULL)
		{
		//	if (d % 10000 == 0)
		//	printf("see nosucc updata\n");
		//	printf("parent: %d\n",parent->addrKey );
			maxChild =maxHeightChild(parent);
			parent->height = ((maxChild == NULL) ? 0 : maxChild->height)+1;
			parent->size = totalChild(parent)+1;

			if(getBalanceFactor(parent) == 2)
			{	
		//		printf("item height with 2: %d\n", parent->addrKey );
				rebalance(parent);
				//break;
			}
			parent = parent->parent;
		}

		return curr;
	
	}
	
}
