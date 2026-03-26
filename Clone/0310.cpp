#include <iostream>

using std::cout;
using std::endl;

// 1. void tmepFunc(int num, int num){} 이랑 void tempFunc(int& num, int& num){}
// 정확히 컴파일러가 구분하는지 궁금하네.

std::pair<int, int> tempFunc(int n1, int n2)
{
    return {n1, n2};
}

std::pair<const int&, const int&> tempFunc(const int& n1, const int& n2)
{
    return {n1, n2};
}
// 참조자 반환하면 나중에 받은 참조자로 가리켜도 쓰레기값을 가리킴. 
// n1, n2는 사라지니까 메모리에서.

int main()
{
    tempFunc(10, 20);
}