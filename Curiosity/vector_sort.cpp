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

    in >> std::noskipws;
    std::istream_iterator<char> start_file{in};
    std::istream_iterator<char> end_file{};

    
    vector<char> storeFile(start_file, end_file);

    cout << static_cast<unsigned long long>(in.tellg()) << endl;

    // 벡터에는 이 입력 반복자 2개 받는 생성자가 존재한다.
    ofstream out{"new_file.txt", std::ios::binary};

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


// 텍스트 모드는 /r/n에서 /r을 제거하고 /n만 읽는다. 
// 따라서 char로 읽는 경우에는 텍스트 모드가 보통 더 적합하다. 
// 그 이유는 바이너리 모드는 int 하나를 4바이트로 처리한다.
//근데 텍스트 모드는 문자로 변환해서 123456도 6바이트로 처리한다. 
// 그래서 바이너리 모드도 char 1바이트씩 처리하는 경우엔 텍스트 모드가 유리하다는 뜻