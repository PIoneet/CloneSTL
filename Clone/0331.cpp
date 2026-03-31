#include <iostream>

using std::cout;
using std::endl;

void f()
{
    cout<< "Fuction Address" << endl;
}

void g()
{
    cout << "second Function Address" << endl;
}

int main()
{
    int a;
    cout << (void*)f << endl;
    cout << std::addressof(g) << endl;
    cout << std::addressof(a) << endl;


}
// 코드 세그먼트(함수) 와 < -> 데이터/스택 영역은 구분된다. 
// cout은 데이터 영역은 자동으로 오버로딩 해서 주소 찍어주는데
// 함수 포인터는 그렇지 않다.



// 우리가 작성한 함수는 컴파일러에 의해 기계어로 번역되고
// 코드 세그먼트에 저장된다. 쓰기는 불가능하고 읽기만 가능하다. 
// 데이터 영역은 읽고 쓰기 가능하다 기본적으로 하지만 둘다 
// 영역의 크기는 고정적이다. 


//ASLR 이라고 보안 프로그램 때문에 코드,데이터, 스택, 힙 영역이
// 주소값 위치가 맨날 바뀐다. 

//함수를 Rvalue 임시 객체처럼 활용하고 싶다 -> 람다 []() {}
// +[]() {} 하면 함수 포인터 된다고함? 