#pragma once
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <stdexcept>

#include "rbtree.h"

typedef unsigned long long INT_64;

static INT_64 G_RRand_rb = 15750;
const INT_64 G_mRand_rb = (1ULL << 63) - 1ULL;
const INT_64 G_aRand_rb = 6364136223846793005ULL;
const INT_64 G_cRand_rb = 1442695040888963407ULL;

void rbtree_sRand_rb() {
    srand(static_cast<unsigned int>(time(nullptr)));
    G_RRand_rb = (INT_64) rand();
}

INT_64 rbtree_LineRand_rb() {
    INT_64 y1, y2;
    y1 = (G_aRand_rb * G_RRand_rb + G_cRand_rb) % G_mRand_rb;
    y2 = (G_aRand_rb * y1 + G_cRand_rb) % G_mRand_rb;
    G_RRand_rb = (y1 & 0xFFFFFFFF00000000ULL) ^ ((y2 & 0xFFFFFFFF00000000ULL) >> 32);
    return G_RRand_rb;
}

void test_rand_rbtree(int n) {
    RBTree<INT_64, int> tree;
    INT_64* m = new INT_64[n > 0 ? n : 1];
    rbtree_sRand_rb();

    if (n <= 0) {
        std::cout << "--- Random Test ---" << std::endl;
        std::cout << "items count:0" << std::endl;
        std::cout << "items count:0" << std::endl;
        std::cout << "1.39*log2(n)=N/A" << std::endl;
        std::cout << "Count insert: N/A" << std::endl;
        std::cout << "Count delete: N/A" << std::endl;
        std::cout << "Count search: N/A" << std::endl << std::endl;
        delete[] m;
        return;
    }
    
    std::cout << "--- Random Test ---" << std::endl;

    for (int i = 0; i < n; i++) {
        m[i] = rbtree_LineRand_rb();
        tree.insert(m[i], 1);
    }
    std::cout << "items count:" << tree.getSize() << std::endl;

    double I = 0, D = 0, S = 0;
    int operations = n / 2;
    if (n == 1) operations = 1;


    for (int i = 0; i < operations; i++) {
        int ind = rand() % n;
        tree.remove(m[ind]);
        D += tree.getNodesVisited();

        INT_64 key_to_insert = rbtree_LineRand_rb();
        tree.insert(key_to_insert, 1);
        I += tree.getNodesVisited();
        m[ind] = key_to_insert;

        try {
            tree[m[rand() % n]];
            S += tree.getNodesVisited();
        } catch (const std::runtime_error& ) {
            S += tree.getNodesVisited();
        } catch (...) {
             S += tree.getNodesVisited();
        }
    }
    
    std::cout << "items count:" << tree.getSize() << std::endl;
    
    double theoretical_complexity = 1.39 * (log((double) n) / log(2.0));
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "1.39*log2(n)=" << theoretical_complexity << std::endl;
    if (operations > 0) {
        std::cout << "Count insert: " << (I / (double)operations) << std::endl;
        std::cout << "Count delete: " << (D / (double)operations) << std::endl;
        std::cout << "Count search: " << (S / (double)operations) << std::endl << std::endl;
    } else {
        std::cout << "Count insert: N/A" << std::endl;
        std::cout << "Count delete: N/A" << std::endl;
        std::cout << "Count search: N/A" << std::endl << std::endl;
    }
    delete[] m;
}

void test_ord_rbtree(int n) {
    RBTree<INT_64, int> tree;
    INT_64* m = new INT_64[n > 0 ? n : 1];
    rbtree_sRand_rb();

    if (n <= 0) {
        std::cout << "--- Ordered Test ---" << std::endl;
        std::cout << "items count:0" << std::endl;
        std::cout << "items count:0" << std::endl;
        std::cout << "1.39*log2(n)=N/A" << std::endl; 
        std::cout << "Count insert: N/A" << std::endl;
        std::cout << "Count delete: N/A" << std::endl;
        std::cout << "Count search: N/A" << std::endl << std::endl;
        delete[] m;
        return;
    }
    
    std::cout << "--- Ordered Test ---" << std::endl;

    for (int i = 0; i < n; i++) {
        m[i] = (INT_64)i * 10000ULL;
        tree.insert(m[i], 1);
    }
     std::cout << "items count:" << tree.getSize() << std::endl;

    double I = 0, D = 0, S = 0;
    int operations = n / 2;
    if (n == 1) operations = 1;

    for (int i = 0; i < operations; i++) {
        int ind = rand() % n;
        tree.remove(m[ind]);
        D += tree.getNodesVisited();

        INT_64 key_to_insert = rbtree_LineRand_rb();
        tree.insert(key_to_insert, 1);
        I += tree.getNodesVisited();
        m[ind] = key_to_insert;

        try {
             tree[m[rand() % n]];
            S += tree.getNodesVisited();
        } catch (const std::runtime_error& ) {
            S += tree.getNodesVisited();
        } catch (...) {
            S += tree.getNodesVisited();
        }
    }
    
    std::cout << "items count:" << tree.getSize() << std::endl;
    
    double theoretical_complexity = 1.39 * (log((double) n) / log(2.0));
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "1.39*log2(n)=" << theoretical_complexity << std::endl;
    if (operations > 0) {
        std::cout << "Count insert: " << (I / (double)operations) << std::endl;
        std::cout << "Count delete: " << (D / (double)operations) << std::endl;
        std::cout << "Count search: " << (S / (double)operations) << std::endl << std::endl;
    } else {
        std::cout << "Count insert: N/A" << std::endl;
        std::cout << "Count delete: N/A" << std::endl;
        std::cout << "Count search: N/A" << std::endl << std::endl;
    }
    delete[] m;
}
