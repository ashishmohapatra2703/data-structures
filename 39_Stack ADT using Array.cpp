#include <iostream>
using namespace std;
class Stack
{
    private:
        int size;
        int top;
        int* S;
    public:
        Stack(int size)
        {
            this->size = size;
            top = -1; //no element initially
            S = new int[size]; //empty array of length as size
        }
        void push(int x);
        int pop();
        int peek(int index);
        int isEmpty();
        int isFull();
        void display();
        int stackTop();
        ~Stack()
        {
            delete[] S;
        }
};

void Stack::push(int x)
{
    if(isFull())
        cout<<" Stack Overflow! "<<endl;
    else
    {
        top++;
        S[top] = x;
    }
}
int Stack::pop()
{
    int x = -1;
    if (isEmpty())
        cout<<" Stack Underflow! "<<endl;
    else
    {
        x = S[top];
        top--;
    }
    return x;
}
int Stack::peek(int index) //position as :- topmost being 1
{
    int x = -1;
    if (top-index+1 < 0 || top-index+1 == size) //top-index+1 is the actual indexing of the stack array
    {
        cout<<" Invalid position! "<<endl;
    }
    else
    {
        x = S[top-index+1];
    }
    return x;
}
int Stack::isEmpty()
{
    if(top == -1)
    {
        return 1;
    }
    return 0;
}
int Stack::isFull()
{
    if (top == size-1)
    {
        return 1;
    }
    return 0;
}
void Stack::display()
{
    for(int i=top; i>=0; i--)
    {
        cout<<" | "<<S[i]<<" | "<<endl<<" ----- "<<endl;
    }
}
int Stack::stackTop()
{
    if(isEmpty())
    {
        return -1;
    }
    return S[top]; //top-most element value
}

int main()
{

    int A[] = {1, 2, 5, 7, 9};
    Stack stk(sizeof(A)/sizeof(A[0]));

    // Populate stack with array elements
    for (int i=0; i<sizeof(A)/sizeof(A[0]); i++)
    {
        stk.push(A[i]);
    }

    stk.push(11);   // Stack Overflow!
    cout << "Stack full: " << stk.isFull() << endl;

    // Display stack;
    cout << "Stack: " << endl;
    stk.display();

    // Peek
    cout << "Peek at 1th: " << stk.peek(1) << endl;
    cout << "Peek at 0th: " << stk.peek(0) << endl;
    cout << "Peek at 3rd: " << stk.peek(3) << endl;
    cout << "Peek at 10th: " << stk.peek(10) << endl;

    // Top element
    cout << "Top element: " << stk.stackTop() << endl;

    // Pop out elements from stack
    cout << "Popped out elements: " << endl;
    for (int i=0; i<sizeof(A)/sizeof(A[0]); i++)
    {
        cout << stk.pop() << ", " << flush;
    }
    cout << endl;
    stk.pop(); // Stack Underflow!

    cout << "Stack empty: " << stk.isEmpty() << endl;

    return 0;
}
