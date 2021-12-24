#include<iostream>
#include<fstream> //file handling
#include<cstdlib> //system
#include<windows.h> //Sleep function
#include<iomanip> //output position
#include "memoryClass.h"
#include "jobClass.h"
#include "dynamicClass.h"

using namespace std;


struct memStruct
{
	int blockNum;
	int memSize;
	int status;
	int used;
	int jobUsage;
};

struct jobStruct
{
	int jobNum;
	int arvTime;
	int prcTime;
	int jobSize;
	int jobMemory;
};

struct dynamicStruct
{
	int jobNum;
	int arvTime;
	int prcTime;
	int jobSize;
	int beginmemory;
	int endmemory;	
};

struct emptyStruct
{
	
	int beginmemory;
	int endmemory;
	int jobSize;
	int sizememory;	
};

template <class Type>
int readFileMem (ifstream& memoryFile, memoryClass<Type>& memory);

template<class Type2>
int readFileJob (ifstream& jobFile, jobClass<Type2>& job);

int valMaxMin (string command,float oriValue, float newValue);

int main()
{
	int choice,choiceFix,choiceDyn;
	cout<<left<<fixed<<showpoint<<setprecision(2);
	ifstream memoryFile;
	ifstream jobFile;
	int loopMem=0, loopJob=0;
	
	int memoryEntered;
	int block;
	int jobProcessed;
	
	jobStruct newStruct;
	jobStruct newStruct2;
	memStruct newStruct3;
	dynamicStruct newStruct4;
	nodeType4<emptyStruct> newStruct5;
	
	for(int i=0; i<=2;i++){
		cout<<setw(20)<<""<<"EVENT-DRIVEN SIMULATION PROGRAM"<<endl;
		cout<<setw(10)<<""<<"To get best view of output show, you should maximize the windows "<<endl;
		cout<<setw(20)<<"";
		
			cout<<"Go to menu in count of ";
			cout<<3-i<<" ...\a";
			Sleep(1000);
			system("cls");
		}
		
	do{
		
		memoryClass<memStruct> memory;
		memoryClass<memStruct> tempMemory;
		jobClass<jobStruct> job;
		jobClass<jobStruct> leave;
		jobClass<jobStruct> waitingQue;
		dynamicClass<dynamicStruct,emptyStruct> dymemory;
		emptyClass<emptyStruct> emptyspace;
		
		float waitQueLength=0; //sum of que length in each enter n out of waiting queue
		float waitQueMax=0; //min que =0
		float waitQueMin=40; //max que =40
		
		float totalWaitTime=0;
		float waitTimeMax=0;
		float waitTimeMin=999999;

	
		memory.initializeList();
		
		memoryFile.open("MemoryList.txt");
		jobFile.open("Joblist.txt");
	
		if(memoryFile){
			//proceed
		}
		else{
			cout<<"File not found. Terminating program..."<<endl;
			system("pause");
			return 0;
		}
		if(memoryFile){
			//proceed
		}
		else{
			cout<<"File not found. Terminating program..."<<endl;
			system("pause");
			return 0;
		}
	
		loopMem =readFileMem(memoryFile,memory);
		loopJob =readFileJob(jobFile,job);
		memoryFile.close();
		jobFile.close();	
		
		do{
			system("cls");
			cout<<char (218);
 			for(int i=1;i<24;i++)
				cout<<char (196);
			cout<<char (191);
			
			cout<<endl<<char (179)<<"Main Menu"<<"\t\t"<<char (179);
			cout<<endl<<char (179)<<"1. Display memory list"<<" "<<char (179);
			cout<<endl<<char (179)<<"2. Display job list"<<"\t"<<char (179);
			cout<<endl<<char (179)<<"3. Fixed partition"<<"\t"<<char (179);
			cout<<endl<<char (179)<<"4. Dynamic partition"<<"\t"<<char (179);
			cout<<endl<<char (179)<<"5. Exit"<<"\t\t"<<char (179)<<endl;
			
			cout<<char (192);
 			for(int i=1;i<24;i++)
				cout<<char (196);
 			cout<<char (217);
 			
			cout<<"\nEnter your choice: ";
			cin>>choice;
		}while(choice>5||choice<1);
		
		switch(choice){
			case 1:
				memory.print();
				cout<<endl;
				break;
			case 2:
				job.print();
				cout<<endl;
				break;
			case 3:
				do{
					system("cls");
					cout<<char (218);
 					for(int i=1;i<24;i++)
						cout<<char (196);
					cout<<char (191);
					
					cout<<endl<<char (179)<<"Fixed Partition Menu"<<"   "<<char (179)<<endl;
					cout<<char (179)<<"1. First Fit Algorithm"<<" "<<char (179)<<endl;
					cout<<char (179)<<"2. Best Fit Algorithm"<<"  "<<char (179)<<endl;
					
					cout<<char (192);
 					for(int i=1;i<24;i++)
						cout<<char (196);
 					cout<<char (217);
 			
					cout<<"\nEnter your choice: ";
					cin>>choiceFix;
				}while(choiceFix>3||choiceFix<1);
				
				switch(choiceFix){
					case 1: //first fit
						
						break;
						
					case 2: //best fit

						while(memory.isEmptyList()==false){
							
							newStruct3=memory.front();
							tempMemory.insertAsc(newStruct3);
							memory.deleteQueue();
						}
						
						while(tempMemory.isEmptyList()==false){
							newStruct3=tempMemory.front();
							memory.insertAsc(newStruct3);
							tempMemory.deleteQueue();
						}

						break;
					
				}
				
				jobProcessed=40;
				cout<<endl;
				cout<<setw(15)<<"TIME"<<setw(15)<<"EVENT"<<setw(15)
				<<"JOB NUM"<<setw(15)<<"JOB SIZE"<<setw(15)<<"MEMORY BLOCK"
				<<"BLOCK SIZE"<<endl;
				for(int i=0;i<100;i++)
					cout<<'-';
				cout<<endl<<endl;
				while(job.isEmptyList()==false)
				{
					while(leave.isEmptyList()==false){
						newStruct=job.front();
						newStruct2=leave.front();
						if(newStruct.arvTime >= (newStruct2.arvTime + newStruct2.prcTime)){
							block=memory.findBlockNum(newStruct2.jobMemory);
							cout<<setw(15)<<newStruct2.arvTime + newStruct2.prcTime
							<<setw(15)<<"Leave"<<setw(15)<<newStruct2.jobNum<<setw(15)
							<<newStruct2.jobSize<<setw(15)<<block<<newStruct2.jobMemory<<endl;
							memory.freeMemory(newStruct2.jobMemory);
							leave.deleteQueue();
					
						}
						else
							break;
					}
					while(waitingQue.isEmptyList()==false){ 
						newStruct=job.front();
						newStruct2=waitingQue.front();
						memoryEntered=memory.search(newStruct2.jobSize);
						block=memory.findBlockNum(memoryEntered);
						if(memoryEntered!=-1)
						{
							cout<<setw(15)<<newStruct.arvTime<<setw(15)<<"Enter"<<setw(15)
							<<newStruct2.jobNum<<setw(15)<<newStruct2.jobSize<<setw(15)
							<<block<<memoryEntered<<endl;	
							totalWaitTime+=(newStruct.arvTime-newStruct2.arvTime);
							newStruct2.jobMemory=memoryEntered;
							newStruct2.arvTime=newStruct.arvTime;
							leave.insertAsc(newStruct2);
							memory.usage(block,newStruct2.jobSize);
							waitingQue.deleteQueue();
						
						}
						else
							break;
								
					}
						
					newStruct=job.front();
					cout<<setw(15)<<newStruct.arvTime<<setw(15);
					if(newStruct.jobSize>9500){
						cout<<"Size overlimit"<<setw(15)<<newStruct.jobNum<<setw(15)
						<<newStruct.jobSize<<setw(15)<<"None"<<"-"<<endl;
						jobProcessed--; //decrease by 1
						job.deleteQueue();
					}
					else
					{
						cout<<"Arrived"<<setw(15)<<newStruct.jobNum<<setw(15)
						<<newStruct.jobSize<<setw(15)<<"None"<<"-"<<endl;
						memoryEntered=memory.search(newStruct.jobSize);
						block=memory.findBlockNum(memoryEntered);

						if(memoryEntered==-1){
							cout<<setw(15)<<newStruct.arvTime<<setw(15)<<"Waiting"
							<<setw(15)<<newStruct.jobNum<<setw(15)<<newStruct.jobSize
							<<setw(15)<<"None"<<"-"<<endl;
							waitingQue.insert(newStruct);
						}
						else{
							cout<<setw(15)<<newStruct.arvTime<<setw(15)<<"Enter"
							<<setw(15)<<newStruct.jobNum<<setw(15)<<newStruct.jobSize
							<<setw(15)<<block<<memoryEntered<<endl;
							newStruct.jobMemory=memoryEntered;
							memory.usage(block,newStruct.jobSize);
							leave.insertAsc(newStruct);
						}
						job.deleteQueue();
					}
							
				
							
					waitQueLength+=waitingQue.getCount();
					waitQueMax=valMaxMin("max",waitQueMax,waitingQue.getCount());
					waitQueMin=valMaxMin("min",waitQueMin,waitingQue.getCount());
	
				} // end of while - all arrived
				
				while(leave.isEmptyList()==false){
					newStruct=leave.front();
					block=memory.findBlockNum(newStruct.jobMemory);
					cout<<setw(15)<<newStruct.arvTime + newStruct.prcTime<<setw(15)<<"Leave"
					<<setw(15)<<newStruct.jobNum<<setw(15)<<newStruct.jobSize<<setw(15)
					<<block<<newStruct.jobMemory<<endl;
					memory.freeMemory(newStruct.jobMemory);
					leave.deleteQueue();
				
							
					while(waitingQue.isEmptyList()==false){
						newStruct2=waitingQue.front(); 
						memoryEntered=memory.search(newStruct2.jobSize);
						block=memory.findBlockNum(memoryEntered);
						
						if(memoryEntered!=-1)
						{
							cout<<setw(15)<<newStruct.arvTime+newStruct.prcTime<<setw(15)
							<<"Enter"<<setw(15)<<newStruct2.jobNum<<setw(15)
							<<newStruct2.jobSize<<setw(15)<<block<<memoryEntered<<endl;	
							totalWaitTime+=((newStruct.arvTime+newStruct.prcTime)
							-newStruct2.arvTime);
							newStruct2.jobMemory=memoryEntered;
							newStruct2.arvTime=newStruct.arvTime+newStruct.prcTime;
							leave.insertAsc(newStruct2);
							memory.usage(block,newStruct2.jobSize);
							waitingQue.deleteQueue();
						
						}
						else
							break;
								
								
					 }
							
					waitQueLength+=waitingQue.getCount();
					waitQueMax=valMaxMin("max",waitQueMax,waitingQue.getCount());
					waitQueMin=valMaxMin("min",waitQueMin,waitingQue.getCount());
						
				}// end of while- all left
				
				cout<<endl;		
				/*cout<<"In waiting list :"<<endl;
				waitingQue.print();
				cout<<"In processing :"<<endl;
				leave.print();*/
					
				system("pause");
				system("cls");
				
				memory.print();
				cout<<"AMOUNT TIME PROCESSING: "<<newStruct.arvTime+newStruct.prcTime<<endl;
				cout<<"TOTAL JOB PROCESSED: "<<jobProcessed<<endl;
				cout<<"JOB PROCESSED PER GIVEN TIME: "
				<<static_cast<float>(jobProcessed)/static_cast<float>(newStruct.arvTime
				+newStruct.prcTime)<<endl;
				cout<<"AVERAGE WAITING QUEUE LENGTH PER EVENT TIME: "
				<<waitQueLength/static_cast<float>(newStruct.arvTime+newStruct.prcTime)<<endl;
				cout<<"WAITING QUEUE LENGTH MAX: "<<static_cast<int>(waitQueMax)<<endl;
				cout<<"WAITING QUEUE LENGTH MIN: "<<static_cast<int>(waitQueMin)<<endl;
				cout<<"TOTAL WAITING TIME IN QUEUE: "<<totalWaitTime<<endl;
				cout<<"AVERAGE WAITING TIME IN QUEUE: "
				<<totalWaitTime/static_cast<float>(newStruct.arvTime+newStruct.prcTime)<<endl<<endl;
				
				break;
				
			case 4:
				do{
					system("cls");
					cout<<char (218);
 					for(int i=1;i<24;i++)
						cout<<char (196);
					cout<<char (191);
			
					cout<<endl<<char (179)<<"Dynamic Partition Menu"<<" "<<char (179)<<endl;
					cout<<char (179)<<"1. First Fit Algorithm"<<" "<<char (179)<<endl;
					cout<<char (179)<<"2. Best Fit Algorithm"<<"  "<<char (179)<<endl;
					cout<<char (179)<<"3. Worst Fit Algorithm"<<" "<<char (179)<<endl;
					
					cout<<char (192);
 					for(int i=1;i<24;i++)
						cout<<char (196);
 					cout<<char (217);
 					
					cout<<"\nEnter your choice: ";
					cin>>choiceDyn;
				}while(choiceDyn>3||choiceDyn<1);
				
				switch(choiceDyn){
					case 1:
						cout<<setw(20)<<"Job Number"<<setw(20)<<"Arrival Time"<<setw(20)<<"Processing Time"
						<<setw(20)<<"Job Size"<<setw(20)<<"Begin Memory"<<setw(20)<<"End Memory"<<"Status"<<endl;
						newStruct4.beginmemory=0;
						newStruct4.endmemory=0;
						do{
							newStruct=job.front();
							newStruct4.arvTime=newStruct.arvTime;
							newStruct4.prcTime=newStruct.prcTime;
							newStruct4.jobNum=newStruct.jobNum;
							newStruct4.jobSize=newStruct.jobSize;
							if(newStruct.jobNum!=1)
							{
								newStruct4.beginmemory=newStruct4.endmemory;
							}
							newStruct4.endmemory+=newStruct4.jobSize;
							if(dymemory.isEmptyList()==false)
							{
								dymemory.jobleave(newStruct.arvTime,emptyspace,newStruct5);
								
							}
							dymemory.insert(newStruct4);
							
							
							
							cout<<setw(20)<<newStruct4.jobNum<<setw(20)<<newStruct4.arvTime<<setw(20)
							<<newStruct4.prcTime<<setw(20)<<newStruct4.jobSize<<setw(20)<<newStruct4.beginmemory<<setw(20)<<newStruct4.endmemory<<"Job Arrive"<<endl;
							
							job.deleteQueue();
						}while(job.isEmptyList()==false);
						cout<<endl<<"EMPTY SPACE IN MEMORY";
						emptyspace.print();
						cout<<endl<<"JOB STILL IN MEMORY"<<endl;
						dymemory.print();
						break;
					case 2:
						//bestfit
						break;
					case 3:
						//worstfit
						cout<<setw(20)<<"Job Number"<<setw(20)<<"Arrival Time"<<setw(20)<<"Processing Time"
						<<setw(20)<<"Job Size"<<setw(20)<<"Begin Memory"<<setw(20)<<"End Memory"<<"Status"<<endl;
						newStruct4.beginmemory=0;
						newStruct4.endmemory=0;
						do{
							newStruct=job.front();
							newStruct4.arvTime=newStruct.arvTime;
							newStruct4.prcTime=newStruct.prcTime;
							newStruct4.jobNum=newStruct.jobNum;
							newStruct4.jobSize=newStruct.jobSize;
							if(newStruct.jobNum!=1)
							{
								newStruct4.beginmemory=newStruct4.endmemory;
							}
							newStruct4.endmemory+=newStruct4.jobSize;
							if(dymemory.isEmptyList()==false)
							{
								dymemory.jobleave(newStruct.arvTime,emptyspace,newStruct5);
								
							}
							dymemory.insertDsc(newStruct4);
							
							
							
							cout<<setw(20)<<newStruct4.jobNum<<setw(20)<<newStruct4.arvTime<<setw(20)
							<<newStruct4.prcTime<<setw(20)<<newStruct4.jobSize<<setw(20)<<newStruct4.beginmemory<<setw(20)<<newStruct4.endmemory<<"Job Arrive"<<endl;
							
							job.deleteQueue();
						}while(job.isEmptyList()==false);
						cout<<endl<<"EMPTY SPACE IN MEMORY";
						emptyspace.print();
						cout<<endl<<"JOB STILL IN MEMORY"<<endl;
						dymemory.print();
						break;
				}
				break;
			case 5:
				//exit();
				break;
		}		
		
		system("pause");
	}while(choice!=5);
	
	system("cls");
	cout<<"\n\n\n\n\t\t\t\t";
	for(int count=0;count<15;count++){
		cout<<'*';
		Sleep(50);
	}
	cout<<"THANK YOU";
	for(int count=0;count<15;count++){
		cout<<'*';
		Sleep(50);
	}
	return 0;
	
}//main


template<class Type>
int readFileMem (ifstream& memoryFile, memoryClass<Type>& memory){

	int loopMem;
	int memSize;
	
	memStruct Information;//declaration the object of the carInfo struct
	
	memoryFile>>loopMem;
	while(memoryFile>>Information.memSize)
		memory.insert(Information);
}

template<class Type2>
int readFileJob (ifstream& jobFile, jobClass<Type2>& job){
	
	int loopJob;
	
	jobStruct Information;
	
	jobFile>>loopJob;
	while(jobFile>>Information.jobNum>>Information.arvTime
	>>Information.prcTime>>Information.jobSize)
		job.insert(Information);
}

int valMaxMin (string command,float oriValue, float newValue){
	if(command=="max"){
		if(newValue>oriValue)
			return newValue;
		else
			return oriValue;
	}
	else{
		if(newValue<oriValue)
			return newValue;
		else
			return oriValue;
	}
}
