//
// Created by juan diego on 3/28/23.
//

#ifndef AVL_TREE_AVLTREE_HPP
#define AVL_TREE_AVLTREE_HPP

#include <queue>

#include "node.cpp"

template<typename Printable>
Print<Printable> print = [](std::ostream &os, const Printable &p) { os << p; };

/**
 * The AVL-tree is a self-balanced tree that makes sure that the binary-search-tree operations are always
 * made in a logarithmic complexity (search, delete and insert).
 *
 * In a avl-tree it is true that, for each node, his balancing factor is not greater than 1 and not lesser than -1.
 * If at any moment this clause is not true, the avl-tree automatically makes a rotation in order to balance the tree.
 *
 * @tparam PK boolean that determines if the avl-tree is indexing a primary key record or not
 * @tparam K the type of the key
 * @tparam V the type of data stored at leaf nodes
 * @tparam Greater callable used to define when a key is greater than another
 * @tparam Index callable used to obtain the index of a value
 */
template<bool PK,
        typename K,
        typename V,
        typename Greater = std::greater<K>,
        typename Index = std::function<K(V)>
>
class avl_tree {
public:
    using NodeType = node_type<PK, K, V>::type;
    using RecordType = record_type<PK, V>::type;

private:
    node<K, V> *root;           //< Is a reference to the first level of the tree
    Greater greater;            //< Receives two keys and returns true the first one is greater than the second
    Index index;                //< Receives a value and returns it corresponding key
    int n;                      //< Total number of keys in the tree

    /// `find` helper
    bool find(K key, node<K, V> *node);

    /// `insert` helper
    bool insert(V value, node<K, V> *&node);

    /// `search` helper
    RecordType search(K key, node<K, V> *&node);

    /// `remove` helper
    bool remove(K key, node<K, V> *&node);

    /// `remove` member function helper
    NodeType *get_min_node(node<K, V> *node);

    /// Access to the height of a node
    int height(node<K, V> *node);

    /// Updates the height of a node
    void update_height(node<K, V> *node);

    /**
     * Verifies if the `node` meets the balancing factor clause.
     * If not, a rotation is needed and calls to `left_rotation` or `right_rotation`
     * depending of the value of the balancing factor.
     */
    void balance(node<K, V> *&node);

    /// Calculates the balancing factor of a `node`
    inline int balancing_factor(node<K, V> *node);

    /// Makes a left rotation using `node` as reference
    void left_rotation(node<K, V> *&node);

    /// Makes a right rotation using `node` as reference
    void right_rotation(node<K, V> *&node);

public:

    explicit avl_tree(Index index, Greater greater = Greater());

    ~avl_tree();

    /// Returns `n`
    int size();

    /// Returns `true` if no value is stored and `false` otherwise
    bool empty();

    /// Frees up the memory in post-order and allows to continue using the tree
    void clear();

    /// Returns the height of the root
    int height();

    /// Returns `true` if `key` is in the tree and `false` otherwise
    bool find(K key);

    /// Inserts a new record on a node descending on the tree, if the node not exists, it is created
    bool insert(V value);

    /// Returns the record(s) which index attribute equals `key`
    RecordType search(K key);

    /// Deletes the record(s) which index attribute equals `key`
    bool remove(K key);

    /**
     * Prints all the AVL-tree
     *
     * Traverses all the tree using BFS
     *
     * @param os std::ostream object to output stream the tree in console or load it to a file
     * @param print_value function parameter that defines how to print a `V` type
     * @param print_key function parameter that defines how to print a `K` type
     */
    void print(std::ostream& os, Print<V> print_v = ::print<V>, Print<K> print_k = ::print<K>);
};


#endif //AVL_TREE_AVLTREE_HPP
