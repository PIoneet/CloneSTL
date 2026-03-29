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
    
    Dog(Dog&& other) : num(other.num) { //우값만 받을 수 있음(수정 가능)
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
    const Dog d1{1102};
    Dog d2 = std::move(d1);
    cout << d2 << endl;
    // const d1을 줬기에 원본 수정이 안되서 복사 생성자가 호출됨.
    // 아예 별개의 new int{*other.num} 메모리를 생성해서 Double Free 아님. 

}


// 오케이 스마트 포인터 정리를 해보겠다. 
// 일단 스마트 포인터는 무조건 초기화할떄 우값 Rvalue를 받는다. 
// 즉 이름이 없는 메모리 주소값을 받는다는 애기다. 그 이유는 소유권을 독점하기 위해
// 만약 좌값을 받는 다면 p2 = p1; 처럼 복사가 가능해야 하기 떄문이다. 

// 근데 Dog&& other로 우값을 받으면 그 시점에서 other는 이름이 생겼기에
// 좌값이 된다. -> 따라서 other.num 같이 멤버 변수에 접근할 수 있는 것이다.
// 또한, && 또한 원본 데이터의 그저 별칭이기 떄문이다.




// 복사 생성자와 이동 생성자를 직접 구현해보고 const일떄 어느 생성자 호출되는지?



// 상수 10은 코드 세그먼트에 저장되는데? 문자열 리터럴은 왜 데이터 세그먼트??
