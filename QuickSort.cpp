#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

enum pivotRule {LEFT, RIGHT, MEDIAN};

void choosePivot(vector<int>& A, int l, int r, pivotRule rule) {
    if(rule == pivotRule::LEFT) {
        return;
    } else if(rule == pivotRule::RIGHT) {
        swap(A[l], A[r]);
    } else if(rule == pivotRule::MEDIAN) {
        int n = r - l + 1;
        if(n < 3) return;
        if((n % 2) == 0)
            n = l + (n / 2) - 1;
        else
            n = l + (n / 2);
        if(((A[l]<A[n]) && (A[n]<A[r])) || ((A[r]<A[n]) && (A[n]<A[l])))
        {
            swap(A[l], A[n]);
        } else if(((A[l]<A[r]) && (A[r]<A[n])) || ((A[n]<A[r]) && (A[r]<A[l]))) {
            swap(A[l], A[r]);
        }
    } else {
        cout << "ERROR: Invalid case" << endl;
    }
}

void qsPartition(vector<int>& A, int l, int r, int& p_index) {
    int pivot = A[l];
    int i = l + 1;
    for (int j = l+1; j <= r; j++) {
        if(A[j] < pivot) {
            swap(A[j], A[i]);
            i++;
        }
    }
    swap(A[l], A[i-1]);
    p_index = i-1;
}

long long quickSort(vector<int>& A, int l, int r, pivotRule rule ) {
    if (l >= r) return 0;
    choosePivot(A, l, r, rule);
    int p_index = -1;
    qsPartition(A, l, r, p_index);
    long long x = quickSort(A, l, p_index-1, rule);
    long long y = quickSort(A, p_index+1, r, rule);
    return r-l+x+y;
}

int main() {

    vector<int> v1;
    ifstream infile1("QuickSort.txt");
    int a;
    while(infile1 >> a)
        v1.push_back(a);
    cout << "Count - Left Pivot " << quickSort(v1, 0, v1.size()-1, pivotRule::LEFT) << endl;

    vector<int> v2;
    ifstream infile2("QuickSort.txt");
    int b;
    while(infile2 >> b)
        v2.push_back(b);
    cout << "Count - Right Pivot " << quickSort(v2, 0, v2.size()-1, pivotRule::RIGHT) << endl;

    vector<int> v3;
    ifstream infile3("QuickSort.txt");
    int c;
    while(infile3 >> c)
        v3.push_back(c);
    cout << "Count - Median Pivot " << quickSort(v3, 0, v3.size()-1, pivotRule::MEDIAN) << endl;
    return 0;
}
