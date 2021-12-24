#include <cassert> 
using namespace std;

template<class Type2>
struct nodeType2
{
	Type2 info;
	nodeType2<Type2> *link;
};

template <class Type2>
class jobClass
{
	private:
		int count;
		nodeType2<Type2> *first;
		nodeType2<Type2> *last;
	public: 
		void initializeList(); 
		bool isEmptyList() const;
		void print() const;
		int length() const;
		void destroyList();
		Type2 front() const; 
		int back() const; 
		void insert(const Type2& newItem);
		void insertAsc (const Type2& newItem);
		void deleteNode(const int& deleteItem); 
		void deleteQueue();
		int getCount();
		jobClass(); 
		~jobClass(); 
};

template <class Type2>
int jobClass<Type2>::getCount(){
	return count;
}

template <class Type2>
void jobClass<Type2>::insertAsc(const Type2& newItem){
	nodeType2<Type2> *current;
	nodeType2<Type2> *trailCurrent;
	nodeType2<Type2> *temp;
	
	bool found;
	
	temp= new nodeType2<Type2>;
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
			if((current->info.arvTime + current->info.prcTime)>=(newItem.arvTime + newItem.prcTime))
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

template <class Type2>
void jobClass<Type2>::deleteQueue(){
	nodeType2<Type2> *temp;
	if(!isEmptyList()){
		temp=first;
		first=first->link;
		delete temp;
		count--;
		if(first==NULL)
			last=NULL;
	}
	else
	cout<<"Cannot remove from an empty list"<<endl;
}

template <class Type2>
bool jobClass<Type2>::isEmptyList() const
{
	return(first==NULL);
}

template <class Type2>
jobClass<Type2>::jobClass()
{
	first=NULL;
	last=NULL;
	count=0;
}

template <class Type2>
void jobClass<Type2>::destroyList()
{
	nodeType2<Type2> *temp;
	
	while(first!=NULL){
		temp=first;
		first=first->link;
		delete temp;
	}
	last=NULL;
	count=0;
}

template <class Type2>
void jobClass<Type2>::initializeList()
{
	destroyList();
}

template <class Type2>
int jobClass<Type2>::length() const
{
	return count;
}

template <class Type2>
Type2 jobClass<Type2>::front() const
{
	assert(first != NULL);
	return first->info;
}

template <class Type2>
int jobClass<Type2>::back() const
{
	assert(last !=NULL);
	return last->info;
}

template <class Type2>
jobClass<Type2>::~jobClass() 
{
	destroyList();
}

template <class Type2>
void jobClass<Type2>::deleteNode(const int& deleteItem)
{
	nodeType2<Type2> *current;
	nodeType2<Type2> *trailCurrent;
	
	bool found;
	
	if(first == NULL)
		cerr<<"cannot delete from an empty list...\n";
	else
	{
		if(first->info == deleteItem)
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
				if(current->info !=deleteItem)
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
		}// end else
	}// end else
}// end funct

template <class Type2>
void jobClass<Type2>::insert(const Type2& newItem)
{
	nodeType2<Type2> *newNode;
	newNode= new nodeType2<Type2>;//create node
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
	count++;
}

template <class Type2>
void jobClass<Type2>::print() const
{
	nodeType2<Type2> *current;
	current=first;
	cout<<left;
	cout<<setw(20)<<"Job Number"<<setw(20)<<"Arrival Time"<<setw(20)<<"Processing Time"
	<<"Job Size"<<endl;
	while(current!= NULL)
	{
		cout<<setw(20)<<current->info.jobNum<<setw(20)<<current->info.arvTime<<setw(20)
		<<current->info.prcTime<<current->info.jobSize<<endl;
		current=current->link;
	}
}
