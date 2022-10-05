#include <memory>
#include <iostream>

class Wezel {
    public:
    std::shared_ptr<Wezel> wsk;
    std::weak_ptr<Wezel> wskw;
    ~Wezel();
};