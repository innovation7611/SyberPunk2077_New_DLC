#include <iostream>
#include <stdlib.h>
#include <queue> 
#include<iomanip>
using namespace std;//ͼ���ڽӱ�ṹ����ά���� 
struct node{
	int data;//���ڵ����� 
	struct node *next; //ָ����һ�ڵ��ָ�� 
};
void createNode(int n,struct node *p){//����ڵ�˳��� 
	for(int i=0;i<n;++i){
		 (*p).data=i+1; 
		 (*p).next=NULL;
		 p++;
	}
};
void createMap(struct node* p,int n,int m){//����ͼ 
	struct node* t,*h;//tָ��pָ���mapͷ���������ƶ�t
	int a,b;
	h=p;
	for(int j=0;j<m;++j){
		cin>>a;//��˵� 
		cin>>b;//�Ҷ˵� 
		struct node* newNode0=(struct node*)malloc(sizeof(struct node));//������󶥵��½ڵ� 
		newNode0->data=a;
		struct node* newNode1=(struct node*)malloc(sizeof(struct node));//������Ҷ����½ڵ� 
		newNode1->data=b; 
		for(int i=0;i<n;++i){//�ҵ�����ı����ˣ�������������
			t=p; 
			if((*t).data==a){//�ҵ�һ�� 
				while((*t).next!=NULL){
					t=(*t).next;
				} 
				(*t).next=newNode1;
				(*newNode1).next=NULL;	
				t=p;
			}
			if((*t).data==b){//�ҵ���һ�� 
				while((*t).next!=NULL){
					t=(*t).next;
				}
				(*t).next=newNode0;
				(*newNode0).next=NULL;	
			} 
			p++;
		} 
		p=h; //pָ��ص�ͷ�� 
	}
};
void search(struct node *p,int n){//��ȱ��������ӡÿ���㲻���������ı��� 
	struct node* t,*pHead;//����ָ��
	int numCount=1;//ÿ�����,�Ӷ��㿪ʼ 
	int floorCount=0;//��ȱ������� 
	int sum=0;//����<=6ʱ���� 
	int last=0;//�������һ��Ԫ��
	int head=0;//����ͷԪ�� 
	int llast=0;//���һ����ӵ�Ԫ�� 
	
	int *visited=new int[n];//�Ƿ���ʹ��ı�־���� 
	for(int m=0;m<n;++m){
			visited[m]=0;
		}
	queue <int> q;//�������� 
	pHead=p;//ͷָ��λ�ò��� 
	t=pHead;//��tָ���ƶ�������ͷ�� 
	for(int i=0;i<n;++i){//��ÿ������Ϊ�׸������ȱ��� 
		t=p;
		for(int m=0;m<n;++m){
			visited[m]=0;
		}
		numCount=1; 
		floorCount=0;
		sum=0;
		
		q.push((*t).data);//������ѹ�����
		visited[(*t).data-1]=1;//�޸���ӱ�־
		last=(*t).data; 
		
		while(!q.empty()){//������в�Ϊ�� 
			
			head=q.front();//�������ڶ���Ԫ�أ����в��� 
			q.pop();//���� 

			t=pHead;//��ͷ����ʼ����
			for(int j=0;j<n;++j){
				if((*t).data==head){
					while((*t).next!=NULL){
						t=(*t).next;
						
						if(visited[(*t).data-1]==0){//δ��� 
							q.push((*t).data);//�ҵ������ 
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
							visited[(*t).data-1]=1;//�޸���ӱ�־
						}
						else {//�Ѿ���� 
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
			cout<<"�߱�"<<endl; 
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
	createNode(n,p);// ��������˳��� 
	//display(p,n);//չʾͼ 
	createMap(p,n,m);//�����߱� 
	//display(p,n);//չʾͼ 
	search(p,n);
	return 0;
}
