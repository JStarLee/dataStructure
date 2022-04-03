#include <iostream>
#include "skipList.h"
#include <fstream>
#include <cmath>
#include <ctime>
#include <string>
using namespace std;
//#define CHECK 0
//#define RESET 0
int SHOW = 0;
int CHECK = 0;
int RESET = 1;
int F_Cmp=0,E_Cmp=0,I_Cmp=0,Cmp=0; 

template <class K,class E>
long long xorSum(skipList<K,E>& skiplist){
	long long result = 0;
	skipNode<K,E> *theNode = skiplist.getHeaderNode();
	for (long long i = 0; i < skiplist.size(); i++) {
		theNode = theNode->next[0];
		result ^= theNode->element.first;
	} 
	return result;
}
int main(int argc,char *argv[]) {
	FILE *fp = NULL; /* 需要注意 */
	if(argc==3){
		freopen(argv[1],"r",stdin);
		freopen(argv[2] ,"w",stdout);
	}else if(argc==4){
		if(argv[3][1]=='S'){
			SHOW = 1;
			freopen(argv[1],"r",stdin);
			freopen(argv[2] ,"w",stdout);
		}else if(argv[3][1]=='C'&&argv[3][2]=='E'){
			CHECK = 1;
			RESET = 1;
			freopen(argv[1],"r",stdin);
			fp = fopen(argv[2], "w");

		}else if(argv[3][1]=='C'&&argv[3][2]!='E'){
			CHECK = 1;
			RESET = 0;
			freopen(argv[1],"r",stdin);
			fp = fopen(argv[2], "w");

		}
	}else{
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	}

	
	long long M, N;
	cin >> M >> N;
	long long theMaxSize = M + N;
	
	skipList<long long, long long> skiplist(LLONG_MAX, theMaxSize);
	long long resultOfXOR = 0, x, op, num;
	long long* arraylist = new long long[N];
	for (long long i = 0; i < N; i++) {
		cin >> x;
		arraylist[i] = x;
	} 
	skiplist.initialise(arraylist, N);

	
	for (long long i = 1; i <= M; i++) {
		cin >> op;

		switch (op) {
			case 1: {
				cin >> num;
				pair<const long long, long long>* ans = skiplist.find(num);
				
				if (ans != NULL)
					cout << "YES" << endl;
				else
					cout << "NO" << endl;
				break;
			}
				
			
			case 2: {
				cin >> num;
				const pair<const long long, long long> thePair(num, num);
				skiplist.insert(thePair);
				cout << xorSum(skiplist) << endl;
				break;
			}
				
			
			case 3: {
				cin >> num;
				skiplist.erase(num);
			
				cout << xorSum(skiplist) << endl;
				break;
			}
						
			case 4: {
				skipNode<long long,long long> *theNode = skiplist.getHeaderNode();
				long long min = theNode->next[0]->element.first;
				skiplist.erase(min);
				cout << min << endl;				
				break;
			}
			
			case 5: {
				skipNode<long long,long long> *theNode = skiplist.getHeaderNode();
				while(theNode->next[0]->element.first != skiplist.getTailKey()){
					theNode=theNode->next[0];
				}
				long long max = theNode->element.first;
				skiplist.erase(max);
				cout << max << endl;
				break;				
			} 		
		}
		if(RESET){
			if (i%(M/2) == 0) {
				skiplist.reset(M+N);
			}
		}
		
		
	}
	

	if(CHECK){
		fprintf(fp,"查找比较次数：%d\n删除比较次数：%d\n插入比较次数：%d",F_Cmp,E_Cmp,I_Cmp);
	}
	fclose(fp);

	return 0;

}

