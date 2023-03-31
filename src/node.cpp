//
// Created by juan diego on 3/28/23.
//

#include "node.hpp"

//-----------------------------------------------------------------------------

template<typename K, typename V>
node<K, V>::node(K key)  : key(key), height(0), left(nullptr), right(nullptr) {}

//-----------------------------------------------------------------------------

template<typename K, typename V>
node<K, V>::~node() = default;

//-----------------------------------------------------------------------------

template<typename K, typename V>
void node<K, V>::kill_self() {
    if (left) {
        left->kill_self();
    }
    if (right) {
        right->kill_self();
    }
    delete this;
}

//-----------------------------------------------------------------------------

template<typename K, typename V>
pk_node<K, V>::pk_node(K key, V value)  : node<K, V>(key), record(value) {}

//-----------------------------------------------------------------------------

template<typename K, typename V>
pk_node<K, V>::~pk_node() = default;

//-----------------------------------------------------------------------------

template<typename K, typename V>
void pk_node<K, V>::print(std::ostream &os, Print<K> print_key, Print<V> print_value) {
    os << "(";
    print_key(os, this->key);
    os << ", ";
    print_value(os, this->record);
    os << ")";
}

//-----------------------------------------------------------------------------

template<typename K, typename V>
non_pk_node<K, V>::non_pk_node(K key, V value) : node<K, V>(key) {
    this->record.push_back(value);
}

//-----------------------------------------------------------------------------

template<typename K, typename V>
non_pk_node<K, V>::~non_pk_node() = default;

//-----------------------------------------------------------------------------

template<typename K, typename V>
void non_pk_node<K, V>::insert(V value) {
    this->record.push_back(value);
}

//-----------------------------------------------------------------------------

template<typename K, typename V>
void non_pk_node<K, V>::print(std::ostream &os, Print<K> print_key, Print<V> print_value) {
    os << "(";
    print_key(os, this->key);
    os << ": {";
    for (auto it = record.begin(); it != record.end(); ++it) {
        print_value(os, *it);
        os << ((std::next(it) != record.end()) ? ", " : "");
    }
    os << "})";
}

//-----------------------------------------------------------------------------

template<typename K, typename V>
struct node_type<true, K, V> {
    typedef pk_node<K, V> type;
};

//-----------------------------------------------------------------------------

template<typename K, typename V>
struct node_type<false, K, V> {
    typedef non_pk_node<K, V> type;
};

//-----------------------------------------------------------------------------

template<typename V>
struct record_type<true, V> {
    typedef V type;
};

//-----------------------------------------------------------------------------

template<typename V>
struct record_type<false, V> {
    typedef std::list<V> type;
};

//-----------------------------------------------------------------------------
