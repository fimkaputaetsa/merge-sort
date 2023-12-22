#include "merge-sort.hpp"
#include <iostream>
#include <string>

int main() {
    List a { 61, 92, 83, 43, 45, 66, 77, 18, 29, 81 };
    mergesort(a);
        for (auto ptr = a.head.get(); ptr; ptr = ptr->next.get()) {
                std::cout << ptr->value << " ";
        }
}
