#include <iostream>
#include <chrono>

using std::cout;
using std::endl;
using namespace std;



int 오름차순(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
    //만약 double 2개를 받으면 큰일난다. 
    // 00 00 00 00 00 3F F0 이렇게 받았는데 4바이트 읽으면 
    //a가 1.0인데 00 00 00 00읽어서 0이라고 인식해버리니까.
}

void f()
{
    cout<< "Fuction Address" << endl;
}

void ff()
{
    cout << "Fuction Changed" << endl;
}



int main()
{
    
    
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < 100; i++){
        cout << "Hello" << '\n';
    }
    auto stop = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<std::chrono::milliseconds>(stop-start);

    cout << duration.count() << endl;

    void (*gg)() = f; 
    gg();

    gg = ff;
    gg();
}

// qsort는 c 아키텍쳐 알고리즘이다. 그레서 &말고 void*을 사용한다. 
// sort는 c++ 아키텍쳐 알고리즘이다. 