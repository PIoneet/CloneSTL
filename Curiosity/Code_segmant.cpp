#include <iostream>

using std::cout;
using std::endl;

int main()
{
    const char* data_segmant_arr = "Hello";

    //cout <<&10 << endl; 10은 그저 어셈블리에서 명령어 안에 10이 그대로 들어감.
    cout << &"Hello" << endl; // 문자열은 커서 데이터 영역에 실제 메모리 주소 있음.
    cout << (void*)data_segmant_arr << endl;

}

// 10은 왜 코드 세그먼트에 그리고 "Hello" 문자 리터럴은 왜 데이터 세그먼트 영역
// 둘다 같은 상수 리터럴인데 말이다.

// 애초에 "Hello"라는 리터럴이 저장된 영역에 포인터가 접근해서 사용하는 구조라
// 위 두개의 주소값이 같은 것을 알 수 있는 대목이다.
