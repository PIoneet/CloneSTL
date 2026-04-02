#include <iostream>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
#include <ranges>

using std::cout;
using std::endl;
using std::sort;
using std::array;
using namespace std::views;
using namespace std::chrono;


std::default_random_engine dre;
std::uniform_int_distribution uid{1, 1000};
// generate, generate 람다, for 루프 초기화 이거 3개 비교해보자.

int f()
{
    static int i; // 아 그니까 static이라 하면 하나만 존재하는 int i니까 호출할때마다 1씩 증가됨.
    return ++i;
}

int ff() // 전역 함수를 호출하는 방식은 인라인 최적화가 더 어렵다고함.
{
     // static 키워드 없으니까 호출할때마다 매번 다른 랜덤값을 반환함.
    return uid(dre);
}

array<int, 1'0000'0000> test_arr{};
int main()
{
    auto start = high_resolution_clock::now();
    std::generate(test_arr.begin(), test_arr.end(), ff);
    //for(int& num: test_arr){
    //    num = uid(dre);
    //}
    //for(int i=0; i<test_arr.size(); i++){
    //    test_arr[i] = uid(dre);
    //}
    //std::generate(test_arr.begin(), test_arr.end(), [](){return uid(dre);});
    // 람다 방식은 main 지역 함수 안이라서 인라인 최적화가 간편함.
    auto stop = high_resolution_clock::now();

    for(int num: test_arr | take(100)){
        cout << num << '\n';
    }
    
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << duration << endl;
}


//high_resolution_clock::now; -> 이렇게 적으면 함수의 포인터 즉 주소값을 복사해서 대입하겠다는 의미다.
// 무조건 함수를 호출해서 반환값을 받아야 한다. 주소값을 - 연산하니까 차감된 이상한 주소 long long 데이터가 된것이다.



// for루프랑 Generate는 그다지 차이점이 없다는 사실에 도달했다.
// 루프 선회보다 랜덤값 생성이 더 오래걸린다고함. 

// 정렬에서는 이 속도 차이가 많이 발생했는데 값 초기화에서는 그렇지 않았다.