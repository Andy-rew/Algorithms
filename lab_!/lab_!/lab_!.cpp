
#include <iostream>

using namespace std;
//динамический массив
void ArrayList()
{
    int n;
    cin >> n;
    int* mas = new int [n]; 
    delete[] mas;
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
//стек - урезанный список. Операции: добавление элемента в начало списка, удаление первого элемента

int main()
{
   
	system("pause");
	return 0;
}

