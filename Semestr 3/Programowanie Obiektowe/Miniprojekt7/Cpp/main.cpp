#include <iostream>
#include <string>


//Zadanie 1
template<typename T>
T maximum(T const &a, T const &b)
{
    return a > b ? a : b;
}

//Zadania 3,5,6
template <typename T>
class X
{
private:
    //int x;
    T x;

public:
    X(){};

    // X(int _x)
    // {
    //     this->x = _x;
    // }

    X(T _x)
    {
        this->x = _x;
    }

    // int getX() const
    // {
    //     return x;
    // }

    T getX() const
    {
        return x;
    }

    friend std::ostream &operator << (std::ostream &os, X const &x)
    {
        os << x.x;
        return os;
    }

};

template <typename T>
bool operator > (X<T> const &a, X<T> const &b)
{
    return a.getX() > b.getX();
}

//Zadanie 8
template <>
bool operator > (X<std::string> const &a, X<std::string> const &b)
{
    return a.getX().size() > b.getX().size();
}

//Zadanie 9
template <typename T, typename C = X<T>>
class Y
{
    T zmienna;
    C klasaX;
};

//Zadanie 10
template <typename T>
class A
{
    typename T::id i;

public:
    void f() { i.g(); }
};

class B
{
public:
    class id
    {
    public:
        void g(){ std::cout<<"Hallo"<<std::endl;};
    };
};


//Zadanie 11
auto maxLambda = [](auto a, auto b)
{
    return a > b ? a : b;
};


int main()
{
    //Zadanie 2
    std::cout<<maximum(6, 7)<<std::endl;
    std::cout<<maximum(6.3, 7.3)<<std::endl;
    // std::cout<<maximum(6.5, 7)<<std::endl; //Nigdzie nie jest określone jaki typ danych ma zostać porównany: double czy int
    std::cout<<maximum<double>(4, 5)<<std::endl;
    std::cout<<maximum<double>(4.1, 5.7)<<std::endl;
    std::cout<<maximum<int>(4.6, 3)<<std::endl;
    std::cout<<maximum<double>(4.6, 3)<<std::endl;
    std::cout<<maximum<bool>(4.6, 3)<<std::endl;
    // std::cout<<maximum<std::string>(4.6, 3)<<std::endl; // Brak prostej konwersji int lub double do std::string
    std::cout<<maximum<std::string>("aaa", "bb")<<std::endl;

    //Zadanie 4
    // std::cout<<maximum(X(4), X(3))<<std::endl;

    //Zadanie 7
    std::cout<<maximum(X<int>(4), X<int>(3))<<std::endl;

    //Zadanie 8
    std::cout<<maximum(X<std::string>("aaa"), X<std::string>("bb"))<<std::endl;

    //Zadanie 9
    Y<int> y;
    Y<int, double> y2;

    //Zadanie 10
    A<B> ab;
    ab.f();

    //Zadanie 11
    bool b = maxLambda(3, 3.14);
    auto c = maxLambda(3, 3.14);

    std::cout<<b<<std::endl;
    std::cout<<c<<std::endl;

    return 0;
}