#include <bits/stdc++.h>
//для этого крутого импорта нужен GNU C++ компилятор, если у вас другой, то удалите его и заимпортите нужные вручную :С
//давайте без виндовых импортов, плез :С
//ну тут вам они вообще не за чем

using namespace std;

//Сортировать нужно в неубывающем порядке (1, 3, 2, 6, 2, 4) => (1, 2, 2, 3, 4, 6)


//Если не знаете как пользоваться итераторами, то комментите этот дефайн и реализуйте метод c индексами с:
#define ITER

#ifdef ITER

int minRunLength(int n)
{
     int  flag = 0;
       while (n >= 64)
        {
         flag |= n & 1;
         n >>= 1;
        }
       return n + flag;
}

vector <int> InsertionSort( vector<int> &run )
{
    int value, j;
    for (int i = 1; i < run.size(); ++i)
    {
        value = run[i];
        j = i -1;
        while (j >= 0 && run[j] > value)
        {
            run[j + 1] = run[j];
            run[j] = value;
            j--;
        }
    }
    return run;
}


vector <int> merge (vector<int>::iterator it1, int size1, vector<int>::iterator it2, int size2 ) //Galloping Mode
{
    vector<int>  merg;
    vector<int>::iterator end1 = it1;
    advance (end1, size1);
    vector<int>::iterator end2 = it2;
    advance (end2, size2);
    vector<int>::iterator bin;

    int from1 = 0, from2 = 0, i = 0;
    int len1 = size1, len2 = size2, prei1 = 0, prei2 = 0;
     while ( len1 != 0 && len2 !=0 )
    {

     if (*it1 < *it2)
      {
         merg.push_back(*it1);
        it1++;
        len1--;      
        from1++;
      }
      else
        {
         merg.push_back(*it2);
         it2++;
         len2--;
         from2++;
        }
      if (from1 == 7)
      {
          bin = lower_bound(it1, end1, *it2);
          if ( bin == end1)
          {
              for ( vector<int>::iterator j = it1; j < end1; ++j)
              {

                  merg.push_back( *it1);
                  ++it1;

              }
              len1 =0;
          }
          from1 = 0;
      }
      if (from2 == 7)
       {
          bin = lower_bound(it2, end2, *it1);
              if ( bin == end2)
              {
                  for ( vector<int>::iterator j = it2; j < end2; ++j)
                  {

                      merg.push_back( *it2);
                      ++it2;

                    }

                     len2 =0;
                }
               from2 = 0;
       }
      i++;
}
     if (len1 == 0)
     {
         for (int i = 0; i < len2; ++i)
         {
             merg.push_back(*it2);
             it2++;
         }
     }
     else
     {
         for (int i = 0; i < len1; ++i)
         {
             merg.push_back(*it1);
             it1++;
         }
     }

    return merg;
}
/*
vector <int> merge (vector<int>::iterator it1, int size1, vector<int>::iterator it2, int size2 ) //без галопа
{
    vector<int>  merg;
    int len1 = size1, len2 = size2;
    while ( len1 != 0 && len2 !=0 )
    {
      if (*it1 < *it2)
      {
          merg.push_back(*it1);
          it1++;
          len1--;
      }
      else
        {
          merg.push_back(*it2);
          it2++;
          len2--;
        }
    }
   if (len1 == 0)
   {
       for (int i = 0; i < len2; ++i)
       {
           merg.push_back(*it2);
           it2++;
       }
   }
   else
   {
       for (int i = 0; i < len1; ++i)
       {
           merg.push_back(*it1);
           it1++;
       }
   }

    return merg;
}*/
//сортировать нужно интервал [begin, end)
void timsort(vector<int>::iterator begin, vector<int>::iterator end)
{
   int start = clock();
int n = 0;
for (vector <int> :: iterator i = begin; i != end; ++i)
         n++;
int minrun = minRunLength(n);
vector<vector<int>> run;
run.push_back(vector<int>());
int i = 0;
vector<int>::iterator beg;
beg = begin;
do
{
    while (*beg > *(beg + 1) && beg < end)
    {
        run[i].push_back(*beg);
        beg++;
    }
    if (run[i].empty() == true)
    {
        while (*beg <= *(beg + 1) && beg < end)
        {
            run[i].push_back(*beg);
            beg++;
        }
    }
    while (run[i].size() < minrun && beg < end)
    {
        run[i].push_back(*beg);
        beg++;
    }
     run[i] = InsertionSort(run[i]);
    if (beg != end)
    {
        ++i;
        run.push_back(vector<int>());
    }


}while(beg != end);
vector<int>  merg;
stack<pair<vector<int>::iterator,int>> stack;
vector<int>::iterator itx1;
vector<int>::iterator ity1;
vector<int>::iterator itz1;
if (n < 64)
 {
    int z = 0;
    for (vector<int>::iterator k = begin; k < end; ++k)
    {
        *begin = run[i].at(z);
        begin++;
        ++z;
    }
 }
else
{
    int str = 0, stackSize = 0;
    int x1 = 0, y1 = 0, z1 = 0;



    while (str < run.size())
    {

        if (run.size() == 2)
        {
            stack.push(make_pair(run[str].begin(),run[str].size()));
            stack.push(make_pair(run[str+1].begin(),run[str+1].size()));
            itx1 =  stack.top().first;
            x1 =  stack.top().second;
            stack.pop();
            ity1 =  stack.top().first;
            y1 =  stack.top().second;
            stack.pop();
            z1 = 0;
            merg = merge(itx1, x1, ity1, y1);
            stack.push(make_pair(merg.begin(),merg.size()));
            break;
        }

       stack.push(make_pair(run[str].begin(),run[str].size()));
       if (stack.size() >= 3)
       {
           stackSize = stack.size();
           itx1 =  stack.top().first;
           x1 =  stack.top().second;
           stack.pop();
           ity1 =  stack.top().first;
           y1 =  stack.top().second;
           stack.pop();
           itz1 =  stack.top().first;
           z1 =  stack.top().second;
           stack.pop();

            if (x1 <= y1 + z1 || y1 <= z1)
            {
                if (x1 < z1)
                {
                     merg = merge(itx1, x1, ity1, y1);

                     stack.push(make_pair(itz1, z1));
                     stack.push(make_pair(merg.begin(),merg.size()));
                }
                else
                {
                    merg = merge(ity1, y1, itz1, z1);
                    stack.push(make_pair(itx1,x1));

                    stack.push(make_pair(merg.begin(),merg.size()));

                }
            }


}

        str++;
        if (str == run.size())
        {
            itx1 =  stack.top().first;
            x1 =  stack.top().second;
            stack.pop();
            ity1 =  stack.top().first;
            y1 =  stack.top().second;
             stack.pop();
            merg = merge(itx1, x1, ity1, y1);
            stack.push(make_pair(merg.begin(),merg.size()));
        }
    }



 for (vector<int>::iterator k = begin; k < end; ++k)
 {
     *begin = *stack.top().first;
     begin++;
     stack.top().first++;
 }
}
/*int endi = clock();
cout << endl << endl << (endi - start)/CLOCKS_PER_SEC << endl;*/
}

#else

//индексация должна быть с нуля, сортировать нужно интервал [begin, end)
void timsort(vector<int> &vector, int begin, int end) {

}

#endif

int testcaseNumber = 1;

bool testcase(const vector<int> &testVector,
              const vector<int>::const_iterator &begin,
              const vector<int>::const_iterator &end
) {
    try {
        vector<int> f(testVector), s(testVector);
        auto fl = f.begin() + distance(testVector.begin(), begin), fr = fl + distance(begin, end);
        auto sl = s.begin() + distance(testVector.begin(), begin), sr = sl + distance(begin, end);
        sort(fl, fr);
#ifdef ITER
        timsort(sl, sr);
#else
        timsort(s, distance(s.begin(), sl), distance(s.begin(), sr));
#endif
        cout << testcaseNumber++ << " testcase: ";
        if (equal(fl, fr, sl)) {
            cout << "Test passed" << endl;
            return true;
        }

        cout << "Something is wrong" << endl;
        auto iter = fl;
        cout << "Answer:      ";
        while (iter != fr) {
            cout << setw(4) << *iter << ' ';
            iter++;
        }
        cout << endl << "Your output: ";
        iter = sl;
        while (iter != sr) {
            cout << setw(4) << *iter << ' ';
            iter++;
        }
        cout << endl;
        return false;
    }
    catch (...) {
        cout << "exception >_<";
        return false;
    }
}

int main() {
    vector<int> testVector = {1, 5, 2, 5, 7, 1, -1, 0, 0, 6, 2, 13, 6, 2, 6, 2, 3, 6, 34, 234, 234, 45, 63, 46, 345, 32,
                              5432, 34, 5, 4, 32, 53, 24, 6736, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    srand(time(NULL));
    {
        for (int i =0; i < 10000; ++i)
        {
            testVector.push_back(rand() % 500);
        }
    }
    bool result = true;

   result &= testcase(testVector, testVector.begin(), testVector.end());

    result &= testcase(testVector, testVector.begin(), testVector.begin() + 3);
    result &= testcase(testVector, testVector.begin(), testVector.begin());
    result &= testcase(testVector, testVector.begin() + 5, testVector.begin() + 5 + 3);
    result &= testcase(testVector, testVector.begin() + 13, testVector.begin() + 13 + 10);
    result &= testcase(testVector, testVector.begin() + 34, testVector.begin() + 34 + 9);

    vector<int> newTestVector = {1, 5, 2,43, 5, 7, 1, -1, 0, 0, 6, 2, 13,34, 6, 2, 6, 2, 3, 6, 34, 234, 234, 45, 63, 46, 345, 32,
                                 5432, 34, 5, 4, 32, 53, 24, 6736, 9, 8, 7, 6, 5, 4, 5,43, 3, 2, 1, 0, 65, 444,23, 234 ,32423, 324, 423, 234, 23, 4,4,3,2,6,7,77,454,123,55,343,4353,3453, 56, 100,345,66,67,0 };
    //тесты пишите по аналогии с тем, как они написаны выше


    result &= testcase(newTestVector, newTestVector.begin(), newTestVector.end());


    cout << "Result: ";
    cout << ((result) ? "Your solution passed the pretests c:"
                      : "Something's wrong, I can feel it. Just a feeling I've got, like something's about to happen, but I don't know what")
         << endl;

}
