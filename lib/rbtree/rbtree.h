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
        bool isNil;

        Node(const KeyType& k, const DataType& d, Color c = RED, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr)
            : key(k), data(d), color(c), parent(p), left(l), right(r), isNil(false) {}

        Node() : color(BLACK), parent(nullptr), left(nullptr), right(nullptr), isNil(true) {}
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
            Node* uncle;
            if (z->parent == z->parent->parent->left) {
                uncle = z->parent->parent->right;
                if (getColor(uncle) == RED) {
                    setColor(z->parent, BLACK);
                    setColor(uncle, BLACK);
                    setColor(z->parent->parent, RED);
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    setColor(z->parent, BLACK);
                    setColor(z->parent->parent, RED);
                    rightRotate(z->parent->parent);
                }
            } else {
                uncle = z->parent->parent->left;
                if (getColor(uncle) == RED) {
                    setColor(z->parent, BLACK);
                    setColor(uncle, BLACK);
                    setColor(z->parent->parent, RED);
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    setColor(z->parent, BLACK);
                    setColor(z->parent->parent, RED);
                    leftRotate(z->parent->parent);
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
            node = node->left;
        }
        return node;
    }

    Node* findMaxNodeInSubtree(Node* node) const {
        if (!node) return nullptr;
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }


    void removeFixup(Node* x) {
        while (x != root && getColor(x) == BLACK) {
            nodesVisited++;
            if (x->parent == nullptr) break;

            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (getColor(w) == RED) {
                    setColor(w, BLACK);
                    setColor(x->parent, RED);
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w == nullptr) {
                     x = x->parent;
                     continue;
                }
                if (getColor(w->left) == BLACK && getColor(w->right) == BLACK) {
                    setColor(w, RED);
                    x = x->parent;
                } else {
                    if (getColor(w->right) == BLACK) {
                        setColor(w->left, BLACK);
                        setColor(w, RED);
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    if (w == nullptr) {
                        x = x->parent;
                        continue;
                    }
                    setColor(w, getColor(x->parent));
                    setColor(x->parent, BLACK);
                    setColor(w->right, BLACK);
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                Node* w = x->parent->left;
                if (getColor(w) == RED) {
                    setColor(w, BLACK);
                    setColor(x->parent, RED);
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                 if (w == nullptr) {
                     x = x->parent;
                     continue;
                 }
                if (getColor(w->right) == BLACK && getColor(w->left) == BLACK) {
                    setColor(w, RED);
                    x = x->parent;
                } else {
                    if (getColor(w->left) == BLACK) {
                        setColor(w->right, BLACK);
                        setColor(w, RED);
                        leftRotate(w);
                        w = x->parent->left;
                    }
                     if (w == nullptr) {
                        x = x->parent;
                        continue;
                     }
                    setColor(w, getColor(x->parent));
                    setColor(x->parent, BLACK);
                    setColor(w->left, BLACK);
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        if (x != nullptr) setColor(x, BLACK);
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
            clearRecursive(root);
            root = nullptr;
            count = 0;
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
            nodesVisited = 0;
            node = findNodeRecursive(root, key);
                                             
            if(node) return node->data;
            else {
                 throw std::runtime_error("RBTree::operator[]: Critical error - node not found after insert.");
            }
        }
    }

    bool insert(const KeyType& key, const DataType& data) {
        nodesVisited = 0;
        Node* z = new Node(key, data);
        
        if (root == nullptr) {
            root = z;
            setColor(root, BLACK);
            count++;
            nodesVisited = 1;
            return true;
        }
        
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
        if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
        
        count++;
        insertFixup(z);
        return true;
    }

    bool remove(const KeyType& key) {
        nodesVisited = 0;
        Node* z = findNodeRecursive(root, key);
        if (z == nullptr) {
            return false;
        }
        
        Node* y_replaced = z;
        Node* x_child_of_y = nullptr;
        Color originalColor_of_y = getColor(y_replaced);

        if (z->left == nullptr) {
            x_child_of_y = z->right;
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            x_child_of_y = z->left;
            transplant(z, z->left);
        } else {
            y_replaced = findMinNodeInSubtree(z->right);
            originalColor_of_y = getColor(y_replaced);
            x_child_of_y = y_replaced->right;
            
            if (y_replaced->parent == z) {
                if (x_child_of_y != nullptr) x_child_of_y->parent = y_replaced;
            } else {
                transplant(y_replaced, y_replaced->right);
                y_replaced->right = z->right;
                if(y_replaced->right != nullptr) y_replaced->right->parent = y_replaced;
            }
            transplant(z, y_replaced);
            y_replaced->left = z->left;
            if(y_replaced->left != nullptr) y_replaced->left->parent = y_replaced;
            setColor(y_replaced, getColor(z));
        }
        delete z;
        count--;

        if (originalColor_of_y == BLACK) {
            if (x_child_of_y != nullptr) {
                removeFixup(x_child_of_y);
            }
        }
        if (root != nullptr) setColor(root, BLACK);
        return true;
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
        char color = (t->color)? 'R':'B';
        std::cout << "(" << t->key << ", " << color << ")" << std::endl;
        Show(t->left, level + 1);
    }

    size_t getNodesVisited() const {
        return nodesVisited;
    }

    void clearNodesVisited() {
        nodesVisited = 0;
    }

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
                 throw std::out_of_range("Exception");
            }
            return current_node->data;
        }

        KeyType getKey() const {
             if (!current_node) {
                 throw std::out_of_range("Exception");
            }
            return current_node->key;
        }

        ForwardIterator& operator++() {
            if (!current_node) {
                throw std::out_of_range("Exception");
            }

            if (current_node->right) {
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
            if (!current_node) {
                 if (tree_ptr && tree_ptr->root) {
                     current_node = getMaxInSubtree(tree_ptr->root);
                 } else {
                      throw std::out_of_range("Exception");
                 }
                 return *this;
            }

             if (tree_ptr && current_node == getMinInSubtree(tree_ptr->root)) {
                 throw std::out_of_range("Exception");
             }

            if (current_node->left) {
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
                 throw std::out_of_range("Exception");
            }
            return current_node->data;
        }

        KeyType getKey() const {
             if (!current_node) {
                 throw std::out_of_range("Exception");
            }
            return current_node->key;
        }

        ReverseIterator& operator++() {
             if (!current_node) {
                 throw std::out_of_range("Exception");
            }
            
            if (tree_ptr && current_node == getMinInSubtree(tree_ptr->root)) {
                 current_node = nullptr;
                 return *this;
            }

            if (current_node->left) {
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
            if (!current_node) {
                 if (tree_ptr && tree_ptr->root) {
                     current_node = getMinInSubtree(tree_ptr->root);
                 } else {
                    throw std::out_of_range("Exception");
                 }
                 return *this;
            }
            
            if (tree_ptr && current_node == getMaxInSubtree(tree_ptr->root)) {
                throw std::out_of_range("Exception");
            }

            if (current_node->right) {
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
};

#endif // RBTREE_H
