#include "JednorekiBandyta.h"
#include "Logger.h"
#include "Stopper.h"


//Zad.14
void foo(JednorekiBandyta jb)
{
    std::cout<<jb.getCost()<<std::endl;
}

//Zad.18
void bar(const JednorekiBandyta &jb)
{
    std::cout<<jb.getRewardPercentage()<<std::endl;
}

//Zad.20
void baz(JednorekiBandyta &jb)
{
    std::cout<<jb.getWinProbability()<<std::endl;
}

//Zad.22
void qux(JednorekiBandyta &&jb)
{
    std::cout<<jb.getCost()<<std::endl;
}

int main()
{
    srand(time(NULL));

    JednorekiBandyta Game1; //Zad.8 Konstruktor domyślny
    JednorekiBandyta Game2(Game1); //Zad.10 Konstruktor kopiujący (deep copy)
    JednorekiBandyta Game3 = {100.0, 50.0, 0.1}; //Zad.12 Konstruktor konwertujący
    JednorekiBandyta Game4(std::move(Game3)); //Zad.11 Konstruktor przenoszący
    

    //std::cout<<"foo\n";
    JednorekiBandyta Game5;
    Game5.setCost(500.0);
    
    foo(Game5);                   //Zad.15 obiekt zostaje skopiowany (konstruktor kopiujący)
    foo(std::move(Game5));        //Zad.16 tworzony jest nowy obiekt, do którego przenoszone są wartości z obiektu Game5 (konstruktor przenoszący)
    foo({200.0, 100.0, 0.2});     //Zad.17 podane wartości są konwertowane do nowego obiektu (konstruktor konwertujący)


    //std::cout<<"bar\n";
    JednorekiBandyta Game6;
    Game6.setRewardPercentage(50);

    bar(Game6);                    //Zad.19/15 w funkcji nie jest tworzony nowy obiekt, operuje ona na Game6 bezpośrednio (konstruktor nie jest wywoływany)
    bar(std::move(Game6));         //Zad.19/16 funkcja przenosi obiekt Game6 do własnej instancji (konstruktor nie jest wywoływany)
    bar({200.0, 100.0, 0.2});      //Zad.19/17 podane wartości są konwertowane do nowego obiektu (konstruktor konwertujący)


    //std::cout<<"baz\n";
    JednorekiBandyta Game7;
    Game7.setWinProbability(0.5);

    baz(Game7);                   //Zad.21/15 w funkcji nie jest tworzony nowy obiekt, operuje ona na Game7 bezpośrednio (konstruktor nie jest wywoływany)
    //baz(std::move(Game7));      //Zad.21/16 błąd, przekazywane wartości muszą być non-const/lvalue
    //baz({200.0, 100.0, 0.2});   //Zad.21/17 jak powyżej


    //std::cout<<"qux\n";
    JednorekiBandyta Game8;
    Game8.setCost(500.0);

    //qux(Game8);                 //Zad.23/15 błąd, próba przekazania lvalue w miejsce rvalue
    qux(std::move(Game8));        //Zad.23/16 funkcja przenosi Game8 do własnej instancji, nie tworzy nowego (konstruktor nie jest wywoływany)
    qux({200.0, 100.0, 0.2});     //Zad.23/17 funkcja tworzy nowy obiekt, wywołuje konstruktor konwertujący

    
    Game1.log("Lorem ipsum"); //Zad.26 Aby można było wywołać tą funkcję dziedziczenie musi być publiczne
    

    JednorekiBandyta Game(1000.0, 50.0, 0.2);
    std::string action="play";
            
    int i=0;
    while(i<1){
        Game.play();
        Game.calcWinRate();
        //std::cout<<"Your win to lose ratio equals: "<<Game.getWinRate()<<"%"<<std::endl;
        //std::cout<<"Write \"play\" for another game, \"stop\" to finish playing."<<std::endl;
        // std::cin>>action;
        i++;
    }
    Game.Display();
    Game.Reset();
    //Game.Display();
}