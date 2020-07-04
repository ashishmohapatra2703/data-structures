#include <iostream>
using namespace std;
class Node
{
    public:
        int data;
        Node* next;
};
class Stack
{
    private:
        Node* top;
    public:
        Stack()
        {
            top = nullptr;
        }
        void push(int x);
        int pop();
        int peek(int index);
        int isEmpty();
        int isFull();
        int stackTop();
        void display();
        ~Stack()
        {
            Node *p = top;
            while(top != NULL)
            {
                top = top->next;
                delete p;
                p = top;
            }
        }
};

void Stack::push(int x)
{
    Node *t=new Node;
    if(t == nullptr) // no node is created => t is NULL
        cout << "Stack Overflow!" << endl; // heap memory is full
    else
    {
        t->data = x;
        t->next = top;
        top = t;
    }
}
int Stack::pop()
{
    int x = -1;
    if (top == nullptr)
        cout << "Stack Underflow!" << endl;
    else
    {
        Node *p = top;
        top = top->next;
        x = p->data;
        delete p;
    }
    return x;
}
int Stack::peek(int index)
{
    if (isEmpty())
        return -1;
    else
    {
        Node *p = top;
        for (int i=0;  p!=nullptr && i<index-1; i++)
        {
            p = p->next;
        }
        if (p != nullptr) //valid position
            return p->data;
        else
            return -1; //out of scope position
    }
}
int Stack::isFull()
{
    Node *t = new Node;
    if(t==nullptr) // no node is created => heap memory is full => t is NULL
        return 1;
    else
        return 0;
    delete t; //new node deleted
}
int Stack::isEmpty()
{
    if(top==nullptr)
        return 1;
    else
        return 0;
}
int Stack::stackTop()
{
    if (top!=nullptr)
    {
        return top->data; // top-most Node value
    }
    return -1;
}
void Stack::display()
{
    Node *p=top;
    while(p!=0)
    {
        cout<<" | "<<p->data<<" | "<<endl<<" ----- "<<endl;
        p=p->next;
    }
}

int main()
{
    int A[] = {1, 3, 5, 7, 9};
    Stack stk;
    // Populate stack
    for (int i=0; i<sizeof(A)/sizeof(A[0]); i++)
    {
        stk.push(A[i]); // LL size is unlimited unless & until heap memory is full
    }
    //push elements as many as we can , LL can grow (dynamic size)

    // Display stack;
    cout << "Stack: " << endl;
    stk.display();

    cout << "Stack peek at 3rd: " << stk.peek(3) << endl;
    cout << "Stack peek at 10th: " << stk.peek(10) << endl;
    cout << "Stack top: " << stk.stackTop() << endl;

    cout << "Stack full: " << stk.isFull() << endl;
    cout << "Stack empty: " << stk.isEmpty() << endl;

    // Pop out elements from stack
    cout << "Popped: " << flush;
    for (int i=0; i<sizeof(A)/sizeof(A[0]); i++)
    {
        cout << stk.pop() << ", " << flush;
    }
    cout << endl;

    // Underflow
    cout << stk.pop() << endl;

    return 0;
}
