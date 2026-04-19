#include <iostream>
#include <functional>
#include <vector>

using namespace std;

template<class T>
void change(T& a, T& b)
{
    T temp{a};
    a= b;
    b = temp;

    cout << "Template change " << endl;
}


void change(int& a, int& b)
{
    int temp = a;
    a = b;
    b = temp;

    cout << "Global change " << endl;

    //타입 정확히 일치하는게 호출 우선순위 높음.
    // 템플릿이 컴파일할떄 좀 더 걸림.
}




int main()
{
    vector<function<void(int&)>> funcs;
    funcs.reserve(10'0000);
    for(int i=0; i<5; ++i){
        funcs.push_back([](int& i){
            
            cout << i << endl;
        });
        cout << "size: " << funcs.size() << endl;
        funcs[i](i);
        // 캡처에 넣었고 아까는 인자가 필요없었음.
    }

    int a{1}, b{2};
    //function<void(int&, int&)> change; 

    /*
    void (*change)(int&, int&) = [](int& a, int& b){
        int temp = a;
        a = b;
        b = temp;
        cout << "Local Lambda change" << endl;
    };
    */

    auto change = [&a, &b](){
        int temp = a;
        a = b;
        b = temp;
        cout << "Captur Local Lambda change" << endl;
    };

    change(); //캡처는 인자로 안받으니까 이렇게 쓴다.

    cout << a << " " << b;
}


// 함수 포인터는 멤버 변수를 담을 수 없다. 오로지 함수의 메모리 주소만 저장하기 때문.
// []안에 들어가는걸 캡처라고 부르는데 외부 변수를  람다 내부에서 사용하는 경우를 애기함.