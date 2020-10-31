#include <iostream>
#include <algorithm>
using namespace std;

void Show(int *mas, int length)
{
    for (int i = 0; i < length; ++i)
    {
        cout << mas[i] << ' ';
    }
    cout << endl;
}

void SelectionSort(int *mas, int length) // сортировка выборкой, O(n^2)
{
    for (int i = 0; i < length; ++i)
    {
        for (int j = i + 1; j < length;++j)
        {
            if (mas[i]> mas[j])
                swap(mas[i], mas[j]);
        }
    }
    Show (mas, length);
}

void BubleSort(int *mas, int length) // сортировка пузырьком, O(n^2)
{
    for (int i = 0; i < length; ++i)
    {
        for (int j = length - 1; j > i; --j)
        {
            if (mas[j - 1] > mas[j])
                swap (mas[j-1], mas[j]);
        }
    }
    Show (mas, length);
}

void InsertionSort(int *mas, int length) //сортировка вставками, O(n^2)
{
    int value, j;
    for (int i = 1; i < length; ++i)
    {
        value = mas[i];
        j = i -1;
        while (j >= 0 && mas[j] > value)
        {
            mas[j + 1] = mas[j];
            mas[j] = value;
            j--;
        }
        Show (mas, length);
    }
    Show (mas, length);
}

void MergeSort (int *mas, int length) //сортировка слиянием, O(n log n)
{

}

void QuickSort (int*mas, int length) // быстрая сортировка, O(n log n)
{

}

void HeapSort (int *mas, int length) // пирамидальная сортировка, O(n log n)
{

}
int main()
{
    const int length = 10;
    int mas[length] {6, 3, 2, 7, 9, 0, 1, 8, 5, 4};
    //SelectionSort(mas, length);
    //BubleSort(mas, length);
    //InsertionSort(mas, length);
    MergeSort(mas, length);
    //QuickSort(mas, length);
    //HeapSort(mas, length);
    return 0;
}
