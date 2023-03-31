//
// Created by juan diego on 3/28/23.
//

#include "avltree.hpp"

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

template<bool PK, typename K, typename V, typename Greater, typename Index>
bool avl_tree<PK, K, V, Greater, Index>::insert(V value, node<K, V> *&node) {
    if (!node) {
        node = new node_type<PK, K, V>::type(index(value), value);
        ++n;
        return true;
    }

    bool inserted;
    if (greater(index(value), node->key)) {
        inserted = insert(value, node->right);
    } else if (greater(node->key, index(value))) {
        inserted = insert(value, node->left);
    } else {
        if (!PK) {
            auto *copy = reinterpret_cast<non_pk_node<K, V> *>(node);
            copy->insert(value);
            return true;
        }
        return false;
    }

    if (inserted) {
        update_height(node);
        balance(node);
    }
    return inserted;
}

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

template<bool PK, typename K, typename V, typename Greater, typename Index>
bool avl_tree<PK, K, V, Greater, Index>::remove(K key, node<K, V> *&node) {
    if (!node) {
        return false;
    }

    bool removed;
    if (greater(key, node->key)) {
        removed = remove(key, node->right);
    } else if (greater(node->key, key)) {
        removed = remove(key, node->left);
    } else {
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
        --n;
        return true;
    }

    if (removed) {
        update_height(node);
        balance(node);
    }
    return removed;
}

//-----------------------------------------------------------------------------

template<bool PK, typename K, typename V, typename Greater, typename Index>
avl_tree<PK, K, V, Greater, Index>::NodeType *avl_tree<PK, K, V, Greater, Index>::get_min_node(node<K, V> *node) {
    while (node->left) {
        node = node->left;
    }
    return reinterpret_cast<NodeType *>(node);

}

//-----------------------------------------------------------------------------

template<bool PK, typename K, typename V, typename Greater, typename Index>
int avl_tree<PK, K, V, Greater, Index>::height(node<K, V> *node) {
    if (!node) {
        return -1;
    }
    return node->height;
}

//-----------------------------------------------------------------------------

template<bool PK, typename K, typename V, typename Greater, typename Index>
void avl_tree<PK, K, V, Greater, Index>::update_height(node<K, V> *node) {
    if (!node) {
        return;
    }
    node->height = std::max(this->height(node->left), this->height(node->right)) + 1;
}

//-----------------------------------------------------------------------------

template<bool PK, typename K, typename V, typename Greater, typename Index>
void avl_tree<PK, K, V, Greater, Index>::balance(node<K, V> *&node) {
    int bf = balancing_factor(node);

    if (bf >= 2) {
        if (balancing_factor(node->left) <= -1)
            left_rotation(node->left);
        right_rotation(node);
    }

    if (bf <= -2) {
        if (balancing_factor(node->right) >= 1)
            right_rotation(node->right);
        left_rotation(node);
    }
}

//-----------------------------------------------------------------------------

template<bool PK, typename K, typename V, typename Greater, typename Index>
inline int avl_tree<PK, K, V, Greater, Index>::balancing_factor(node<K, V> *node) {
    return this->height(node->left) - this->height(node->right);
}

//-----------------------------------------------------------------------------

template<bool PK, typename K, typename V, typename Greater, typename Index>
void avl_tree<PK, K, V, Greater, Index>::right_rotation(node<K, V> *&node) {
    ::node<K, V> *child = node->left;
    node->left = child->right;
    child->right = node;

    update_height(node);
    update_height(child);
    node = child;
}

//-----------------------------------------------------------------------------

template<bool PK, typename K, typename V, typename Greater, typename Index>
void avl_tree<PK, K, V, Greater, Index>::left_rotation(node<K, V> *&node) {
    ::node<K, V> *child = node->right;
    node->right = child->left;
    child->left = node;

    update_height(node);
    update_height(child);
    node = child;
}

//-----------------------------------------------------------------------------

template<bool PK, typename K, typename V, typename Greater, typename Index>
avl_tree<PK, K, V, Greater, Index>::avl_tree(Index index, Greater greater) : n(0), root(nullptr), index(index) {
}

//-----------------------------------------------------------------------------

template<bool PK, typename K, typename V, typename Greater, typename Index>
avl_tree<PK, K, V, Greater, Index>::~avl_tree() {
    if (root) {
        root->kill_self();
    }
}

//-----------------------------------------------------------------------------

template<bool PK, typename K, typename V, typename Greater, typename Index>
int avl_tree<PK, K, V, Greater, Index>::height() {
    return this->height(root);
}

//-----------------------------------------------------------------------------

template<bool PK, typename K, typename V, typename Greater, typename Index>
void avl_tree<PK, K, V, Greater, Index>::clear() {
    if (!root) {
        return;
    }

    root->kill_self();
    n = 0;
}

//-----------------------------------------------------------------------------

template<bool PK, typename K, typename V, typename Greater, typename Index>
bool avl_tree<PK, K, V, Greater, Index>::empty() {
    return !root;
}

//-----------------------------------------------------------------------------

template<bool PK, typename K, typename V, typename Greater, typename Index>
int avl_tree<PK, K, V, Greater, Index>::size() {
    return n;
}

//-----------------------------------------------------------------------------

template<bool PK, typename K, typename V, typename Greater, typename Index>
bool avl_tree<PK, K, V, Greater, Index>::find(K key) {
    if (!root) {
        return false;
    }
    return find(key, root);
}

//-----------------------------------------------------------------------------

template<bool PK, typename K, typename V, typename Greater, typename Index>
bool avl_tree<PK, K, V, Greater, Index>::insert(V value) {
    return insert(value, root);
}

//-----------------------------------------------------------------------------

template<bool PK, typename K, typename V, typename Greater, typename Index>
avl_tree<PK, K, V, Greater, Index>::RecordType avl_tree<PK, K, V, Greater, Index>::search(K key) {
    return search(key, root);
}

//-----------------------------------------------------------------------------

template<bool PK, typename K, typename V, typename Greater, typename Index>
bool avl_tree<PK, K, V, Greater, Index>::remove(K key) {
    return remove(key, root);
}

//-----------------------------------------------------------------------------

template<bool PK, typename K, typename V, typename Greater, typename Index>
void avl_tree<PK, K, V, Greater, Index>::print(std::ostream &os, Print<V> print_v, Print<K> print_k) {
    if (!root) {
        return;
    }

    std::queue<std::pair<node<K, V> *, int>> queue;
    int level = 0;
    queue.push({root, level});

    while (!queue.empty()) {
        auto &[node, lvl] = queue.front();
        queue.pop();

        if (lvl > level) {
            ++level;
            os << std::endl;
        }

        node->print(os, print_k, print_v);
        os << "    ";

        if (node->left) {
            queue.push({node->left, lvl + 1});
        }
        if (node->right) {
            queue.push({node->right, lvl + 1});
        }
    }
}

//-----------------------------------------------------------------------------
