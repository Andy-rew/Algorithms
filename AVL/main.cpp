#include <iostream>
#include <string>
using namespace std;

template <typename type>
struct node
{
    type key;
    struct node<type> *left;
    struct node<type> *right;
    int balance;
    node(type x)
    {
        this->key = x;
        this->right = NULL;
        this->left = NULL;
        this->balance = 1;
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
    node<type>*nd=NULL;
    int check_balance(node<type> *x);
    int height(node<type> *x);
    void fixheight(node<type> *x);
    node<type> *balance(node<type> *a);
    node<type> *LeftSmallRotate(node<type> *a);
    node<type> *RightSmallRotate(node<type> *a);
    node<type> *FindMinKey(node<type> *a);
    node<type> *DelMin(node<type> *a);
    node<type> *NewInsert(node<type> *root, type val);
    node<type>* NewFind(node<type> *root, type val);
    node<type>* NewRemove(node<type> *root, type val);
};
template<typename type>
tree<type>::tree()
{
    node<type>*nd = NULL;
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
    if  (NewFind(nd, val) == NULL)
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
    return height(x->left) - height(x->right);
}

template<typename type>
int tree<type>::height(node<type> *x)
{
    return x->balance;
}

template<typename type>
node<type>* tree<type>::balance(node<type> *a) // ????????????
{
    if ((check_balance(a) == -2 && check_balance(a->right) == -1 )|| (check_balance(a) == -2 && check_balance(a->right) == 0 )) // ????? ????? ????????
    {
        return LeftSmallRotate(a);
    }
    if ((check_balance(a) == 2 && check_balance(a->right) == 1 )|| (check_balance(a) == 2 && check_balance(a->right) == 0 )) // ????? ?????? ????????
    {
        return RightSmallRotate(a);
    }
    if ((check_balance(a) == -2 && check_balance(a->right) == 1 && check_balance(a->right->left) == 1 ) ||
        (check_balance(a) == -2 && check_balance(a->right) == 1 && check_balance(a->right->left) == -1) ||
        (check_balance(a) == -2 && check_balance(a->right) == 1 && check_balance(a->right->left) == 0)) // ??????? ????? ????????
    {
        a->right = RightSmallRotate(a->right);
        return LeftSmallRotate(a);
    }
    if ((check_balance(a) == 2 && check_balance(a->right) == -1 && check_balance(a->right->left) == -1 ) ||
        (check_balance(a) == 2 && check_balance(a->right) == -1 && check_balance(a->right->left) == 1) ||
        (check_balance(a) == 2 && check_balance(a->right) == -1 && check_balance(a->right->left) == 0)) // ??????? ?????? ????????
    {
        a->left = LeftSmallRotate(a->left);
        return RightSmallRotate(a);
    }
}

template<typename type>
void tree<type>::fixheight(node<type> *x)
{
    int l = height(x->left);
    int r = height(x->right);
    if (l > r)
    {
        x->balance = l + 1;
    }
    else
    {
        x->balance = r + 1;
    }
}

template<typename type>
node<type>* tree<type>::LeftSmallRotate(node<type> *a)
{
    node<type> *b = a->right;
    b->left = a;
    fixheight(a);
    fixheight(b);
    nd = b;
    return nd;
}

template<typename type>
node<type>* tree<type>::RightSmallRotate(node<type> *a)
{
    node<type> *b = a->left;
    b->right = a;
    fixheight(b);
    fixheight(a);
    nd = b;
    return nd;
}

template<typename type>
node<type> *tree<type>::FindMinKey(node<type> *a)
{
    if (a->left)
    {
        return FindMinKey(a->left);
    }
    else
    {
        return a;
    }
}

template<typename type>
node<type>* tree<type>::DelMin(node<type> *a)
{
    if (a->left == NULL)
    {
        return a->right;
    }
    a->left = DelMin(a->left);
    return balance(a);
}

template<typename type>
node<type>* tree<type>::NewInsert(node<type> *root, type val)
{
    if (find(val) == true)
    {
        return NULL;
    }
    else
    {
        //?????????
        if (!root)
        {
            nd = new node<type>(val);
            return nd;
        }
        else
        {
            if ( val <root->key)
            {
                root->left = NewInsert(root->left, val);
            }
            else
            {
                root->right = NewInsert(root->right, val);
            }
        }
        root = balance(root);
        nd = root;
        return nd;
    }
}

template<typename type>
node<type>* tree<type>::NewFind(node<type> *root, type val)
{
    // ????? - true; ??? - false
    if (!root)
    {
        return NULL;
    }

    if (val == root->key)
    {
        nd = root;
        return nd;
    }
    if ( val < root->key)
    {
        NewFind (root->left, val);
    }
    else
    {
        NewFind (root->right, val);
    }
}

template<typename type>
node<type>* tree<type>::NewRemove(node<type> *root, type val)
{
    if (find(val) == false)
    {
        return NULL;
    }
    else
    {
        //???????
        if ( val < root->key)
        {
            root->left = NewRemove(root->left, val);
        }
        else
        {
            if ( val >root->key)
            {
                root->right = NewRemove(root->right, val);
            }
            if (val ==root->key)
            {
                node<type> *l = root->left;
                node<type> *r = root->right;
                delete root;
                if (!r)
                {
                    nd = l;
                    return nd;
                }
                else
                {
                    node<type> *min = FindMinKey(r);
                    min->right = DelMin(r);
                    min->left = l;
                    min = balance(min);
                    nd = min;
                    return nd;
                }
            }
        }
        root = balance(root);
        nd = root;
        return nd;
    }
}


int main()
{
    tree<int> tre;
    tre.insert(5);
    cout << tre.find(5) << endl;
    cout << tre.find(6) << endl;
    tre.remove(5);
    cout << tre.find(5) << endl;
    cout << endl;
    tree<string> tre1;
    tre1.insert("tree");
    cout << tre1.find("tree")<< endl;
    cout << tre1.find("not a tree") << endl;
    tre1.remove("tree");
    cout << tre1.find("tree")<< endl;
    return 0;
}
