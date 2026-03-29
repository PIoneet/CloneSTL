#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::ostream;

class Dog{
public:
    Dog() = default;
    //Dog(int val) : num(&val) {} //이거 겁나 위험함. 생성자도 함수라서 val이 사라짐.
    Dog(int val): num(new int{val}) {
        cout << "General Constructor Valid" << endl;
    }
    
    Dog(const Dog& other) : num(new int{*other.num}) { // 좌갑 우값 다 가능
        cout << "Copy Constructor valid" << endl;
    }
    
    Dog(Dog&& other) : num(std::move(other.num)) { //우값만 받을 수 있음(수정 가능)
        cout << "Move Constructor valid" << endl;
    } 

    //소멸자가 필요가 없어진다. 스마트 포인터가 알아서 해제해주니까 말이다.

private:
    std::unique_ptr<int> num;

friend ostream& operator<<(ostream& os, const Dog& dog){
    if(dog.num){
        os << *dog.num;
    }
    else{
        os << "Invalid Access" << endl;
    }
    
    return os;
}

};

int main()
{
    Dog d1{1102};
    Dog d2 = std::move(d1);
    cout << d2 << endl;
    cout << d1 << endl; 

}

// std::unique_ptr<int> num; 이 되면 num을 other.num으로 초기화 할 수가 없다.
// other.num은 Lvalue니까 말이다.



// 복사 생성자와 이동 생성자를 직접 구현해보고 const일떄 어느 생성자 호출되는지?



// 상수 10은 코드 세그먼트에 저장되는데? 문자열 리터럴은 왜 데이터 세그먼트??
