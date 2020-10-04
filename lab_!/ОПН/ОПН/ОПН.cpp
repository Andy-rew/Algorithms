

#include <iostream>
#include <conio.h>

using namespace std;

struct Node
{
    char data;
    Node* next;
};

class List
{
public:
    List();
    ~List();
    void push_front(char data);
    void pop_front();
    char peek();
    void print();
    void clear();
    bool ifempty();
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

void List::push_front(char data)
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

void List::pop_front()
{
    Node* tmp = head;
    head = head->next;
    size--;
    delete tmp;
}

char List::peek()
{   
    if (head != NULL)
        return head->data;
}

void List::clear()
{
    while (size != 0)
    {
        pop_front();
    }
}
bool List::ifempty()
{
    if (head == NULL)
         return true;
    else 
        return false;
}
int main()
{
    List stc;
    char a;
    char* mas = (char*)malloc(sizeof(char));
    int i = 0, ifFalse = 0;
    bool ifstc = false;
    do
    {
        a = _getch();
        if (a >= '0' && a <= '9' || a == '!')
        {
            cout << a;
            if (ifstc == false && stc.ifempty() == false)
                ifFalse = 1;
            mas[i] = a;
            mas = (char*) realloc(mas, (i + 2 + ifFalse) * sizeof(char));
            if (ifFalse == 1)
            {
                ifFalse = 0;
                mas[i + 1] = stc.peek();
                stc.pop_front();
                ++i;
            }
            ++i;
            if (ifstc == true)
                ifstc = false;
        }
        if (a == '+' || a == '-' || a == '*' || a == '/')
        {
            cout << a;
            stc.push_front(a);
            ifstc = true;
        }
    } while (a != 13);
    cout << endl << mas;
    system("pause");
    return 0;
}

