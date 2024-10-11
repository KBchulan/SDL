#include <set>
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <cassert>
#include <climits>
#include <typeinfo>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <unordered_set>

namespace Test
{
    using namespace std;

    // 原始字面量
    // 原始自变量为R"()",原封不动的输出（）内的东西，
    // 前后若是定义，就必须相等
    void character_1()
    {
        string str1 = "MINI\\vvv";
        cout << str1 << endl;
        string str2 = "HALU\\bbb";
        cout << str2 << endl;
        string str3 = R"(LILER\\aaa)";
        cout << str3 << endl;
    }

    // 超长整形long long,2^63-1(16字节)
    void character_2()
    {
        long long max = LLONG_MAX;
        long long min = LLONG_MIN;
        unsigned long long x = ULLONG_MAX;

        cout << max << endl
             << min << endl
             << x << endl;
    }

    // 类成员的快速初始化
    class Cat
    {
    public:
        Cat() = default;
        ~Cat() = default;

        Cat(string name) : name(name) {}

        const void print() const
        {
            cout << a << endl
                 << b << endl
                 << c << endl
                 << d << endl
                 << e << endl
                 << name << endl;
        }

    private:
        int a{1};
        int b = 2;
        inline static int c = 3; // 静态成员
        static const int d = 4;  // 静态常量成员
        inline static const char *const e = "i am hansdom";
        string name;
    };

    void character_3()
    {
        unique_ptr<Cat> cat = make_unique<Cat>("lala");
        cat->print();
    }

    // final and override
    // final修饰虚函数时标明终止，后续无法再改写，修饰类时无法被继承
    // override明确表示要续写虚函数，且能保证命名正确
    class Player
    {
    public:
        Player() = default;
        virtual ~Player() = default;

        virtual void on_update(double delta)
        {
            cout << "111" << endl;
        }

        virtual void on_updata(double delta)
        {
            cout << "aaaa";
        }
    };

    class MainPlayer : public Player
    {
    public:
        using Player::Player;
        ~MainPlayer() = default;

        void on_update(double delta) final override
        {
            Player::on_update(delta);
            cout << "2222" << endl;
        }
    };

    class SecondPlayer final : public Player
    {
    public:
        using Player::Player;
        ~SecondPlayer() = default;
    };

    void character_4()
    {
        unique_ptr<Player> player(new MainPlayer());
        player->on_update(0.5);
        player->on_updata(1);
    }

    // 模板的优化,即增加默认参数
    template <class T, size_t N = 10>
    class Travel
    {
    public:
        Travel() = default;
        ~Travel() = default;

        Travel(T _nums)
        {
            this->nums = _nums;
        }

        void travel()
        {
            for (const auto &num : nums)
            {
                cout << num << endl;
            }
            cout << N << endl;
        }

    private:
        T nums;
    };

    void character_5()
    {
        std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        unique_ptr<Travel<std::vector<int>>> travel(new Travel<std::vector<int>>(nums));
        travel->travel();
    }

    // 字符类型的转换,val_to_str,str_to_val
    void character_6()
    {
        int val = 6;
        cout << to_string(val) << endl;
        cout << to_string((long)val) << endl;
        cout << to_string((long long)val) << endl;

        string str = "55";
        cout << stoi(str) << endl;
        cout << stol(str) << endl;
        cout << stoull(str) << endl;
    }

    // 普通断言若是不满足则程序直接结束(运行时才会发挥作用)
    // 静态断言若是不满足条件在编译时就会报错
    void character_7()
    {
        unique_ptr<int> a = make_unique<int>(5);
        assert(*a > 1);
        const int x = 5;
        static_assert(x == 5, "not 32");
    }

    // 异常声明
    // 基础try-catch-throw：try中的代码如果正常执行，则跳过catch，
    // 若出现异常：默认异常const exception& e,e.what()
    // 使用throw抛出特定异常
    // 动态异常声明noexcept:表示此函数不抛出异常
    struct MyException
    {
        string msg;
        MyException(const string &msg) : msg(msg) {}
        virtual ~MyException() = default;

        void print()
        {
            cout << msg << endl;
        }
    };

    double divisiton(int a, int b)
    {
        if (b == 0)
        {
            throw MyException("the son is zero");
        }
        return static_cast<double>(a / b);
    }

    void get_vec_val(const vector<int> &num) noexcept
    {
        int idx = 10;
        // assert(num.at(idx));
    }

    void character_8()
    {
        try
        {
            int a = 10, b = 5, c = 0;
            vector<int> d = {1, 2, 3};
            get_vec_val(d);
            divisiton(a, c);
        }
        catch (MyException e)
        {
            e.print();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    // auto和decltype自动类型推导
    // 用auto定义需要初始化,推导时说白了就是相当于一个或多个单词（占位符号）
    // auto只有在修饰指针或者volatile时才会记录const
    // auto：STL遍历，泛型编程
    // decltype规则：普通变量就是变量类型，函数则为其右值，传入纯左值就可以有修饰符号
    // 应用：泛型编程中推导类型，返回类型后置（与auto联合使用）
    // 区别：decltype：在不需要定义变量或者不能定义变量但是需要得到类型时才使用(基本都是模板里才会用到)
    template <typename T, typename U>
    auto adde(T t, U u)
    {
        return t + u;
    }

    template <typename R, typename T, typename U>
    R addf(T t, U u)
    {
        return t + u;
    }

    void character_9()
    {
        int tmp = 10;
        auto *a = &tmp;
        // cout << *a << endl;

        vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        for (auto it = vec.begin(); it != vec.end(); it++)
        {
            cout << *it << " ";
        }
        for (const auto &ve : vec)
        {
            cout << ve << " ";
        }
        cout << endl;

        decltype(tmp) b;
        cout << typeid(b).name() << endl;

        double tmp2 = 10.1;
        cout << addf<decltype(tmp + tmp2)>(tmp, tmp2) << endl;
        cout << adde(tmp, tmp2) << endl;
    }

    // 基于范围的for循环
    // 第一次确定范围，随后遍历，只进行一次
    // set和关联型容器如map和unordered_map这种是不能修改里边的first值的，也就是key值
    /*
    容器类型整理：
    1.序列容器：vector,  deque,  list,  forward_list
    2.有序关联容器：set,  multiset,  map,  multimap
    3.无序关联容器：unordered_set,  unordered_multiset,  unordered_map,  unordered_multimap
    4.容器适配器：stack,  queue, priority_queue
    5.其他：array,  string
    */
    void character_10()
    {
        vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        // 迭代器用法与指针相同
        for (auto it = a.begin(); it != a.end(); it++)
        {
            cout << (*it)++ << " ";
        }
        cout << endl;
        for (const auto &val : a)
        {
            cout << val << " ";
        }
        cout << endl;

        map<int, string> mp = {{1, "lucy"}, {2, "runb"}, {3, "nini"}};
        // m为pair对象，即键值对
        for (const auto &m : mp)
        {
            cout << m.first << " " << m.second << endl;
        }

        // set默认升序
        set<int> se = {1, 2, 35, 4, 5, 6};
        for (const auto &s : se)
        {
            cout << s << " ";
        }
        cout << *se.find(3);
    }

    // nullptr:解决c++中 ”NULL=0“ 的问题，引入nullptr专门用来初始化空类型指针，不做演示，总之这样用就ok了

    // lambda:匿名函数,
    /*
    []()opt ->return{ }
    []:& = a this
    ():不说
    */
    class Dog
    {
    public:
        Dog() = default;
        ~Dog() = default;

        void capture()
        {
            auto f = [&](int z) mutable
            {
                x++;
                y++;
                cout << x << " " << y << " " << x + y << endl;
                return x + y + z;
            };

            f(10);
        }

    private:
        int x = 5;
        int y = 10;
    };

    void character_11()
    {
        unique_ptr<Dog> dog = make_unique<Dog>();
        dog->capture();
    }

    // callback
    void character_12(std::function<void()> callback)
    {
        callback = []() {};
        callback();
    }

    /*--------------------------------------*/
    //               优化                    //
    /*--------------------------------------*/

    // constexpr:常量在编译时执行，反之在程序运行时执行
    // 表示只读的场景使用const,常量引用也是const，表明常量(编译时就确定的值)的场景用constexpr
    constexpr int add(int a, int b)
    {
        return a + b;
    }

    void character_13()
    {
        constexpr int coun = 15;
        cout << coun << endl;
        struct aaa
        {
            const int w = 0;
        };
        constexpr aaa a;
        cout << a.w << endl;
        cout << add(2, 3) << endl;
    }

    // 委托构造函数和继承构造函数
    class Bird
    {
    public:
        Bird() = default;
        Bird(int a)
        {
            this->a = a;
        }

        Bird(int a, int b) : Bird(a)
        {
            this->b = b;
        }

        Bird(int a, int b, int c) : Bird(a, b)
        {
            this->c = c;
        }

        void print_info()
        {
            cout << a << " " << b << " " << c << endl;
        }

    private:
        int a;
        int b;
        int c;
    };

    class Base
    {
    public:
        Base() = default;
        explicit Base(int x, int y) : x(x), y(y) {}
        explicit Base(const Base &base) : x(base.x), y(base.y) {}
        explicit Base(Base &&base) : x(base.x), y(base.y) {}

        virtual ~Base() = default;

        virtual void print_info()
        {
            cout << x << " " << y << " " << endl;
        }

    public:
        const int x;
        const int y;
    };

    class Child final : public Base
    {
    public:
        Child() = default;
        explicit Child(int x, int y, int z, int w) : Base(x, y), z(z), w(w) {}
        // 移动构造函数，将右值转化为左值，避免拷贝构造函数的开销
        explicit Child(Child &&child) : Base(child.x, child.y), z(child.z), w(child.w) {}

        ~Child() = default;

        void print_info() final override
        {
            Base::print_info();
            cout << z << endl;
            cout << w << endl;
            add();
        }

        void add()
        {
            cout << "aaa" << endl;
        }

    private:
        const int z = 5;
        const int w = 7;
    };

    void character_14()
    {
        shared_ptr<Bird> bird = make_shared<Bird>(1, 2, 8);
        unique_ptr<Base> child(new Child(1, 2, 3, 9));
        bird->print_info();
        child->print_info();
    }

    // 右值引用类型:&&
    // 左值引用类型:&
    // const Test& t可以返回任何引用类型
    // 对于需要动态申请大量资源的类，应该设计移动构造函数，以提高程序效率。需要注意的是，我们一般在提供移动构造函数的同时，也会提供常量左值引用的拷贝构造函数，以保证移动不成还可以使用拷贝构造函数
    /*
    值：左值（可取地址的值）
       右值（只能提供数据而无地址）
       |--纯右值（非引用返回的临时变量、运算表达式产生的临时变量、原始字面量和 lambda 表达式等）
       |--将亡值（与右值引用相关的表达式，比如，T&&类型函数的返回值、 std::move 的返回值等）
    */
    /*  特性：1.T&& 和 auto&&表示未定引用类型(const T&&为右值引用)

    */
    class Test
    {
    public:
        Test() : nums(new int(20))
        {
            cout << "create" << endl;
        }

        Test(const Test &test) : nums(new int(*test.nums))
        {
            cout << "create copy" << endl;
        }

        Test(Test &&a) : nums(a.nums) {}

        ~Test()
        {
            cout << "destroy" << endl;
        }

    public:
        shared_ptr<int> nums;
    };

    string str()
    {
        return "helkl";
    }

    template <typename T>
    void func(const T &&x)
    {
        T a = 5;
    }

    void character_15()
    {
        constexpr int a = 15; // a为左值，15是字面量，属于右值
        int &&b = 520;
        string &&c = str();
        func(10);
        // func(a);   //左值不可用
        Test test = Test();
        cout << *test.nums << endl;
        cout << "-------------" << endl;
    }

    // 转移和完美转发

};

int main(int argc, char **argv)
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    {
        using namespace Test;
        character_14();
    }

    return 0;
}