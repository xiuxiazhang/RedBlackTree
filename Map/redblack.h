#include <stdlib.h>
#include <stdio.h>

#define ElemType void *
#define Black 1
#define Red 0
//#define ValueType int
struct RedBlackNode
{
    int color;
    ElemType key;
//    ValueType value; // for Map

    struct RedBlackNode * left;
    struct RedBlackNode * right;
    struct RedBlackNode * parent;
};

typedef struct 
{
    int keyword;
    int value;
}Pair;
typedef struct RedBlackNode * RedBlackPtr;
typedef struct RedBlackNode * RbTreePtr;
RedBlackPtr LeftRotate(RedBlackPtr T, RedBlackPtr x);
RedBlackPtr RightRotate(RedBlackPtr T, RedBlackPtr x);
//insert 
//RedBlackPtr RbInsert(RedBlackPtr T, RedBlackPtr  z);
RedBlackPtr RbInsertFix(RedBlackPtr T, RedBlackPtr z);
RedBlackPtr RbDelete(RedBlackPtr T, RedBlackPtr z);
RedBlackPtr TreeSuccessor(RedBlackPtr x);
RedBlackPtr TreeMinimum(RedBlackPtr x);
RedBlackPtr TreeMaxmum(RedBlackPtr x);
RbTreePtr RbDeleteFixup(RedBlackPtr T, RedBlackPtr x);
//int RbEqual(RbTreePtr dest, RedBlackNode source);
int RbCopy(RbTreePtr dest, RbTreePtr  source);

//RbTreePtr RbSearch(RbTreePtr T, ElemType  key);
RbTreePtr RbSearch(RbTreePtr T, ElemType  key, int (*cmp)(const void *, const void *));
//RbTreePtr DataInsert(RbTreePtr T, ElemType  key, int (*cmp)(const void *, const void *)) ; // insert <key,value> pair
RbTreePtr DataInsert(RbTreePtr T, ElemType  key, int (*cmp)(const void *, const void *),int (*DealDup)(const void *,const void *));  // insert <key,value> pair
//RbTreePtr MakeNode(ElemType key,ValueType value);
//RbTreePtr MapInsert(RbTreePtr T, ElemType  key, ValueType  value);  // insert <key,value> pair
RbTreePtr  MapDelete(RbTreePtr T, ElemType key);
//int TreeBFS(RbTreePtr T);
void DisplayMap(void * x);
int cmp_map(const void * x, const void *y);
RedBlackPtr RbInsert(RedBlackPtr T, RedBlackPtr  z, int (*cmp)(const void  *, const void *));
RbTreePtr MapInsert(RbTreePtr T, int keyword, int value); // int (*cmp)(const void *, const void *))  // insert <key,value> pair)
RbTreePtr MapErase(RbTreePtr T, int keyword);
Pair * MakePair(int keyword, int value);
RbTreePtr MakeNode(ElemType key);
