#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <iterator>

using namespace std;

int main()
{
    vector<string> srr;
    srr.reserve(10'0000);
    
    cout << accumulate(istream_iterator<int>{cin}, {}, 10LL) << endl;
     // ctrl z해서 cin이 -> {}가 되면 종료하라는 뜻. EOF 신호
    string input;
    while(cin >> input){
        srr.push_back(input);
    }

    cout << accumulate(srr.begin(), srr.end(), string{"Hello"}, []
    (const string& arr, const string& k){
        return arr.empty() ? k : arr + " " + k;
    }) << endl;
    // accumulate는 3번째 인자로 반환형 타입을 명시적으로 요구함.
    //begin()이 타입을 가지지만 기존 원소 타입과 다른 반환형을 반환하는 경우도 고려함.
}