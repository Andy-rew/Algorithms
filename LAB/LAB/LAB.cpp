
#include <iostream>
#include <cstdlib>

using namespace std;
//динамический массив

class Array
{
public:
    Array();
    ~Array();
    void SetSize(int size1);
    void Insert(int data, int pos);
    int GetSize();
    void input();
    void printArr();
    int GetEl(int pos);
   
private:
    int size;
    int* mas = new int[size];

};

Array::Array()
{
    size = 2;
}

Array::~Array()
{
    delete[] mas;
}

void Array::SetSize(int size1)
{
    int OldSize = size;
    while (size < size1)
    {
        size *= 2;
    }
    while (size > size1)
    {
        if (size / 2 >= size1)
            size /= 2;
        else
            break;
    }
    if (OldSize < size1)
    {
        int* mas1 = new int[size];
        for (int i = 0; i < OldSize; ++i)
        {
            mas1[i] = mas[i];
        }
        mas = mas1;
    }
    else
    {
        int* mas1 = new int[size1];
        for (int i = 0; i < size1; ++i)
        {
            mas1[i] = mas[i];
        }
        mas = mas1;
        size = size1;
    }
}

void Array::Insert(int data, int pos)
{
    if (pos >= size)
    {
        if (pos == size)
            SetSize(pos + 1);
        else
            SetSize(pos);
        mas[pos] = data;
    }
    else
    {
        mas[pos] = data;
    }
}

int Array::GetSize()
{
    return size;
}

void Array::input()
{
    for (int i = 0; i < size; ++i)
    {
        cin >> mas[i];
    }
}

void Array::printArr()
{
    for (int i = 0; i < size; ++i)
    {
        cout << mas[i] << ' ';
    }
    cout << endl;
}

int Array::GetEl(int pos)
{
    if (pos < size)
        return mas[pos];
    else
        cout << endl << "Error" << endl;
}



void ArrayList()
{
    /*Array mas;
    mas.input();
    mas.printArr();
    mas.Insert(100, 2);
    mas.printArr();
    mas.Insert(200, 3);
    mas.Insert(200, 4);
    mas.Insert(200, 5);
    mas.Insert(200, 6);
    mas.Insert(200, 7);
    mas.Insert(999, 2);
    mas.SetSize(5);
    mas.printArr();*/
}
//односвязный список
struct Node
{
    int data;
    Node* next;
};

class List
{
public:
	List();
	~List();
    void push_back(int data);
    void push_front(int data);
    void print();
    void insert(int data, int index);
    void pop_front();
    void clear();
    int GetSize()
    {
        return size;
    }
private:
    Node* head;
    int size;
};

List::List()
{
    head = NULL;
    size = 0;
}

List::~List()
{
    clear();
}

void List::push_back(int data)
{
    Node* nd = new Node;
    nd->data = data;
    nd->next = NULL;
    if (head == NULL)
        head = nd;
    else
    {
        Node* current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = nd;
    }
    size++;
}

void List::push_front(int data)
{
    Node* nd = new Node;
    nd->data = data;
    nd->next = head;
    head = nd;
    size++;
}

void List::print()
{
    Node* current = head;
    while (current != NULL)
    {
        cout << current->data << endl;
        current = current->next;
    }
}

void List::insert(int data, int index)
{
    if (index == 0)
    {
        push_front(data);
    }
    else
    {
        Node* nd = new Node;
        Node* current = head;
        nd->data = data;
        for (int i = 0; i < index - 1; ++i)
        {
            current = current->next;
        }
        nd->next = current->next;
        current->next = nd;
        size++;
    }
}

void List::pop_front()
{
    Node* tmp = head;
    head = head->next;
    size--;
    delete tmp;
}

void List::clear()
{
    while (size != 0)
    {
        pop_front();
    }
}
//стек - урезанный список. Операции: добавление элемента в начало списка, удаление первого элемента, посмотреть первый элемент, проверить на пустоту

int main()
{
    ArrayList();
	system("pause");
	return 0;
}

