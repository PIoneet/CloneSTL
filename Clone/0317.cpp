#include <iostream>
#include <random>
#include <array>
#include <fstream>

using std::cout;
using std::endl;
using std::array;
using std::ofstream;
using std::ios;

std::random_device rd;
std::default_random_engine dre;
std::uniform_int_distribution uid{1, 1000};

// 문제: 랜덤의 int 1000만개를 int.txt 파일에 텍스트 모드로 저장해라.
// 그리고 파일의 크기를 확인해보고 얼마나 나오는지 봐보자.

int main()
{
    ofstream out{"int.txt", ios::binary};
    
    for(int i=0; i<1'0000; ++i){
        out.write(reinterpret_cast<const char*>(&i), sizeof(double));
        // 8바이트를 주기로 정수 0, 1, 2 .. 이렇게 저장된다는건가.
    }
    
}