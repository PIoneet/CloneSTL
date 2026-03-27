#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

class Dog{
public:
    Dog() = default;
    Dog(int val) : num(val) {}
    //Dog(int val1, int val2) : num{val1}, num2{val2} {}
    // explicit 키워드를 쓰면 생성자를 통한 암시적 형변환 방지 가능하다.


    /*
    operator bool(){
        return num; //num이 0이면 false를 출력한다.
    }
    */

    explicit operator char(){
        return num;
    }

    explicit operator int(){
        return num;
    }

    explicit operator double(){
        return num;
    }

    template<class T>
    void change(T& d1, T& d2){
        cout << d1 << "  " << d2 << endl;
        cout << "template Function call" << endl;
    }


private:
    int num{};
    int num2{};


friend ostream& operator<<(ostream& os, const Dog& dog){
    os << dog.num;
    return os;
}
};

template<class T>
void change(const T& d1, const T& d2)
{
    cout << d1 << "  " << d2 << endl;
    cout << "Global Template Call" << endl;
}

//읽기 전용 함수라 const &를 고려함.
//소유권 강탈은 && 사용한다.
// T&&는 Lvalue Rvalue 둘다 받을 수 있다.(템플릿인 경우)
// 생성자 암시적 형변환 방지로 explicit 키워드 쓴다. 
// const 쓰면 Rvalue 수명 연장해서 받을 수 있게 된다.

void change(const Dog& d1, const Dog& d2)  
{
    cout << d1 << "  " << d2 << endl;
    cout << "Global Function call" << endl;
}

void change(Dog& d1, Dog& d2)  
{
    cout << d1 << "  " << d2 << endl;
    cout << "No Const Global Function call" << endl;
}

Dog&& stealDog(Dog&& d)
{
    cout << "I stealed the Dog, It's Mine." << endl;
    cout << d << endl; //Dog&&도 별칭일 뿐이지 d는 d.num을 나타낸다. 
    return std::move(d);
}


int main()
{
    Dog a1{1234}; 
    Dog a2{5678};
    change(a1, a2);
    //change(Dog(24), Dog(224));
    change(int{23}, int{33});
    Dog d{224};
    Dog d2 = stealDog(Dog(444)); //이동 생성자 호출됨.
    Dog d3;
    d3 = stealDog(Dog(55555)); // 이건 이동 생성자가 아니라 이동 대입 연산자 호출
    cout << d2 << endl;
}

//&참조자는 Lvalue reference다. 그래서 Rvalue 즉 금방 사라질 수 있는 놈과
// 연결되지 못하게 막는다.
// 그걸 받으려면 &&참조자를 써야 한다.

// const? 를 쓰면 모든 Rvalue들을 다 받을 수 있는건지? 
// T&&는 왜 Rvalue Lvalue를 모두 받을 수 있는건지
// -> 이걸 보편 참조라고 부른다. 
// Lvalue가 오면 Dog&로 받고 Rvalue가 오면 Dog로 받는다. 
// 템플릿은 똑똑해서 이걸 구분해서 받는 것이 가능하다.

// std::foward()를 써야 하는이유?


// const 는 함수가 끝날떄까지 그 임시 객체의 수명을 연장시킬 수 있다.
// const를 써서 int 타입의 인자를 Dog로 암시적 형변환해서 받았음. -> explicit으로 해결
// Dog의 생성자 중에서 int 하나 받는 생성자가 있기 때문임.



// 컴파일러는 우선순위 알고리즘이 존재한다. 
// chnage(a1, a2);를 했을떄 a1, a2는 수정 가능한 Lvalue 2개를 받는 함수를 가장 먼저 찾음.
// 못 찾으면 const 붙여서 상수로 만들어야 하는 함수 -> 그 다음이 새 함수 찍어야 되는 템플릿 순서다.
// 결론적으로 컴파일러 입장에선 함수의 인자랑 매개변수가 가장 유사한 경우에 손을 들어준다.


