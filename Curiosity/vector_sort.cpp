#include <iostream>
#include <vector>
#include <fstream>

using std::vector;
using std::ifstream;
using std::cout;
using std::endl;

int main()
{
    vector<char> k;
    k.reserve(10'0000);
    cout << "k의 힙 주소: " << (void*)k.data() << endl;
    
    
    ifstream in{"vector_sort.cpp"};
    char c;
    in >> std::noskipws;
    while(in >> c){  // 파일을 다 읽으면 탈출한다.
        cout << "k의 용량: " << k.capacity() << endl;
        cout << "k의 힙 주소: " << (void*)k.data() << endl;
        k.push_back(c);
    }

    
    /*
    for(char c:k)
        cout << c;
    cout << endl;
    */
}