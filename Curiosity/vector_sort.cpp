#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>


using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::ofstream;



int main()
{

    ifstream in{"vector_sort.cpp", std::ios::binary};

    std::istream_iterator<char> start_file{in};
    std::istream_iterator<char> end_file{};

    in >> std::noskipws;
    vector<char> storeFile(start_file, end_file);

    cout << static_cast<unsigned long long>(in.tellg()) << endl;

    // 벡터에는 이 입력 반복자 2개 받는 생성자가 존재한다. 

    for(auto i = storeFile.rbegin(); i != storeFile.rend(); ++i){
        cout << *i;
    }

    ofstream out{"new_file.txt" ,std::ios::binary};

    //out.write(reinterpret_cast<char*>(storeFile.data()), sizeof(storeFile));
    // 이렇게 전달하면 스택 메모리 24바이트만 반환한다. 
    
    std::reverse(storeFile.begin(), storeFile.end());
    out.write(reinterpret_cast<char*>(storeFile.data()), storeFile.size() * sizeof(char));
    
    /*
    for(char c : storeFile){
        cout << c;
    }
    */

}