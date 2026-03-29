#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::ostream;

class Dog{
public:
    Dog(int val) : num{val} {}
    
private:
    int num;

friend ostream& operator<<(ostream& os, const Dog dog){
    os << dog.num;
    return os;
}

};

void exSmartPointer(int& a)
{
    std::unique_ptr<int> p;
}

int returnInt(int a)
{
    cout << a << endl;
    return a;
}


int main()
{
    int k{10100101};
    const Dog& myDog = Dog(1001); //Rvalue는 const &로 받아야 한다.
    cout << myDog << endl; 

    int a{100};
    int& b = a;
    returnInt(b);

    Dog d2{102};
    std::unique_ptr<Dog> p{};

    if(p){
        //cout << *p.get() << endl;
        cout <<"pointer is active" << endl;
    }
    else{
        //cout << p.get() << endl;
        cout << "pointer is null" << endl;
    }

}

// p는 스마트 포인터 즉 클래스를 기반으로 한 객체라서 생성자로 자동 초기화됨.
// 따라서 p든 p{}든 똑같다. 
// int, double 같은 기본형 타입들은 {}을 안하면 자동 초기화가 안된다. 
// nullptr을 역참조 하려고 하면 컴파일러는 프로그램을 강제 종료한다.


// 상수 리터럴에는 &을 붙일 수 없다. &은 Lvalue에 붙여야 한다. 

// 의문 : Dog(100)은 상수 100과 달리 스택에 물리적 주소가 있을까?? 
//Dog(100)은 스택에 물리적 주소가 생기긴 하는데 c++에서는 임시 객체의 주소를
// 가질 수 없도록 해놓아서  &으로 접근 자체가 불가하다. 

// 스마트 포인터는 해제될떄 메모리를 delete 하기 때문에 스택의 메모리 주소를 안받음.
// 혹여나 스택에서 delete가 일어나면 안되기 때문이다.

// 1. Dog d2 = std::move(d1); -> 이동 생성자 호출이다. 
// 2. Dog d2; d2 = Dog(1000); -> 이건 operator= 이동 대입 연산자다. 
// 3. const Dog& myDog = Dog(1001); -> 이건 그냥 임시 객체 수명 연장이다. 

// 복사 생성자와 이동 생성자를 직접 구현해보고 const일떄 어느 생성자 호출되는지?



// 상수 10은 코드 세그먼트에 저장되는데? 문자열 리터럴은 왜 데이터 세그먼트??




// 의문: 참조자&와 원본 Lvalue를 인자로 보냈을때 완전히 똑같이 취급할까?
// 네 별칭이라서 둘은 차이점이 없습니다. 