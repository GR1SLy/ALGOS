#ifndef UNTITLED11_MYBST_H
#define UNTITLED11_MYBST_H

#include <iostream>
#include "NodeBST.h"
#include <list>
#include <stack>
#include <queue>
#include <utility>

using std::cout;
using std::endl;

template <typename T, typename K>
class MyBST {
public:
    MyBST() : size(0), root(nullptr) {}

    explicit MyBST(MyBST* a) {
        Copy(a->root);
    }

    ~MyBST() {
        Clear(root);
    }

    int GetSize() {
        return size;
    }

    int GetNum() {
        return NumOfViews;
    }

    void SetNum() {
        NumOfViews = 0;
    }

    void IncNum() {
        NumOfViews++;
    }

    void Clear(NodeBST<T, K>* t) {
        if (t == nullptr) 
            return;
        Clear(t->left);
        Clear(t->right);
        delete t;
        IncNum();
        size--;
        root = nullptr;
    }

    bool IsEmpty() {
        return root == nullptr;
    }

    int Insert(K k, T data) {
        NodeBST<T, K>** current = &root;

        while (*current != nullptr) {
            IncNum();
            if (k == (*current)->key) {
                return 0;
            }
            if (k < (*current)->key) {
                current = &(*current)->left;
            }
            else {
                current = &(*current)->right;
            }
        }

        *current = new NodeBST<T, K>(data, k);
        IncNum();
        size++;
        return 1;
    }

    void L_t_R(NodeBST<T, K>* t) {
        if (!t)
            return;
        if (t->left)
            L_t_R(t->left);
        cout << t->key << " ";
        if (t->right)
            L_t_R(t->right);
    }

    NodeBST<T, K>* GetRoot() {
        return root;
    }

    void Copy(NodeBST<T, K>* t) {
        if (t == nullptr) return;
        Insert(t->key, t->value);
        Copy(t->left);
        Copy(t->right);
    }

    NodeBST<T, K>* Search(K k) {
        NodeBST<T, K>* current = root;

        if (current != nullptr) {
            while (current != nullptr) {
                if (k == current->key) {
                    return current;
                }
                if (k < current->key) {
                    current = current->left;
                    IncNum();
                }
                else {
                    current = current->right;
                    IncNum();
                }
            }
        }

        throw std::invalid_argument("Exception");
    }

    int ReplaceByKey(K k, T data) {
        NodeBST<T, K>* tt = Search(k);
        if (tt == nullptr) {
            return 0;
        }
        else {
            tt->value = data;
            return 1;
        }
    }

    int Delete(K k) {
        NodeBST<T, K>** current = &root;
        NodeBST<T, K>* parent = nullptr;

        while (*current != nullptr && (*current)->key != k) {
            IncNum();
            parent = *current;
            if (k < (*current)->key) {
                current = &(*current)->left;
            }
            else {
                current = &(*current)->right;
            }
        }

        if (*current == nullptr) {
            return 0;
        }

        NodeBST<T, K>* toDelete = *current;
        IncNum();

        if (toDelete->left == nullptr || toDelete->right == nullptr) {
            *current = (toDelete->left != nullptr) ? toDelete->left : toDelete->right;
            if (*current != nullptr) {
                IncNum();
            }
            delete toDelete;
            size--;
            return 1;
        }

        NodeBST<T, K>** minNode = &toDelete->right;
        while ((*minNode)->left != nullptr) {
            IncNum();
            minNode = &(*minNode)->left;
        }

        toDelete->key = (*minNode)->key;
        toDelete->value = (*minNode)->value;

        NodeBST<T, K>* temp = *minNode;
        *minNode = (*minNode)->right;
        if (*minNode != nullptr) {
            IncNum();
        }
        delete temp;
        size--;

        return 1;
    }

    void Show(NodeBST<T, K>* t, int level) {
        if (t == nullptr && level == 0) {
            cout << "Tree is empty" << endl;
            return;
        }

        if (t == nullptr) {
            for (int i = 0; i < 3 * level; i++)
                cout << "   ";
            cout << "*" << endl;
            return;
        }
        Show(t->right, level + 1);
        for (int i = 0; i < 2 * level; i++)
            cout << "   ";
        cout << t->key << " " << t->value << endl;
        Show(t->left, level + 1);
    }

    int Height(NodeBST<T, K>* t) {
        if (t == nullptr) 
            return 0;
        IncNum();
        return 1 + std::max(Height(t->left), Height(t->right));
    }

    int ExternalPathLength() {
        return ExternalPathLengthHelper(root, 0);
    }

    int ExternalPathLengthHelper(NodeBST<T, K>* node, int depth) {
    if (node == nullptr) return 0;
    IncNum();
    if (node->left == nullptr && node->right == nullptr) {
        std::cout << "Leaf: " << node->key << "; depth: " << depth << std::endl;
        return depth; // Только листья
    }
    return ExternalPathLengthHelper(node->left, depth + 1) + 
           ExternalPathLengthHelper(node->right, depth + 1);
    }

    NodeBST<T, K>* Min(NodeBST<T, K>* node) const {
        if (node == nullptr) return nullptr;
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    NodeBST<T, K>* Max(NodeBST<T, K>* node) const {
        if (!node) return nullptr;
        while (node->right) {
            node = node->right;
        }
        return node;
    }

    NodeBST<T, K>* GetNext(NodeBST<T, K>* node) const {
        if (!node) return nullptr;

        if (node->right) {
            return Min(node->right);
        }

        NodeBST<T, K>* current = root;
        NodeBST<T, K>* successor = nullptr;

        while (current) {
            if (node->key < current->key) {
                successor = current;
                current = current->left;
            }
            else if (node->key > current->key) {
                current = current->right;
            }
            else {
                break;
            }
        }
        return successor;
    }

    NodeBST<T, K>* GetPrev(NodeBST<T, K>* node) const {
        if (!node) return nullptr;

        if (node->left) {
            return Max(node->left);
        }

        NodeBST<T, K>* current = root;
        NodeBST<T, K>* predecessor = nullptr;

        while (current) {
            if (node->key > current->key) {
                predecessor = current;
                current = current->right;
            }
            else if (node->key < current->key) {
                current = current->left;
            }
            else {
                break;
            }
        }
        return predecessor;
    }

    class Iterator {
        MyBST* p;
        NodeBST<T, K>* cur;
    public:
        explicit Iterator(NodeBST<T, K>* cur_, MyBST* p_) : cur(cur_), p(p_) {};
        T& operator* () { 
            if (p->GetSize() == 0 || cur == nullptr) throw std::invalid_argument("Exception");
            return cur->value;
        }
        Iterator& operator++() {
            if (cur != nullptr) {
                cur = p->GetNext(cur);
            }
            return *this;
        }
        Iterator& operator--() {
            if (cur) {
                cur = p->GetPrev(cur);
            }
            else {
                cur = p->Max(p->GetRoot());
            }
            return *this;
        }
        bool operator==(const Iterator& it) { 
            return cur == it.cur;
        }
        bool operator!=(const Iterator& it) { 
            return cur != it.cur; 
        }
    };

    class ReverseIterator {
        MyBST* p;
        NodeBST<T, K>* cur;
    public:
        ReverseIterator(NodeBST<T, K>* cur_, MyBST* p_) : cur(cur_), p(p_) {};
        T& operator* () { 
            if (p->GetSize() == 0 || cur == nullptr) throw std::invalid_argument("Exception");
            return cur->value;
        }
        ReverseIterator& operator++() {
            if (cur) {
                cur = p->GetPrev(cur);
            }
            return *this;
        }
        ReverseIterator& operator--() {
            if (cur) {
                cur = p->GetNext(cur);
            }
            else {
                cur = p->Min(p->GetRoot());
            }
            return *this;
        }
        bool operator==(const ReverseIterator& it) { 
            return cur == it.cur; 
        }
        bool operator!=(const ReverseIterator& it) { 
            return cur != it.cur; 
        }
    };

    Iterator begin() {
        NodeBST<T, K>* t = root;
        if (t != nullptr) {
            while (t->left != nullptr) t = t->left;
        }
        return Iterator(t, this);
    }
    Iterator end() {
        NodeBST<T, K>* t = root;
        if (t != nullptr) {
            while (t->right != nullptr) t = t->right;
        }
        return Iterator(t->right, this);
    }

    ReverseIterator rbegin() {
        NodeBST<T, K>* t = root;
        if (t != nullptr) {
            while (t->right != nullptr) t = t->right;
        }
        return ReverseIterator(t, this);
    }
    ReverseIterator rend() {
        NodeBST<T, K>* t = root;
        if (t != nullptr) {
            while (t->left != nullptr) t = t->left;
        }
        return ReverseIterator(t->left, this);
    }

private:
    int size = 0;
    NodeBST<T, K>* root = nullptr;
    static int NumOfViews;
};

template class MyBST<int, int>;
typedef unsigned long long INT_64;
template class MyBST<INT_64, int>;

template <typename T, typename K>
int MyBST<T, K>::NumOfViews = 0;

#endif 