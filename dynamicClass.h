#include <cassert> 
#include<iostream>
#include "emptyClass.h"
using namespace std;

template<class Type3,class Type4>
struct nodeType3
{
	Type3 info;
	nodeType3<Type3 ,  Type4> *link;
};

template <class Type3 , class Type4>
class dynamicClass
{
	private:
		int count;
		nodeType3<Type3 ,  Type4> *first;
		nodeType3<Type3 ,  Type4> *last;
	public:
		void initializeList(); 
		bool isEmptyList() const;
		void print() const;
		int length() const;
		void destroyList();
		int front() const; 
		int back() const; 
		void insert(Type3& newItem); 
		void insertDsc( Type3& newItem);
		void deleteNode(const int& deleteItem); 
		void deleteQueue();
		void search(const int& searchItem);
		void jobleave(const int& arvItem, emptyClass<Type4>& emptyspace,nodeType4<Type4>& newStruct5);
		dynamicClass();
		~dynamicClass();
	
};


template<class Type3 , class Type4>
dynamicClass<Type3 ,  Type4> :: dynamicClass()
{
	first=NULL;
	last=NULL;
	count=0;
}
	
template<class Type3 , class Type4>
dynamicClass<Type3 ,  Type4> :: ~dynamicClass()
{
	destroyList();
}

template<class Type3 , class Type4>
void dynamicClass<Type3 ,  Type4> :: initializeList()
{
	destroyList();
}

template<class Type3 , class Type4>
bool dynamicClass<Type3 ,  Type4> :: isEmptyList() const
{
	return(first==NULL);
}

template<class Type3 , class Type4>
void dynamicClass<Type3 ,  Type4> :: print() const
{
nodeType3<Type3 ,  Type4> *current;
	current=first;
	cout<<left;
	cout<<setw(20)<<"Job Number"<<setw(20)<<"Arrival Time"<<setw(20)<<"Processing Time"
	<<setw(20)<<"Job Size"<<setw(20)<<"Begin memory"<<"End memory"<<endl;
	while(current!= NULL)
	{
		cout<<setw(20)<<current->info.jobNum<<setw(20)<<current->info.arvTime<<setw(20)
		<<current->info.prcTime<<setw(20)<<current->info.jobSize<<setw(20)<<current->info.beginmemory<<current->info.endmemory<<endl;
		current=current->link;
	}
}

template<class Type3 , class Type4>
int dynamicClass<Type3 ,  Type4> :: length() const
{
	return count;
}

template<class Type3 , class Type4>
void dynamicClass<Type3 ,  Type4> :: destroyList()
{
	nodeType3<Type3 ,  Type4> *temp;
	
	while(first!=NULL)
	{
		temp=first;
		first=first->link;
		delete temp;
	}
	last=NULL;
	count=0;
}

template<class Type3 , class Type4>
int dynamicClass<Type3 ,  Type4> :: front() const
{
	assert(first != NULL);
	return first->info;
}
	
template<class Type3 , class Type4>
int dynamicClass<Type3 ,  Type4> :: back() const
{
	assert(last !=NULL);
	return last->info;
}

template<class Type3 , class Type4>
void dynamicClass<Type3 ,  Type4> :: insert(Type3& newItem)
{
	
	nodeType3<Type3 ,  Type4> *newNode;
	newNode= new nodeType3<Type3 ,  Type4>;
	newNode->info= newItem;
	newNode->link=NULL;
	if(first==NULL)
	{
		first=newNode;
		last=newNode;
	}
	else
	{
		last->link=newNode;
		last=last->link;
	}
}

template <class Type3 , class Type4>
void dynamicClass<Type3 , Type4>::insertDsc( Type3& newItem){
	nodeType3<Type3 , Type4> *current;
	nodeType3< Type3 , Type4> *trailCurrent;
	nodeType3< Type3 , Type4> *temp;
	
	bool found;
	
	temp= new nodeType3<Type3 , Type4>;
	temp->info = newItem;
	temp->link =NULL;
	
	if(first==NULL){
		first= temp;
		last=temp;
	}
	
	else{
		current=first;
		found=false;
		
		while(current!= NULL && !found)
			if(current->info.jobSize <= newItem.jobSize)
				found=true;
			else{
				trailCurrent=current;
				current=current->link;
			}
		
		if(current == first){
			temp->link = first;
			first= temp;
		}
		else{
			trailCurrent->link=temp;
			temp->link=current;
			
			if(current==NULL){
				last=temp;
			}
		}
	}
}

template<class Type3 , class Type4>
void dynamicClass<Type3 ,  Type4> :: deleteNode(const int& deleteItem)
{
	nodeType3<Type3 ,  Type4> *current;
	nodeType3<Type3 ,  Type4> *trailCurrent;
	
	bool found;
	
	if(first == NULL)
		cout<<"Cannot delete from an empty list."<<endl;
	else
	{
		if(first->info.jobNum == deleteItem)
		{
			current=first;
			first= first->link;
			count--;
			if(first==NULL)
				last=NULL;
			delete current;
		}
		else
		{
			found = false;
			trailCurrent=first;
			current=first->link;
			
			while(current!=NULL&& !found)
			{
				if(current->info.jobNum !=deleteItem)
				{
					trailCurrent = current;
					current=current->link;
				}
				else
					found=true;
			}
			
			if(found)
			{
				trailCurrent->link=current->link;
				count--;
				
				if(last ==current)
					last=trailCurrent;
				delete current;
			}
			else
				cout<<"Item to be deleted is not in the list."<<endl;
		}
	}
}

template<class Type3 , class Type4>
void dynamicClass<Type3 ,  Type4> :: deleteQueue()
{
	nodeType3<Type3 ,  Type4> *temp;
	if(!isEmptyList())
	{
		temp=first;
		first=first->link;
		delete temp;
		if(first==NULL)
		last=NULL;
	}
	else
	cout<<"Cannot delete from an empty list"<<endl;
}

template <class Type3 , class Type4>
void dynamicClass<Type3 ,  Type4>::search(const int& searchItem){
	nodeType3<Type3 ,  Type4> *current;
	nodeType3<Type3 ,  Type4> *trailcurrent;
	bool found=false;
	current=first;
	
	while(current != NULL && !found){
		if((current->info.begin-trailcurrent->info.end)>=searchItem){
			found=true;
		}
		else{
			trailcurrent=current;
			current=current->link;
		}
	}
		
	if(found==true){
		insert(searchItem);
	}
	else{
		return -1;
	}
}

template <class Type3 , class Type4>
void dynamicClass<Type3 ,Type4>::jobleave(const int& arvItem, emptyClass<Type4>& emptyspace, nodeType4<Type4>& newStruct5 )
{
	nodeType3<Type3 ,  Type4> *current;

	current=first;
	
	while(current != NULL){
		
		if(current->info.arvTime+current->info.prcTime <= arvItem)
		{
		cout<<setw(20)<<current->info.jobNum<<setw(20)<<current->info.arvTime<<setw(20)
		<<current->info.prcTime<<setw(20)<<current->info.jobSize<<setw(20)<<"-"<<setw(20)<<"-"<<"Job Leave"<<endl;
		deleteNode(current->info.jobNum);
		
		newStruct5.info.beginmemory=current->info.beginmemory;
		newStruct5.info.endmemory=current->info.endmemory;
		newStruct5.info.sizememory = (current->info.jobSize);
		emptyspace.insert(newStruct5.info);
		}
			current=current->link;
	}
}
