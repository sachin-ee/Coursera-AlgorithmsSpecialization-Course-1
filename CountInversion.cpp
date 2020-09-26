#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

long long countSplitInv(vector<long long>& A, long long left_low, long long left_high, long long right_low, long long right_high)
{
    long long res = 0;
    vector<long long> L;
    vector<long long> R;

    for(long long x = left_low; x <= left_high; x++)
    {
        L.push_back(A[x]);
    }
    for(long long y = right_low; y <= right_high; y++)
    {
        R.push_back(A[y]);
    }
    size_t i = 0; size_t j = 0;
    for(long long k = left_low; k <= right_high; k++)
    {
        if(i == L.size() && j != R.size())
        {
            A[k] = R[j];
            j++;
        } else if(j == R.size() && i != L.size())
        {
            A[k] = L[i];
            i++;
        }
        if(i < L.size() && j < R.size() && L[i] < R[j])
        {
            A[k] = L[i];
            i++;
        }
        else if(i < L.size() && j < R.size() && L[i] > R[j])
        {
            res += L.size() - i;
            A[k] = R[j];
            j++;
        }
    }

    return res;
}

long long sortAndCount(vector<long long>& A, long long low, long long high)
{
    long long res = 0;
    if(low >= high)
        res = 0;
    else
    {
        long long mid = low + ((high - low) / 2);
        long long x = sortAndCount(A, low, mid);
        long long y = sortAndCount(A, mid+1, high);
        long long z = countSplitInv(A, low, mid, mid+1, high);
        res = x + y + z;
    }
    return res;
}

int main()
{
    vector<long long> v;
    long long a;
    ifstream infile("IntegerArray.txt");
    while(infile >> a)
        v.push_back(a);
    cout << "Size of vector " << v.size() << endl;
    cout << "Count Inversions " << sortAndCount(v, 0, (v.size()-1)) << endl;
    return 0;
}
