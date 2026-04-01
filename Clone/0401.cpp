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
    out.write(reinterpret_cast<char*>(a.data()), a.size() * sizeof(Dog));


}