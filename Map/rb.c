#include "redblack.h"
#include <stdio.h>
#include <stdlib.h>
struct RedBlackNode nilNode={Black,0,0,NULL, NULL,NULL,0};
// assume that right[x] != NilPtr[T] , and the parent of root is NilPtr[T]
//what you  need do is to keep the points of six  node (x,y, and their child,
//and x->parent.   six links
void DisplayMap(void * x)
{
    Pair *key=(Pair *)x;
    printf("(%d %d)\t",key->keyword,key->value);
}
RedBlackPtr LeftRotate(RedBlackPtr T, RedBlackPtr x)
{
    RedBlackPtr NilPtr =&nilNode;
    RedBlackPtr y=x->right; ///
    RedBlackPtr root;
    root=T;
    x->right=y->left;
   // if(y->left !=NilPtr)  // I think this is not need to determine if
    {
        y->left->parent=x; //change y->left  's parent value  
    }
    y->parent=x->parent; //
    if(x->parent==NilPtr) //x is root
    {
        root=y; // y as a root
    }
    else  //6 parent 
    {
        if (x== x->parent->left) // x is left child
        {
            x->parent->left=y;
        }
        else
        {
            x->parent->right=y;
        }
    }
    y->left=x;
    x->parent=y;
    return root;

}
//assume x-> left is not null. 
//need six links 
RedBlackPtr RightRotate(RedBlackPtr T, RedBlackPtr x)
{
    RedBlackPtr y=x->left;
    RedBlackPtr root;
    // x is y's left child
    x->left = y->right ;
    y->right->parent=x; 
    RedBlackPtr NilPtr =&nilNode;

    if  (x->parent==NilPtr)
        root=y;
    else
    {
        if(x==x->parent->left)
            x->parent->left=y;
        else
            x->parent->right=y;
    }
   
   y->right=x;
   y->parent=x->parent; 
   x->parent=y;
   return root;
}

//insert 
int cmp_map(const void * x, const void *y)
{
    const Pair  * xx=x;
    const Pair * yy=y;

    if(xx->keyword > yy->keyword)
        return 1; //greater
    else if (xx->keyword < yy->keyword)
        return -1; // less
    else
        return 0;//equal
}

RedBlackPtr RbInsert(RedBlackPtr T, RedBlackPtr  z, int (*cmp)(const void  *, const void *))
{
    RedBlackPtr y=&nilNode;
    RedBlackPtr x=T;
    RedBlackPtr NilPtr =&nilNode;
    RedBlackPtr root;
    root=T;
    while (x!=NilPtr)
    {
        y=x;  // 
//        if(z->key < x->key)
        if( (*cmp)(z->key,x->key) ==-1) // z less than x
        {
            x=x->left;  //
        }
        else if((*cmp) (z->key, x->key)==1)
       // else if (z->key > x->key)
        {
            x=x->right;
        }
        else //equal donot need to insert
        {
            printf("z is already in\n");
            return NilPtr;
        }
    }
    // y is x's parent , x is nill leaf 
    z->parent = y;
    if (y==NilPtr)  // x is root
    {
        root=z;
    }
    else if ((*cmp)(z->key, y->key)==-1)
//    else if (z->key  < y->key)
    {
        y->left = z;    
    }
    else
    {
        y->right= z;    
    }
    z->left=NilPtr;
    z->right=NilPtr;
    z->color=Red;  //  0 is red
    root=RbInsertFix(root, z); //
    return root;
}


RedBlackPtr RbInsertFix(RedBlackPtr T, RedBlackPtr z)
{
    RedBlackPtr  y;
    RedBlackPtr root;
    root=T;
    while(z->parent->color== Red) // z is  not root ,otherwise it should not have color
    {
        if (z->parent==z->parent->parent->left)  // z's parent is left child
        {
            y=z->parent->parent->right; // y is z's parent's brother, z's uncle
            if(y->color ==Red)
            {
                z->parent->color =Black;
                y->color=Black;
                z->parent->parent->color=Red;
                z=z->parent->parent;
            }
            else 
            {
                if (z==  z->parent->right)  
                {
                    z=z->parent; 
                    root=LeftRotate(root,z);
                }
                z->parent->color=Black; //this will exit while  loop
                z->parent->parent->color=Red;
                root=RightRotate(root,z->parent->parent);
            }
            
        }  /// the text book is not good on align
        else if(z->parent== z->parent->parent->right)//similar to left
        {
            y=z->parent->parent->left;
            if(y->color==Red)
            {
                z->parent->color=Black;
                y->color=Black;
                z->parent->parent->color=Red;
                z=z->parent->parent;
            }
            else 
            {if (z==  z->parent->left)  
                {
                z=z->parent; 
                root=RightRotate(root,z);
                }
                z->parent->color=Black; // this will exit while loop
                z->parent->parent->color=Red;
               root= LeftRotate(root,z->parent->parent);
            }
        }
    }
    root->color = Black;
    return root;
}

RedBlackPtr RbDelete(RedBlackPtr T, RedBlackPtr z)
{
    RedBlackPtr y,x;
    RedBlackPtr NilPtr =&nilNode;
    RedBlackPtr root;
    root=T;
    if(z->left== NilPtr  || z->right== NilPtr)
    {
        y=z;  // I need to delete
    }
    else
        y=TreeSuccessor(z);//???
    if(y->left!=  NilPtr)
    {
        x=y->left;  //y's child  
    }
    else x=y->right;  
    x->parent=y->parent;
    if(y->parent == NilPtr) // y is root
    {
        root=x;
    }
    else if  (y==y->parent->left)
    {
        y->parent->left =x;
    }
    else
        y->parent->right=x;

    if  (y!=z)
    {
        z->key= y->key;
    }
    if (y->color==Black)
        root=RbDeleteFixup(root,x);
    free(y); /// 
    return root;
}

// inorder travel
RedBlackPtr TreeSuccessor(RedBlackPtr x)
{
    RedBlackPtr y;
    RedBlackPtr NilPtr =&nilNode;
    if  (x->right!=NilPtr)
        return TreeMinimum(x->right);
    y=x->parent;
    while(y!=NilPtr  && x==y->right)
    {
        x=y;
        y=y->parent;
    }
    return y;
}

RedBlackPtr TreeMinimum(RedBlackPtr x)
{
    RedBlackPtr NilPtr =&nilNode;
    while( x->left  !=NilPtr)
        x=x->left;
    return x;
}
RedBlackPtr TreeMaxmum(RedBlackPtr x)
{
    RedBlackPtr NilPtr =&nilNode;
    while( x->right!=NilPtr)
        x=x->right;
    return x;
}
// Not totally understand
RbTreePtr RbDeleteFixup(RedBlackPtr T, RedBlackPtr x)
{
    RedBlackPtr w,p;

    RedBlackPtr root;
    root=T;
    while (x!=root && x->color ==Black)
    {
        if(x==x->parent->left)
        {
            w=x->parent->right;// x's brother
            if(w->color == Red)
            {
                w->color=Black;
                x->parent->color=Red;
                root=LeftRotate(root,x->parent);
                w=x->parent->right;
            }
            if(w->left->color==Black && w->right->color==Black)
            {
                w->color=Red;
                x=x->parent;
            }
            else 
            {
                if (w->right->color == Black)
                {
                    w->left->color = Black;
                    w->color=Red;
                    root=RightRotate(root,w);
                    w=x->parent->right;
                }
                w->color=x->parent->color;
                x->parent->color = Black;
                w->right->color =Black;
            }
        }  //right child
        else if(x==x->parent->right)
        {
            w=x->parent->left;// x's brother
            if(w->color == Red)
            {
                w->color=Black;
                p->parent->color=Red;
                root=LeftRotate(root,x->parent);
                w=x->parent->left;
            }
            else if(w->left->color==Black && w->right->color==Black)
            {
                w->color=Red;
                x=x->parent;
            }
            else 
            {
                if (w->left->color == Black)
                {
                    w->right->color = Black;
                    w->color=Red;
                    root=LeftRotate(root,w);
                    w=x->parent->left;
                }
                w->color=x->parent->color;
                x->parent->color = Black;
                w->right->color =Black;
                root=RightRotate(root,x->parent);
                x=root;
            }
        }
    }
    x->color = Black;
}
//nonrecursive
RbTreePtr RbSearch(RbTreePtr T, ElemType  key, int (*cmp)(const void *, const void *))
{
    RbTreePtr x;
    x=T;
    //while(x!=&nilNode && x->key != key)
    while(x!=&nilNode && (*cmp)(x->key, key)!=0)
    {
        //if(key < x->key )
        if((*cmp)(key , x->key )==-1)
            x=x->left;
        else
            x=x->right;
    }
    if(x!=&nilNode)
        DisplayMap(x->key);
       // printf("x->key %d\n",x->key);

    return x;
}

RbTreePtr DataInsert(RbTreePtr T, ElemType  key, int (*cmp)(const void *, const void *),int (*DealDup)(const void *,const void *))  // insert <key,value> pair
{
    // make a node 
    RbTreePtr y;
  //  ElemType key=kv.key;
    
    //if((y=RbSearch(T,key))==&nilNode) // a new node
    if((y=RbSearch(T,key,cmp))==&nilNode) // a new node
    {
        RbTreePtr x=MakeNode(key);
        //RbTreePtr x=MakeNode(key,value);
        T=RbInsert(T, x,cmp);
    }
    else  // already in
    {
       // y->count ++; // record the number in;
        //y->value = value;
        (*DealDup)(y->key,key);
        printf(" change key value  in the RB tree\n");
    }
    return T;
}
int DealDupMap(void *x,void *key)
{
    Pair *keykey=key;
    Pair *xx=x;
    xx->keyword = keykey->keyword;
    return 0;
    //xx->value=keykey->value;
}
RbTreePtr MapInsert(RbTreePtr T, int keyword, int value) // int (*cmp)(const void *, const void *))  // insert <key,value> pair)
{
    Pair *x=MakePair(keyword,value);
    DataInsert(T,x,(int (*)(const void *,const void *))&cmp_map,(int (*)(const void *,const void *))&DealDupMap);
}
//Erase by a key
RbTreePtr  DataErase(RbTreePtr T, ElemType key,int (*cmp)(const void *, const void *))  //
{
    RbTreePtr x;
    //if ((x=RbSearch(T,key))!=&nilNode)  // can find key
    if((x=RbSearch(T,key,cmp))!=&nilNode) // can find key
    {
           T=RbDelete(T,x);
    }
    else
    {
        printf("cannot find key\n");
    }
        return T;
}
RbTreePtr MapErase(RbTreePtr T, int keyword)
{
    Pair *x=MakePair(keyword,0); //value is arbitray
    DataErase(T,x,&cmp_map);
}
/*
int CheckKey(RbTreePtr T, ElemType key,int (*cmp)(const void *, const void *))  //
{
    RbTreePtr x;
    //if((x=RbSearch(T,key))!=&nilNode)
    if((x=RbSearch(T,key,cmp))!=&nilNode) // can find key
    {
        return 1;
    }
    else
        return 0;
}
*/
#if 0
int TreeNodes(RbTreePtr T)
{
    RbTreePtr x;
    int s;
    x=T;
    if(x == &nilNode)
        return 0;
    else if(x->left== &nilNode && x->right== &nilNode)
        return 1;
    else
    {
        return TreeNodes(x->left)+TreeNodes(x->right)+1;
    }

}
#endif

int index=0;
#if 0   //only for  being called once
int PreOrder(RbTreePtr T,int *array)
{
    RbTreePtr x;
    int i;
    int i1,i2;
    x=T;
    static int indexj=0;
    if(x!= &nilNode)
    {
        PreOrder(x->left,array);
        array[indexj] =x->key;
        indexj ++;
        PreOrder(x->right,array);
    }
    return 0;
}
#endif 
int PreOrderPrint(RbTreePtr T)
{
    RbTreePtr x;
    x=T;
    if(x!= &nilNode)
    {
        PreOrderPrint(x->left);
//        printf("%d\n",x->key);
    //    printf("%d %d\n",index++, x->key);
        DisplayMap(x->key);
      //  printf("
        PreOrderPrint(x->right);
    }
    else
        return 0;
}
/// index global
int PreOrderList(RbTreePtr T,ElemType * array)
{
    RbTreePtr x;
    x=T;
    if(x!= &nilNode)
    {
        PreOrderList(x->left,array);
//        printf("%d %d\n",index++, x->key);
       array[index] = x->key;
        index ++;
        PreOrderList(x->right,array);
    }
    else
        return 0;
}

int MapExtract(RbTreePtr T, ElemType *array)
{
    index=0;
    PreOrderList(T,array);
}


#if 0
//-------------------------------------------------------------//
//Map using Red Black Tree//
int MapInitialize()
{
    //an empty red black tree allocate a node ptr
    return T;
}




/// multiple set using red black tree
// increase a field named count to record whether x has appeared in
int MultiMapInitilize()
{

}

RbTreePtr MultiMapInsert(RbTreePtr T, ElemType key)
{
    RbTreePtr x;
    if (x=RbSeach(T,e)!=NilPtr) // has inserted before
    {
        x->count++;
    }
    else // insert a new node
    {
        RbTreeInsert(T, x);
    }
}


RbTreePtr MultiMapDelete(RbTreePtr T, ElemType key)
{
    RbTreePtr x,y;
   //make node x;
   y=RbSeach(T,key);
  if(y!=NilPtr && y->count >1) // has appeared more than once 
  {
      y->count --;
  }
  else
  {
     RbDelete(T,x);
  }
}
#endif
int RbCopy(RbTreePtr dest, RbTreePtr  source)
{
    dest->key = source->key;
  //  dest->value= source->value;
    dest->color= source->color;
    dest->left= source->left;
    dest->right= source->right;
    dest->parent= source->parent;
    return 0;
}
#if 0
int RbEqual(RbTreePtr dest, RedBlackNode source)
{
     if(dest->key == source.key && dest->color==source.color && dest->left== source.left &&  dest->right== source.right &&  dest->parent= source.parent)
         return 1;
     else
         return 0;

}
#endif
RbTreePtr RbInit()
{
    RedBlackPtr NilPtr =&nilNode;
    RbTreePtr x;
    x=(RbTreePtr )malloc(sizeof(struct RedBlackNode)); //
    x=NilPtr;
    //RbCopy(x,NilPtr);
    return x; 
}
RbTreePtr MakeNode(ElemType key)
{
    RedBlackPtr NilPtr =&nilNode;
    RbTreePtr x;
    x=(RbTreePtr )malloc(sizeof(struct RedBlackNode)); //
    RbCopy(x,NilPtr);
    x->key=key;
   // x->value=value;
    return x;
}

ElemType DataFind(RbTreePtr T, ElemType key,int (*cmp)(const void *,const void *))
{
    RbTreePtr x;
    x=T;
    //while(x!=&nilNode && x->key != key)
    while(x!=&nilNode && (*cmp)(x->key, key)!=0)
    {
        //if(key < x->key )
        if((*cmp)(key, x->key)==-1)
            x=x->left;
        else
            x=x->right;
    }
    if(x!=&nilNode)
    {
        return x->key;  /// need to 
       // printf("x->key %d\n",x->key);
    }
    return NULL;  //assume all keys are positive integers
}
int MapFind(RbTreePtr T, int keyword)
{
    Pair *x=MakePair (keyword, 0);
    Pair * key;
    key=(Pair *)DataFind(T,x,&cmp_map);
    if(key==NULL)
        printf("cannot find key\n");
    else
        return key->value;
    return -1;
}
Pair * MakePair(int keyword, int value)
{
    Pair *x=(Pair *)malloc(sizeof(Pair));
    x->keyword = keyword;
    x->value = value;
    return x;
}

int main()
{
    RbTreePtr T;
    RbTreePtr T2;
    T=RbInit();
    T2=RbInit();

#if 1
    T=MapInsert(T,1,4);
    T=MapInsert(T,2,2);
    T=MapInsert(T,1,9);
    T=MapInsert(T,3,4);
    T=MapInsert(T,5,15);
    T=MapInsert(T,3,20);
#endif    

    printf("xxxxx----------------------------------------------------------\n");
    TreeBFS(T);
    printf("xxxx----------------------------------------------------------\n");

    int  value=MapFind(T,5);
    printf("find %d\n",value);
  //  printf(("find value  %d\n",value);
#if 0
    T2=MapInsert(T2,1);
    T2=MapInsert(T2,2);
    T2=MapInsert(T2,1);
    T2=MapInsert(T2,3);

    printf("key %d\n",T->key);
    printf("color %d\n",T->color);
    printf("count %d\n", T->count);
    printf("key %d\n",T->left->key);
    printf("color %d\n",T->left->color);
    printf("count %d\n", T->left->count);
    printf("key %d\n",T->right->key);
    printf("color %d\n",T->right->color);
    printf("count %d\n", T->right->count);

    printf("test in map %d\n",InMap(T,2));
    printf("nodes in map %d\n",TreeNodes(T));
//    printf("%d\n",T->key);
    printf("----------------------------------------------------------\n");
    printf("key %d\n",T2->key);
    printf("color %d\n",T2->color);
    printf("count %d\n", T2->count);
    printf("key %d\n",T2->left->key);
    printf("color %d\n",T2->left->color);
    printf("count %d\n", T2->left->count);
    printf("key %d\n",T2->right->key);
    printf("color %d\n",T2->right->color);
    printf("count %d\n", T2->right->count);
    printf("----------------------------------------------------------\n");
    int array[6];
//    static indexj=0;
    PreOrder(T2,array);

    PreOrder(T,array);
    int i;
    for(i=0;i<6;i++)
        printf("%d\n",array[i]);
    PreOrderPrint(T2);
    index=0; 
    PreOrderPrint(T2);
    printf("xxxxx----------------------------------------------------------\n");
    TreeBFS(T);
    printf("xxxx----------------------------------------------------------\n");
   T= MapDelete(T,3);
//    T= RbDelete(T,y);
        
    printf("key %d\n",T->key);
    printf("color %d\n",T->color);
    printf("key %d\n",T->left->key);
    printf("color %d\n",T->left->color);
    printf("key %d\n",T->right->key);
    printf("color %d\n",T->right->color);
    printf("nodes in map %d\n",TreeNodes(T));
//    printf("%d\n",T->key);
#endif
    return 0;
}

