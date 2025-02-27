#include "lib/list/List.h"
#include <iostream>

void displayMenu() {
    std::cout << "\nМеню:\n";
    std::cout << "1: Вставить в начало\n";
    std::cout << "2: Удалить из начала\n";
    std::cout << "3: Вставить после индекса\n";
    std::cout << "4: Удалить после индекса\n";
    std::cout << "5: Проверить наличие элемента\n";
    std::cout << "6: Получить элемент по индексу\n";
    std::cout << "7: Поменять элемент по индексу\n";
    std::cout << "8: Очистить список\n";
    std::cout << "9: Проверить, пуст ли список\n";
    std::cout << "10: Найти индекс элемента\n";
    std::cout << "11: Итератор: Встать в начало\n";
    std::cout << "12: Итератор: Сделать шаг\n";
    std::cout << "13: Итератор: Узнать текущий элемент\n";
    std::cout << "14: Итератор: Заменить текущий элемент\n";
    std::cout << "15: Создать второй итератор и сравнить\n";
    std::cout << "16: Вывести список\n";
    std::cout << "0: Выйти\n";
    std::cout << "Выберите операцию: ";
}

template<typename T>
void handleMenu(List<T>& list, typename List<T>::iterator& it) {
    int choice;
    T value;
    int index;
    do {
        displayMenu();
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "Введите значение для вставки: ";
                std::cin >> value;
                list.push_front(value);
                break;
            case 2:
                list.pop_front();
                std::cout << "Элемент удален из начала.\n";
                break;
            case 3:
                std::cout << "Введите индекс и значение для вставки: ";
                std::cin >> index >> value;
                try {
                    list.insert_after(index, value);
                } catch (const std::exception& e) { 
                    std::cout << "Exception" << std::endl; 
                }
                break;
            case 4:
            {
                std::cout << "Введите индекс для удаления следующего элемента: ";
                std::cin >> index;
                try {
                    list.erase_after(index);
                } catch (const std::exception& e) {
                    std::cout << "Exception" << std::endl;
                }
                break;
            }
            case 5:
            {
                std::cout << "Введите значение для проверки: ";
                std::cin >> value;
                std::cout << list.contains(value) << std::endl;
                break;
            }
            case 6:
            {
                std::cout << "Введите индекс: ";
                std::cin >> index;
                try {
                    std::cout << list.at(index) << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cout << "Exception: " << std::endl;
                }
                break;
            }
            case 7:
            {
                std::cout << "Введите индекс и новое значение: ";
                std::cin >> index >> value;
                try {
                    list.swap_to(value, index);
                } catch (const std::exception& e) {
                    std::cout << "Exception: " << std::endl;
                }
                break;
            }
            case 8:
            {
                list.clear();
                std::cout << "Список очищен.\n";
                break;
            }
            case 9:
                std::cout << list.empty() << std::endl;
                break;
            case 10:
            {
                std::cout << "Введите значение для поиска: ";
                std::cin >> value;
                std::cout << list.find(value) << std::endl;
                break;
            }
            case 11:
            {
                it = list.begin();
                std::cout << *it << std::endl;
                break;
            }
            case 12: 
                ++it;
                break;
            case 13:
                std::cout << *it << std::endl;
                break;
            case 14:
            {
                std::cout << "Введите новый элемент: ";
                cin >> *it;
                break;
            }
            case 15:
            {
                auto it2 = list.begin();
                std::cout << "First iterator: " << *it << " Second iterator: " << *it2 << std::endl;
                std::cout << (it == it2) << std::endl;
                break;
            }
            case 16:
                list.print();
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

int main() {
    List<int> list;
    auto it = list.begin();
    handleMenu<int>(list, it);

    return 0;
}