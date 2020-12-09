#include <iostream>
#include <utility>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> parent;

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
    void sort();
    void pop_front();
    void clear();
    int GetSize()
    {
        return size;
    }
    Node* Gethead()
    {
        return head;
    }
    int EdgeCount;
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



List MAinGraf;

int find(int x)
{
    int res = x;
    while (parent[res] > 0)
    {
        res = parent[res];
    }
    return res;
}

void unite (int x, int y)
{
    int sum = parent[x] + parent[y];
    if (parent[x] >= sum)
    {
        parent[x] = y;
        parent[y] = sum;
    }
    else
        {
            parent[y] = x;
            parent[x] = sum;
        }
}
void kraskala()
{
    int size_res = 1, inCount = 1, parent1, parent2;
    vector<pair<char,char>> res_tree;
    parent.resize(MAinGraf.GetSize());
    for (int i = 0; i < MAinGraf.GetSize(); i++)
    {
        parent[i] = -1;
    }
    Node *a;
    a = MAinGraf.Gethead();
    int res_sum = 0;
    while(size_res <= MAinGraf.GetSize() && inCount <= MAinGraf.EdgeCount - 1)
    {
        parent1 = find(a->data.first.first);
        parent2 = find(a->data.first.second);
        if (parent1 != parent2)
        {
            res_tree.push_back(a->data.first);
            res_sum+=a->data.second;
            inCount++;
            unite(parent1,parent2);
        }
        a = a->next;
        size_res++;
    }
    sort(begin(res_tree),end(res_tree));
    for(int i = 0; i < res_tree.size(); i++)
    {
        cout << res_tree[i].first << ' ' << res_tree[i].second << endl;
    }
    cout << res_sum;
}

void input()
{

    pair< pair<char,char>, int > data;
    ifstream file(R"(C:\Users\andy_\CLionProjects\Kraskala\in.txt)");
    string str, EdgeCount;
    int val;
    while (!file.eof())
    {
        getline(file,str);
        string str_num;
        for (int i = 0; i < str.size(); ++i)
        {
            if (str[i] >= '0' && str[i] <= '9')
            {
                str_num+=str[i];
            }
        }
        EdgeCount+=str[0];
        EdgeCount+=str[2];
        val = atoi(str_num.c_str());
        pair< pair<char,char>, int > data = make_pair(make_pair(str[0],str[2]),val);
        MAinGraf.push_back(data);
    }
    sort(begin(EdgeCount),end(EdgeCount));
    auto result =  unique(begin(EdgeCount),end(EdgeCount));
    EdgeCount.erase(result,end(EdgeCount));
    MAinGraf.EdgeCount = EdgeCount.size();
    MAinGraf.EdgeCount;
    MAinGraf.sort();
    kraskala();
    file.close();
}

int main()
{
   input();
    return 0;
}
