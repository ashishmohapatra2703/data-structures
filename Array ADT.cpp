#include <iostream>
using namespace std;

class Array
{
    private:
        int *A; // An pointer holding the heap array of ints (size defined at initialization)
        int size;// Max number of elements array can contain
	    int length;	// Number of populated elements in array
        void Swap(int *,int *);//local function USED in the public member functions of the class & useless to call from object(so private)
    public:
        Array(int sz=10)
        {
            size=sz;
            length=0;
            A=new int[size];
        }
        ~Array()
        {
            delete []A;
        }
        void Display();
        void Append(int x);
        void Insert(int index,int x);
        int Delete(int index);
        int LinearSearch(int key);
        int BinarySearch(int key);
        int Get(int index);
        void Set(int index,int x);
        int Max();
        int Min();
        int Sum();
        float Avg();
        void Reverse();
        void Reverse2();
        void InsertSort(int x);
        int isSorted();
        void Rearrange();
        friend Array* MergeSortedArrays(Array *arr1,Array *arr2);
        friend Array* UnionSorted(Array *arr1,Array *arr2);
        friend Array* IntersectionSorted(Array *arr1,Array *arr2);
        friend Array* DifferenceSorted(Array *arr1,Array *arr2);
};

void Array::Swap(int* x, int* y)
{
    int temp = *x;
	*x = *y;
	*y = temp;
}
void Array::Display()
{
    cout<<"\nElements of are :- ";
    for(int i=0;i<length;i++)
        cout<<A[i]<<" , ";
}
void Array::Append(int x)
{
    if (size <= length)
        cout<<"Can't append any more elements. Array is full!\n";
    else
        A[length++]=x;
}
void Array::Insert(int index,int x)
{
    if (size <= length)
		cout<<"Can't insert any more elements. Array is full!\n";
	else if (index > length)
		cout<<"Can't insert element beyond current last element (length is "<<length<<", requested index is "<<index<<endl;
    else if (index < 0)
		cout<<"Can't insert element at negative index "<<index<<endl;
	else
    {
		cout<<"Inserting value "<<x<<" at index "<<index<< endl;
        if(index>=0 && index <=length)  //index <= length bcoz of insertion in next to the 'last occupied element'
        {
            for(int i=length;i>index;i--)
            {
                A[i]=A[i-1];
            }
            A[index]=x;
            length++;
        }
    }
}
void Array::InsertSort(int x) //Insert an element in it's ordered place in a sorted array
{
    int i=length-1;
    if(length==size)
    {
        cout<<"Can not be inserted as Length=size , No free space in array";
        return;
    }
    while(i>=0 && A[i]>x)
    {
        A[i+1]= A[i];
        i--;
    }
    A[i+1]=x;
    length++;
}
int Array::Delete(int index)
{
    if(index>=0 && index<length)   //index < length
    {
        int x=A[index];
        for(int i=index;i<length-1;i++)
        {
            A[i]=A[i+1];
        }
        length--;
        cout<<"\nThe deleted element from given index is :- "<<x;
    }
    cout<<"Index Out of Range";
}
int Array::LinearSearch(int key)
{
    for(int i=0;i<length;i++)
    {
        if(A[i]==key)
        {
            Swap(&A[i],&A[i-1]); //Pass by Address
            return (i-1);
        }
    }
    return -1;
}
int Array::BinarySearch(int key)
{
    int l=0,h=length-1;
    while(l<=h)
    {
        int mid=(l+h)/2;
        if(key==A[mid])
        {
            return mid;
        }
        else if(key<A[mid])
            h=mid-1;
        else
            l=mid+1;
    }
    return -1;
}
int Array::Get(int index)
{
    if(index>=0 && index<length)
    {
        return A[index];
    }
    cout<<"Index out of range";
}
void Array::Set(int index,int x)
{
    if(index>=0 && index< length)
    {
        A[index]=x;
    }
}
int Array::Max()
{
    int max=A[0];
    for(int i=1;i<length;i++)
    {
        if(A[i]>max)
            max=A[i];
    }
    return max;
}
int Array::Min()
{
    int min=A[0];
    for(int i=1;i<length;i++)
    {
        if(A[i]<min)
            min=A[i];
    }
    return min;
}
int Array::Sum()
{
    int s=0;
    for(int i=0;i<length;i++)
    {
        s+=A[i];
    }
    return s;
}
float Array::Avg()
{
    return (float)Sum()/length;
}
void Array::Reverse()
{
    Array temp(length); //cannot convert 'Array*' to 'int*' in initialization DOUBT

    int i,j;
    for(i=length-1,j=0;  i>=0;  i--,j++)
        temp.A[j]=A[i];
    for(i=0;i<length;i++)
        A[i]=temp.A[i];
}
void Array::Reverse2()
{
    int i,j;
    for(i=0,j=length-1;  i<j;  i++,j--)
    {
        Swap(& A[i],& A[j]);
    }
}
int Array::isSorted()
{
    for(int i=0;i<length-1;i++) // i<length-1 up to second last element
    {
        if(A[i]>A[i+1])
            cout<<"false";
    }
    cout<<"true";
}
void Array::Rearrange()
{
    int i=0;
    int j= length-1;
    while(i<j)
    {
        while( A[i]<0)
            i++;
        while( A[j]>=0)
            j--;
        if(i<j)
            Swap(& A[i],& A[j]);
    }
}
Array* MergeSortedArrays(Array *arr1,Array *arr2) //its return type should be Array *
{
    int i=0,j=0,k=0;
    Array *result= new Array(arr1->length+arr2->length); //size

    while(i<arr1->length && j<arr2->length)
    {
        if(arr1->A[i] <  arr2->A[j])
            result->A[k++]=arr1->A[i++];
        else
            result->A[k++]=arr2->A[j++];
    }
    for( ; i<arr1->length; i++)
        result->A[k++]=arr1->A[i];
    for( ; j<arr2->length; j++)
        result->A[k++]=arr2->A[j];

    result->length=k;
    return result;       //as it is returning pointer of type Array
}
Array* UnionSorted(Array *arr1,Array *arr2) //call by address
{
    int i=0,j=0,k=0;
    Array *result= new Array(arr1->length+arr2->length);

    while(i<arr1->length && j<arr2->length)
    {
        if(arr1->A[i] <  arr2->A[j])
            result->A[k++]=arr1->A[i++];
        else if(arr1->A[i] >  arr2->A[j])
            result->A[k++]=arr2->A[j++];
        else
        {
            result->A[k++]=arr1->A[i++];
            j++;
        }
    }
    for( ; i<arr1->length; i++)
        result->A[k++]=arr1->A[i];
    for( ; j<arr2->length; j++)
        result->A[k++]=arr2->A[j];

    result->length=k;
    return result;
}
Array* IntersectionSorted(Array *arr1,Array *arr2)
{
    int i=0,j=0,k=0;
    Array *result= new Array(arr1->length+arr2->length);

    while(i<arr1->length && j<arr2->length)
    {
        if(arr1->A[i] <  arr2->A[j])
            i++;
        else if(arr1->A[i] >  arr2->A[j])
            j++;
        else
        {
            result->A[k++]=arr1->A[i++];
            j++;
        }
    }
    result->length=k;
    return result;
}
Array* DifferenceSorted(Array *arr1,Array *arr2)
{
    int i=0,j=0,k=0;
    Array *result= new Array(arr1->length+arr2->length);

    while(i<arr1->length && j<arr2->length)
    {
        if(arr1->A[i] <  arr2->A[j])
            result->A[k++]=arr1->A[i++];
        else if(arr1->A[i] >  arr2->A[j])
            j++;
        else
        {
            i++;
            j++;
        }
    }
    for( ; i<arr1->length; i++)
        result->A[k++]=arr1->A[i];

    result->length=k;
    return result;
}



int main()
{
    int sz;
    cout<<"Enter Size of Array";
    cin>>sz;

    Array *arr1; //a pointer of type Array
    arr1=new Array(sz); //The data type of pointer and the variable must match
                        //Array is a class name . ( ) are used for calling it’s constructor.

    // OR use directly  Array arr1(sz);

    Array *arr2 = new Array(sz);
    Array *arr3;

    int ch;
    int x,index;
    do
    {
        cout << "Menu\n";
        cout << "1. Append\n";
		cout << "2. Insert\n";
		cout << "3. Delete\n";
		cout << "4. Linear Search\n";
		cout << "5. Binary Search\n";
		cout << "6. Get\n";
		cout << "7. Set\n";
		cout << "8. Max\n";
		cout << "9. Min\n";
		cout << "10. Sum\n";
		cout << "11. Average\n";
		cout << "12. Reverse\n";
		cout << "13. Check array is Sorted or not\n";
		cout << "14. Insert in Sorted array\n";
		cout << "15. Rearrange\n";
		cout << "16. MergeSortedArrays\n";
		cout << "17. UnionSorted\n";
		cout << "18. IntersectionSorted\n";
		cout << "19. DifferenceSorted\n";
		cout << "20. Display\n";
		cout << "21. Exit\n\n";

        cout<<"Enter your choice :- ";
        cin>>ch;
        switch (ch)
        {
            case 1:
                cout<<"Enter the element :- ";
                cin>>x;
                arr1->Append(x);
                break;
            case 2:
                cout<<"Enter an element and then the index :- ";
                cin>>x>>index;
                arr1->Insert(index, x);
                arr1->Display();
                break;
            case 3:
                cout<<"Enter index from which element is to be deleted :- ";
                cin>>index;
                arr1->Delete(index);
                break;
            case 4:
                cout<<"Enter element/key to Linear search :- ";
                cin>>x;
                index = arr1->LinearSearch(x);

                if (index > -1)
                    cout<<"Element found at index "<<index<<endl;
                else
                    cout<<"Element not found"<<endl;
                break;
            case 5:
                cout<<"Enter element/key to Binary Search (iff Sorted Array):- ";
                cin>>x;
                index = arr1->BinarySearch(x);

                if (index > -1)
                    cout<<"Element found at index "<<index<<endl;
                else
                    cout<<"Element not found"<<endl;
                break;
            case 6:
                cout<<"Enter the index :- ";
                cin>>index;
                cout<<"\nThe value at given index is = "<<arr1->Get(index);
                break;
            case 7:
                cout<<"Enter an element to be set/replaced and then the index :- ";
                cin>>x>>index;
                arr1->Set(index, x);
                break;
            case 8:
                cout<<"The 'max element' value is :- "<<arr1->Max();
                break;
            case 9:
                cout<<"The 'min element' value is :- "<<arr1->Min();
                break;
            case 10:
                cout<<"The Sum of all elements in the array is :- "<<arr1->Sum();
                break;
            case 11:
                cout<<"The Mean of all elements in the array is :- "<<arr1->Avg();
                break;
            case 12:
                arr1->Reverse();
                cout<<"\nOR by 2nd Method"<<endl;
                arr1->Reverse2();
                arr1->Display();
                break;
            case 13:
                arr1->isSorted();
            case 14:
                cout<<"Enter the element :- ";
                cin>>x;
                arr1->InsertSort(x);
                arr1->Display();
                break;
            case 15:
                arr1->Rearrange();
                arr1->Display();
                break;
            case 16:
                arr3= MergeSortedArrays(arr1,arr2); //function is taking address of type Array
                arr3->Display();
                break;
            case 17:
                arr3= UnionSorted(arr1,arr2); //as Already arr1 is a pointer => NO NEED OF &  ,i.e., for call by reference
                arr3->Display();
                break;
            case 18:
                arr3= IntersectionSorted(arr1,arr2);
                arr3->Display();
                break;
            case 19:
                arr3 = DifferenceSorted(arr1,arr2);
                arr3->Display();
                break;
            case 20:
                cout<<"\nFor arr1";
                arr1->Display();
                cout<<"\nFor arr2";
                arr2->Display();
                break;
            case 21:
                break;
		}
	} while (ch < 21);

    return 0;
}
