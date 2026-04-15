#include <iostream>
#include <memory>


int main()
{
    std::unique_ptr<char[]> p;
    std::unique_ptr<int> k;

    k.reset(new int(10));
}