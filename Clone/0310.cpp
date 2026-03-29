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
   
}

// 템플릿 const T& 는 -> 읽기하겠다는 애기임. const라서 복사 생성자로 복사함.
// T&&도 Lvalue, Rvalue 다 받을 수 있음. std::foward를 써서 저장하거나 이동 가능
// 복사를 안하기 때문에 굉장히 효율적임. 

// 템플릿이 아닌 경우 int&& 같은 건 임시 객체 이동시킬떄 Rvalue 이동에 쓰임.

