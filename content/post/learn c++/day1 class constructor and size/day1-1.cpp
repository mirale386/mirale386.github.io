#include <iostream>

class C1
{
};

class C2
{
public:
    void func() {}
};

class C3 : C2
{
};

class C4 : virtual C2
{
};

class C5
{
public:
    virtual void vfunc() {}
};

class C6 : C5
{
};

class C7 : virtual C5
{
};

int main()
{
    std::cout << "C1(empty class) size = " << sizeof(C1) << std::endl;
    std::cout << "C2(have a function) size = " << sizeof(C2) << std::endl;
    std::cout << "C3(extend C2) size = " << sizeof(C3) << std::endl;
    std::cout << "C4(virtual extend C2) size = " << sizeof(C4) << std::endl;
    std::cout << "C5(have a virtual function) size = " << sizeof(C5) << std::endl;
    std::cout << "C6(extend C5) size = " << sizeof(C6) << std::endl;
    std::cout << "C7(virtual extend C5) size = " << sizeof(C7) << std::endl;
}