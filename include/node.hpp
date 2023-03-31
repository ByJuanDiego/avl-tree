//
// Created by juan diego on 3/28/23.
//

#ifndef AVL_TREE_NODE_HPP
#define AVL_TREE_NODE_HPP

#include <list>

template<typename K, typename V>
struct node {
    K key;
    int height;
    node<K, V> *left;
    node<K, V> *right;

    explicit node(K key) : key(key), height(0), left(nullptr), right(nullptr) {}

    ~node() = default;

    virtual void kill_self() {
        if (left) {
            left->kill_self();
        }
        if (right) {
            left->kill_self();
        }
        delete this;
    }
};

template<typename K, typename V>
struct pk_node : public node<K, V> {
    V record;

    explicit pk_node(K key, V value) : node<K, V>(key), record(value) {}

    ~pk_node() = default;
};

template<typename K, typename V>
struct non_pk_node : public node<K, V> {
    std::list<V> record;

    explicit non_pk_node(K key, V value) : node<K, V>(key) {
        this->record.push_back(value);
    }

    ~non_pk_node() = default;

    void insert(V value) {
        this->record.push_back(value);
    }
};

template<bool PK, typename K, typename V>
struct get_node;

template<typename K, typename V>
struct get_node<true, K, V> {
    typedef pk_node<K, V> type;
};

template<typename K, typename V>
struct get_node<false, K, V> {
    typedef non_pk_node<K, V> type;
};

template<bool PK, typename V>
struct record_type;

template<typename V>
struct record_type<true, V> {
    typedef V type;
};

template<typename V>
struct record_type<false, V> {
    typedef std::list<V> type;
};

#endif //AVL_TREE_NODE_HPP
