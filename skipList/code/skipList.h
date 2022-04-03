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
	    skipList(K, int maxPairs = 10000); // ����һ�� progs Ϊ 0.5 ������ 
	    ~skipList();
			
	    bool empty() const {return Size == 0;}
	    int size() const {return Size;}
	    bool initialise(long long* arraylist,int size); // ��ʼ������Ϊ�ϸ����� 
	    bool initialise2(long long* arraylist,int size); // ��ʼ������Ϊ�ϸ����� 

	    pair<const K, E>* find(const K&) const;			// ���ؼ��ֲ��� �������ҵ���Ԫ�ص�ָ�� 
	      
	    void erase(const K&);							//ɾ�� 
	    void insert(const pair<const K, E>&);			//���룬���Ѿ����ڣ���дֵ�� 
	    skipNode<K,E>* getHeaderNode(){ return headerNode; }  //����ͷ��� 
	    K getTailKey(){ return tailKey; }					  //�������ؼ��ֵ�ֵ 
	    void output(ostream& out) const;
		void reset(int maxSize);							//�ع����� 

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
      float cutOff;          // ��Ϊ������ɲ�������Ҫ���� 
      int level() const;     
      int levels;            // ��ǰ�Ĵ��ڵ��ܲ��� 
      int Size;             // Ԫ������ 
      int maxLevel;          // ���Ĳ��� 
      K tailKey;             // ʹ�ô�����Ϊβ����־ 
      skipNode<K,E>* search(const K&) const;
                             
      skipNode<K,E>* headerNode;  
      skipNode<K,E>* tailNode;    
      skipNode<K,E>** last;      
};
template class
skipList<long long, long long>;
// ���� <<
template <class K, class E>
ostream& operator<<(ostream& out, const skipList<K,E>& x)
   {x.output(out); return out;}

#endif
