#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

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

template<class T>
void testCompiler(T& d1)
{
    cout << d1 << endl;
    cout << "Template wins" << endl;
}

void testCompiler(const Dog& d1)
{
    cout << d1 << endl;
    cout << "Global Function Wins" << endl;
}

int main()
{
    Dog d1{10000};
    testCompiler(d1);
    testCompiler(Dog(22222));
}

// 결과를 보면 알다시피 템플릿이 항상 우선순위가 전역함수에 비해 늦는건 아니다.
// d1 즉 Lvalue를 주면 그 인자에 부합함 매개변수를 가진 템플릿이 선택되고
// 둘이 같은 경우에는 전역함수가 이긴다. 
// 여기서 전역함수는 따로 const를 붙여야 해서 선택받지 못한 것임. 


// 템플릿이 일반 전역함수보다 속도가 느린 것은 아니다. 
// 빌드할떄는 전역함수가 더 빠를 수는 있다. 템플릿은 타입이 선택되고 나서 기계어로 번역하니까
// 근데 빌드하고 나면 기계어로는 템플릿이든 일반 전역함수든 같아서 
// 실행속도의 차이는 없다. 단순히 컴파일러가 우선적으로 어느 방식을 선택하느냐의 차이지.
