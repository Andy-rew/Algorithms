#include <iostream>
#include <string>
using namespace std;

template <typename type>
struct node
{
    type key;
    struct node<type> *left;
    struct node<type> *right;
    struct node<type> *parent;
    int balance; // -1 0 1
    node(type x)
    {
        this->key = x;
        this->right = nullptr;
        this->left = nullptr;
        this->balance = 1;
        this->parent = nullptr;
    }
};


template <typename type>
class tree
{
public:
    tree();
    ~tree();
    bool insert (type val);
    bool find(type val);
    bool remove(type val);

private:
    node<type>*nd;
    int check_balance(node<type> *x);
    void FixBalance(node<type> *root, node<type> *a);
    void LeftSmallRotate(node<type> *root, node<type> *x);
    void RightSmallRotate(node<type> *root, node<type> *x);
    void BigLeftRotate(node<type> *root, node<type> *x);
    void BigRightRotate(node<type> *root, node<type> *x);
    node<type> *FindMinKey(node<type> *a);
    node<type> *NextNode(node<type> *root, node<type> *x);
    node<type> *search(node<type> *root, type val);
    node<type> *NewInsert(node<type> *root, type val);
    node<type>* NewFind(node<type> *root, type val);
    node<type>* NewRemove(node<type> *root, type val);
};
template<typename type>
tree<type>::tree()
{
    nd = NULL;
}

template<typename type>
tree<type>::~tree()
{

}
template<typename type>
bool tree<type>::insert(type val)
{
    if(NewInsert(nd, val) == NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}

template<typename type>
bool tree<type>::find(type val)
{
    if  (NewFind(nd, val) == nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

template<typename type>
bool tree<type>::remove(type val)
{
    if  (NewRemove(nd, val) == NULL)
    {
        return false;
    }
    else
    {
        return true;
    }
}

template<typename type>
int tree<type>::check_balance(node<type> *x)
{
    return x->balance;
}

template<typename type>
void tree<type>::LeftSmallRotate(node<type> *root, node<type> *x)
{
    node<type> *y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
    {
        node<type> *y1 = y->left;
        y1->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            root = y;
        }
        else
        {
            node<type> *x1 = x->parent;
            if (x1->left == x)
            {
                x1->left = y;
            }
            else
            {
                x1->right = y;
            }
        }
    }
    y->left = x;
    x->parent = y;
}

template<typename type>
void tree<type>::RightSmallRotate(node<type> *root, node<type> *x)
{
    node<type> *y = x->left;
    x->left = y->right;
    if (y->right != nullptr)
    {
        node<type> *y1 = y->right;
        y1->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            root = y;
        }
        else
        {
            node<type> *x1 = x->parent;
            if (x1->right == x)
            {
                x1->right = y;
            }
            else
            {
                x1->left = y;
            }
        }
    }
    y->right = x;
    x->parent = y;
}
template<typename type>
void tree<type>::BigLeftRotate(node<type> *root, node<type> *x)
{
    LeftSmallRotate(&root, &x->left);
    RightSmallRotate(&root, &x);
}
template<typename type>
void tree<type>::BigRightRotate(node<type> *root, node<type> *x)
{
    RightSmallRotate(&root, &x->right);
    LeftSmallRotate(&root, &x);
}
template<typename type>
node<type> *tree<type>::FindMinKey(node<type> *a)
{
    if (a->left == nullptr)
    {
        return a;
    }
    else
    {
        return FindMinKey(a->left);
    }
}

template<typename type>
node<type>* tree<type>::NewInsert(node<type> *root, type val)
{
    node<type> *FindNewVal = search(root, val);

     node<type> *NewNode = new node<type>(val);
    NewNode->parent = FindNewVal;
    if (FindNewVal == nullptr)
    {
        root = NewNode;
        nd = root;
    }
    else
    {
        if (NewNode->key < FindNewVal->key)
        {
            FindNewVal->left = NewNode;
        }
        else
        {
            FindNewVal->right = NewNode;
        }
    }
    node<type> *curr = NewNode;
    while (curr != nullptr)
    {
        FixBalance(root,curr);
        curr = curr->parent;
    }
    return root;
}

template<typename type>
node<type>* tree<type>::NewFind(node<type> *root, type val)
{
    if (!root)
    {
        return NULL;
    }

    if (val == root->key)
    {
        return root;
    }
    if ( val < root->key)
    {
       return NewFind (root->left, val);
    }
    else
    {
       return NewFind (root->right, val);
    }
}

template<typename type>
node<type>* tree<type>::NewRemove(node<type> *root, type val)
{
    if (find(val) == false)
    {
        return nullptr;
    }
    else
    {
        node<type> *DelNode = search(root, val);
        node<type> *var;
        node<type> *x;
        if (DelNode->parent == nullptr && DelNode->right == nullptr && DelNode->left == nullptr)
        {
            nd = nullptr;
            return new node<type>(val);
        }
        if (DelNode->left == nullptr || DelNode->right == nullptr)
        {
            var = DelNode;
        }
        else
        {
            var = FindMinKey(DelNode);
        }
        if (var->left != nullptr)
        {
            x = var->left;
        }
        else
        {
            x = var->right;
        }
        if (x != nullptr)
        {
            x->parent = var->parent;
        }
        if (var->parent == nullptr)
        {
            root = x;
        }
        else
        {
            if (var == var->parent->left)
            {
                var->parent->left = x;
            }
            else
            {
                var->parent->right = x;
            }
        }
        if (var != DelNode)
        {
            DelNode->key = var->key;
        }
        node<type> *curr = var->parent;
        while (curr != nullptr)
        {
            FixBalance(root, curr);
            curr = curr->parent;
        }
        return root;
    }

}

template<typename type>
node<type> *tree<type>::search(node<type> *root, type val)
{
    node<type> *y = nullptr;
    node<type> *x = root;
    while (x != nullptr && val != x->key)
    {
        y = x;
        if (val < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    if (x != nullptr)
    {
        y = x;
    }
    return y;
}

template<typename type>
void tree<type>::FixBalance(node<type> *root, node<type> *a)
{
    if ((check_balance(a) == -2 && check_balance(a->right) == -1 )|| (check_balance(a) == -2 && check_balance(a->right) == 0 ))
    {
        LeftSmallRotate(root, a);
    }
    if ((check_balance(a) == 2 && check_balance(a->right) == 1 )|| (check_balance(a) == 2 && check_balance(a->right) == 0 ))
    {
        RightSmallRotate(root, a);
    }
    if ((check_balance(a) == -2 && check_balance(a->right) == 1 && check_balance(a->right->left) == 1 ) ||
        (check_balance(a) == -2 && check_balance(a->right) == 1 && check_balance(a->right->left) == -1) ||
        (check_balance(a) == -2 && check_balance(a->right) == 1 && check_balance(a->right->left) == 0))
    {
        RightSmallRotate(root,a->right);
        LeftSmallRotate(root, a);
    }
    if ((check_balance(a) == 2 && check_balance(a->right) == -1 && check_balance(a->right->left) == -1 ) ||
        (check_balance(a) == 2 && check_balance(a->right) == -1 && check_balance(a->right->left) == 1) ||
        (check_balance(a) == 2 && check_balance(a->right) == -1 && check_balance(a->right->left) == 0))
    {
        LeftSmallRotate(root, a->left);
        RightSmallRotate(root, a);
    }
}

template<typename type>
node<type> *tree<type>::NextNode(node<type> *root, node<type> *x)
{
    if (x->right != nullptr)
    {
        return FindMinKey(x->right);
    }
    node<type> *val = x->parent;
    while (val != nullptr && x == val->right)
    {
        x = val;
        val = val->parent;
    }
    return val;
}


int main()
{
    tree<int> tre;
    tre.insert(5);
    tre.insert(6);
    tre.insert(3);
    tre.insert(4);
    tre.insert(7);
    tre.insert(10);
    tre.insert(11);
    tre.insert(22);
    cout << tre.find(23) << endl;
    tre.remove(3);
    cout << tre.find(6) << endl;
    tre.insert(6);
    tre.remove(5);
    tre.remove(10);
    cout << tre.find(10) << endl;
    cout << tre.find(6) << endl;
    cout << endl;
    tree<string> tre1;
    tre1.insert("tree");
    cout << tre1.find("tree")<< endl;
    cout << tre1.find("not a tree") << endl;
    tre1.remove("tree");
    cout << tre1.find("tree")<< endl;
    return 0;
}
