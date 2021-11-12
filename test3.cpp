#include <iostream>
#include <stdlib.h>
#include <queue> 
#include<iomanip>
using namespace std;//图的邻接表结构，六维世界 
struct node{
	int data;//本节点数字 
	struct node *next; //指向下一节点的指针 
};
void createNode(int n,struct node *p){//创造节点顺序表 
	for(int i=0;i<n;++i){
		 (*p).data=i+1; 
		 (*p).next=NULL;
		 p++;
	}
};
void createMap(struct node* p,int n,int m){//创建图 
	struct node* t,*h;//t指向p指向的map头部，后续移动t
	int a,b;
	h=p;
	for(int j=0;j<m;++j){
		cin>>a;//左端点 
		cin>>b;//右端点 
		struct node* newNode0=(struct node*)malloc(sizeof(struct node));//创造边左顶点新节点 
		newNode0->data=a;
		struct node* newNode1=(struct node*)malloc(sizeof(struct node));//创造边右顶点新节点 
		newNode1->data=b; 
		for(int i=0;i<n;++i){//找到输入的边两端，做两个边链表
			t=p; 
			if((*t).data==a){//找到一端 
				while((*t).next!=NULL){
					t=(*t).next;
				} 
				(*t).next=newNode1;
				(*newNode1).next=NULL;	
				t=p;
			}
			if((*t).data==b){//找到另一端 
				while((*t).next!=NULL){
					t=(*t).next;
				}
				(*t).next=newNode0;
				(*newNode0).next=NULL;	
			} 
			p++;
		} 
		p=h; //p指针回到头部 
	}
};
void search(struct node *p,int n){//广度遍历数组打印每个点不超过六个的比例 
	struct node* t,*pHead;//遍历指针
	int numCount=1;//每层个数,从顶点开始 
	int floorCount=0;//广度遍历层数 
	int sum=0;//层数<=6时个数 
	int last=0;//队列最后一个元素
	int head=0;//队列头元素 
	int llast=0;//最后一个入队的元素 
	
	int *visited=new int[n];//是否访问过的标志集合 
	for(int m=0;m<n;++m){
			visited[m]=0;
		}
	queue <int> q;//建立队列 
	pHead=p;//头指针位置不变 
	t=pHead;//将t指针移动到链表头部 
	for(int i=0;i<n;++i){//以每个顶点为首个顶点广度遍历 
		t=p;
		for(int m=0;m<n;++m){
			visited[m]=0;
		}
		numCount=1; 
		floorCount=0;
		sum=0;
		
		q.push((*t).data);//将顶点压入队列
		visited[(*t).data-1]=1;//修改入队标志
		last=(*t).data; 
		
		while(!q.empty()){//如果队列不为空 
			
			head=q.front();//返回现在队首元素，进行查找 
			q.pop();//出队 

			t=pHead;//从头部开始查找
			for(int j=0;j<n;++j){
				if((*t).data==head){
					while((*t).next!=NULL){
						t=(*t).next;
						
						if(visited[(*t).data-1]==0){//未入队 
							q.push((*t).data);//找到，入队 
							llast= (*t).data;
							++numCount;
							if((*t).next==NULL&&head==last){
								last=(*t).data;
								++floorCount;
								if(floorCount<=6){
									sum+=numCount;	
									numCount=0;
								}
							} 
							visited[(*t).data-1]=1;//修改入队标志
						}
						else {//已经入队 
							if((*t).next==NULL&&head==last){
								last=llast;
								++floorCount;
								if(floorCount<=6){
									sum+=numCount;	
									numCount=0;
								}
							}
						}
					}
					
					break; 	
				}
				++t;
			} 
		} 
		cout<<(*p).data<<": ";
		cout<<setprecision(2)<<setiosflags(ios::fixed)<<double(sum)/double(n)*100.00<<"%"<<endl;
		++p;
	} 
	 
};
void display(struct node *p,int n){
	struct node* t;
	for(int i=0;i<n;++i){
		t=p;
		cout<<(*t).data<<endl;
		while((*t).next!=NULL){
			t=(*t).next;
			cout<<"边表"<<endl; 
			cout<<(*t).data<<endl;
		}
		p++;
	}	
};
int main(){
	int n,m;
	cin>>n;
	cin>>m;
	struct node map[n];
	struct node *p=map;
	createNode(n,p);// 创建顶点顺序表 
	//display(p,n);//展示图 
	createMap(p,n,m);//创建边表 
	//display(p,n);//展示图 
	search(p,n);
	return 0;
}
