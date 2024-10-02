/*
练习一些知识点
*/

#include <bits/stdc++.h>

class Student
{
public:
    Student() = default;
    ~Student() = default;

    int get_x()
    {
        return this->x;
    }

private:
    int x = 5;
};

template <typename T>
void Swap(T &a, T &b)
{
    T tem = a;
    a = b;
    b = tem;
}

int main()
{
    Student *st;
    st = new Student();
    std::cout << st->get_x();
    delete st;
    int a = 5, b = 110;
    Swap<int>(a, b);
    double x=2.6,y=5.1;
    Swap<double>(x,y);

    return 0;
}