#include <iostream>
#include <utility>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

struct Node
{
    pair< pair<char,char>, int > data;
    Node* next;
};

class List
{
public:
    List();
    ~List();
    void push_back(pair< pair<char,char>, int > data);
    void push_front(pair< pair<char,char>, int > data);
    void print();
    void insert(pair< pair<char,char>, int > data, int index);
    void pop_back();
    void sort();
    void sortAlpha();
    void pop_front();
    void clear();
    pair< pair<char,char>, int >& operator [] (int index);
    int GetSize()
    {
        return size;
    }
    Node* Gethead()
    {
        return head;
    }
    int ndCount;
private:
    Node* head;
    int size;
};

List::List()
{
    head = nullptr;
    size = 0;
}

List::~List()
{
    clear();
}

void List::push_back(pair< pair<char,char>, int > data)
{
   Node* nd = new Node;
   nd->data = data;
    nd->next = nullptr;
    if (head == nullptr)
        head = nd;
    else
    {
        Node* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = nd;
    }
    size++;

}

void List::push_front(pair< pair<char,char>, int > data)
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
    while (current != nullptr)
    {
        cout << current->data.first.first << " " << current->data.first.second << " "<< current->data.second << endl;
        current = current->next;
    }
}

void List::insert(pair< pair<char,char>, int > data, int index)
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

void List::sort()
{//insertion sort
    Node* val, *b, *p, *h = nullptr;
    for (Node* i = head; i != nullptr; )
    {
        val = i;
        i = i->next;
        b = h;
        for (p = nullptr; (b != nullptr) && (val->data.second > b->data.second); )
        {
            p = b;
            b = b->next;
        }
        if (p == nullptr)
        {
            val->next = h;
            h = val;
        }
        else
            {
                val->next = b;
                p->next = val;
            }
    }
    if (h != nullptr)
        head = h;
}

pair<pair<char, char>, int> &List::operator[](int index)
{
    Node *cur = head;
    int val = 0;
    while (cur != nullptr)
    {
        if (val == index)
        {
            return cur->data;
        }
        cur = cur->next;
        val++;
    }

}

void List::sortAlpha()
{
    Node* val, *b, *p, *h = nullptr;
    for (Node* i = head; i != nullptr; )
    {
        val = i;
        i = i->next;
        b = h;
        for (p = nullptr; (b != nullptr) && (val->data.first.first > b->data.first.first); )
        {
            p = b;
            b = b->next;
        }
        if (p == nullptr)
        {
            val->next = h;
            h = val;
        }
        else
        {
            val->next = b;
            p->next = val;
        }
    }
    if (h != nullptr)
        head = h;
}

void List::pop_back()
{
    Node *cur = head;
    for (int i = 0; i < size - 2; i++)
    {
        cur = cur->next;
    }
    cur->next = nullptr;
    size--;
}

List MAinGraf;
List res_tree;
bool IfCycle = false;

int find(int x,  int *parent)
{
    int res = x;
    if (res != parent[res])
        parent[res] = find(parent[res], parent);
    return parent[res];
}

void unite (int x, int y, int *parent, int *rank)
{
    if (rank[x] > rank[y])
    {
        parent[y] = x;
    }
    else
    {
        parent[x] = y;
    }
    if (rank[x] == rank[y])
    {
        rank[y]++;
    }
}

void kraskala()
{
    int   parent1, parent2;
    int *parent = new int[MAinGraf.ndCount + 1];
    int *rank = new int[MAinGraf.ndCount + 1];
    for (int i = 0; i <= MAinGraf.ndCount; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
    Node *a;
    a = MAinGraf.Gethead();
    int res_sum = 0;
    while( a != nullptr)
    {
        parent1 = find((int) a->data.first.first -'A', parent);
        parent2 = find((int)a->data.first.second-'A', parent);
        if (parent1 != parent2)
        {
            res_sum += a->data.second;
            res_tree.push_back(a->data);
            unite(parent1, parent2, parent, rank);
        }
        a = a->next;
    }
    res_tree.sortAlpha();
    a = res_tree.Gethead();
    while (a != nullptr)
    {
        cout << a->data.first.first << ' ' << a->data.first.second << endl;
        a = a->next;
    }
    cout << res_sum;

}

void input()
{
    pair< pair<char,char>, int > data;
    ifstream file;
    file.open(R"(C:\Users\andy_\CLionProjects\Kraskala\in.txt)");
    string str, ndCount;
    int val;
    while (!file.eof())
    {
        getline(file,str);
        string str_num;
        for (int i = 0; i < str.length(); ++i)
        {
            if (str[i] >= '0' && str[i] <= '9')
            {
                str_num+=str[i];
            }
        }
        ndCount+= str[0];
        ndCount+=str[2];

        val = atoi(str_num.c_str());
        pair< pair<char,char>, int > data = make_pair(make_pair(min(str[0],str[2]),max(str[0],str[2])),val);
        MAinGraf.push_back(data);
    }
    sort(begin(ndCount),end(ndCount));
    auto result =  unique(begin(ndCount),end(ndCount));
    ndCount.erase(result,end(ndCount));
    MAinGraf.ndCount = ndCount.length();

    MAinGraf.sort();
    file.close();
    kraskala();

}

int main()
{
   input();
    return 0;
}
