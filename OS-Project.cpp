#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int size; // user input size
int *Array; // array for storing
int frame_size; // frame size
int max_range; // range of reference string

void Input(int Algo_type)
{
	cout<<"Enter Size of Data: ";cin>>size;
	Array=new int[size];
	if(Algo_type==1)
	{
		cout<<"Enter Maximum Range of Reference String: ";cin>>max_range;
		srand(time(0));
		cout<<"Reference String is: ";
		for(int i=0;i<size;i++)
		{
			Array[i]=rand()%(max_range+1);
			cout<<Array[i]<<" ";
		}
		cout<<endl;
	}
	else if(Algo_type==2)
	{
		cout<<"Enter Data You Want(Reference String): ";
		for(int i=0;i<size;i++)
		cin>>Array[i];
	}
	cout<<"Enter Frame Size: ";cin>>frame_size;
	cout<<"\nAlgorithm\t"<<"PageFaults\t"<<"HitCount\t"<<"Page_Fault-Ratio\t"<<"Hit-Ratio"<<endl;
}
class BitArray
{
	public:
	int data;
	bool bit;
	BitArray(int value=-1,bool bol=false)
	{
		data=value;
		bit=bol;
	}
};
class Node
{
	public:
	int data;
	Node *next;
	Node(int value=-1,Node *nood=nullptr)
	{
		data=value;
		next=nood;
	}
};
class Queue
{
	Node *head;
	public:
	Queue()
	{
		head=nullptr;
	}
	void Enqueue(int value)
	{
		Node *temp=head;
		Node *newnode=new Node(value);
		newnode->next=nullptr;
		if(temp==nullptr)
		{
			head=newnode;
			return;
		}
		while(temp->next!=nullptr)
		{
			temp=temp->next;
		}
		temp->next=newnode;
	}
	void Dequeue()
	{
		Node *temp=head;
		if(temp==nullptr)
		{
			cout<<"QUEUE IS EMPTY"<<endl;
			return;
		}
		head=head->next;
		delete(temp);
	}
	bool Check(int value)
	{
		Node* temp=head;
		while(temp!=nullptr)
		{
			if(temp->data==value)
			{
				return true;
			}
			temp=temp->next;
		}
		return false;
	}
	int Size()
	{
		Node* temp=head;
		int count=0;
		while(temp!=nullptr)
		{
			temp=temp->next;
			count++;
		}
		return count;
	}
	bool ISEmpty()
	{
		if(head==NULL)
			return true;
		return false;
	}
	void Remove(int value)
	{
		if(head->data==value)
		{
			Node *temp=head;
			head=head->next;
			delete temp;
		}
		else
		{
			Node *temp=head;
			Node *temp1=temp->next;
			while(temp1->data!=value)
			{
				temp1=temp1->next;
				temp=temp->next;
			}
			temp->next=temp1->next;
			delete temp1;
		}
	}
	void Traverse()
	{
		for(Node *temp=head;temp!=nullptr;temp=temp->next)
		cout<<temp->data<<" ";	
	}
	~Queue()
	{	
		while(head!=nullptr)
		{
			Node *temp=head;
			head=head->next;
			delete temp;
		}
	}
};
class Stack
{
	BitArray *BA;
	int top;
	public:
	Stack()
	{
		BA=new BitArray[frame_size];
		top=0;
	}
	bool Check(int value)
	{
		for(int i=0;i<frame_size;i++)
		{
			if(value==BA[i].data)
			return true;
		}
		return false;
	}
	void UP_Top() { top++; }
	void Zero_Top() { top=0; }	
	void Push(int value)
	{
			BA[top%frame_size].data=value;
			top++;
	}
	int Pop()
	{
		int Top_value=BA[top].data;
		BA[top].data=-1;
		top--;
		return Top_value;
	}
	void Set_Bit(int value)
	{
		for(int i=0;i<frame_size;i++)
		{
			if(value==BA[i].data)
			{
				BA[i].bit=true;
				break;
			}
		}
	}
	void Reset_Bit(){ BA[top%frame_size].bit=false; }
	bool Get_Bit(){ return BA[top%frame_size].bit; }
	void Traverse()
	{
		for(int i=0;i<frame_size;i++)
		cout<<BA[i].data<<"-"<<BA[i].bit<<" ";
	}
	~Stack()
	{
		delete[] BA;
	}
};
class FIFO
{
	int pfault;
	int hit;
	Stack s;
	public:
	FIFO()
	{
		pfault=0;
		hit=0;
	}
	void Working()
	{
		for(int i=0;i<size;i++)
		{
			if(!s.Check(Array[i]))
			{
				s.Push(Array[i]);
				pfault++;
			}
		}
		hit=size-pfault;
		cout<<"FIFO\t\t   "<<pfault<<"\t\t   "<<hit<<"\t\t     "<<((float(pfault)/(size))*100)<<"%"<<"\t\t   ";
		cout<<((float(hit)/(size))*100)<<"%"<<endl;
	}
	void Reset()
	{
		s.Zero_Top();
		for(int i=0;i<frame_size;i++)
		{
			s.Push(-1);
		}
		s.Zero_Top();
		pfault=0;
	}
};
class LRU
{
	int pfault;
	int hit;
	Queue q;
	public:
	LRU()
	{
		pfault=0;
		hit=0;
	}
	void Working()
	{
		for(int i=0;i<size;i++)
		{
			if(q.Size()!=frame_size && !q.Check(Array[i]))
			{
				q.Enqueue(Array[i]);
				pfault++;
			}
			else if(q.Size()==frame_size && !q.Check(Array[i]))
			{
				q.Dequeue();
				q.Enqueue(Array[i]);
				pfault++;
			}
			else if(q.Check(Array[i]))
			{
				q.Remove(Array[i]);
				q.Enqueue(Array[i]);
			}
		}
		hit=size-pfault;
		cout<<"LRU\t\t   "<<pfault<<"\t\t   "<<hit<<"\t\t     "<<((float(pfault)/(size))*100)<<"%"<<"\t\t   ";
		cout<<((float(hit)/(size))*100)<<"%"<<endl;
	}
	void Reset()
	{
		while(!q.ISEmpty())
		{
			q.Dequeue();
		}
		pfault=0;
	}
};
class SCA
{
	Stack s;
	int pfault;
	int hit;
	public:
	SCA()
	{
		pfault=0;
		hit=0;
	}
	void Working()
	{
		for(int i=0;i<size;i++)
		{
			if(!s.Check(Array[i]) && !s.Get_Bit())
			{
				s.Push(Array[i]);
				pfault++;
			}
			else if(s.Get_Bit())
			{
				s.Reset_Bit();
				s.UP_Top();
				i--;
			}
			else if(s.Check(Array[i]))
			{
				s.Set_Bit(Array[i]);
			}
		}
		hit=size-pfault;
		cout<<"SCA\t\t   "<<pfault<<"\t\t   "<<hit<<"\t\t     "<<((float(pfault)/(size))*100)<<"%"<<"\t\t   ";
		cout<<((float(hit)/(size))*100)<<"%"<<endl;	
	}
	void Reset()
	{
		s.Zero_Top();
		for(int i=0;i<frame_size;i++)
		{
			s.Push(-1);
			s.Zero_Top();
		}
		s.Zero_Top();
	}
};
void End()
{
	system("cls");
	cout<<"\n\n\n\n\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n";
	cout<<"\t\t\t\t\xB2\xB2    \t\t\t\t       \xB2\xB2\n";
	cout<<"\t\t\t\t\xB2\xB2   THANK-YOU FOR USING THIS $YSTEM.  \xB2\xB2\n";
	cout<<"\t\t\t\t\xB2\xB2     \t\t\t\t       \xB2\xB2";
	cout<<"\n\t\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n";
	cout<<"\n\n\n\n\n\n";
	exit(0);
}
int choice(int x)
{
		char choise;
		fflush(stdin);
		cin>>choise;
		while(choise<'1' || choise>'1'+x-1)
		{
			cout<<"\n\t\tWrong Choice!\n\n";
			cout<<"\n\t\tEnter your choice : ";
			fflush(stdin);
			cin>>choise;
		}
		return choise-'0';
}
int Menu()
{
	system("cls");
	cout<<"\n\n\t\t\t\t--------------------------------------------------------"<<endl;
	cout<<"\t\t\t\t Welcome To The \"Page Replacement Algorithms\" OS Project"<<endl;
	cout<<"\t\t\t\t--------------------------------------------------------"<<endl;
	cout<<"\t\t\t\t \\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\ \n\n\n";
	cout<<"\t\t\t\t\t1-> Enter Data Automatically\n\n";
	cout<<"\t\t\t\t\t2-> Enter Data Manually\n\n";
	cout<<"\t\t\t\t\t3-> Exit\n\n\n\n";
	cout<<"\n__________________________\n";
	cout<<"\n\tEnter your choice : ";
	int x=choice(3);
	
	FIFO fifo;LRU lru;SCA sca;   // Main Objects
	
	if(x==1)
	{
		system("cls");
		Input(x);
		fifo.Working();
		lru.Working();
		sca.Working();
		fifo.Reset();
		lru.Reset();
		sca.Reset();
		cout<<"\n\n";
		system("pause");
		Menu();
	}
	else if(x==2)
	{
		system("cls");
		Input(x);
		fifo.Working();
		lru.Working();
		sca.Working();
		fifo.Reset();
		lru.Reset();
		sca.Reset();
		cout<<"\n\n";
		system("pause");
		Menu();
	}
	else if(x==3)
	{
		End();
	}
}
int main()
{
	Menu();
	delete[] Array; 
}
