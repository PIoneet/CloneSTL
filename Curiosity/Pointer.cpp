#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::ostream;

class Dog{
public:
    Dog() = default;
    //Dog(int val) : num(&val) {} //이거 겁나 위험함. 생성자도 함수라서 val이 사라짐.
    Dog(int val): num(new int{val}) {}
    Dog(Dog&& other) : num(other.num) {
        cout << "Move Constructor valid" << endl;
    } 

    ~Dog(){
        if(num){
            cout << "Delete Heap memory" << endl;
            delete num;
        }
        else{
            cout << "No Heap Memories left" << endl;
        }
    }

private:
    int* num;

friend ostream& operator<<(ostream& os, const Dog& dog){
    os << *dog.num;
    return os;
}

};





int main()
{
    Dog d2 = std::move(Dog(101001));
    cout << d2 << endl;

}
// 복사 생성자와 이동 생성자를 직접 구현해보고 const일떄 어느 생성자 호출되는지?



// 상수 10은 코드 세그먼트에 저장되는데? 문자열 리터럴은 왜 데이터 세그먼트??
