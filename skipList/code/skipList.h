#ifndef skipList_
#define skipList_

#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include "skipNode.h"
#include "myExceptions.h"

using namespace std;

template<class K, class E>
class skipList 
{
   public:
	    skipList(K, int maxPairs = 10000); // 构造一个 progs 为 0.5 的跳表 
	    ~skipList();
			
	    bool empty() const {return Size == 0;}
	    int size() const {return Size;}
	    bool initialise(long long* arraylist,int size); // 初始化数组为严格跳表 
	    bool initialise2(long long* arraylist,int size); // 初始化数组为严格跳表 

	    pair<const K, E>* find(const K&) const;			// 按关键字查找 ，返回找到的元素的指针 
	      
	    void erase(const K&);							//删除 
	    void insert(const pair<const K, E>&);			//插入，若已经存在，则复写值。 
	    skipNode<K,E>* getHeaderNode(){ return headerNode; }  //返回头结点 
	    K getTailKey(){ return tailKey; }					  //返回最大关键字的值 
	    void output(ostream& out) const;
		void reset(int maxSize);							//重构跳表 

		void output2() const
		{	
			for(int i=0;i<=6;i++){
				cout << i << ": ";
				for (skipNode<long long,long long>* currentNode = headerNode->next[i];
		                       currentNode != tailNode;
		                       currentNode = currentNode->next[i])
			      	cout << currentNode->element.first <<"  ";
		    	cout <<endl<<endl;
			}
		}
   private:
      float cutOff;          // 作为随机生成层数的重要参数 
      int level() const;     
      int levels;            // 当前的存在的总层数 
      int Size;             // 元素总数 
      int maxLevel;          // 最大的层数 
      K tailKey;             // 使用大数作为尾结点标志 
      skipNode<K,E>* search(const K&) const;
                             
      skipNode<K,E>* headerNode;  
      skipNode<K,E>* tailNode;    
      skipNode<K,E>** last;      
};
template class
skipList<long long, long long>;
// 重载 <<
template <class K, class E>
ostream& operator<<(ostream& out, const skipList<K,E>& x)
   {x.output(out); return out;}

#endif
