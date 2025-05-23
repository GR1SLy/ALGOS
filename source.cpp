#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "lib/rbtree/rbtree.h"
#include "lib/rbtree/test.h"
#include "lib/tree/Test.h"

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.good()) {
             if (std::cin.peek() == '\n') {
                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                 return value;
            } else {
                 std::cout << "Ошибка ввода. Пожалуйста, введите целое число.\n";
                 clearInputBuffer();
            }
        } else {
            std::cout << "Ошибка ввода. Пожалуйста, введите целое число.\n";
            clearInputBuffer();
        }
    }
}

std::string getStringInput(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

int main() {
    RBTree<int, std::string> tree;
    int choice;

    tree.insert(10, "10");
    tree.insert(20, "20");
    tree.insert(30, "30");
    tree.insert(40, "40");
    tree.insert(50, "50");
    tree.insert(60, "60");
    tree.insert(70, "70");
    tree.insert(80, "80");
    tree.insert(90, "90");
    // tree.clearNodesVisited();

    RBTree<int, std::string>::ForwardIterator fwd_it = tree.begin();
    RBTree<int, std::string>::ReverseIterator rev_it = tree.rbegin();

    do {
        std::cout << "\n========= Меню RB-Дерева =========" << std::endl;
        std::cout << "--- Дерево ---" << std::endl;
        std::cout << "1. Включить элемент" << std::endl;
        std::cout << "2. Удалить по ключу" << std::endl;
        std::cout << "3. Данные по ключу (operator[])" << std::endl;
        std::cout << "4. Размер (getSize)" << std::endl;
        std::cout << "5. Пустое? (isEmpty)" << std::endl;
        std::cout << "6. Очистить (clear)" << std::endl;
        std::cout << "7. Вывести дерево (print)" << std::endl;

        std::cout << "\n--- Прямой Итератор ---" << std::endl;
        std::cout << "10. it = tree.begin()" << std::endl;
        std::cout << "12. ++it" << std::endl;
        std::cout << "13. --it" << std::endl;
        std::cout << "14. Прочитать *it" << std::endl;
        std::cout << "15. Изменить *it" << std::endl;
        std::cout << "16. Сравнить it == tree.begin()" << std::endl;
        std::cout << "17. Сравнить it == tree.end()" << std::endl;
        
        std::cout << "\n--- Обратный Итератор ---" << std::endl;
        std::cout << "20. rit = tree.rbegin()" << std::endl;
        std::cout << "22. ++rit" << std::endl;
        std::cout << "23. --rit" << std::endl;
        std::cout << "24. Прочитать *rit" << std::endl;
        std::cout << "25. Изменить *rit" << std::endl;
        std::cout << "26. Сравнить rit == tree.rbegin()" << std::endl;
        std::cout << "27. Сравнить rit == tree.rend()" << std::endl;

        std::cout << "\n--- Тестирование ---" << std::endl;
        std::cout << "30. Запустить тесты" << std::endl;
        std::cout << "\n0. Выход" << std::endl;
        std::cout << "====================================" << std::endl;
        
        choice = getIntInput("Выбор: ");

        int key;
        std::string data_val;
        
        try { 
            switch (choice) {
                case 1:
                    key = getIntInput("Ключ (int): ");
                    data_val = getStringInput("Данные (string): ");
                    std::cout << (tree.insert(key, data_val) ? "true" : "false") << std::endl;
                    break;
                case 2:
                    if (tree.isEmpty()) { std::cout << "false\n"; break; }
                    key = getIntInput("Ключ для удаления: ");
                    std::cout << (tree.remove(key) ? "true" : "false") << std::endl;
                    break;
                case 3:
                    key = getIntInput("Ключ для доступа (operator[]): ");
                    try {
                        std::string& found_data = tree[key];
                        std::cout << "\"" << found_data << "\"" << std::endl;
                        data_val = getStringInput("Новые данные (Enter - оставить): ");
                        if (!data_val.empty()) {
                            tree[key] = data_val;
                            std::cout << "true\n";
                        }
                    } catch (const std::exception& e) {
                        // std::cout << "false (" << e.what() << ")" << std::endl;
                        std::cout << "Exception" << std::endl;
                    }
                    break;
                case 4:
                    std::cout << tree.getSize() << std::endl;
                    break;
                case 5:
                    std::cout << (tree.isEmpty() ? "true" : "false") << std::endl;
                    break;
                case 6:
                    std::cout << (tree.clear() ? "true" : "false") << std::endl;
                    fwd_it = tree.end();
                    rev_it = tree.rend();
                    break;
                case 7:
                    std::cout << "Format: (KEY, COLOR)" << std::endl;
                    tree.print();
                    break;
                
                case 10: fwd_it = tree.begin(); std::cout << "true\n"; break;
                case 11: fwd_it = tree.end(); std::cout << "true\n"; break;
                case 12: ++fwd_it; std::cout << "true\n"; break;
                case 13: --fwd_it; std::cout << "true\n"; break;
                case 14: std::cout << "\"" << *fwd_it << "\"" << std::endl; break;
                case 15:
                    data_val = getStringInput("Новые данные для *it: ");
                    *fwd_it = data_val;
                    std::cout << "true\n";
                    break;
                case 16: std::cout << (fwd_it == tree.begin() ? "true" : "false") << std::endl; break;
                case 17: std::cout << (fwd_it == tree.end() ? "true" : "false") << std::endl; break;
                
                case 20: rev_it = tree.rbegin(); std::cout << "true\n"; break;
                case 21: rev_it = tree.rend(); std::cout << "true\n"; break;
                case 22: ++rev_it; std::cout << "true\n"; break;
                case 23: --rev_it; std::cout << "true\n"; break;
                case 24: std::cout << "\"" << *rev_it << "\"" << std::endl; break;
                case 25:
                    data_val = getStringInput("Новые данные для *rit: ");
                    *rev_it = data_val;
                    std::cout << "true\n";
                    break;
                case 26: std::cout << (rev_it == tree.rbegin() ? "true" : "false") << std::endl; break;
                case 27: std::cout << (rev_it == tree.rend() ? "true" : "false") << std::endl; break;

                case 30:
                    {
                        int n_test = getIntInput("Введите количество элементов n для теста: ");
                        if (n_test <= 0) {
                            std::cout << "false\n";
                            break;
                        }
                        std::cout << "=====RBTREE TESTS=====" << std::endl;
                        test_rand_rbtree(n_test);
                        test_ord_rbtree(n_test);
                        std::cout << "=====BST TESTS=====\n--- Random test ---" << std::endl;
                        test_rand(n_test);
                        std::cout << "\n--- Ordered test ---" << std::endl;
                        test_ord(n_test);
                        std::cout << "true\n";
                    }
                    break;
                case 0:
                    std::cout << "Выход." << std::endl;
                    break;
                default:
                    std::cout << "false" << std::endl;
            }
        } catch (const std::out_of_range& e) {
            // std::cout << "false (" << e.what() << ")" << std::endl;
            std::cout << "Exception" << std::endl;
        } catch (const std::exception& e) {
            //  std::cout << "false (" << e.what() << ")" << std::endl;
            std::cout << "Exception" << std::endl;
        }
    } while (choice != 0);

    return 0;
}