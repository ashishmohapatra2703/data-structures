#include <iostream>
using namespace std;
class Node
{
    public:
        int data;
        Node *next;
};
class LinkedList
{
    private:
        Node *first; //head node pointer
        Node *last; //tail node pointer
    public:
        LinkedList() //Non-Parameterized constructor
        {
            first=NULL;
            last=NULL;
        }
        LinkedList(int A[],int n) //Parameterized constructor (initialization of LL when object is created)
        {
            Node *t; //temp node pointer
            first=new Node;
            first->data=A[0];
            first->next=NULL;
            last=first;
            for(int i=1;i<n;i++) //from 2nd node to last
            {
                t=new Node;
                t->data=A[i];
                t->next=NULL;
                last->next=t;
                last=t;
            }
        }
        LinkedList(const LinkedList &l) //Copy constructor (Deep Copy)
        {
            Node *t = l.first;

            first=new Node;
            first->data=t->data;
            first->next=NULL;
            last=first;
            t=t->next; //pointing to 2nd node of l
            while(t!=NULL)//until last node
            {
                last->next=new Node;
                last=last->next;
                last->data=t->data;
                last->next=NULL;
                t=t->next;
            }
        }
        void Display();
        int Length();
        int Add();
        int Max();
        Node* Search(int key);
        void Insert(int index,int x);
        void Append(int x); //Insert at last
        void InsertinSorted(int x);
        int Delete(int index);
        bool isSorted();
        void RemoveDuplicate();
        void Reverse();
        friend LinkedList Concatenate(LinkedList &l1,LinkedList &l2);
        friend LinkedList MergeSortedLL(LinkedList &l1,LinkedList &l2);
        Node* gethead()
        {
            return first;
        }
        ~LinkedList() //Destructor
        {
            Node *p=first;
            while(first!=NULL)
            {
                first=first->next;
                delete p;
                p=first;
            }
        }
};

void LinkedList::Display()
{
    Node *p=first;
    while(p!=0)
    {
        cout<<p->data;
        p=p->next;
        if(p!=0) //no -> at the last iteration for last node
            cout<<" -> ";
    }
    cout<<endl;
}
int LinkedList::Length()
{
    Node *p=first;
    int len=0;
    while(p)
    {
        len++;
        p=p->next;
    }
    return len;
}
int LinkedList::Add()
{
    Node *p=first;
    int sum=0;
    while(p)
    {
        sum += p->data;
        p=p->next;
    }
    return sum;
}
int LinkedList::Max()
{
    Node *p=first;
    int max=INT_MIN;
    while(p!=0)
    {
        if(p->data >max)
            max=p->data;
        p=p->next;
    }
    return max;
}
Node* LinkedList::Search(int key) //Linear Search with move to head improvisation
{
    Node *p=first;
    Node *q=0;
    while(p!=NULL)
    {
        if(key==p->data)
        {
            q->next=p->next;
            p->next=first;
            first=p;
            return p;
        }
        q=p;
        p=p->next;
    }
    return NULL;
}
void LinkedList::Insert(int index,int x)
{
    Node *p=first;
    Node *t=new Node;
    t->data=x;
    t->next=NULL;
    if(index < 0 || index > Length())
        return;
    if(index == 0)
    {
        t->next=first;
        first=t;
    }
    else
    {
        for(int i=0; i<index-1; i++)
        {
            p=p->next;
        }
        t->next=p->next;
        p->next=t;
    }
}
void LinkedList::Append(int x) //Insert at last
{
    Node *t=new Node;
    t->data=x;
    t->next=NULL;
    if(first==NULL)
    {
        first=last=t;
    }
    else
    {
        last->next=t;
        last=t;
    }
}
void LinkedList::InsertinSorted(int x)
{
    Node *p=first;
    Node *q=NULL;
    while(p!=0 && p->data<x)
    {
        q=p;
        p=p->next;
    }
    Node *t=new Node;
    t->data=x;
    t->next=q->next;
    q->next=t;
}
int LinkedList::Delete(int index)
{
    Node *p=first;
    Node *q=NULL;
    int x=-1;
    if(index < 1 || index > Length())
        return -1;
    if(index==1)
    {
        first=first->next;
        x=p->data;
        delete p;
    }
    else
    {
        for(int i=0; i<index-1 &&p; i++)
        {
            q=p;
            p=p->next;
        }
        if(p)
        {
            q->next=p->next;
            x=p->data;
            delete p;
        }
    }
    return x;
}
bool LinkedList::isSorted()
{
    Node *p=first;
    int x=INT_MIN;
    while(p)
    {
        if(p->data<x)
            return false;
        x=p->data;
        p=p->next;
    }
    return true;
}
void LinkedList::RemoveDuplicate()
{
    Node *q=first;
    Node *p=q->next;
    while(p!=0)
    {
        if(q->data!=p->data)
        {
            q=p;
            p=p->next;
        }
        else
        {
            q->next=p->next;
            delete p;
            p=q->next;
        }
    }
}
void LinkedList::Reverse() //sliding pointers
{
    Node *p=first;
    Node *q=NULL;
    Node *r=NULL;
    while(p!=NULL)
    {
        r=q;
        q=p;
        p=p->next;
        q->next=r;
    }
    last=first;
    first=q;
}
LinkedList Concatenate(LinkedList &l1,LinkedList &l2)
{
    LinkedList l1dupt(l1);
    LinkedList l2dupt(l2);
    (l1dupt.last)->next = (l2dupt.first);
    l2dupt.first = NULL;
    return l1dupt;
}
LinkedList MergeSortedLL(LinkedList &l1,LinkedList &l2) //pass by reference
{
    LinkedList result; //unparameterized constructor
    if((l1.first)->data < (l2.first)->data)
    {
        (result.first)=(result.last)=(l1.first);
        (l1.first)=(l1.first)->next;
        (result.last)->next=NULL;
    }
    else //(l1.first)->data >= (l2.first)->data
    {
        (result.first)=(result.last)=(l2.first);
        (l2.first)=(l2.first)->next;
        (result.last)->next=NULL;
    }
    while((l1.first)!=NULL && (l2.first)!=NULL)
    {
        if((l1.first)->data < (l2.first)->data)
        {
            (result.last)->next=(l1.first);
            (result.last)=(l1.first);
            (l1.first)=(l1.first)->next;
            (result.last)->next=NULL;
        }
        else //(l1.first)->data >= (l2.first)->data
        {
            (result.last)->next=(l2.first);
            (result.last)=(l2.first);
            (l2.first)=(l2.first)->next;
            (result.last)->next=NULL;
        }
    }
    if((l1.first)!=NULL)
        (result.last)->next=(l1.first);
    else if((l2.first)!=NULL)
        (result.last)->next=(l2.first);

    return result;
}
//Copy constructor is called when a new object is created from an existing object, as a copy of the existing object.
//And assignment operator (overload) is called when an already initialized object is assigned a new value from another existing object.
int main()
{
    int A[]={2,8,10,15};
    LinkedList l1(A,4);
    l1.Insert(3,12);
    l1.Append(16);
    //l1.Reverse();
    cout<<l1.Delete(3)<<" deleted"<<endl;
    cout<<"LinkedList l1 = ";
    l1.Display();

    int B[]={3,4,7,12,14};
    LinkedList l2(B,5);
    cout<<"LinkedList l2 = ";
    l2.Display();

    LinkedList l3 = Concatenate(l1,l2);
    cout<<"LinkedList l1 = ";
    l1.Display();
    cout<<"LinkedList l2 = ";
    l2.Display();
    cout<<"LinkedList l3,concat = ";
    l3.Display();

    LinkedList l4 = MergeSortedLL(l1,l2);
    cout<<"LinkedList l1 = ";
    l1.Display();
    cout<<"LinkedList l2 = ";
    l2.Display();
    cout<<"LinkedList l3,concat = ";
    l3.Display();
    cout<<"LinkedList l4,merges = ";
    l4.Display();
    return 0;
}
