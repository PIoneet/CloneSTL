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

    string getName() const { //이렇게 하면 복사하지 않고 수정도 하지 않을 수 있음.
        return name; //string을 반환하면 복사한 임시 객체를 반환함(Rvalue)
    }

    string& getName() {
        return name;
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

array<Dog, 1000> a;
int main()
{
    ofstream out{"ex.txt", ios::binary};
    auto start = std::chrono::high_resolution_clock::now();
    //qsort(a.data(), a.size(), sizeof(Dog), qsortGlobalAscender);
    //sort(a.begin(), a.end(), sortGlobalAscender);

    // const Dog&으로 하면 따로 복사본을 만드는거 아니면 객체의 멤버를 수정못함.
    for(const Dog& dogs: a){ //애초에 dogs.name을 바꿀거라 const를 쓰면 안됐음.
        string&& sortName = dogs.getName(); //오른쪽은 Lvalue임. 
        sort(sortName.begin(), sortName.end());
    }


    sort(a.begin(), a.end(), [](const Dog& x, const Dog& y){
        return x.getName().size() > y.getName().size();
    });
    auto stop = std::chrono::high_resolution_clock::now();
    cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start) << endl;
    
    
    out.write(reinterpret_cast<char*>(a.data()), a.size() * sizeof(Dog));

    ifstream in{"ex.txt", ios::binary};
    if(not in){
        return 20260401;
    }
    in.read(reinterpret_cast<char*>(a.data()), sizeof(Dog));
    for(const Dog& dogs: a | std::views::take(1000)){
        cout << dogs << '\n';
    }

}

// read는 읽어올 파일의 데이터를 어디에 저장할지에 중점을 맞추어 놓았다. 

// 바이너리 모드로 적었으면 읽을때도 무조건 바이너리 모드로 읽어야 한다. 
// 다 안읽고 중간에 끊기거나 하는 문제가 생긴다.


// 코드 94줄은 진짜 굉장히 재밌는 코드다. 
// 잘 보면 const Dog& dogs로 루프를 돌고 있어서 dogs 객체의 name은 수정 절대 불가다. 
//근데 나는 getName() const에서 임시 객체 복사본을 수정하면 된다고 생각했고
//string&&으로 임시 객체 수명 연장도 했다. 하지만 결국 for문 돌면 복사본을 정렬하고
// 바로 사라진다. 임시 객체이기 때문이다. 그래서 컴파일 오류는 없지만 정렬이 안된거다.

