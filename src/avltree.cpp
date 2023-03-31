//
// Created by juan diego on 3/28/23.
//

#include "avltree.hpp"

template<bool PK, typename K, typename V, typename Greater, typename Index>
bool avl_tree<PK, K, V, Greater, Index>::find(K key, node<K, V> *node) {
    if (!node) {
        return false;
    }
    if (greater(key, node->key)) {
        return find(key, node->right);
    }
    if (greater(node->key, key)) {
        return find(key, node->left);
    }
    return true;
}

template<bool PK, typename K, typename V, typename Greater, typename Index>
bool avl_tree<PK, K, V, Greater, Index>::insert(V value, node<K, V> *&node) {
    if (!node) {
        node = new get_node<PK, K, V>::type(index(value), value);
        return true;
    }

    if (greater(index(value), node->key)) {
        return insert(value, node->right);
    }
    if (greater(node->key, index(value))) {
        return insert(value, node->left);
    }

    if (PK) {
        return false;
    }
    auto *copy = reinterpret_cast<non_pk_node<K, V> *>(node);
    copy->insert(value);
    return true;
}

template<bool PK, typename K, typename V, typename Greater, typename Index>
avl_tree<PK, K, V, Greater, Index>::RecordType avl_tree<PK, K, V, Greater, Index>::search(K key, node<K, V> *&node) {

    if (!node) {
        throw std::runtime_error("The key not exists!");
    }

    if (greater(key, node->key)) {
        return search(key, node->right);
    }
    if (greater(node->key, key)) {
        return search(key, node->left);
    }

    return reinterpret_cast<NodeType *>(node)->record;
}

template<bool PK, typename K, typename V, typename Greater, typename Index>
bool avl_tree<PK, K, V, Greater, Index>::remove(K key, node<K, V> *&node) {
    if (!node) {
        return false;
    }

    if (greater(key, node->key)) {
        return remove(key, node->right);
    }
    if (greater(node->key, key)) {
        return remove(key, node->left);
    }

    if (!node->right && !node->left) {
        delete node;
        node = nullptr;
    } else if (!node->left) {
        auto *temp = reinterpret_cast<NodeType *>(node);
        node = node->right;
        delete temp;
    } else if (!node->right) {
        auto *temp = reinterpret_cast<NodeType *>(node);
        node = node->left;
        delete temp;
    } else {
        NodeType *temp = get_min_node(node->right);
        reinterpret_cast<NodeType *>(node)->record = temp->record;
        node->key = temp->key;
        remove(node->key, node->right);
    }
}

template<bool PK, typename K, typename V, typename Greater, typename Index>
avl_tree<PK, K, V, Greater, Index>::NodeType *avl_tree<PK, K, V, Greater, Index>::get_min_node(node<K, V> *node) {
    while (node->left) {
        node = node->left;
    }
    return reinterpret_cast<NodeType *>(node);

}

template<bool PK, typename K, typename V, typename Greater, typename Index>
void avl_tree<PK, K, V, Greater, Index>::update_height() {

}

template<bool PK, typename K, typename V, typename Greater, typename Index>
void avl_tree<PK, K, V, Greater, Index>::balance() {

}

template<bool PK, typename K, typename V, typename Greater, typename Index>
avl_tree<PK, K, V, Greater, Index>::avl_tree(Index index, Greater greater) : n(0), root(nullptr), index(index) {
}


template<bool PK, typename K, typename V, typename Greater, typename Index>
bool avl_tree<PK, K, V, Greater, Index>::find(K key) {
    if (!root) {
        return false;
    }
    return find(key, root);
}

template<bool PK, typename K, typename V, typename Greater, typename Index>
bool avl_tree<PK, K, V, Greater, Index>::insert(V value) {
    if (insert(value, root)) {
        ++n;
        return true;
    }
    return false;
}

template<bool PK, typename K, typename V, typename Greater, typename Index>
avl_tree<PK, K, V, Greater, Index>::RecordType avl_tree<PK, K, V, Greater, Index>::search(K key) {
    return search(key, root);
}

template<bool PK, typename K, typename V, typename Greater, typename Index>
bool avl_tree<PK, K, V, Greater, Index>::remove(K key) {
    return remove(key, root);
}
