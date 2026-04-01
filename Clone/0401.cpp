#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <print>
#include <array>
#include <algorithm>
#include <chrono>
#include <ranges>
#include <format>

using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::array;
using std::print;
using std::ofstream;
using std::ios;
using std::ifstream;
using std::sort;
using std::format;
using namespace std::chrono;

std::default_random_engine dre;
std::uniform_int_distribution<size_t> uidID{1, 999'9999}; // 이건 템플릿 클래스다.
std::uniform_int_distribution uidLen{1, 16};
std::uniform_int_distribution uidChar{'a', 'z'};

class Dog{
public:
    Dog(): id{uidID(dre)}{
        size_t len = uidLen(dre);
        for(int i=0; i<len; ++i){
            name+=uidChar(dre);
        }
    }

    int operator-(const Dog& other) const {
        if(this->id > other.id) return 1; //오름차순이니까 큰게 뒤로 간다. 
        if(this->id < other.id) return -1; // 음수일때는 바꾸지 않는다.
        return 0; // 같은 값이 들어오는 경우도 고려해야 한다.
    }

    size_t getID() const{ //이 함수를 호출한 객체를 절대 수정 안하겠다는 약
        //cout << "const getter valid" << '\n';
        return id;
    }

    // 둘은 오버로딩 관계다. const가 서로를 구분해준다. 
    //위 함수는 const 객체만이 호출 가능하고 아래는 수정 가능한 객체일떄 우선적으로 접근한다.
    
    size_t& getID(){
        //cout << "general const valid" << '\n';
        return id;
    }

private:
    string name;
    size_t id;

friend ostream& operator<<(ostream& os, const Dog& dog){
    os << format("{:<20} {}", dog.id, dog.name);
    return os;
}
};

bool sortGlobalAscender(const Dog& x, const Dog& y)
{
    return x.getID() < y.getID();
}

int qsortGlobalAscender(const void* a, const void* b){
    return *(Dog*)a - *(Dog*)b;
}

array<Dog, 1000'0000> a;
int main()
{
    ofstream out{"ex.txt", ios::binary};
    auto start = std::chrono::high_resolution_clock::now();
    //qsort(a.data(), a.size(), sizeof(Dog), qsortGlobalAscender);
    //sort(a.begin(), a.end(), sortGlobalAscender);
    sort(a.begin(), a.end(), [](const Dog& x, const Dog& y){
        return x.getID() < y.getID();
    });
    auto stop = std::chrono::high_resolution_clock::now();
    cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start) << endl;
    
    for(const Dog& dogs: a | std::views::take(100)){
        cout << dogs << '\n';
    }
    
    out.write(reinterpret_cast<char*>(a.data()), a.size() * sizeof(Dog));


}

// sort는 inline 방식을 써서 훨씬 빠르다. 내부적으로 std::swap을 써서 바꾼다.
//이 함수는 이동 생성자와 이동 대입 연산자를 써서 소유권을 교체하기에 
// string을 써도 소멸자가 2번 호출되는 Double Free 오류를 걱정 안해도 된다. 



// 와 아니 디버거 모드에서 sort 26660ms 그니까 26초 정도 나왔는데
// -O3 Release 모드로 하니까 4초까지 줄었다. 이게 모드 간의 속도 차이가
// 엄청나구나 싶었다. Inline 인라인이 디버거 모드에서는 오히려 독인가보네.