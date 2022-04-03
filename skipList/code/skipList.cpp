/*skipList.cpp*/ 
#include "skipList.h"

template<class K, class E>
skipList<K,E>::skipList(K largeKey, int maxPairs)
{
   	cutOff = 0.5 * RAND_MAX;
   	maxLevel = (int) floor(logf((float) maxPairs) / logf(2)); //�����ܲ��� 
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

   	// ͨ��0��ָ��ɾ�����н�� 
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
	// ��prob=0.5��ʼ��Ϊ�ϸ����� 
	int* record=new int[size+2], *lastRecord = new int[size+2],* tmp; //��¼��һ�εĽ����� 
	
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
	record[1]=(lastRecord[0] +1 + lastRecord[1] -1)/2;   //ȡ��һ������������м��� 
	record[2]=lastRecord[1];
	/*��¼�ֱ�Ϊ�� 
		-1��size
		-1��...��(size-1)/2��...��size
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
		while(lastRecord[j]!=size){				//����size��ζ�ŵ����յ� 
			record[k++] = lastRecord[j];
			if (lastRecord[j] + 1 == lastRecord[j+1]) {
				beforeNode->next[i] = beforeNode->next[i+1];	//������ӣ�����ĺ��Ҳ��ǰ������һ��ĺ�̣� 
				beforeNode = beforeNode->next[i+1];  		//����beforeNode 
				j++;
				continue;
			}
			
			record[k++] = (lastRecord[j] + 1 + lastRecord[j+1] - 1)/2;
			newNode = new skipNode<K,E>(pair<K,E>(arraylist[record[k-1]], arraylist[record[k-1]]), i+1);
			
      		beforeNode->next[i] = newNode;				//ǰ������ 
			newNode->next[i] = beforeNode->next[i+1];	//������ӣ�����ĺ��Ҳ��ǰ������һ��ĺ�̣� 
			beforeNode = beforeNode->next[i+1];  		//����beforeNode 
			j++;
		}
		record[k] = lastRecord[j]; //���Ͻ�β���յ㣩�ļ�¼ 
		//���� 
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
	// ��prob=0.5��ʼ��Ϊ�ϸ����� 	
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
		for(int j = 0;j<=size;j+=gap){				//����size��ζ�ŵ����յ� 
			newNode = new skipNode<K,E>(pair<K,E>(arraylist[j], arraylist[j]), i);
			
      		beforeNode->next[i] = newNode;				//ǰ������ 
			newNode->next[i] = beforeNode->next[i+1];	//������ӣ�����ĺ��Ҳ��ǰ������һ��ĺ�̣� 
			beforeNode = beforeNode->next[i+1];  		//����beforeNode 
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
	/* �ҵ��򷵻�ָ��ؼ���Ϊ theKey �Ľ�� �� 
 	   �Ҳ����򷵻� NULL��*/

   	if (theKey >= tailKey)
      	return NULL;  // ������Χ

   	skipNode<K,E>* beforeNode = headerNode;
   	// �𼶱��� 
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
{	// ���������һ���������ø���ĸ��ʷֱ�Ϊ0.5��0.25��0.125... 
   	int lev = 0;
   	while (rand() <= cutOff)
      	lev++;
   	return (lev <= maxLevel) ? lev : maxLevel;
}

template<class K, class E>
skipNode<K,E>* skipList<K,E>::search(const K& theKey) const
{	
 	/* ͬ find���������������еĲ�ѯ��¼�� 
 	last �м�¼�¸ý�������в��ǰ����� �� 
 	���صĽ������ key>=theKey ��key-theKey��С*/ 
	extern int F_Cmp,E_Cmp,I_Cmp,Cmp;
   	skipNode<K,E>* beforeNode = headerNode;
   	for (int i = levels; i >= 0; i--)
   	{
      	while (beforeNode->next[i]->element.first < theKey) {//���� i �� 
      		Cmp++;
         	beforeNode = beforeNode->next[i];
		}				 
      	last[i] = beforeNode;  								//��¼ i ��ǰ����� 
   	}
   	return beforeNode->next[0];
}

template<class K, class E>
void skipList<K,E>::insert(const pair<const K, E>& thePair)
{	/* �����㣬��� theKey ���ڣ��򷵸�д */ 
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

   	// ��������������㡣����ͨ���������ʽ��ȷ��������ڵ����㡣 
   	int theLevel = level(); 
   	// ��֤�������һ�� 
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
   
   	// ���²��� 
   	while (levels > 0 && headerNode->next[levels] == tailNode)
      	levels--;
   	// ɾ����� 
    delete theNode;
    // ���´�С 
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
void skipList<K,E>::reset(int maxSize){							//�ع����� 

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

