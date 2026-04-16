#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <list>


using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::string;
using std::cin;
using std::ofstream;
using std::sort;

int main()
{
    vector<string> vs{"333", "1", "55555", "4444", "22"};
    vs.reserve(100'000);

    //vector는 연속적인 메모리라서 포인터로도 원소에 접근이 가능하다. 
    string* vs_pointer = vs.data();
    cout << *vs_pointer << endl;
    ++vs_pointer;
    cout << *vs_pointer << endl;

    auto it = vs.begin();
    cout << *it << endl;
    ++it;
    cout << *it << endl;


    std::list<string> ls{"333", "1", "55555"};
    auto ls_it = ls.begin();
    cout << *ls_it << endl;
    ++ls_it;   //반복자는 포인터와 달리 ++하면 이중연결리스트의 다음 next로 접근 가능. 포인터는 안됨. 
    cout << *ls_it << endl;



    cout << sizeof vs << endl; //최적화 모드, 디버그 모드냐에따라 크기가 다르다. 
    cout << addressof(vs) << endl;  //스택의 주소를 찍어줌.
    
    
    string input;
    while(cin >> input){
        vs.push_back(input);
    }

    //sort(vs.begin(), vs.end(), std::greater<string>{});
    sort(vs.begin(), vs.end(), [](const string& a, const string& b){
        return a > b;
    });

    std::copy(vs.begin(), vs.end(), std::ostream_iterator<string>(cout, "  "));
    // 벡터에 들어간 내용을 스트림에 복사해서 출력하는 방식을 사용했음.

}