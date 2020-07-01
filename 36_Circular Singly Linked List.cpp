#include <iostream>
using namespace std;
class Node
{
    public:
        int data;
        Node* next;
};
class CircularLinkedList
{
    private:
        Node* head;
    public:
        CircularLinkedList(int A[], int n) //constructor
        {
            Node* t; //temp node pointer
            Node* tail; //last node pointer

            head = new Node;
            head->data = A[0];
            head->next = head; //circular
            tail = head;
            for(int i=1; i<n; i++)
            {
                t = new Node;
                t->data = A[i];
                t->next = tail->next; //all ongoing node's link point to pioneer head
                tail->next = t;
                tail = t;
            }
        }
        void Display();
        void recursiveDisplay1(Node* p);
        void recursiveDisplay2(Node *p);
        int Length();
        void Insert(int index,int x);
        int Delete(int pos);
        Node* getHead()
        {
            return head;
        }
        ~CircularLinkedList() //destructor
        {
            Node *p=head;
            while((p->next)!=head)
            {
                p=p->next;
            } //now p is pointing to last node
            while(p!=head)
            {
                p->next=head->next;
                delete head;
                head=p->next; //head shifting from left to right
            }
            if(p==head) //one node remaining(rightmost) or only one node present case
            {
                delete head;
                head=nullptr;
                p=nullptr;
            }
        }
};

void CircularLinkedList::Display()
{
    Node *p=head; //1st node
    do
    {
        cout<<p->data<<flush;
        p=p->next;
        if(p!=head) //no -> at the last iteration for last node
            cout<<" -> "<<flush;
    }while (p!=head);//loop ends when 2nd time p==head
}
void CircularLinkedList::recursiveDisplay1(Node *p)
{
    static int flag=0;
    if (p!=head || flag==0) //display the first head node data
    {
        flag=1;
        cout<<p->data<<" -> "<<flush;
        recursiveDisplay1(p->next);
    }
    flag=0; //so that if we call display function once again, it should work with flag=0. (as flag is static)
}
void CircularLinkedList::recursiveDisplay2(Node *p)
{
    cout<<p->data<<" -> "<<flush; //first print the current node data
    if((p->next)!=head)   //then check for next node
    {
        return recursiveDisplay2(p->next);
    }
}
//when a program writes output, it is stored in buffer( temp memory area)
//flush will force it to be sent it to the destination. Display screen.
//endl will take new line and flush.
int CircularLinkedList::Length()
{
    Node *p=head;
    int len=0;
    do
    {
        len++;
        p=p->next;
    }while(p!=head);
    return len;
}
void CircularLinkedList::Insert(int index,int x)
{
    Node *p=head;
    Node *t=new Node;
    t->data=x;
    t->next=NULL;

    if(index < 0 || index > Length()) //not valid index
        return;
    if(index==0) //inserting before first node
    {
        if(head==NULL) //empty LL
        {
            head=t;
            head->next=head; //circular
        }
        else//head!=NULL i.e, head is pointing on some node
        {
            while(p->next != head)
            {
                p=p->next;
            } //now p is pointing to last node
            p->next=t;
            t->next=head;
            head=t; //change of head position
        }
    }
    else //at index after first node
    {
        for(int i=0; i<index-1; i++)
        {
            p=p->next;
        }
        t->next=p->next;
        p->next=t;
    }
}
int CircularLinkedList::Delete(int pos)
{
    Node *p=head;
    Node *q=NULL;

    int x=-1;
    if(pos < 1 || pos > Length())
        return -1;
    if(pos==1)
    {
        x=head->data; //to be returned
        while((p->next) != head)
        {
            p=p->next;
        }    //now p is pointing to last node
        if(p==head) //only 1 node
        {
            delete head;
            head=NULL;
        }
        else
        {
            p->next=head->next; //last node circularly connected to 2nd node
            delete head;
            head=p->next; //2nd position become head node
        }

    }
    else //after first node
    {
        for(int i=0; i<pos-1 ; i++)
        {
            q=p;//q follows p
            p=p->next;
        } //now p is pointing to "pos" node
        q->next=p->next;
        x=p->data; //to be returned
        delete p;
    }
    return x;
}
int main() {

    int A[] = {1, 3, 5, 7, 9};
    CircularLinkedList c1(A, 5); //or use sizeof(A)/sizeof(A[0])

    c1.Insert(5,15);
    c1.Insert(0,10);
    cout<<c1.Delete(1)<<" deleted"<<endl;
    c1.Display();
    cout<<endl;
    c1.recursiveDisplay1(c1.getHead());
    cout<<endl;
    c1.recursiveDisplay2(c1.getHead());
    cout<<endl;
    cout<<"Length = "<<c1.Length()<<endl;
    cout<<"Head data is = "<<(c1.getHead())->data<<endl;
    return 0;
}
