#include <iostream>
#include "AATree.h"

int main() {
    AATree tree;

    // Вставляємо раціональні числа
    tree.insert(Rational(1, 2));
    tree.insert(Rational(3, 4));
    tree.insert(Rational(1, 3));
    tree.insert(Rational(6, 7));
    tree.insert(Rational(7, 8));
    tree.insert(Rational(8, 9));


    
                              // Пошук раціональних чисел
    cout << "Search 1/2: " << tree.search(Rational(1, 2)) << endl;
    cout << "Search 2/3: " << tree.search(Rational(2, 3)) << endl;
    cout << "Search 6/7: " << tree.search(Rational(6, 7)) << endl;
    cout<<endl;

    // Вивід дерева
    
    tree.inorder();
    cout<<endl;

    return 0;
}

