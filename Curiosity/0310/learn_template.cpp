#include <iostream>

using namespace std;

template<class T>
void change(T& a, T& b)
{
    T temp{a};
    a= b;
    b = temp;
}


template<class T>
void change(T&& a, T&& b)
{
    T temp = a;
    a = b;
    b = temp;
    cout << "RValue" << endl;
    cout << a << " " << b << endl;
}


int main()
{
    int a{1}, b{2};
    //change(a, b);

    change(2, 5);

    //cout << a << " " << b;
}