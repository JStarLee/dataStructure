#ifndef skipNode_
#define skipNode_
#include<utility>
using namespace std;
template <class K, class E>
struct skipNode 
{
   pair<const K, E> element;
   skipNode<K,E> **next;   

   skipNode(const pair<const K, E>& thePair, int size)
            :element(thePair){next = new skipNode<K,E>* [size];}
};

#endif
