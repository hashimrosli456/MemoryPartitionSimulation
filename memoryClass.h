#include <cassert> 
using namespace std;

template<class Type>
struct nodeType
{
	Type info;
	nodeType<Type> *link;
};

template <class Type>
class memoryClass
{
	private:
		int count;
		nodeType<Type> *first;
		nodeType<Type> *last;
	public: 
		void initializeList(); 
		bool isEmptyList() const;
		void print() const;
		int length() const;
		void destroyList();
		Type front() const; 
		int back() const; 
		void insert(Type& newItem); 
		void deleteNode(const int& deleteItem); 
		void deleteQueue();
		void insertAsc ( Type& newItem);
		void insertDsc ( Type& newItem);
		void freeMemory(const int& mem);
		int search(const int& searchItem);
		int findBlockNum(const int& size);
		void usage(const int& block, const int& jobSize);
		memoryClass(); 
		~memoryClass(); 
	
};

template <class Type>
void memoryClass<Type>::insertAsc( Type& newItem){
	nodeType<Type> *current;
	nodeType<Type> *trailCurrent;
	nodeType<Type> *temp;
	
	bool found;
	
	temp= new nodeType<Type>;
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
			if(current->info.memSize >= newItem.memSize)
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

template <class Type>
void memoryClass<Type>::insertDsc( Type& newItem){
	nodeType<Type> *current;
	nodeType<Type> *trailCurrent;
	nodeType<Type> *temp;
	
	bool found;
	
	temp= new nodeType<Type>;
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
			if(current->info.memSize <= newItem.memSize)
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

template<class Type>
void memoryClass<Type>::usage(const int& block, const int& jobSize){
	
	nodeType<Type> *current;
	bool found=false;
	current=first;
	
	while(current != NULL && !found){
		if(current->info.blockNum==block){
			found=true;
			current->info.jobUsage+=jobSize;
		}
		else{
			current=current->link;
		}
	}
}


template<class Type>
int memoryClass<Type>::findBlockNum(const int& size){
	nodeType<Type> *current;
	bool found=false;
	current=first;
	
	while(current != NULL && !found){
		if(current->info.memSize==size){
			found=true;
			return current->info.blockNum;
		}
		else{
			current=current->link;
		}
	}
}

template<class Type>
void memoryClass<Type>::freeMemory(const int& mem){
	nodeType<Type> *current;
	bool found=false;
	current=first;
	
	while(current != NULL && !found){
		if(current->info.memSize==mem){
			found=true;
			current->info.status=0;
		}
		else{
			current=current->link;
		}
	}
}

template <class Type>
int memoryClass<Type>::search(const int& searchItem){
	nodeType<Type> *current;
	bool found=false;
	current=first;
	
	while(current != NULL && !found){
		if(current->info.memSize>=searchItem &&current->info.status!=1){
			found=true;
		}
		else{
			current=current->link;
		}
	}
		
	if(found==true){
		current->info.status=1;
		current->info.used++;
		return current->info.memSize;
	}
	else{
		return -1;
	}
}

template <class Type>
void memoryClass<Type>::deleteQueue(){
	nodeType<Type> *temp;
	if(!isEmptyList()){
		temp=first;
		first=first->link;
		delete temp;
		if(first==NULL)
			last=NULL;
	}
	else
	cout<<"Cannot remove from an empty list"<<endl;
}

template <class Type>
bool memoryClass<Type>::isEmptyList() const
{
	return(first==NULL);
}

template <class Type>
memoryClass<Type>::memoryClass()
{
	first=NULL;
	last=NULL;
	count=0;
}

template <class Type>
void memoryClass<Type>::destroyList()
{
	nodeType<Type> *temp;
	
	while(first!=NULL){
		temp=first;
		first=first->link;
		delete temp;
	}
	last=NULL;
	count=0;
}

template <class Type>
void memoryClass<Type>::initializeList()
{
	destroyList();
}

template <class Type>
int memoryClass<Type>::length() const
{
	return count;
}

template <class Type>
Type memoryClass<Type>::front() const
{
	assert(first != NULL);
	return first->info;
}

template <class Type>
int memoryClass<Type>::back() const
{
	assert(last !=NULL);
	return last->info;
}

template <class Type>
memoryClass<Type>::~memoryClass() 
{
	destroyList();
}

template <class Type>
void memoryClass<Type>::deleteNode(const int& deleteItem)
{
	nodeType<Type> *current;
	nodeType<Type> *trailCurrent;
	
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

template <class Type>
void memoryClass<Type>::insert(Type& newItem)
{
	newItem.status=0;
	newItem.blockNum=++count;
	newItem.used=0;
	newItem.jobUsage=0;
	nodeType<Type> *newNode;
	newNode= new nodeType<Type>;//create node
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

template <class Type>
void memoryClass<Type>::print() const
{
	nodeType<Type> *current;
	current=first;
	float storageBlock;
	float utilize;
	float avgUtilize=0;
	float fragmentation=0;
	float totalStorage=0;
	string blockUsage;
	int i=1;
	cout<<setw(20)<<"Memory Block"<<setw(20)<<"Memory Size"<<setw(10)<<"Status"
	<<setw(10)<<"Used"<<setw(20)<<"Job Usage"<<"Storage Utilization"<<endl;
	for(int i=0;i<100;i++)
		cout<<'-';
	cout<<endl<<endl;
	while(current!= NULL)
	{
		storageBlock=static_cast<float>(current->info.used)*
		static_cast<float>(current->info.memSize);
		utilize=(static_cast<float>(current->info.jobUsage)/storageBlock)*100;
		fragmentation+= (storageBlock)- (static_cast<float>(current->info.jobUsage));
		totalStorage+=storageBlock;
		if(utilize>80.0)
			blockUsage=" (Heavily used)";
		else if(utilize<20.0||current->info.jobUsage==0)
		{
			blockUsage=" (Under used)";
			if(current->info.jobUsage==0)
				utilize=0;
		}
		else
			blockUsage=" ";
			
		avgUtilize+=utilize;

		cout<<setw(20)<<i++<<setw(20)<<current->info.memSize<<setw(10)
		<<current->info.status<<setw(10)<<current->info.used<<setw(20)<<current->info.jobUsage
		<<utilize<<" %"<<blockUsage<<endl;
		current=current->link;
	}
	
	avgUtilize=avgUtilize/10;
	cout<<endl<<"AVERAGE STORAGE UTILIZATION: "<<avgUtilize<<" %"<<endl;
	cout<<"TOTAL INTERNAL FRAGMENTATION: "<<static_cast<int>(fragmentation)<<endl;
	cout<<"AVERAGE PERCENTAGE OF INTERNAL FRAGMENTATION OVER TOTAL STORAGE: "
	<<(fragmentation/totalStorage)*100<<" %"<<endl;
}
