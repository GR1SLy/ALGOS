#ifndef RBTREE_H
#define RBTREE_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <vector>


template <typename KeyType, typename DataType>
class RBTree {
private:
    enum Color { RED, BLACK };

    struct Node {
        KeyType key;
        DataType data;
        Node *left, *right, *parent;
        Color color;

        Node(const KeyType& k, const DataType& d, Color c = RED, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr)
            : key(k), data(d), color(c), parent(p), left(l), right(r) {} 

    };

    Node* root;
    size_t count;
    mutable size_t nodesVisited; 

    Color getColor(Node* node) const {
        if (node == nullptr) return BLACK; 
        return node->color;
    }

    void setColor(Node* node, Color color) {
        if (node == nullptr) return;
        node->color = color;
    }

    void leftRotate(Node* x) {
        nodesVisited++;
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* y) {
        nodesVisited++;
        Node* x = y->left;
        y->left = x->right;
        if (x->right != nullptr) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nullptr) {
            this->root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
        x->right = y;
        y->parent = x;
    }

    void insertFixup(Node* z) { 
        while (z != root && getColor(z->parent) == RED) {
            nodesVisited++;
            Node* parent_z = z->parent;
            Node* grandparent_z = parent_z->parent; 

            if (parent_z == grandparent_z->left) {
                Node* uncle_z = grandparent_z->right;
                if (getColor(uncle_z) == RED) { 
                    setColor(parent_z, BLACK);
                    setColor(uncle_z, BLACK);
                    setColor(grandparent_z, RED);
                    z = grandparent_z; 
                } else { 
                    if (z == parent_z->right) {
                        z = parent_z;
                        leftRotate(z);
                        parent_z = z->parent;
                    }
                    setColor(parent_z, BLACK);
                    setColor(grandparent_z, RED); 
                    rightRotate(grandparent_z);
                }
            } else { 
                Node* uncle_z = grandparent_z->left;
                if (getColor(uncle_z) == RED) {
                    setColor(parent_z, BLACK);
                    setColor(uncle_z, BLACK);
                    setColor(grandparent_z, RED);
                    z = grandparent_z;
                } else {
                    if (z == parent_z->left) {
                        z = parent_z;
                        rightRotate(z);
                        parent_z = z->parent;
                    }
                    setColor(parent_z, BLACK);
                    setColor(grandparent_z, RED);
                    leftRotate(grandparent_z);
                }
            }
        }
        setColor(this->root, BLACK);
    }

    void transplant(Node* u, Node* v) {
        nodesVisited++;
        if (u->parent == nullptr) {
            this->root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    Node* findMinNodeInSubtree(Node* node) const {
        if (!node) return nullptr;
        while (node->left != nullptr) {
            nodesVisited++;
            node = node->left;
        }
        return node;
    }

    Node* findMaxNodeInSubtree(Node* node) const {
        if (!node) return nullptr;
        while (node->right != nullptr) {
            nodesVisited++;
            node = node->right;
        }
        return node;
    }

    void removeFixup(Node* x, Node* xp) {
        while (x != root && getColor(x) == BLACK) {
            nodesVisited++;
            if (xp == nullptr) { 
                break;
            }

            if (x == xp->left) {
                Node* w = xp->right; 
                if (getColor(w) == RED) { 
                    setColor(w, BLACK);
                    setColor(xp, RED);
                    leftRotate(xp);
                    w = xp->right;
                }
                if (w == nullptr) {
                    x = xp;
                    xp = xp->parent;
                    continue;
                }
                if (getColor(w->left) == BLACK && getColor(w->right) == BLACK) { 
                    setColor(w, RED);
                    x = xp;
                    xp = xp->parent;
                } else {
                    if (getColor(w->right) == BLACK) {
                        setColor(w->left, BLACK);
                        setColor(w, RED);
                        rightRotate(w);
                        w = xp->right;
                    }
                    if (w == nullptr) { 
                         x = xp; xp = xp->parent; continue;
                    }
                    setColor(w, getColor(xp));
                    setColor(xp, BLACK);
                    setColor(w->right, BLACK);
                    leftRotate(xp);
                    x = root;
                }
            } else { 
                Node* w = xp->left; 
                if (getColor(w) == RED) {
                    setColor(w, BLACK);
                    setColor(xp, RED);
                    rightRotate(xp);
                    w = xp->left;
                }
                if (w == nullptr) {
                    x = xp;
                    xp = xp->parent;
                    continue;
                }
                if (getColor(w->right) == BLACK && getColor(w->left) == BLACK) {
                    setColor(w, RED);
                    x = xp;
                    xp = xp->parent;
                } else {
                    if (getColor(w->left) == BLACK) { 
                        setColor(w->right, BLACK);
                        setColor(w, RED);
                        leftRotate(w);
                        w = xp->left;
                    }
                     if (w == nullptr) { 
                         x = xp; xp = xp->parent; continue;
                     }
                    setColor(w, getColor(xp));
                    setColor(xp, BLACK);
                    setColor(w->left, BLACK);
                    rightRotate(xp);
                    x = root;
                }
            }
        }
        if (x != nullptr) { 
            setColor(x, BLACK);
        }
    }


    Node* findNodeRecursive(Node* current, const KeyType& key) const {
        nodesVisited++;
        if (current == nullptr || current->key == key) {
            return current;
        }
        if (key < current->key) {
            return findNodeRecursive(current->left, key);
        } else {
            return findNodeRecursive(current->right, key);
        }
    }

    void clearRecursive(Node* node) {
        if (node != nullptr) {
            clearRecursive(node->left);
            clearRecursive(node->right);
            delete node;
        }
    }

    Node* copyRecursive(Node* sourceNode, Node* parentNode) {
        if (sourceNode == nullptr) {
            return nullptr;
        }
        Node* newNode = new Node(sourceNode->key, sourceNode->data, sourceNode->color, parentNode);
        newNode->left = copyRecursive(sourceNode->left, newNode);
        newNode->right = copyRecursive(sourceNode->right, newNode);
        return newNode;
    }

public:
    class ForwardIterator;
    class ReverseIterator;

    RBTree() : root(nullptr), count(0), nodesVisited(0) {}

    RBTree(const RBTree& other) : root(nullptr), count(0), nodesVisited(0) {
        root = copyRecursive(other.root, nullptr);
        count = other.count;
    }

    RBTree& operator=(const RBTree& other) {
        if (this != &other) {
            clear();
            root = copyRecursive(other.root, nullptr);
            count = other.count;
        }
        return *this;
    }

    ~RBTree() {
        clearRecursive(root);
    }

    size_t getSize() const {
        return count;
    }

    bool isEmpty() const {
        return count == 0;
    }

    bool clear() {
        clearRecursive(root);
        root = nullptr;
        count = 0;
        nodesVisited = 0;
        return true;
    }

    DataType& operator[](const KeyType& key) {
        nodesVisited = 0;
        Node* node = findNodeRecursive(root, key);
        if (node != nullptr) {
            return node->data;
        } else {
            DataType default_val = DataType();
            insert(key, default_val);
            Node* inserted_node = findNodeRecursive(root, key); 
            if(inserted_node) return inserted_node->data;
            else {
                 throw std::runtime_error("RBTree::operator[]: Critical error - node not found after insert.");
            }
        }
    }

    DataType& find(const KeyType& key) {
        return this->operator[](key);
    }

    bool insert(const KeyType& key, const DataType& data) {
        nodesVisited = 0;
        Node* z = new Node(key, data);
        
        Node* y = nullptr;
        Node* x = this->root;

        while(x != nullptr){
            nodesVisited++;
            y = x;
            if(z->key < x->key){
                x = x->left;
            } else if (z->key > x->key) {
                x = x->right;
            } else { 
                x->data = data; 
                delete z;       
                return true;    
            }
        }
        
        z->parent = y;
        if (y == nullptr) {
            this->root = z;
            nodesVisited++;
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }

        insertFixup(z);
        count++;
        return true;
    }

    bool remove(const KeyType& key) {
        nodesVisited = 0;
        Node* z = findNodeRecursive(root, key);
        if (z == nullptr) {
            return false;
        }

        Node* y = z;
        Node* x = nullptr;
        Node* xp = nullptr;
        Color originalColor_of_y = getColor(y);

        if (z->left == nullptr) {
            x = z->right;
            xp = z->parent;
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            x = z->left;
            xp = z->parent;
            transplant(z, z->left);
        } else {
            y = findMinNodeInSubtree(z->right);
            originalColor_of_y = getColor(y);
            x = y->right;

            if (y->parent == z) {
                xp = y;
                if (x != nullptr) {
                    x->parent = y;
                }
            } else {
                xp = y->parent;
                transplant(y, y->right);
                y->right = z->right;
                if (y->right != nullptr) {
                    y->right->parent = y;
                }
            }
            transplant(z, y);
            y->left = z->left;
            if (y->left != nullptr) {
                y->left->parent = y;
            }
            setColor(y, getColor(z));
        }

        delete z;
        count--;

        if (originalColor_of_y == BLACK) {
            Node* actual_parent_for_fixup = (x != nullptr) ? x->parent : xp;
            removeFixup(x, actual_parent_for_fixup);
        }
        
        if (this->root != nullptr) {
            setColor(this->root, BLACK);
        }
        return true;
    }

    size_t getNodesVisited() const {
        return nodesVisited;
    }

    void clearNodesVisited() {
        nodesVisited = 0;
    }

    class ForwardIterator {
    private:
        const RBTree* tree_ptr;
        Node* current_node;

        Node* getMinInSubtree(Node* node) const {
            if (!node) return nullptr;
            while (node->left) node = node->left;
            return node;
        }

        Node* getMaxInSubtree(Node* node) const {
            if (!node) return nullptr;
            while (node->right) node = node->right;
            return node;
        }

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = DataType;
        using difference_type = std::ptrdiff_t;
        using pointer = DataType*;
        using reference = DataType&;

        ForwardIterator(const RBTree* t, Node* n) : tree_ptr(t), current_node(n) {}

        reference operator*() const {
            if (!current_node) {
                 throw std::out_of_range("Dereferencing end or invalid iterator");
            }
            return current_node->data;
        }

        const KeyType& getKey() const {
             if (!current_node) {
                 throw std::out_of_range("Accessing key from end or invalid iterator");
            }
            return current_node->key;
        }


        ForwardIterator& operator++() {
            if (!current_node) {
                throw std::out_of_range("Incrementing end or invalid iterator");
            }

            if (current_node->right != nullptr) {
                current_node = getMinInSubtree(current_node->right);
            } else {
                Node* p = current_node->parent;
                while (p != nullptr && current_node == p->right) {
                    current_node = p;
                    p = p->parent;
                }
                current_node = p;
            }
            return *this;
        }

        ForwardIterator operator++(int) {
            ForwardIterator temp = *this;
            ++(*this);
            return temp;
        }
        
        ForwardIterator& operator--() {
            if (!tree_ptr || tree_ptr->isEmpty()) {
                throw std::out_of_range("Decrementing iterator on empty or invalid tree");
            }
            if (!current_node) {
                 current_node = getMaxInSubtree(tree_ptr->root);
                 if (!current_node) {
                     throw std::out_of_range("Cannot decrement end iterator of an empty tree");
                 }
                 return *this;
            }
            if (current_node == getMinInSubtree(tree_ptr->root)) {
                 throw std::out_of_range("Decrementing past the beginning of the tree");
            }

            if (current_node->left != nullptr) {
                current_node = getMaxInSubtree(current_node->left);
            } else {
                Node* p = current_node->parent;
                while (p != nullptr && current_node == p->left) {
                    current_node = p;
                    p = p->parent;
                }
                current_node = p;
            }
            return *this;
        }

        ForwardIterator operator--(int) {
            ForwardIterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const ForwardIterator& other) const {
            return current_node == other.current_node && tree_ptr == other.tree_ptr;
        }

        bool operator!=(const ForwardIterator& other) const {
            return !(*this == other);
        }
    };

    class ReverseIterator {
    private:
        const RBTree* tree_ptr;
        Node* current_node;
        
        Node* getMinInSubtree(Node* node) const {
            if (!node) return nullptr;
            while (node->left) node = node->left;
            return node;
        }

        Node* getMaxInSubtree(Node* node) const {
            if (!node) return nullptr;
            while (node->right) node = node->right;
            return node;
        }

    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = DataType;
        using difference_type = std::ptrdiff_t;
        using pointer = DataType*;
        using reference = DataType&;

        ReverseIterator(const RBTree* t, Node* n) : tree_ptr(t), current_node(n) {}
        
        reference operator*() const {
             if (!current_node) {
                 throw std::out_of_range("Dereferencing rend or invalid reverse iterator");
            }
            return current_node->data;
        }

        const KeyType& getKey() const {
             if (!current_node) {
                 throw std::out_of_range("Accessing key from rend or invalid reverse iterator");
            }
            return current_node->key;
        }

        ReverseIterator& operator++() {
             if (!current_node) {
                 throw std::out_of_range("Incrementing rend or invalid reverse iterator");
            }
        
            if (tree_ptr && current_node == getMinInSubtree(tree_ptr->root)) {
                 current_node = nullptr;
                 return *this;
            }

            if (current_node->left != nullptr) {
                current_node = getMaxInSubtree(current_node->left);
            } else {
                Node* p = current_node->parent;
                while (p != nullptr && current_node == p->left) {
                    current_node = p;
                    p = p->parent;
                }
                current_node = p;
            }
            return *this;
        }

        ReverseIterator operator++(int) {
            ReverseIterator temp = *this;
            ++(*this);
            return temp;
        }

        ReverseIterator& operator--() {
            if (!tree_ptr || tree_ptr->isEmpty()) {
                throw std::out_of_range("Decrementing reverse iterator on empty or invalid tree");
            }
            if (!current_node) {
                 current_node = getMinInSubtree(tree_ptr->root);
                  if (!current_node) {
                     throw std::out_of_range("Cannot decrement rend iterator of an empty tree");
                 }
                 return *this;
            }
            
            if (tree_ptr && current_node == getMaxInSubtree(tree_ptr->root)) {
                throw std::out_of_range("Decrementing past the rbegin() of the tree");
            }

            if (current_node->right != nullptr) {
                current_node = getMinInSubtree(current_node->right);
            } else {
                Node* p = current_node->parent;
                while (p != nullptr && current_node == p->right) {
                    current_node = p;
                    p = p->parent;
                }
                current_node = p;
            }
            return *this;
        }
        
        ReverseIterator operator--(int) {
            ReverseIterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const ReverseIterator& other) const {
            return current_node == other.current_node && tree_ptr == other.tree_ptr;
        }

        bool operator!=(const ReverseIterator& other) const {
            return !(*this == other);
        }
    };

    ForwardIterator begin() const {
        return ForwardIterator(this, findMinNodeInSubtree(root));
    }

    ForwardIterator end() const {
        return ForwardIterator(this, nullptr);
    }

    ReverseIterator rbegin() const {
        return ReverseIterator(this, findMaxNodeInSubtree(root));
    }

    ReverseIterator rend() const {
        return ReverseIterator(this, nullptr);
    }
    void print() {
        Show(root, 0);
    }
    void Show(Node* t, int level) {
        if (t == nullptr && level == 0) {
            std::cout << "Tree is empty" << std::endl;
            return;
        }
        if (t == nullptr) {
            for (int i = 0; i < 3 * level; i++)
                std::cout << "   ";
            std::cout << "*" << std::endl;
            return;
        }
        Show(t->right, level + 1);
        for (int i = 0; i < 2 * level; i++)
            std::cout << "   ";
        char color = (t->color)? 'B':'R';
        std::cout << "(" << t->key << ", " << color << ")" << std::endl;
        Show(t->left, level + 1);
    }
};

#endif
