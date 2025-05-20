#pragma once
#include <ctime>
#include <cmath>
#include <iostream>
#include "MyBST.h"
using namespace std;

typedef unsigned long long INT_64;
static INT_64 RRand = 15750;
const INT_64 mRand = (1ULL << 63) - 1;
const INT_64 aRand = 6364136223846793005ULL;
const INT_64 cRand = 1442695040888963407ULL;

void sRand() {
    srand(time(0));
    RRand = (INT_64)rand();
}


INT_64 LineRand() {
    INT_64 y1, y2;
    y1 = (aRand * RRand + cRand) % mRand;
    y2 = (aRand * y1 + cRand) % mRand;
    RRand = y1 ^ (y1 >> 17);
    RRand ^= (y2 << 31);
    return RRand;
}

void test_rand(int n) {
        MyBST<INT_64, int> tree;
        INT_64* m = new INT_64[n];
        sRand();
        for (int i = 0; i < n; i++) {
            m[i] = LineRand();
            tree.Insert(m[i], 1);
        }
        cout << "items count: " << tree.GetSize() << endl;
        double I = 0;
        double D = 0;
        double S = 0;

        for (int i = 0; i < n / 2; i++)
            if (i % 10 == 0)         
            {
                tree.SetNum();
                tree.Delete(LineRand());
                D += tree.GetNum();
                tree.SetNum();
                tree.Insert(m[rand() % n], 1);
                I += tree.GetNum();
                try {
                    tree.SetNum();
                    tree.Search(LineRand());
                    S += tree.GetNum();
                }
                catch (const exception& e) {
                    S += tree.GetNum();
                }
            }
            else
            {
                int ind = rand() % n;
                tree.SetNum();
                tree.Delete(m[ind]);
                D += tree.GetNum();
                INT_64 key = LineRand();
                tree.SetNum();
                tree.Insert(key, 1);
                I += tree.GetNum();
                m[ind] = key;
                tree.SetNum();
                try {
                    tree.Search(LineRand());
                    S += tree.GetNum();
                }
                catch (const exception& e) {
                    S += tree.GetNum();              
                }
            }
        cout << "items count: " << tree.GetSize() << endl;
        cout << "1.39*log2(n)= " << 1.39 * (log((double)n) / log(2.0)) << endl;
        cout << "Count Insert: " << I / (n / 2) << endl;
        cout << "Count delete: " << D / (n / 2) << endl;
        cout << "Count search: " << S / (n / 2) << endl;
        delete[] m;
}

void test_ord(int n) {
        MyBST<INT_64, int> tree;
        INT_64* m = new INT_64[n];
        for (int i = 0; i < n; i++) {
            m[i] = i * 10000;
            tree.Insert(m[i], 1);
        }
        cout << "items count: " << tree.GetSize() << endl;

        double I = 0;
        double D = 0;
        double S = 0;

        sRand();
        for (int i = 0; i < n / 2; i++) {
            if (i % 10 == 0)         
            {
                int k = LineRand() % (10000 * n);
                k = k + !(k % 2);
                tree.SetNum();
                tree.Delete(k);
                D += tree.GetNum();
                tree.SetNum();
                tree.Insert(m[rand() % n], 1);
                I += tree.GetNum();
                k = LineRand() % (10000 * n);
                k = k + !(k % 2);
                try {
                    tree.SetNum();
                    tree.Search(k);
                    S += tree.GetNum();
                }
                catch (const exception& e) {
                    S += tree.GetNum();
                }
            }
            else         
            {
                int ind = rand() % n;
                tree.SetNum();
                tree.Delete(m[ind]);
                D += tree.GetNum();
                int k = LineRand() % (10000 * n);
                k = k + k % 2;             
                tree.SetNum();
                tree.Insert(k, 1);
                I += tree.GetNum();
                m[ind] = k;
                try {
                    tree.SetNum();
                    tree.Search(m[rand() % n]);
                    S += tree.GetNum();
                }
                catch (const exception& e) {
                    S += tree.GetNum();
                }
            }
        }
    
        cout << "items count: " << tree.GetSize() << endl;
        cout << "n/2 = " << n / 2 << endl;
        cout << "Count Insert: " << I / (n / 2) << endl;
        cout << "Count delete: " << D / (n / 2) << endl;
        cout << "Count search: " << S / (n / 2) << endl;
        delete[] m;
}
