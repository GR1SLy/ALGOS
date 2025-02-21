#include "lib/list/List.h"
#include <iostream>
using namespace std;

int main() {
    List<int> l1;
    l1.push_front(1);
    l1.push_front(2);
    l1.push_front(3);
    l1.insert_after(1, 83);
    l1.print();
    // List<int>::iterator it = l1.begin();
    // for (it = l1.begin(); it != l1.end(); ++it) cout << *it << endl;
    // cout << *(it) << endl;
    // for (int k : l1) cout << k << endl;
    // cout << *(l1.find(83)) << endl;
    List<int>::iterator it = l1.find(123);
    cout << *(it) << endl;
    
    std::cout << "Hello, world!" << std::endl;
    return 0;
}