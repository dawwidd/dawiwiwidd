#include <memory>
#include "wezel.hpp"


int main() {

    //Zad.4 C++ zwalnia pamięć zawsze i natychmiastowo, nie czeka z czyszczeniem aż dostępna pamięć się zapełni
    for(int i = 0; i < 10; i++) {
        //Zad.3
        //std::unique_ptr<Wezel>(new Wezel());

        //Zad.5/6 Wynik działania kodu z zad5 jest taki sam jak tego z zad3
        //std::shared_ptr<Wezel> w1 = std::make_shared<Wezel>();

        //Zad.8 Pamięć nie jest zwalniana, wskaźniki są zapętlone, wskazują jeden na drugiego
        // std::shared_ptr<Wezel> w1 = std::make_shared<Wezel>();
        // std::shared_ptr<Wezel> w2 = std::make_shared<Wezel>();
        // w1->wsk = w2;
        // w2->wsk = w1;

        //Zad.10 Wykorzystanie std::weak_ptr do rozwiązania problemu cyklicznych referencji
        std::shared_ptr<Wezel> w1 = std::make_shared<Wezel>();
        std::weak_ptr<Wezel> w2 = w1;
    }

    return 0;
}