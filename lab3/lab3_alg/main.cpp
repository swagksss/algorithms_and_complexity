
//
//#include <algorithm>
//
//#include <iostream>
//
//
//using namespace std;
//
//class Rational {
//private:
//    int num, den;
//    int gcd(int a, int b) {
//        while (b != 0) {
//            int r = a % b;
//            a = b;
//            b = r;
//        }
//        return a;
//    }
//public:
//    Rational(int n = 0, int d = 1) {
//
//        int g = gcd(n, d);
//        num = n / g;
//        den = d / g;
//        if (den < 0) {
//            num *= -1;
//            den *= -1;
//        }
//    }
//    int numerator() const { return num; }
//    int denominator() const { return den; }
//    bool operator<(const Rational& other) const {
//        return num * other.den < other.num * den;
//    }
//};
//
//class SplayTree {
//private:
//
//    struct Node {
//        Rational val;
//        Node* parent;
//        Node* left;
//        Node* right;
//        Node(Rational v, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr) : val(v), parent(p), left(l), right(r) {}
//    };
//    Node* root;
//    void rotateLeft(Node* x);
//    void rotateRight(Node* x);
//    void splay(Node* x);
//    Node* findNode(const Rational& val);
//
//public:
//    SplayTree() : root(nullptr) {}
//    ~SplayTree() { clear(); }
//    void insert(const Rational& val);
//    void remove(const Rational& val);
//    bool find(const Rational& val);
//    void clear();
//    void print(Node* node) {
//        if (node != nullptr) {
//            print(node->left);
//            cout << node->val.numerator() << "/" << node->val.denominator() << " ";
//            print(node->right);
//        }
//    }
//
//    void print() {
//        print(root);
//        cout << endl;
//    }
//
//};
//
//
//void SplayTree::rotateLeft(Node* x) {
//    Node* y = x->right;
//    x->right = y->left;
//    if (y->left != nullptr) y->left->parent = x;
//    y->parent = x->parent;
//    if (x->parent == nullptr) root = y;
//    else if (x == x->parent->left) x->parent->left = y;
//    else x->parent->right = y;
//    y->left = x;
//    x->parent = y;
//}
//
//void SplayTree::rotateRight(Node* x) {
//    Node* y = x->left;
//    x->left = y->right;
//    if (y->right != nullptr) y->right->parent = x;
//    y->parent = x->parent;
//    if (x->parent == nullptr) root = y;
//    else if (x == x->parent->left) x->parent->left = y;
//    else x->parent->right = y;
//    y->right = x;
//    x->parent = y;
//}
//
//void SplayTree::splay(Node* x) {
//    while (x->parent != nullptr) {
//        if (x->parent->parent == nullptr) {
//            if (x->parent->left == x) rotateRight(x->parent);
//            else rotateLeft(x->parent);
//        }
//        else if (x->parent->left == x && x->parent->parent->left == x->parent) {
//            rotateRight(x->parent->parent);
//            rotateRight(x->parent);
//        }
//        else if (x->parent->right == x && x->parent->parent->right == x->parent) {
//            rotateLeft(x->parent->parent);
//            rotateLeft(x->parent);
//        }
//        else if (x->parent->left == x && x->parent->parent->right == x->parent) {
//            rotateRight(x->parent);
//            rotateLeft(x->parent);
//        }
//        else {
//            rotateLeft(x->parent);
//            rotateRight(x->parent);
//        }
//    }
//}
//
//void SplayTree::insert(const Rational& val) {
//// if the tree is empty, insert the value as the root
//    if (root == nullptr) {
//        root = new Node(val);
//        return;
//    }
//// search for the position to insert the value
//Node* curr = root;
//while (true) {
//    if (val < curr->val) {
//        if (curr->left == nullptr) {
//            curr->left = new Node(val, curr);
//            curr = curr->left;
//            break;
//        }
//        else curr = curr->left;
//    }
//    else if (curr->val < val) {
//        if (curr->right == nullptr) {
//            curr->right = new Node(val, curr);
//            curr = curr->right;
//            break;
//        }
//        else curr = curr->right;
//    }
//    else return; // the value is already in the tree
//    }
//// splay the inserted node to the root
//    splay(curr);
//    }
//
//void SplayTree::remove(const Rational& val) {
//// search for the node with the value to remove
//    Node* curr = findNode(val);
//    if (curr == nullptr) return; // the value is not in the tree
//// splay the node to the root
//    splay(curr);
//// remove the node and adjust the tree
//    if (curr->left == nullptr) {
//        if (curr->right != nullptr) curr->right->parent = nullptr;
//        root = curr->right;
//        delete curr;
//    }
//    else if (curr->right == nullptr) {
//        curr->left->parent = nullptr;
//        root = curr->left;
//        delete curr;
//    }
//    else {
//        Node* minRight = curr->right;
//        while (minRight->left != nullptr) minRight = minRight->left;
//        if (minRight->parent != curr) {
//            minRight->parent->left = minRight->right;
//            if (minRight->right != nullptr) minRight->right->parent = minRight->parent;
//            minRight->right = curr->right;
//            minRight->right->parent = minRight;
//        }
//        minRight->left = curr->left;
//        minRight->left->parent = minRight;
//        if (curr->parent == nullptr) root = minRight;
//        else if (curr == curr->parent->left) curr->parent->left = minRight;
//        else curr->parent->right = minRight;
//        minRight->parent = curr->parent;
//        delete curr;
//}
//}
//
//bool SplayTree::find(const Rational& val) {
//Node* node = findNode(val);
//if (node == nullptr) return false;
//else {
//splay(node);
//return true;
//}
//}
//
//void SplayTree::clear() {
//while (root != nullptr) remove(root->val);
//}
//
//SplayTree::Node* SplayTree::findNode(const Rational& val) {
//Node* curr = root;
//while (curr != nullptr) {
//if (val < curr->val) curr = curr->left;
//else if (curr->val < val) curr = curr->right;
//else return curr;
//}
//return nullptr;
//}
//
//int main() {
//SplayTree tree;
//tree.insert(Rational(1, 2));
//tree.insert(Rational(3, 4));
//tree.insert(Rational(2, 3));
//tree.insert(Rational(5, 6));
//cout << "Tree after insertions: ";
//tree.print();
//cout << endl;
//cout << "Removing 3/4 from the tree";
//cout << endl;
//tree.remove(Rational(3,4));
//    cout << endl;
//    cout << "Insert 7/8 ";
//    tree.insert(Rational(7,8));
//    cout << endl;
//    cout << endl;
//    cout << "Tree after removal: ";
//    tree.print();
//    cout << endl;
//    cout << "Finding 2/3 in the tree: " << tree.find(Rational(2, 3)) << endl;
//    cout << "Finding 3/4 in the tree: " << tree.find(Rational(3, 4)) << endl;
//    cout << "Clearing the tree." << endl;
//    tree.clear();
//    cout << "Tree after clearing: ";
//    tree.print();
//    cout << endl;
//    return 0;
//    }

//________________________________________________________________________________________________

#include <algorithm>
#include <iostream>

using namespace std;
//клас який представляє раціональні числа
class Rational {
private:
    int num, den;
    //найбільший спільний дільник (НСД) чисельника та знаменника, який використовується для зведення дробу до його найпростішої форми.
    int gcd(int a, int b) {
        while (b != 0) {
            int r = a % b;
            a = b;
            b = r;
        }
        return a;
    }
public:
    //Конструктор Rational використовує функцію gcd для спрощення чисельника та знаменника перед збереженням їх в об’єкті. Якщо знаменник є від’ємним, конструктор також гарантує, що знак від’ємного значення завжди стоїть у чисельнику, щоб зберегти узгодженість представлення.
    Rational(int n = 0, int d = 1) {
        int g = gcd(n, d);
        num = n / g;
        den = d / g;
        if (den < 0) {
            num *= -1;
            den *= -1;
        }
    }
    int numerator() const { return num; }
    int denominator() const { return den; }
    bool operator<(const Rational& other) const {
        return num * other.den < other.num * den;
    }
    bool operator==(const Rational& other) const {
        return num == other.num && den == other.den;
    }



};
//клас SplayTree, який представляє саморегулююче бінарне дерево пошуку
class SplayTree {
private:
    //структура Node,  представляє вузол у дереві, що містить значення Rational і покажчики на його батьківського, лівого та правого дочірніх елементів
    struct Node {
        Rational val;
        Node* parent;
        Node* left;
        Node* right;
        Node(Rational v, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr) : val(v), parent(p), left(l), right(r) {}
    };
    Node* root;
    void rotateLeft(Node* x);
    void rotateRight(Node* x);
    void splay(Node* x);
    Node* findNode(const Rational& val);
    void split(Node* node, const Rational& val, Node*& left, Node*& right);
    Node* merge(Node* left, Node* right);

public:
    SplayTree() : root(nullptr) {}
    ~SplayTree() { clear(); }
    void insert(const Rational& val);
    void remove(const Rational& val);
    bool find(const Rational& val);
    void clear();
    void print(Node* node) {
        if (node != nullptr) {
            print(node->left);
            cout << node->val.numerator() << "/" << node->val.denominator() << " ";
            print(node->right);
        }
    }

    void print() {
        print(root);
        cout << endl;
    }


};

//функція rotateLeft для класу SplayTree
void SplayTree::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

//функція rotateRight для класу SplayTree
void SplayTree::rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != nullptr) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->right = x;
    x->parent = y;
}

//операція розширення на заданому вузлі x
void SplayTree::splay(Node* x) {
    while (x->parent != nullptr) {
        if (x->parent->parent == nullptr) {
            if (x->parent->left == x) rotateRight(x->parent);
            else rotateLeft(x->parent);
        }
        else if (x->parent->left == x && x->parent->right == x->parent->parent->right) {
            rotateRight(x->parent);
            rotateLeft(x->parent);
            }
            else if (x->parent->right == x && x->parent->parent->left == x->parent) {
            rotateLeft(x->parent);
            rotateRight(x->parent);
            }
            else if (x->parent->left == x && x->parent->parent->left == x->parent) {
            rotateRight(x->parent->parent);
            rotateRight(x->parent);
            }
            else {
            rotateLeft(x->parent->parent);
            rotateLeft(x->parent);
            }
            }
            }

            //функція шукає вузол у розширюваному дереві
            typename SplayTree::Node* SplayTree::findNode(const Rational& val) {
                Node* current = root;
                while (current != nullptr) {
                    if (current->val == val) {
                        splay(current);
                        return current;
                    }
                    else if (current->val < val) {
                        if (current->right == nullptr) {
                            splay(current);
                            return nullptr;
                        }
                        current = current->right;
                    }
                    else {
                        if (current->left == nullptr) {
                            splay(current);
                            return nullptr;
                        }
                        current = current->left;
                    }
                }
                return nullptr;
                }

            //метод розбиття для класу SplayTree
            void SplayTree::split(Node* node, const Rational& val, Node*& left, Node*& right) {
                if (node == nullptr) {
                    left = nullptr;
                    right = nullptr;
                    return;
                }
                splay(node);
                if (node->val < val) {
                    left = node;
                    right = node->right;
                    if (right != nullptr) right->parent = nullptr;
                    node->right = nullptr;
                }
                else {
                    right = node;
                    left = node->left;
                    if (left != nullptr) left->parent = nullptr;
                    node->left = nullptr;
                }
                }

            //функція merge() для дерева SplayTree приймає два вузли дерева як вхідні дані, лівий і правий, і повертає новий вузол SplayTree, що представляє об’єднане дерево.
            typename SplayTree::Node* SplayTree::merge(Node* left, Node* right) {
                if (left == nullptr) return right;
                if (right == nullptr) return left;
                Node* current = left;
                while (current->right != nullptr) current = current->right;
                splay(current);
                current->right = right;
                right->parent = current;
                return current;
                }

            // функція insert вставляє новий вузол зі значенням val у Splay Tree
void SplayTree::insert(const Rational& val) {
    Node* foundNode = findNode(val);
    if (foundNode != nullptr) {
        // If a node with the same value already exists, update its key value
        foundNode->val = val;
        splay(foundNode);
        return;
    }
    Node* left;
    Node* right;
    split(root, val, left, right);
    Node* newNode = new Node(val, nullptr, left, right);
    if (left != nullptr) left->parent = newNode;
    if (right != nullptr) right->parent = newNode;
    root = newNode;
    
}


            // функція видаляє вузол із заданим значенням із розширюваного дерева
            void SplayTree::remove(const Rational& val) {
                Node* node = findNode(val);
                if (node == nullptr) return;
                splay(node);
                Node* left = node->left;
                Node* right = node->right;
                if (left != nullptr) left->parent = nullptr;
                if (right != nullptr) right->parent = nullptr;
                
                root = merge(left, right);
                delete node;
                }

                bool SplayTree::find(const Rational& val) {
                    return findNode(val) != nullptr;
                }

            //Метод clear класу SplayTree видаляє всі елементи з дерева
            void SplayTree::clear() {
                while (root != nullptr) remove(root->val);
                }
int main() {
    SplayTree tree;
    //Вставляємо раціональні числа
    tree.insert(Rational(1, 2));
    tree.insert(Rational(3, 4));
    tree.insert(Rational(2, 3));
    tree.insert(Rational(5, 6));
    //Друкуємо дерево
    cout << "Дерево після вставок: ";
    tree.print();
    cout << endl;
    //Видалення раціонального числа
    cout << "Видалення 3/4 ";
    cout << endl;
    tree.remove(Rational(3,4));
    cout << endl;
    //Додаємо раціональне число
    cout << "Вставка 7/8 ";
    tree.insert(Rational(7,8));
    cout << endl;
    cout << endl;
    //Друкуємо дерево
    cout << "Дерево після видалення та вставки: ";
    tree.print();
    cout << endl;
    //Пошук раціональних чисел
    cout << "Пошук 2/3 в дереві: " << tree.find(Rational(2, 3)) << endl;
    cout << "Пошук 3/4 в дереві: " << tree.find(Rational(3, 4)) << endl;
    //Очищаємо дерево та друкуємо дерево
    cout << "Очищення дерева." << endl;
    tree.clear();
    cout << "Дерево після очищення: ";
    tree.print();
    cout << endl;
    return 0;
    }

