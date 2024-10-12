#include <memory>
#include <iostream>

namespace NORMAL
{
    using namespace std;

    // 默认实参，在virtual修饰的函数中，默认实参根据类的静态类型确定
    struct Base
    {
        virtual void f(int a = 5)
        {
            std::cout << "Base" << a << std::endl;
        }
    };

    struct Child : Base
    {
        void f(int a = 7)
        {
            std::cout << "Bhild" << a << std::endl;
        }
    };

    void print_info()
    {
        std::unique_ptr<Base> ua = std::make_unique<Child>();
        // 输出：Bhild5
        ua->f();
    }
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);std::cout.tie(0);
    {
        using namespace NORMAL;
        print_info();
    }
}