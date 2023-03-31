#include <iostream>
#include <iomanip>

#include "avltree.cpp"
#include "transaction.hpp"

void primary_key_indexing() {
    std::function<int(const transaction *)> index = [&](const transaction *t) {
        return t->amount;
    };
    avl_tree<true, int, transaction *, std::greater<>, decltype(index)> avl(index);
    std::cout << avl.insert(new transaction("u1", "u2", 1)) << std::endl;
    std::cout << avl.insert(new transaction("ux", "uv", 1)) << std::endl;
    std::cout << avl.insert(new transaction("u9", "u2", 1)) << std::endl;
    std::cout << avl.insert(new transaction("u3", "u5", 1)) << std::endl;

    std::cout << avl.insert(new transaction("u4", "u3", 2)) << std::endl;

    std::cout << avl.insert(new transaction("u4", "u3", 3)) << std::endl;
    std::cout << avl.insert(new transaction("u4", "u3", 6)) << std::endl;
    std::cout << avl.insert(new transaction("u4", "u3", 9)) << std::endl;

    std::cout << avl.insert(new transaction("u4", "u3", 10)) << std::endl;
    std::cout << avl.insert(new transaction("u4", "u3", 11)) << std::endl;
    std::cout << avl.insert(new transaction("u4", "u3", 11)) << std::endl;
    std::cout << avl.insert(new transaction("u4", "u3", 4)) << std::endl;

    avl.remove(11);
    avl.remove(10);

    avl.print(std::cout, [](std::ostream &os, transaction *tx) {
        os << std::quoted(tx->to_string());
    });
    std::cout << std::endl;

    std::cout << std::quoted(avl.search(1)->to_string()) << std::endl;
}

void non_primary_key_indexing() {
    std::function<int(const transaction *)> index = [&](const transaction *t) {
        return t->amount;
    };
    avl_tree<false, int, transaction *, std::greater<>, decltype(index)> avl(index);
    std::cout << avl.insert(new transaction("u1", "u2", 1)) << std::endl;
    std::cout << avl.insert(new transaction("ux", "uv", 1)) << std::endl;
    std::cout << avl.insert(new transaction("u9", "u2", 1)) << std::endl;
    std::cout << avl.insert(new transaction("u3", "u5", 1)) << std::endl;

    std::cout << avl.insert(new transaction("u4", "u3", 2)) << std::endl;

    std::cout << avl.insert(new transaction("u4", "u3", 3)) << std::endl;
    std::cout << avl.insert(new transaction("u4", "u3", 6)) << std::endl;
    std::cout << avl.insert(new transaction("u4", "u3", 9)) << std::endl;

    std::cout << avl.insert(new transaction("u4", "u3", 10)) << std::endl;
    std::cout << avl.insert(new transaction("u4", "u3", 11)) << std::endl;
    std::cout << avl.insert(new transaction("u4", "u3", 11)) << std::endl;
    std::cout << avl.insert(new transaction("u4", "u3", 4)) << std::endl;
    std::cout << "size: " << avl.size() << std::endl;

    avl.remove(11);
    avl.remove(10);

    avl.print(std::cout, [](std::ostream &os, transaction *tx) {
        os << std::quoted(tx->to_string());
    });
    std::cout << std::endl;

    for (transaction *tx: avl.search(1)) {
        std::cout << std::quoted(tx->to_string()) << std::endl;
    }

    std::cout << "size: " << avl.size() << std::endl;
}

int main() {
    primary_key_indexing();
    non_primary_key_indexing();
    return EXIT_SUCCESS;
}
