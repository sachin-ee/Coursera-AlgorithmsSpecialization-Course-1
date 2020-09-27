#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

void padZeros(string &a, string &b)
{
    int pad = labs(a.length() - b.length());
    if(a.length() > b.length())
        b.insert(0, pad, '0');
    else
        a.insert(0, pad, '0');
}

string strAdd(string &a, string &b)
{
    string result="";
    if(a.length() != b.length())
        padZeros(a,b);
    int carry=0;
    for(int i=a.length()-1; i>=0; i--)
    {
        string str1(1,a[i]); // char to string
        string str2(1,b[i]);
        stringstream ss1(str1); // string to stringstream
        stringstream ss2(str2);
        int int_a = 0;
        int int_b = 0;
        ss1 >> int_a; // stringstream to int
        ss2 >> int_b;
        int tmp = int_a + int_b + carry;
        if(tmp>9)
        {
            carry=1;
            tmp=tmp%10;
        }
        else
            carry=0;
        result.insert(0,to_string(tmp));
    }
    if(carry==1)
        result.insert(0,to_string(carry));

    return result;
}

string recMultiply(const string &x, const string &y)
{
    string result="";
    if(x.length()==1 || y.length()==1)
        result = to_string(stoi(x) * stoi(y));
    else
    {
        int str_len = x.length();
        string a = x.substr(0, (str_len/2));
        string b = x.substr(str_len/2);
        string c = y.substr(0, (str_len/2));
        string d = y.substr(str_len/2);

        string ac = recMultiply(a, c);
        string bd = recMultiply(b, d);
        string ad = recMultiply(a, d);
        string bc = recMultiply(b, c);

        string new_ac = ac.append(str_len, '0');
        string acplusbd = strAdd(new_ac, bd);
        string adplusbc = strAdd(ad, bc);
        string new_adplusbc = adplusbc.append(str_len/2, '0');
        result = strAdd(acplusbd, new_adplusbc);
    }
    return result;
}
int main()
{
    cout << recMultiply(string("3141592653589793238462643383279502884197169399375105820974944592"), string("2718281828459045235360287471352662497757247093699959574966967627")) << endl;
    return 0;
}
