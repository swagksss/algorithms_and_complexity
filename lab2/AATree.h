#include <iostream>
#include <algorithm>

using namespace std;

// Структура для представлення раціонального числа
struct Rational {
    int num, denom;
    Rational(int n = 0, int d = 1) : num(n), denom(d) {}
};

// Структура для представлення вузла в AA-дереві
struct Node {
    Rational data;
    int level;
    Node* left, * right;
    Node(Rational d = Rational(), int l = 1, Node* p = nullptr, Node* q = nullptr) :
        data(d), level(l), left(p), right(q) {}
};

// Клас для представлення AA-дерева
class AATree {
public:
    AATree() : root(nullptr) {}

    // Вставляємо в дерево раціональне число
    void insert(const Rational& r) {
        root = insert(root, r);
    }

    // Пошук раціонального числа в дереві
    bool search(const Rational& r) {
        return search(root, r);
    }

    // Упорядкований обхід дерева (для тестування)
    void inorder() {
        inorder(root);
        cout << endl;
    }

private:
    Node* root;

    // Вставляємо раціональне число в піддерево з коренем у вузлі
    Node* insert(Node* node, const Rational& r) {
        if (node == nullptr) {
            return new Node(r);
        }

        if (r.num == node->data.num && r.denom == node->data.denom) {
            // Раціональне число вже є в дереві
            return node;
        }
        else if (r.num * node->data.denom < node->data.num * r.denom) {
            node->left = insert(node->left, r);
        }
        else {
            node->right = insert(node->right, r);
        }

        // Операції нахилу та розбиття
        if (node->left != nullptr && node->left->level == node->level) {
            node = rotateRight(node);
        }
        if (node->right != nullptr && node->right->right != nullptr && node->right->right->level == node->level) {
            node = rotateLeft(node);
            node->level++;
        }

        return node;
    }

    // Пошук раціонального числа в піддереві з коренем у вузлі
    bool search(Node* node, const Rational& r) {
        while (node != nullptr) {
            if (r.num == node->data.num && r.denom == node->data.denom) {
                return true;
            }
            else if (r.num * node->data.denom < node->data.num * r.denom) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }
        return false;
    }

    // Упорядкований обхід піддерева з коренем у вузлі (з метою тестування)
    void inorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        inorder(node->left);
        cout << node->data.num << "/" << node->data.denom << " ";
        inorder(node->right);
    }

    // Поверніть вузол праворуч
    Node* rotateRight(Node* node) {
        Node* left = node->left;
        node->left = left->right;
        left->right = node;
        return left;
    }

    // Поверніть вузол ліворуч
    Node* rotateLeft(Node* node) {
        Node* right = node->right;
        node->right = right->left;
        right->left = node;
        return right;
    }
};




