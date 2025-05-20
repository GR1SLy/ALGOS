#ifndef UNTITLED11_NODEBST_H
#define UNTITLED11_NODEBST_H

template <typename T, typename K>
class NodeBST {
public:
	NodeBST() :left(nullptr), right(nullptr) {}
	NodeBST(T value_, K key_) :value(value_), key(key_), left(nullptr), right(nullptr) {}
	NodeBST* left = nullptr;
	NodeBST* right = nullptr;
	T value;
	K key;
};


#endif
