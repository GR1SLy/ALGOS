#pragma once
#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <stdexcept>

#include "rbtree.h"
#include "../tree/MyBST.h"

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
    MyBST<INT_64, int> bst;
    INT_64* m = new INT_64[n > 0 ? n : 1];
    rbtree_sRand_rb();
    
    std::cout << "\n--- Random Test ---\n" << std::endl;

    for (int i = 0; i < n; i++) {
        m[i] = rbtree_LineRand_rb();
        tree.insert(m[i], 1);
        bst.Insert(m[i], 1);
    }
    std::cout << "   BST\titems count:" << bst.GetSize() << std::endl;
    std::cout << "RBTREE\titems count:" << tree.getSize() << std::endl;
    std::cout << std::endl;

    double IRB = 0, D = 0, S = 0, IBST = 0, d = 0, s = 0;
    int operations = (n > 1) ? n / 2 : 1;


    for (int i = 0; i < operations; i++) {
        int ind = rbtree_LineRand_rb() % n;
        tree.remove(m[ind]);
        if (i % 10 != 0) D += tree.getNodesVisited();
        bst.SetNum();
        bst.Delete(m[ind]);
        if (i % 10 != 0) d += bst.GetNum();

        tree.insert(m[ind], 1);
        if (i % 10 != 0) IRB += tree.getNodesVisited();
        bst.SetNum();
        bst.Insert(m[ind], 1);
        if (i % 10 != 0) IBST += bst.GetNum();

        try {
            int sid = rbtree_LineRand_rb() % n;
            tree[m[sid]];
            S += tree.getNodesVisited();
            bst.SetNum();
            bst.Search(m[sid]);
            s += bst.GetNum();
        } catch (const std::exception& ) {
            S += tree.getNodesVisited();
            s += bst.GetNum();
        } catch (...) {
            S += tree.getNodesVisited();
            s += bst.GetNum();
        }
    }
    
    std::cout << "=== RBTREE ===" << std::endl;
    std::cout << "items count:" << tree.getSize() << std::endl;
    
    double theoretical_complexity_rb = 1.002 * (log((double) n) / log(2.0));
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "1.002*log2(n)=" << theoretical_complexity_rb << std::endl;
    if (operations > 0) {
        std::cout << "Count insert: " << (IRB / (double)operations) << std::endl;
        std::cout << "Count delete: " << (D / (double)operations) << std::endl;
        std::cout << "Count search: " << (S / (double)operations) << std::endl << std::endl;
    } else {
        std::cout << "Count insert: N/A" << std::endl;
        std::cout << "Count delete: N/A" << std::endl;
        std::cout << "Count search: N/A" << std::endl << std::endl;
    }

    std::cout << "===  BST   === " << std::endl;
    std::cout << "items count:" << bst.GetSize() << std::endl;
    
    double theoretical_complexity_bst = 1.39 * (log((double) n) / log(2.0));
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "1.39*log2(n)=" << theoretical_complexity_bst << std::endl;
    if (operations > 0) {
        std::cout << "Count insert: " << (IBST / (double)operations) << std::endl;
        std::cout << "Count delete: " << (d / (double)operations) << std::endl;
        std::cout << "Count search: " << (s / (double)operations) << std::endl << std::endl;
    } else {
        std::cout << "Count insert: N/A" << std::endl;
        std::cout << "Count delete: N/A" << std::endl;
        std::cout << "Count search: N/A" << std::endl << std::endl;
    }
    delete[] m;
}

void test_ord_rbtree(int n) {
    RBTree<INT_64, int> tree;
    MyBST<INT_64, int> bst;
    INT_64* m = new INT_64[n > 0 ? n : 1];
    rbtree_sRand_rb();
    
    std::cout << "\n--- Ordered Test ---\n" << std::endl;

    for (int i = 0; i < n; i++) {
        m[i] = i * 10000;
        tree.insert(m[i], 1);
        bst.Insert(m[i], 1);
    }

    std::cout << "RBTREE\titems count:" << tree.getSize() << std::endl;
    std::cout << "   BST\titems count:" << bst.GetSize() << std::endl << std::endl;

    double IRB = 0, D = 0, S = 0, IBST = 0, d = 0, s = 0;
    int operations = (n > 1) ? n / 2 : 1;

    for (int i = 0; i < operations; i++) {
        int ind = rbtree_LineRand_rb() % n;
        tree.remove(m[ind]);
        if (i % 10 != 0) D += tree.getNodesVisited();
        bst.SetNum();
        bst.Delete(m[ind]);
        if (i % 10 != 0) d += bst.GetNum();

        tree.insert(m[ind], 1);
        IRB += tree.getNodesVisited();
        bst.SetNum();
        bst.Insert(m[ind], 1);
        IBST += bst.GetNum();

        try {
            int sid = rbtree_LineRand_rb() % n;
            tree[m[sid]];
            S += tree.getNodesVisited();
            bst.SetNum();
            bst.Search(m[sid]);
            s += bst.GetNum();
        } catch (const std::exception& ) {
            S += tree.getNodesVisited();
            s += bst.GetNum();
        } catch (...) {
            S += tree.getNodesVisited();
            s += bst.GetNum();
        }
    }
    
    std::cout << "=== RBTREE ===" << std::endl;
    std::cout << "items count:" << tree.getSize() << std::endl;
    
    double theoretical_complexity_rb = 1.002 * (log((double) n) / log(2.0));
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "1.002*log2(n)=" << theoretical_complexity_rb << std::endl;
    if (operations > 0) {
        std::cout << "Count insert: " << (IRB / (double)operations) << std::endl;
        std::cout << "Count delete: " << (D / (double)operations) << std::endl;
        std::cout << "Count search: " << (S / (double)operations) << std::endl << std::endl;
    } else {
        std::cout << "Count insert: N/A" << std::endl;
        std::cout << "Count delete: N/A" << std::endl;
        std::cout << "Count search: N/A" << std::endl << std::endl;
    }

    std::cout << "===  BST   === " << std::endl;
    std::cout << "items count:" << bst.GetSize() << std::endl;
    
    double theoretical_complexity_bst = (double) n / 2.0;
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "n/2=" << theoretical_complexity_bst << std::endl;
    if (operations > 0) {
        std::cout << "Count insert: " << (IBST / (double)operations) << std::endl;
        std::cout << "Count delete: " << (d / (double)operations) << std::endl;
        std::cout << "Count search: " << (s / (double)operations) << std::endl << std::endl;
    } else {
        std::cout << "Count insert: N/A" << std::endl;
        std::cout << "Count delete: N/A" << std::endl;
        std::cout << "Count search: N/A" << std::endl << std::endl;
    }
    delete[] m;
}
