#include <iostream>
#include <utility>
#include "avltree.cpp"

struct tx {
    int amount;
    std::string emisor;

    explicit tx(int am, std::string em) : amount(am), emisor(std::move(em)) {}

    friend std::ostream& operator<<(std::ostream& os, const tx& t) {
        os << "(" << t.amount << ", " << t.emisor << ")";
        return os;
    }
};

int main() {
    std::function<int(const tx*)> index = [&](const tx* t){
        return t->amount;
    };
    avl_tree<true, int, tx *, std::greater<>, decltype(index)> avl(index);
    std::cout << avl.insert(new tx(1, "papas")) << std::endl;
    std::cout << avl.insert(new tx(1, "papas")) << std::endl;

    std::cout << avl.find(1) << std::endl;
    avl.remove(1);
    std::cout << avl.find(1) << std::endl;

//    for (auto x : avl.search(1)) {
//        std::cout << *x << std::endl;
//    }
//    std::cout << *avl.search(1) << std::endl;
    return EXIT_SUCCESS;
}
