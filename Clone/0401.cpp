#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <print>
#include <array>
#include <algorithm>

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

    size_t getID() const{ //이 함수를 호출한 객체를 절대 수정 안하겠다는 약
        cout << "const getter valid" << '\n';
        return id;
    }

    // 둘은 오버로딩 관계다. const가 서로를 구분해준다. 
    //위 함수는 const 객체만이 호출 가능하고 아래는 수정 가능한 객체일떄 우선적으로 접근한다.
    
    size_t& getID(){
        cout << "general const valid" << '\n';
        return id;
    }

private:
    string name;
    size_t id;

friend ostream& operator<<(ostream& os, const Dog& dog){
    print(os, "[:20] {}", dog.id, dog.name);
    return os;
}
};

array<Dog, 1000'0000> a;
int main()
{
    ofstream out{"ex.txt", ios::binary};
    sort(a.begin(), a.end(), [](const Dog& x, const Dog& y){
        return x.getID() < y.getID();
    });
    out.write(reinterpret_cast<char*>(a.data()), a.size() * sizeof(Dog));


}