//
// Created by juan diego on 3/28/23.
//

#ifndef AVL_TREE_NODE_HPP
#define AVL_TREE_NODE_HPP

#include <list>
#include <ostream>
#include <functional>

template<typename Printable>
using Print = std::function<void(std::ostream &, const Printable &)>;

template<typename K, typename V>
struct node {
    K key;
    int height;
    node<K, V> *left;
    node<K, V> *right;

    explicit node(K key);

    virtual ~node();

    virtual void kill_self();

    virtual void print(std::ostream &os, Print<K> print_key, Print<V> print_value) = 0;
};

template<typename K, typename V>
struct pk_node : public node<K, V> {
    V record;

    explicit pk_node(K key, V value);

    ~pk_node();

    void print(std::ostream &os, Print<K> print_key, Print<V> print_value) override;
};


template<typename K, typename V>
struct non_pk_node : public node<K, V> {
    std::list<V> record;

    explicit non_pk_node(K key, V value);

    ~non_pk_node();

    void insert(V value);

    void print(std::ostream &os, Print<K> print_key, Print<V> print_value) override;
};


//< Gets the type of the node using `PK` value
template<bool PK, typename K, typename V>
struct node_type;

//< Gets the type of the record using `PK` value
template<bool PK, typename V>
struct record_type;

#endif //AVL_TREE_NODE_HPP
