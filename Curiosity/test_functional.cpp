#include <iostream>
#include <functional>

using std::cout;
using std::endl;


class example{
public:
    void operator()(int i){
        cout << i << '\n';
        return; 
    }
};


void g()
{
    cout << "123" << endl;
}

int main()
{

    std::function<void(int)> f = example();
    // operator() 가 정의된 클래스나 구조체 객체도 담을 수 있음.
    std::function<void(int)> ff;
    // int 1개를 인자로 넣고 아무것도 반환하지 않는 함수 포인터를 담는 바구니
    ff = [](int n){    
        return n;
    };

    std::function<void()> fff;

    fff = [](){};


    void (*hi)() = g;
    // hi* 랑 *hi는 뭔차이인건지 찾아봐야겠다.
    void (*gg)() = [](){};

    //void (*gg)() 랑 void()는 서로 같은 데이터 타입인데 왼쪽은 Lvalue인듯
    
}


// void(int) 그니까 사실 void()가 함수 타입을 나타냄. 
// int는 함수가 반환할떄 int 재료가 필요하다는 뜻?