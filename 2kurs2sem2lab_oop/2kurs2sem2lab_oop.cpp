// 2kurs2sem2lab_oop.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include "time.h"
#include <chrono>

using namespace std;
void show(vector<int> m) {
    for (int i = 0; i < m.size(); i++)
        cout << m[i]<<' ';
    cout << endl;
}

class sort {
public:
    
    vector<int> generateData(int n, int range) {
        vector<int> arr;
        srand(time(NULL));

        for (int i = 0; i < n; i++)
            arr.push_back(rand() % range);
        return arr;
    }
    void bubbleSort(vector<int> &arr)
    {
        int i, j,k;
        for (i = 0; i < arr.size() - 1; i++)

            // Last i elements are already in place 
            for (j = 0; j < arr.size() - i - 1; j++)
                if (arr[j] > arr[j + 1])
                {
                   mswap(arr[j], arr[j + 1]);
                    //iter_swap(arr.begin() + j, arr.begin() + j + 1);
                }
    }
    void ShakerSort(vector<int> &arr) {
        int i, j, k;
        for (i = 0; i < arr.size();i++) {
            for (j = i + 1; j < arr.size(); j++) {
                if (arr[j] < arr[j - 1])
                {
                    mswap(arr[j], arr[j - 1]);
                }
            }
            
            for (k = arr.size() - 2; k > i; k--) {
                if (arr[k] < arr[k - 1])
                {
                    mswap(arr[k], arr[k - 1]);
                }
            }
            i++;
        }
    }

    

   void heapSort(vector<int> &arr)
    {
        for (int i = arr.size()/ 2 - 1; i >= 0; i--)
            heapify(arr, arr.size(), i);

        for (int i = arr.size() - 1; i >= 0; i--)
        {
            mswap(arr[0], arr[i]);

            heapify(arr, i, 0);
        }
    }
    vector<int> quickSort(vector<int> &arr, int low, int high)
    {
        int i = low;
        int j = high;
        int pivot = arr[(i + j) / 2];
        int temp;

        while (i <= j)
        {
            while (arr[i] < pivot)
                i++;
            while (arr[j] > pivot)
                j--;
            if (i <= j)
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
                j--;
            }
        }
        if (j > low)
            quickSort(arr, low, j);
        if (i < high)
            quickSort(arr, i, high);
        return arr;
    }

    float difference(string s1, string s2,int n,int range) {
        vector<int> data = generateData(n, range), data1 = data;
        float dur1 = 0, dur2 = 0;
       if (s1=="bubble")
       {
           
           std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
           bubbleSort(data);
           std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

            dur1 = std::chrono::duration<float,std::milli>(end - start).count();
           
       }
       else if (s1 == "shaker") {
           std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
           ShakerSort(data);
           std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

            dur1 = std::chrono::duration<float, std::milli>(end - start).count();
       }
       else if (s1 == "heap") {
           std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
           heapSort(data);
           std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

            dur1 = std::chrono::duration<float, std::milli>(end - start).count();
       }
       else if (s1 == "quick") {
           std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
           quickSort(data,0,n);
           std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

            dur1 = std::chrono::duration<float, std::milli>(end - start).count();
       }

       if (s2 == "bubble")
       {
           std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
           bubbleSort(data1);
           std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

            dur2 = std::chrono::duration<float, std::milli>(end - start).count();

       }
       else if (s2 == "shaker") {
           std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
           ShakerSort(data1);
           std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

            dur2 = std::chrono::duration<float, std::milli>(end - start).count();
       }
       else if (s2 == "heap") {
           std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
           heapSort(data1);
           std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

           dur2 = std::chrono::duration<float, std::milli>(end - start).count();
       }
       else if (s2 == "quick") {
           std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
           quickSort(data1,0,n);
           std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

            dur2 = std::chrono::duration<float, std::milli>(end - start).count();
       }
       cout << dur1 << ' ' << dur2 << endl;
       return dur2 - dur1;
    }
    private:
        void heapify(vector<int> &arr, int n, int i)
        {
            int largest = i;
            int l = 2 * i + 1;
            int r = 2 * i + 2;


            if (l < n && arr[l] > arr[largest])
                largest = l;


            if (r < n && arr[r] > arr[largest])
                largest = r;


            if (largest != i)
            {
                mswap(arr[i], arr[largest]);
                heapify(arr, n, largest);
            }
            
        }
        template <typename T>
        void mswap(T& x, T& y)
        {
            T temp = x;
            x = y;
            y = temp;
        }
        
};
int main()
{
    sort s;
    
    cout<<s.difference("bubble", "shaker", 20, 100);
    
}

