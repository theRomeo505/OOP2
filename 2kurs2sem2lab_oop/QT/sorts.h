#include <iostream>
#include <vector>
#include "time.h"
#include <chrono>
#include <thread>
#include "doctest/doctest.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITHOUT_MAIN

using namespace std;

void show(vector<int> m) {
    for (int i = 0; i < m.size(); i++)
        cout << m[i]<<' ';
    cout << endl;
}
/**
* Class to contain all sort and timechecking functions
*/
class sortClass {
public:
    void merge(vector<int> arr, int l, int m, int r)
    {
        int n1 = m - l + 1;
        int n2 = r - m;

        vector<int> L(n1);
        vector<int> R(n2);

        for (int i = 0; i < n1; i++)
            L[i] = arr[l + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[m + 1 + j];
        int i = 0;

        int j = 0;

        int k = l;

        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }
    void mergeSort(vector<int> arr,int l,int r){
        if(l>=r){
            return;//returns recursively
        }
        int m =l+ (r-l)/2;
        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);
        merge(arr,l,m,r);
    }
    void* merges(vector<int> arr, int low, int high)
    {
        int mid = low + (high - low) / 2;
        if (low < high) {
            mergeSort(arr,low, mid);
            mergeSort(arr,mid + 1, high);
            merge(arr,low, mid, high);
        }
    }
    void initMerge(vector<int> arr){
        int num_of_threads=4;
        vector<thread> threads(num_of_threads);
        for (int i=0;i<num_of_threads;i++){
        int low = i * (arr.size() / num_of_threads);
        int high = (i + 1) * (arr.size() / num_of_threads) - 1;
        threads[i]=std::thread(merges,arr,low,high);
        }
        for (int i = 0; i < 4; i++)
                threads[i].join();
        merge(arr,0, (arr.size() / 2 - 1) / 2, arr.size() / 2 - 1);
            merge(arr,arr.size() / 2, arr.size()/2 + (arr.size()-1-arr.size()/2)/2, arr.size() - 1);
            merge(arr,0, (arr.size() - 1)/2, arr.size() - 1);
    }
    /**
    * Method for generating vector of int
    * \param n - count of numbers
    * \param range - maximum number
    */
    vector<int> generateData(int n, int range) {
        vector<int> arr;
        srand(time(NULL));

        for (int i = 0; i < n; i++)
            arr.push_back(rand() % range);
        return arr;
    }
    /**
   * Method for sorting vector by finding the lowest int (size) times
   * \param arr - vector of int
   */
    vector<int> naive(vector<int> arr) {
        vector<int> b; int min = 32000,imin=0;
        for (int i = 0; i < arr.size(); i++) {
            min = 32000;
            for (int j = 0; j < arr.size(); j++) {
                if (arr[j] > min) {
                    min = arr[j];
                    imin = j;
                }
            }
            b.push_back(arr[imin]);
            arr.erase(arr.begin() + imin);
        }
        return b;
    }
    /**
   * Method for sorting vector by bubble algorythm
   * \param arr - vector of int
   */
    void bubbleSort(vector<int> &arr)
    {
        int i, j,k;
        for (i = 0; i < arr.size() - 1; i++)

            for (j = 0; j < arr.size() - i - 1; j++)
                if (arr[j] > arr[j + 1])
                {
                   mswap(arr[j], arr[j + 1]);
                }
    }
    /**
   * Method for sorting vector by shaker(cocktail) algorythm
   * \param arr - vector of int
   */
    void ShakerSort(vector<int>& a)
    {
        int i, j, k;
        for (i = 0; i < a.size();)
        {
            for (j = i + 1; j < n; j++)
            {
                if (a[j] < a[j - 1])
                    mswap(a[j], a[j - 1]);
            }
            n--;

            for (k = n - 1; k > i; k--)
            {
                if (a[k] < a[k - 1])
                    mswap(a[k], a[k - 1]);
            }
            i++;
        }
    }

    /**
   * Method for sorting vector by heap algoruthm
   * \param arr - vector of int
   */

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
   /**
   * Method for sorting vector by quicksort akgorythm
   * \param arr - vector of int
   * \param low - start point
   * \param high - end point
   */
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
    /**
   * Method for finding the difference between evaluating time of 2 algorythms
   * \param data - vector of int
   * \param s1 - first type of sort
   * \param s2 - second type of sort
   * \return difference between working time of second algorythm - first one
   */
    float difference(vector<int> &data, string s1, string s2) {
        vector<int> data1 = data;
        float dur1 = 0, dur2 = 0;
        std::thread first_thread;
        std::thread second_thread;


       if (s1=="bubble")
       {

           std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
           //bubbleSort(data);
           first_thread=std::thread (bubbleSort,data);
           std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

            dur1 = std::chrono::duration<float,std::milli>(end - start).count();

       }
       else if (s1 == "shaker") {
           std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
           //ShakerSort(data);
           first_thread=std::thread(ShakerSort,data);
           std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

            dur1 = std::chrono::duration<float, std::milli>(end - start).count();
       }
       else if (s1 == "heap") {
           std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
           //heapSort(data);
           first_thread=std::thread(heapSort,data);
           std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

            dur1 = std::chrono::duration<float, std::milli>(end - start).count();
       }
       else if (s1 == "quick") {
           std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
          // quickSort(data,0,data.size()-1);
           first_thread=std::thread(quickSort,data,0,data.size()-1);
           std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

            dur1 = std::chrono::duration<float, std::milli>(end - start).count();
       }
       else if (s1 == "merge"){
           std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
           first_thread=std::thread(mergeSort,data,0,data.size()-1);
           std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
           dur1 = std::chrono::duration<float, std::milli>(end - start).count();
       }

       if (s2 == "bubble")
       {
           std::chrono::steady_clock::time_point start1 = std::chrono::steady_clock::now();
          // bubbleSort(data1);
           second_thread=std::thread (bubbleSort,data1);
           std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();

            dur2 = std::chrono::duration<float, std::milli>(end1 - start1).count();

       }
       else if (s2 == "shaker") {
           std::chrono::steady_clock::time_point start1 = std::chrono::steady_clock::now();
           //ShakerSort(data1);
           second_thread=std::thread(ShakerSort,data1);
           std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();

            dur2 = std::chrono::duration<float, std::milli>(end1 - start1).count();
       }
       else if (s2 == "heap") {
           std::chrono::steady_clock::time_point start1 = std::chrono::steady_clock::now();
           //heapSort(data1);
           second_thread=std::thread (heapSort,data1);
           std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();

           dur2 = std::chrono::duration<float, std::milli>(end1 - start1).count();
       }
       else if (s2 == "quick") {
           std::chrono::steady_clock::time_point start1 = std::chrono::steady_clock::now();
           //quickSort(data1,0,data1.size()-1);
           second_thread=std::thread (quickSort,data1,0,data.size()-1);
           std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();

            dur2 = std::chrono::duration<float, std::milli>(end1 - start1).count();
       }
       else if (s2 == "merge"){
           std::chrono::steady_clock::time_point start1 = std::chrono::steady_clock::now();
           first_thread=std::thread(mergeSort,data1,0,data.size()-1);
           std::chrono::steady_clock::time_point end1 = std::chrono::steady_clock::now();
           dur2 = std::chrono::duration<float, std::milli>(end1 - start1).count();
       }
       first_thread.join();
       second_thread.join();

       cout << dur1 << ' ' << dur2 << endl;
       return dur2 - dur1;
    }
    private:
        /**
   * Methhod to be used in heap sort
   * \param arr - vector of int
   * \param n - end point
   * \param i - current point
   */
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
TEST_CASE("bubble") {
    sortClass sort;
    vector<int> a = sort.generateData(100, 300);
    vector<int> b = sort.naive(a);
    sort.bubbleSort(a);
    for (int i = 0; i < a.size(); i++) {
        CHECK(a[i] == b[i]);
    }

}
TEST_CASE("shaker") {
    sortClass sort;
    vector<int> a = sort.generateData(100, 300);
    vector<int> b = sort.naive(a);
    sort.ShakerSort(a);
    for (int i = 0; i < a.size(); i++) {
        CHECK(a[i] == b[i]);
    }

}
TEST_CASE("heap") {
    sortClass sort;
    vector<int> a = sort.generateData(100, 300);
    vector<int> b = sort.naive(a);
    sort.heapSort(a);
    for (int i = 0; i < a.size(); i++) {
        CHECK(a[i] == b[i]);
    }

}
TEST_CASE("quick") {
    sortClass sort;
    vector<int> a = sort.generateData(100, 300);
    vector<int> b = sort.naive(a);
    sort.quickSort(a);
    for (int i = 0; i < a.size(); i++) {
        CHECK(a[i] == b[i]);
    }

}
TEST_CASE ("merge multi and default"){
    sortClass sort;
    vector<int> a=sort.generateData(100,300);
    vector<int> b=a;
    sort.mergeSort(a,0,a.size()-1);
    sort.initMerge(b);
    for (int i = 0; i < a.size(); i++) {
        CHECK(a[i] == b[i]);
    }
}
