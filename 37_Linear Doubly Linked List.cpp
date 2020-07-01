#include <iostream>
using namespace std;
class Node
{
    public:
        Node* prev;
        int data;
        Node* next;
};
class DoublyLinkedList
{
    private:
        Node* head;
    public:
        DoublyLinkedList()
        {
            head = new Node;
            head->prev = nullptr;
            head->data = 0;
            head->next = nullptr;
        }
        DoublyLinkedList(int A[], int n)
        {
            head = new Node;
            head->prev = nullptr;
            head->data = A[0];
            head->next = nullptr;
            Node *tail = head;

            for(int i=1; i<n; i++)
            {
                Node *t = new Node;
                t->prev = tail;
                t->data = A[i];
                t->next = NULL;
                tail->next = t;
                tail = t;
            }
        }
        void Display();
        int Length();
        void Insert(int index, int x);
        int Delete(int index);
        void Reverse();
        ~DoublyLinkedList()
        {
            Node *p=head;
            while(head!=NULL)
            {
                head = head->next;
                delete p;
                p = head;
            }
        }
};

void DoublyLinkedList::Display()
{
    Node *p=head;
    while(p!=NULL)
    {
        cout<<p->data<<flush;
        p=p->next;
        if(p!=NULL) //no <-> at the last iteration for last node
            cout<<" <-> "<<flush;
    }
    cout<<endl;
}
int DoublyLinkedList::Length()
{
    int length=0;
    Node *p=head;
    while(p!=NULL)
    {
        length++;
        p=p->next;
    }
    return length;
}
void DoublyLinkedList::Insert(int index, int x)
{
    Node *p = head;
    Node *t = new Node;
    t->data = x;

    if (index < 0 || index > Length())
        return;
    if (index == 0) //inserting before first node
    {
        t->prev = nullptr;
        t->next = head;
        head->prev = t;
        head = t;
    }
    else //at index after first node
    {
        for(int i=0; i<index-1; i++)
        {
            p=p->next;
        }
        t->prev = p;
        t->next = p->next;
        if(p->next)
        {
            (p->next)->prev = t; //((p->next)->prev) exists if (p->next)!=NULL
        }
        p->next = t;
    }
}
int DoublyLinkedList::Delete(int index) //position
{
    int x = -1;
    Node* p = head;

    if (index < 0 || index > Length())
        return x;
    if (index == 1) //1st node
    {
        head=head->next; ////2nd position become head node
        if(head) //check if after shifting, head is pointing on any node or not !
        {
            head->prev = nullptr; //head->prev exists if head!=NULL
        }
        x=p->data; //to be returned
        delete p;
    }
    else
    {
        for(int i=0; i<index-1; i++)
        {
            p=p->next;
        }
        (p->prev)->next = p->next;
        if(p->next)
        {
            (p->next)->prev = p->prev; // ((p->next)->prev) exists if (p->next)!=NULL
        }
        x=p->data;
        delete p; //deletion done by jumping links from its before node to its after node
    }
    return x;
}

void DoublyLinkedList::Reverse()
{
    Node *p = head;
    Node *temp;
    while(p != NULL)
    {
        temp = p->next;
        p->next = p->prev;
        p->prev = temp; //**swapping the links of p->prev and p->next at each node**

        p = p->prev; //traverse
        // Need to check the following condition again WHEN REACHED ON LAST NODE
        if (p->next==NULL)
        {
            p->next = p->prev; //**swapping the links of p->prev and p->next**
            p->prev = NULL; //last node become the first node
            head = p;
            break;  //this was work for last node,, do and exit/break;
        }
    }
}
//The condition if(p!=NULL && p->prev==NULL) checks whether the node can be the first node.
//If the node is to be the first node, it should have the next node.
//if(p == NULL)  the node can't be the first node. If we don't swap 'p->next' and 'p->prev', we need not check 'p' again.
//In that case, while(p != NULL) is enough. After the swap,
//however, the 'p' pointer points a different node from the previous 'p'.
//So we need to check again if it is a valid(not NULL) pointer.

int main()
{
    int A[] {1, 3, 5, 7, 9};
    DoublyLinkedList dll(A, sizeof(A)/sizeof(A[0]));
    cout << "Length: " << dll.Length() << endl;

    dll.Insert(0, 11);
    dll.Insert(6, 13);
    dll.Display();

    cout<<dll.Delete(1)<<" is deleted "<<endl;
    cout<<dll.Delete(6)<<" is deleted "<<endl;
    dll.Display();

    dll.Reverse();
    dll.Display();

    return 0;
}
