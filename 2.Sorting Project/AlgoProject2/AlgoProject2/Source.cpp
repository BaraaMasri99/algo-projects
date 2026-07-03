#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

// Selection sort
void selectionSort(int* B, int size)
{
    for (int i = 0; i <= size - 2; i++)
        for (int j = i + 1; j <= size - 1; j++)
        {
            if (B[j] < B[i])
            {
                int temp = B[i];
                B[i] = B[j];
                B[j] = temp;
            }
        }
}
long long selectionFn(long long n) {
    return (long long) n * n;
}
// Insertion Sort
void insertionSort(int A[], int size) {
    for (int j = 1; j < size; j++) {
        int key = A[j];
        int i = j - 1;

        while (i >= 0 && A[i] > key) {
            A[i + 1] = A[i];
            i--;
        }

        A[i + 1] = key;
    }
}
long long insertionFn(long long n) {
    return(long long) n * n;
}
// Merge Sort
void merge(int A[], int left, int mid, int right)
{
    int* B = new int[right - left + 1];
    int i = left;
    int j = mid + 1;
    int k = 0;
    // Merge the two halves
    while (i <= mid && j <= right)
    {
        if (A[i] <= A[j])
        {
            B[k] = A[i];
            i++;
        }
        else
        {
            B[k] = A[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements (left side)
    while (i <= mid)
    {
        B[k] = A[i];
        i++;
        k++;
    }

    // Copy remaining elements (right side)
    while (j <= right)
    {
        B[k] = A[j];
        j++;
        k++;
    }

    // Copy back to original array
    for (int t = left; t <= right; t++)
    {
        A[t] = B[t - left];
    }
    delete[] B; // free memory
}
void mergeSort(int A[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        mergeSort(A, left, mid);
        mergeSort(A, mid + 1, right);
        merge(A, left, mid, right);
    }
}
long long mergeFn(long long n) {
    return (long long)n * log2(n);
}
// Quick Sort
int Partition(int A[], int l, int r)
{
    int pivot = A[r];
    int i = l - 1;

    for (int j = l; j < r; j++)
    {
        if (A[j] <= pivot)
        {
            i++;
            swap(A[i], A[j]);
        }
    }

    swap(A[i + 1], A[r]);
    return i + 1;
}
void QuickSort(int A[], int l, int r)
{
    if (l < r)
    {
        int h = Partition(A, l, r);

        QuickSort(A, l, h - 1);
        QuickSort(A, h + 1, r);
    }
}
long long quickFn(long long n)
{
    return (long long)n * n;// Worst case: O(n^2), Average case: O(n log n)
}
// Heap Sort
void HeapInsert(int v[], int& n, int val)
{
    int i = n;      // insert at current end
    n++;

    while (i > 0 && val > v[(i - 1) / 2])
    {
        v[i] = v[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    v[i] = val;
}
void ShiftDown(int v[], int i, int n)
{
    int temp = v[i];

    while (2 * i + 1 < n)
    {
        int child = 2 * i + 1;   // left child

        if (child + 1 < n && v[child] < v[child + 1])
        {
            child = child + 1;   // right child is larger
        }

        if (v[child] > temp)
        {
            v[i] = v[child];
            i = child;
        }
        else
        {
            break;
        }
    }

    v[i] = temp;
}
void HeapSort(int x[], int n)
{
    int v[50001];
    int heapSize = 0;

    // Heap was built using insertion, so actual time may be slightly higher than optimal heapify implementation
    for (int i = 0; i < n; i++)
    {
        HeapInsert(v, heapSize, x[i]);
    }

    // Sort heap
    for (int i = n - 1; i >= 1; i--)
    {
        swap(v[0], v[i]);
        ShiftDown(v, 0, i);
    }

    // Copy back
    for (int i = 0; i < n; i++)
    {
        x[i] = v[i];
    }
}
long long heapFn(long long n)
{
    return (long long)(n * log2((double)n));
}
// Counting Sort
void CountingSort(int A[], int n)
{
    const int m = 100;          // maximum value in the array
    int* B = new int[n];
    int C[m + 1] = { 0 };

    // Step 1: Count occurrences
    for (int i = 0; i < n; i++)
    {
        C[A[i]]++;
    }

    // Step 2: Cumulative sum
    for (int k = 1; k <= m; k++)
    {
        C[k] = C[k] + C[k - 1];
    }

    // Step 3: Build sorted array (stable)
    for (int i = n - 1; i >= 0; i--)
    {
        B[C[A[i]] - 1] = A[i];
        C[A[i]]--;
    }

    // Step 4: Copy back to original array
    for (int i = 0; i < n; i++)
    {
        A[i] = B[i];
    }

    delete[] B;
}// Helper functions
long long countingFn(long long n)
{
    return (long long)n + 100;//O(n + k), where k = 100
}
// Helping functions 
void fillArray(int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100 + 1;
    }
}

int main()
{
    srand((unsigned)time(NULL));
    cout << fixed << setprecision(6);

    int sizes[4] = { 10000, 20000, 30000, 50000 };

    cout << left
        << setw(12) << "Algorithm"
        << setw(10) << "Size"
        << setw(15) << "Fn"
        << setw(8) << "Exp"
        << setw(12) << "Time" << endl;

    for (int i = 0; i < 4; i++)
    {
        for (int exp = 1; exp <= 2; exp++)
        {
            int* original = new int[sizes[i]];
            fillArray(original, sizes[i]);

            // Selection
            {
                int* arr = new int[sizes[i]];
                copy(original, original + sizes[i], arr);

                clock_t begin = clock();
                selectionSort(arr, sizes[i]);
                clock_t end = clock();

                cout << left
                    << setw(12) << "Selection"
                    << setw(10) << sizes[i]
                    << setw(15) << selectionFn(sizes[i])
                    << setw(8) << exp
                    << setw(12) << double(end - begin) / CLOCKS_PER_SEC << endl;

                delete[] arr;
            }

            // Insertion
            {
                int* arr = new int[sizes[i]];
                copy(original, original + sizes[i], arr);

                clock_t begin = clock();
                insertionSort(arr, sizes[i]);
                clock_t end = clock();

                cout << left
                    << setw(12) << "Insertion"
                    << setw(10) << sizes[i]
                    << setw(15) << insertionFn(sizes[i])
                    << setw(8) << exp
                    << setw(12) << double(end - begin) / CLOCKS_PER_SEC << endl;

                delete[] arr;
            }

            // Merge
            {
                int* arr = new int[sizes[i]];
                copy(original, original + sizes[i], arr);

                clock_t begin = clock();
                mergeSort(arr, 0, sizes[i] - 1);
                clock_t end = clock();

                cout << left
                    << setw(12) << "Merge"
                    << setw(10) << sizes[i]
                    << setw(15) << mergeFn(sizes[i])
                    << setw(8) << exp
                    << setw(12) << double(end - begin) / CLOCKS_PER_SEC << endl;

                delete[] arr;
            }

            // Quick
            {
                int* arr = new int[sizes[i]];
                copy(original, original + sizes[i], arr);

                clock_t begin = clock();
                QuickSort(arr, 0, sizes[i] - 1);
                clock_t end = clock();

                cout << left
                    << setw(12) << "Quick"
                    << setw(10) << sizes[i]
                    << setw(15) << quickFn(sizes[i])
                    << setw(8) << exp
                    << setw(12) << double(end - begin) / CLOCKS_PER_SEC << endl;

                delete[] arr;
            }

            // Heap
            {
                int* arr = new int[sizes[i]];
                copy(original, original + sizes[i], arr);

                clock_t begin = clock();
                HeapSort(arr, sizes[i]);
                clock_t end = clock();

                cout << left
                    << setw(12) << "Heap"
                    << setw(10) << sizes[i]
                    << setw(15) << heapFn(sizes[i])
                    << setw(8) << exp
                    << setw(12) << double(end - begin) / CLOCKS_PER_SEC << endl;

                delete[] arr;
            }

            // Counting
            {
                int* arr = new int[sizes[i]];
                copy(original, original + sizes[i], arr);

                clock_t begin = clock();
                CountingSort(arr, sizes[i]);
                clock_t end = clock();

                cout << left
                    << setw(12) << "Counting"
                    << setw(10) << sizes[i]
                    << setw(15) << countingFn(sizes[i])
                    << setw(8) << exp
                    << setw(12) << double(end - begin) / CLOCKS_PER_SEC << endl;

                delete[] arr;
            }

            // فصل بين كل experiment
            cout << "=====================================================\n";
            delete[] original;
        }

        // فصل بين كل size
        cout << "\n#####################################################\n\n";
    }

    return 0;
}