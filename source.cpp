#include "lib/list/List.h"
#include <iostream>
using namespace std;

void list_test() {
    List<int> l;

    l.push_front(1);
    l.push_front(4);
    l.push_front(7);
    l.push_front(8);
    l.print();
    cout << "Size: " << l.size() << endl;
    cout << "------------------------" << endl;

    List<int>::iterator it = l.begin();
    for (; it != l.end(); ++it) cout << *it << endl;
    cout << *it << endl;
    cout << "------------------------" << endl;

    l.insert_after(2, 83);
    l.print();
    cout << "------------------------" << endl;

    l.erase_after(1);
    l.print();
    cout << "------------------------" << endl;

    l.pop_front();
    l.print();
    cout << "------------------------" << endl;

    cout << l.at(2) << endl;
    cout << "------------------------" << endl;

    l.swap_to(99, 2);
    l.print();
    cout << "------------------------" << endl;

    cout << "Found: " << l.contains(83) << endl;
    cout << "------------------------" << endl;

    List<int>::iterator found = l.find(83);
    cout << *found << endl;
    cout << "------------------------" << endl;


    List<int> l_copy = l;
    l_copy.print();
    cout << "------------------------" << endl;

    cout << "Empty: " << l_copy.empty() << endl;
    cout << "------------------------" << endl;

    l_copy.clear();
    cout << "Empty: " << l_copy.empty() << endl;
    cout << "------------------------" << endl;

}
int main() {
    std::cout << "Hello, world!" << std::endl;
    list_test();
    return 0;
}