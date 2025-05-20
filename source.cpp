#include <iostream>
#include <list>
#include "lib/tree/MyBST.h"
#include "lib/tree/Test.h"
#include <ctime>
#include <cmath>

typedef unsigned long long INT_64;

using std::cout;
using std::cin;
using std::endl;

int Check() {
    int m;
    while (true) {
        cin >> m;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "You entered wrong value, try again" << endl;
        }
        else {
            break;
        }
    }
    return m;
}

void Stat(MyBST<int, int>* tree) {
    cout << "statistics = " << tree->GetNum() << endl;
    tree->SetNum();
}

int Options() {
    cout << "================= Options ==================" << endl;
    cout << "1.  Size of tree" << endl;
    cout << "2.  Clear tree" << endl;
    cout << "3.  Is tree empty?" << endl;
    cout << "4.  Height of tree" << endl;
    cout << "5.  Find the value by key" << endl;
    cout << "6.  Replace the value by key" << endl;
    cout << "7.  Insert new value" << endl;
    cout << "8.  Delete by key" << endl;
    cout << "9.  Show tree" << endl;
    cout << "10. Show list of tree keys" << endl;
    cout << "11. External path length" << endl;
    cout << "12. Set direct iterator to begin" << endl;
    cout << "13. Set reverse iterator to begin" << endl;
    cout << "14. Workload testing" << endl;
    cout << "0.  Exit" << endl;
    cout << "============================================" << endl;
    cout << "Enter the command: ";

    return Check();
}

int IteratorOptions() {
    cout << "============= Iterator Options ==============" << endl;
    cout << "1. Direct iterator ++" << endl;
    cout << "2. Direct iterator --" << endl;
    cout << "3. Direct iterator == end" << endl;
    cout << "4. Print direct iterator value" << endl;
    cout << "5. Change direct iterator value" << endl;
    cout << "0. Exit" << endl;
    cout << "============================================" << endl;
    cout << "Enter the command: ";

    return Check();
}

int RIteratorOptions() {
    cout << "============= Iterator Options ==============" << endl;
    cout << "1. Reverse iterator ++" << endl;
    cout << "2. Reverse iterator --" << endl;
    cout << "3. Reverse iterator == end" << endl;
    cout << "4. Print reverse iterator value" << endl;
    cout << "5. Change reverse iterator value" << endl;
    cout << "0. Exit" << endl;
    cout << "============================================" << endl;
    cout << "Enter the command: ";

    return Check();
}

void IteratorMenu(MyBST<int, int>& tree, MyBST<int, int>::Iterator& iter) {
    bool f = true;

    while (f) {
        switch (IteratorOptions()) {
        case 1:
            ++iter;
            break;
        case 2:
            --iter;
            break;
        case 3:
            cout << "iterator == end()" << endl;
            cout << iter.operator==(tree.end()) << endl;
            break;
        case 4:
            try {
                cout << *iter << endl;
            }
            catch (std::invalid_argument& e) {
                cout << "Exception" << endl;
            }
            break;
        case 5:
            try {
                cout << "Enter new value: ";
                cin >> *iter;
            }
            catch (std::invalid_argument& e) {
                cout << "\nException" << endl;
            }
            break;
        case 0:
            f = false;
            break;
        default:
            cout << "Command with this number doesn't exist. Try 1 to 5" << endl;
            break;
        }

        if (f) {
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            cin.get();
            system("clear");
        }
    }
}

void RIteratorMenu(MyBST<int, int>& tree, MyBST<int, int>::ReverseIterator& riter) {
    bool f = true;

    while (f) {
        switch (RIteratorOptions()) {
        case 1:
            ++riter;
            break;
        case 2:
            --riter;
            break;
        case 3:
            cout << "iterator == rend()" << endl;
            cout << riter.operator==(tree.rend()) << endl;
            break;
        case 4:
            try {
                cout << *riter << endl;
            }
            catch (std::invalid_argument& e) {
                cout << "Exception" << endl;
            }
            break;
        case 5:
            try {
                cout << "Enter new value: ";
                cin >> *riter;
            }
            catch (std::invalid_argument& e) {
                cout << "\nException" << endl;
            }
            break;
        case 0:
            f = false;
            break;
        default:
            cout << "Command with this number doesn't exist. Try 1 to 5" << endl;
            break;
        }

        if (f) {
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            cin.get();
            system("clear");
        }
    }
}

void PrintRespCode(int respCode) {
    cout << "Responce code: " << respCode << endl;
}

void Menu() {
    int k, j;
    int respCode;
    bool f = true;

    MyBST<int, int> tree;

    std::list<int> p;
    bool* ins = new bool;
    NodeBST<int, int>* t = nullptr;

    tree.Insert(15, 15);
    tree.Insert(10, 10);
    tree.Insert(5, 5);
    tree.Insert(50, 50);
    tree.Insert(11, 11);
    tree.Insert(21, 21);
    tree.Insert(25, 25);
    tree.Insert(52, 52);
    tree.Insert(30, 30);
    tree.SetNum();

    auto iter = tree.begin();
    auto riter = tree.rbegin();

    while (f) {
        switch (Options()) {
        case 1:
            cout << tree.GetSize() << endl;
            break;
        case 2:
            cout << "tree is cleared" << endl;
            Stat(&tree);
            tree.Clear(tree.GetRoot());
            Stat(&tree);
            break;
        case 3:
            cout << tree.IsEmpty() << endl;
            break;
        case 4:
            cout << tree.Height(tree.GetRoot()) << endl;
            Stat(&tree);
            break;
        case 5:
            cout << "Enter key to find in tree: ";
            k = Check();
            try {
                t = tree.Search(k);
                if (t) cout << "The value: " << t->value << endl;
            }
            catch (std::invalid_argument& e) {
                cout << "Exception" << endl;
            }
            Stat(&tree);
            break;
        case 6:
            try {
                cout << "Enter key: ";
                k = Check();
                cout << "Enter value to replace: ";
                j = Check();
                respCode = tree.ReplaceByKey(k, j);
                PrintRespCode(respCode);
            }
            catch (std::invalid_argument& e) {
                cout << "Exception" << endl;
            }
            Stat(&tree);
            break;
        case 7:
            cout << "Enter key: ";
            k = Check();
            cout << "Enter value to insert: ";
            j = Check();
            respCode = tree.Insert(k, j);
            PrintRespCode(respCode);
            Stat(&tree);
            break;
        case 8:
            cout << "Enter key to delete: ";
            k = Check();
            respCode = tree.Delete(k);
            PrintRespCode(respCode);
            Stat(&tree); 
            break;
        case 9:
            tree.Show(tree.GetRoot(), 0);   
            break;
        case 10:
            tree.L_t_R(tree.GetRoot());
            cout << endl;
            break;
        case 11:
            cout << tree.ExternalPathLength() << endl;
            Stat(&tree);
            break;
        case 12:
            iter = tree.begin();
            system("clear");
            IteratorMenu(tree, iter);
            break;
        case 13:
            riter = tree.rbegin();
            system("clear");
            RIteratorMenu(tree, riter);
            break;
        case 14:
            system("clear");

            for (int i = 30000, j = 1; j < 2; j++) {

                cout << "Iteration #" << j << endl;
                cout << "Test of the complexity of operations of a random BST tree" << endl;
                test_rand(i);

                cout << endl << "Test of the complexity of operations of a degenerate BST tree:" << endl;
                test_ord(i);

                cout << endl << "-----------------" << endl << endl;
            }
            break;

        case 0:
            f = false;
            break;
        default:
            cout << "Command with this number doesn't exist. Try 1 to 12" << endl;
            break;
        }
        if (f) {
            cout << "\nPress any key to continue..." << endl;
            cin.ignore();
            cin.get();
            system("clear");
        }
    }

}

int main() {
    Menu();
    return 0;
}