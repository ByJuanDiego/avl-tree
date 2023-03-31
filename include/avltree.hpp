//
// Created by juan diego on 3/28/23.
//

#ifndef AVL_TREE_AVLTREE_HPP
#define AVL_TREE_AVLTREE_HPP

#include <functional>
#include <iostream>
#include "node.hpp"

template<bool PK,
        typename K,
        typename V,
        typename Greater = std::greater<K>,
        typename Index = std::function<K(V)>
>
class avl_tree {
public:
    using NodeType = get_node<PK, K, V>::type;
    using RecordType = record_type<PK, V>::type;

private:
    node<K, V> *root;
    Greater greater;
    Index index;
    int n;

    bool find(K key, node<K, V> *node);

    bool insert(V value, node<K, V> *&node);

    RecordType search(K key, node<K, V> *&node);

    bool remove(K key, node<K, V> *&node);

    void update_height();

    void balance();

    NodeType *get_min_node(node<K, V> *node);

public:

    explicit avl_tree(Index index, Greater greater = Greater());

    bool find(K key);

    bool insert(V value);

    RecordType search(K key);

    bool remove(K key);
};


#endif //AVL_TREE_AVLTREE_HPP
