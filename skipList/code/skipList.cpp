/*skipList.cpp*/ 
#include "skipList.h"

template<class K, class E>
skipList<K,E>::skipList(K largeKey, int maxPairs)
{
   	cutOff = 0.5 * RAND_MAX;
   	maxLevel = (int) floor(logf((float) maxPairs) / logf(2)); //计算总层数 
   	levels = 0;  
   	Size = 0;
   	tailKey = largeKey;

   	pair<K,E> tailPair;
   	tailPair.first = tailKey;
   	headerNode = new skipNode<K,E> (tailPair, maxLevel + 1);
   	tailNode = new skipNode<K,E> (tailPair, 0);
   	last = new skipNode<K,E> *[maxLevel+1];

   	for (int i = 0; i <= maxLevel; i++)
       	headerNode->next[i] = tailNode;
}

template<class K, class E>
skipList<K,E>::~skipList()
{
   	skipNode<K,E> *nextNode;

   	// 通过0级指针删除所有结点 
   	while (headerNode != tailNode)
   	{
      	nextNode = headerNode->next[0];
      	delete headerNode;
      	headerNode = nextNode;
   	}
   	delete tailNode;

   	delete [] last;
}
template<class K, class E>
bool skipList<K,E>::initialise(long long* arraylist,int size)
{	
	extern int SHOW;
	skipNode<K,E>* newNode; 
	Size=size;
	if(size==0){
		return true;
	}
	// 按prob=0.5初始化为严格跳表 
	int* record=new int[size+2], *lastRecord = new int[size+2],* tmp; //记录上一次的结点情况 
	
	levels = (int) floor(logf((float) size) / logf(2));

	if(levels==-1){
		levels=0;
	}
	int k;
	for(int i=0;i<size;i++){
		for(int j=i+1;j<size;j++){
			if(arraylist[i]>arraylist[j]){
				k=arraylist[i];
				arraylist[i]=arraylist[j];
				arraylist[j]=k;
			}
		}
	}
	
	lastRecord[0]=(0 - 1);
	lastRecord[1]= (size - 1) +1;
	
	record[0]=lastRecord[0];
	record[1]=(lastRecord[0] +1 + lastRecord[1] -1)/2;   //取上一层的两个结点的中间结点 
	record[2]=lastRecord[1];
	/*记录分别为： 
		-1，size
		-1，...，(size-1)/2，...，size
		...
		-1,0,...,(size-1)/2,...size-1,size
	*/ 
	newNode = new skipNode<K,E>(pair<K,E>(arraylist[record[1]], arraylist[record[1]]), levels + 1);
	headerNode->next[levels] = newNode;
	newNode->next[levels] = tailNode;
	if(SHOW) {
		for (skipNode<K,E>* currentNode = headerNode->next[levels];
                currentNode != tailNode;
            	currentNode = currentNode->next[levels])
      		cout << currentNode->element.first << " ";
		cout << endl;
	}
	 

	tmp = record;
	record = lastRecord;
	lastRecord = tmp;

	for(int i = levels-1;i>=0;i--){

		int j = 0, k = 0;
		skipNode<K,E>* beforeNode=headerNode;
		while(lastRecord[j]!=size){				//等于size意味着到了终点 
			record[k++] = lastRecord[j];
			if (lastRecord[j] + 1 == lastRecord[j+1]) {
				beforeNode->next[i] = beforeNode->next[i+1];	//后继链接（这里的后继也是前驱在上一层的后继） 
				beforeNode = beforeNode->next[i+1];  		//更新beforeNode 
				j++;
				continue;
			}
			
			record[k++] = (lastRecord[j] + 1 + lastRecord[j+1] - 1)/2;
			newNode = new skipNode<K,E>(pair<K,E>(arraylist[record[k-1]], arraylist[record[k-1]]), i+1);
			
      		beforeNode->next[i] = newNode;				//前驱链接 
			newNode->next[i] = beforeNode->next[i+1];	//后继链接（这里的后继也是前驱在上一层的后继） 
			beforeNode = beforeNode->next[i+1];  		//更新beforeNode 
			j++;
		}
		record[k] = lastRecord[j]; //补上结尾（终点）的记录 
		//交换 
		tmp = record;
		record = lastRecord;
		lastRecord = tmp;


		if(SHOW) {
			for (skipNode<K,E>* currentNode = headerNode->next[i];
                    currentNode != tailNode;
            	    currentNode = currentNode->next[i])
      			cout << currentNode->element.first << " " ;
			cout << endl; 
		}
		
	}
	
    delete [] record;
	delete [] lastRecord; 
	return true; 
}
template<class K, class E>
bool skipList<K,E>::initialise2(long long* arraylist,int size)
{	
	extern int SHOW;
	skipNode<K,E>* newNode; 
	Size=size;
	if(size==0){
		return true;
	}
	// 按prob=0.5初始化为严格跳表 	
	levels = (int) floor(logf((float) size) / logf(2));

	if(levels==-1){
		levels=0;
	}
	int k;
	for(int i=0;i<size;i++){
		for(int j=i+1;j<size;j++){
			if(arraylist[i]>arraylist[j]){
				k=arraylist[i];
				arraylist[i]=arraylist[j];
				arraylist[j]=k;
			}
		}
	}
	int gap = 1;
	for(int i = levels;i>=0;i++){	
		int j = 0, k = 0;
		gap = pow(2,i)-1;
		skipNode<K,E>* beforeNode=headerNode;
		for(int j = 0;j<=size;j+=gap){				//等于size意味着到了终点 
			newNode = new skipNode<K,E>(pair<K,E>(arraylist[j], arraylist[j]), i);
			
      		beforeNode->next[i] = newNode;				//前驱链接 
			newNode->next[i] = beforeNode->next[i+1];	//后继链接（这里的后继也是前驱在上一层的后继） 
			beforeNode = beforeNode->next[i+1];  		//更新beforeNode 
		}
		if(SHOW) {
			for (skipNode<K,E>* currentNode = headerNode->next[i];
                    currentNode != tailNode;
            	    currentNode = currentNode->next[i])
      			cout << currentNode->element.first << " " ;
			cout << endl; 
		}
		
	}
	
	return true; 
}
template<class K, class E>
pair<const K,E>* skipList<K,E>::find(const K& theKey) const
{	

	extern int F_Cmp,E_Cmp,I_Cmp,Cmp;
	/* 找到则返回指向关键字为 theKey 的结点 ， 
 	   找不到则返回 NULL。*/

   	if (theKey >= tailKey)
      	return NULL;  // 超出范围

   	skipNode<K,E>* beforeNode = headerNode;
   	// 逐级遍历 
    for (int i = levels; i >= 0; i--)          
        while (beforeNode->next[i]->element.first < theKey){
        	beforeNode = beforeNode->next[i];
			F_Cmp++;
		}
        	
        	
    if (beforeNode->next[0]->element.first == theKey){
    	F_Cmp++;
    	return &beforeNode->next[0]->element;
	}
    	
	else 
		return NULL;  
}

template<class K, class E>
int skipList<K,E>::level() const
{	// 随机的生成一个层数，让各层的概率分别为0.5，0.25，0.125... 
   	int lev = 0;
   	while (rand() <= cutOff)
      	lev++;
   	return (lev <= maxLevel) ? lev : maxLevel;
}

template<class K, class E>
skipNode<K,E>* skipList<K,E>::search(const K& theKey) const
{	
 	/* 同 find，不过保留了所有的查询记录。 
 	last 中记录下该结点在所有层的前驱结点 。 
 	返回的结点满足 key>=theKey ，key-theKey最小*/ 
	extern int F_Cmp,E_Cmp,I_Cmp,Cmp;
   	skipNode<K,E>* beforeNode = headerNode;
   	for (int i = levels; i >= 0; i--)
   	{
      	while (beforeNode->next[i]->element.first < theKey) {//遍历 i 层 
      		Cmp++;
         	beforeNode = beforeNode->next[i];
		}				 
      	last[i] = beforeNode;  								//记录 i 层前驱结点 
   	}
   	return beforeNode->next[0];
}

template<class K, class E>
void skipList<K,E>::insert(const pair<const K, E>& thePair)
{	/* 插入结点，如果 theKey 存在，则返复写 */ 
	extern int F_Cmp,E_Cmp,I_Cmp,Cmp;
   	if (thePair.first >= tailKey) 
   	{ostringstream s;
    	s << "Key = " << thePair.first << " Must be < " << tailKey;
    	throw illegalParameterValue(s.str());
   	}  
   
   	skipNode<K,E>* theNode = search(thePair.first);
   	I_Cmp += Cmp;
   	Cmp = 0;
   	if (theNode->element.first == thePair.first)
   	{
      	theNode->element.second = thePair.second;
      	return;
   	}

   	// 不存在则新增结点。并且通过随机的形式，确定结点所在的最大层。 
   	int theLevel = level(); 
   	// 保证最多新增一层 
   	if (theLevel > levels)
   	{
      	theLevel = ++levels;
      	last[theLevel] = headerNode;
   	}	

   	skipNode<K,E>* newNode = new skipNode<K,E>(thePair, theLevel + 1);
   	for (int i = 0; i <= theLevel; i++)
   	{
      	newNode->next[i] = last[i]->next[i];
      	last[i]->next[i] = newNode;
   	}

   	Size++;
   	return;
}

template<class K, class E>
void skipList<K,E>::erase(const K& theKey)
{
	extern int F_Cmp,E_Cmp,I_Cmp,Cmp;
   	if (theKey >= tailKey) 
    	return;

   
   	skipNode<K,E>* theNode = search(theKey);
    E_Cmp += Cmp;
   	Cmp = 0;
   	if (theNode->element.first != theKey) 
      	return;

   	for (int i = 0; i <= levels &&
                   last[i]->next[i] == theNode; i++)
      	last[i]->next[i] = theNode->next[i];
   
   	// 更新层数 
   	while (levels > 0 && headerNode->next[levels] == tailNode)
      	levels--;
   	// 删除结点 
    delete theNode;
    // 更新大小 
    Size--;
}

template<class K, class E>
void skipList<K,E>::output(ostream& out) const
{	
   	for (skipNode<K,E>* currentNode = headerNode->next[0];
                       currentNode != tailNode;
                       currentNode = currentNode->next[0])
      	out << currentNode->element.first << " ";
}

template<class K, class E>
void skipList<K,E>::reset(int maxSize){							//重构跳表 

	long long* arraylist = new long long[maxSize];
	long long i = 0;
	for (skipNode<long long,long long>* currentNode = headerNode->next[0];
	                   currentNode != tailNode;
	                   currentNode = currentNode->next[0]){
			arraylist[i++] = currentNode->element.first;
	} 
	
	skipList<K,E>* theList = new skipList<K,E>(LLONG_MAX, maxSize);
	theList->initialise(arraylist,Size);
	this->last = theList->last;
	this->levels = theList->levels;
	this->maxLevel = theList->maxLevel;
	this->Size = theList->Size;
	this->headerNode = theList->headerNode; 
	this->tailKey = theList->tailKey;
	this->tailNode = theList->tailNode;
} 

