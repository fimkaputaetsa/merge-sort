#include "merge-sort.hpp"
#include <memory>

List::List(std::initializer_list<int> list) {
    // Задание №1: сделать список из list
    ListElement * tail = nullptr;
    for (auto number : list) {
        if (tail) {
            tail->next = std::make_unique<ListElement>(number, nullptr);
            tail = tail->next.get();
        } else {
            head = std::make_unique<ListElement>(number, nullptr);
            tail = head.get();
        }
    }
}
auto mergesort(List &list) noexcept -> void {
    // Сортировка слиянием
    // 1. Определяем середину списка (см. ветку list-algo семинаров)
    ListElement *middle = nullptr;

    if (!list.head.get()) {
        return;
    }

    auto size = list.getsize();

    if (size == 1) {
        return;
    }

    middle = list.head.get();
    for (size_t i = 0; i < size / 2 - 1; ++i) {
        middle = middle->next.get();
    }

    // 2. Переносим вторую половину в новый список
    List second;
    if (middle) {
        second.head = std::move(middle->next);
    }

    // 3. Для каждой половины запускаем mergesort
    mergesort(list);
    mergesort(second);

    // 4. Делаем merge от результатов,
    
    list = merge(std::move(list), std::move(second));
}
auto merge(List a, List b) noexcept -> List {
    // Слияние двух упорядоченных списков
    List result;
    ListElement *tail =
        nullptr; // должен указывать на последний элемент списка result

    if (!b.head) {
        return a;
    }

    if (!a.head) {
        return b;
    }

    if (a.head->value > b.head->value) {
        result.head = std::move(b.head);
        tail = result.head.get();
        b.head = std::move(tail->next);

    } else {
        result.head = std::move(a.head);
        tail = result.head.get();
        a.head = std::move(tail->next);
    }

    while (a.head && b.head) {
        // Выбираем меньший из a.head.value и b.head.value
        // и переносим a.head или b.head в конец result,
        // после чего переносим tail->next обратно
        // в a.head или b.head

        if (a.head->value < b.head->value) {
            tail->next = std::move(a.head);
            tail = tail->next.get();
            a.head = std::move(tail->next);
        } else {
            tail->next = std::move(b.head);
            tail = tail->next.get();
            b.head = std::move(tail->next);
        }
    }
    // переносим оставшийся список в конец result
    if (a.head) {
        tail->next = std::move(a.head);
    } else if (b.head) {
        tail->next = std::move(b.head);
    }

    return result;
}
