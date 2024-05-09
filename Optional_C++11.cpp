#include <iostream>
#include <string>

#define NULL_VAL -128

template<typename T>
class Optional
{
public: 
    constexpr Optional() = default;
    constexpr Optional(const T& V) : Value(V), Flag(true){};

    [[nodiscard]] T Get() const
    {
        return Flag ? Value : static_cast<T>(NULL_VAL);
    }

    void operator = (const T& V)
    {
        Value = V;
        Flag = true;
    }

    friend std::ostream& operator << (std::ostream& OS, const Optional& Obj) 
    {
        return OS << Obj.Get();
    }

private:
    T Value{};
    bool Flag{false};
};

template<>
std::string Optional<std::string>::Get() const
{
    return Flag ? Value : "";
}

template<typename T>
class Optional<T*>
{
public: 
    constexpr Optional() = default;
    constexpr Optional(T* V) : Value(V){};

    [[nodiscard]] const T* Get() const
    {
        return Value;
    }

    void operator = (const T& V)
    {
        Value = &V;
    }

    const T operator*() const 
    { 
        return *Value;
    }

    friend std::ostream& operator << (std::ostream& OS, const Optional& Obj) 
    {
        return Obj.Get() == nullptr ? OS : OS << Obj.Get();
    }

private:
    T* Value{nullptr};
};

int main()
{
    Optional<int> a = 3;
    a = 5;
    Optional<float> b;

    int temp = 7;
    Optional<int*> c = &temp;

    Optional<const char*> d = "fekfj";

    Optional<const char*> e;
    const char* print = (e.Get() == nullptr) ? "nullptr" : "not nullptr";

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << *c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;
    std::cout << print << std::endl;
}
 
