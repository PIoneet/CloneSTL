#include <iostream>

using std::cout;
using std::endl;

class Dog{
public:
    Dog() = default;
    Dog(int val) : num(val) {}

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

private:
    int num{};

};


int main()
{
    Dog d(65); //오 65하니까 아스키 코드 'A'나왔음.
    cout << static_cast<char>(d) << endl; //d를 int로 형변환해서 num을 출력한다.
    cout << static_cast<double>(d) << endl;

}