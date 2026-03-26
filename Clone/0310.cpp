#include <iostream>

using std::cout;
using std::endl;

// 1. void tmepFunc(int num, int num){} 이랑 void tempFunc(int& num, int& num){}
// 정확히 컴파일러가 구분하는지 궁금하네.
using namespace std;

void distinguishValue(int& a)
{
    cout << "Lvalue." << endl;
}

void distinguishValue(int&& a)
{
    cout << "Rvalue." << endl;
}

int main()
{
    int a = 100;
    distinguishValue(a);    // 이름 있는 메모리
    distinguishValue(1000); //임시 객체
    distinguishValue(std::move(a));
}