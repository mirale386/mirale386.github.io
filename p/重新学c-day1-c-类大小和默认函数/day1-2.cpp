class Test
{
public:
    Test();
    ~Test();

    Test(const Test &);
    Test &operator=(const Test &);

    Test *operator&();
    Test const *operator&() const;

    Test(Test &&);
    Test &operator=(Test &&);
};