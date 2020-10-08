

#include <iostream>
#include <conio.h>
#include <string>

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
    string stIn;
    string stOut;
    getline(cin, stIn);
    for (int i = 0; i < stIn.size(); i++)
    {
        switch (stIn[i])
        {
        case '^': // высокий
            stc.push_front(stIn[i]);
            break;
        case '*':   //средний
        case '/':
            while ((stc.peek() == '^' || stc.peek() == '*' || stc.peek() == '/') && stc.ifempty() == false)
            {
                stOut += stc.peek();
                stc.pop_front();
            }
            stc.push_front(stIn[i]);
            break;
        case '+':   //низкий
        case '-':
            while ((stc.peek() == '^' || stc.peek() == '*' || stc.peek() == '/' || stc.peek() == '+' || stc.peek() == '-') && stc.ifempty() == false)
            {
                stOut += stc.peek();
                stc.pop_front();
            }
            stc.push_front(stIn[i]);
            break;
        case '(': //самый низкий
            stc.push_front(stIn[i]);
            break;
        case ')':
            while (stc.peek() != '(' && stc.ifempty() == false)
            {
                stOut += stc.peek();
                stc.pop_front();
            }
            stc.pop_front();
            break;
        default:
            stOut += stIn[i];
            break;
        }
        while (i == stIn.size() - 1 && stc.ifempty() == false)
        {
            
            stOut += stc.peek();
            stc.pop_front();
        }
    }
    cout << endl << stOut << endl;
    system("pause");
    return 0;
}

