#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::ostream;
using std::string;
using namespace std::string_literals;



template<class T>
void testCompiler(const T& d1)
{
    cout << d1 << endl;
    cout << "Template wins" << endl;
}


class Dog{
public:
    Dog() = default;
    Dog(int val) : num(val) {}

private:
    int num{};

friend ostream& operator<<(ostream& os, const Dog& dog){
    os << dog.num;
    return os;
}
// const가 없으면 Dog d1{};는 출력가능해도 Dog(223)는 출력 못한다. 
};


template<>
void testCompiler<int>(const int& d1)
{
    cout << d1 << endl;
    cout << "Template Specialization Wins: int" << endl;
}


template<>
void testCompiler<string>(const string& d1)
{
    cout << d1 << endl;
    cout << "Template Specialization Wins: string" << endl;
}

template<>
void testCompiler<const char*>(const char* const& d1)
{
    cout << d1 << endl;
    cout << "Template Specialization Wins: string_literal" << endl;
}

int main()
{
    int a{1};
    Dog d1{100};
    testCompiler(a);
    testCompiler(d1);
   // 문자열 리터럴은 string이 아니기 떄문에 string 특수화가 아니라 템플릿에서 실행됨.
   // "Hello"는 컴파일러 입장에서 string이 아니라 const char[]이다.
   
}


// 진짜 재밌는게 보통 문자 배열을 함수의 인자로 보내면 포인터로 변하는데
// 위와 같이 참조자&로 받으면 const char[] 타입을 유지해서 포인터로 안바뀜.
// 그래서 문자열 리터럴 특수화에 걸리지 않게 된 것이다. 

