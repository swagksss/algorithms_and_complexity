//#include <iostream>
//#include <vector>
//#include <unordered_map>
//
//using namespace std;
//
//struct Complex {
//    double real;
//    double imag;
//};
//
//// Хеш-функція для комплексних чисел
//struct ComplexHash {
//    size_t operator()(const Complex& c) const {
//        return hash<double>()(c.real) ^ hash<double>()(c.imag);
//    }
//};
//
//// Функція порівняння для комплексних чисел
//struct ComplexEqual {
//    bool operator()(const Complex& a, const Complex& b) const {
//        return a.real == b.real && a.imag == b.imag;
//    }
//};
//
////Клас з реалізацією хеш-таблиці
//class PerfectHash {
//public:
//
//    // У конструкторі PerfectHash перебираємо вектор комплексних чисел і зберігаємо індекс кожного комплексного числа в хеш-таблиці.
//
//
//    PerfectHash(const vector<Complex>& keys) {
//        for (int i = 0; i < keys.size(); i++) {
//            table_[keys[i]] = i;
//        }
//    }
////функція виконує ітерацію по вектору комплексних чисел, отримуючи  значення (індекс у векторі ключів), пов’язаного з даним ключем (комплексним числом) із хеш-таблиці
//    int operator[](const Complex& key) const {
//        return table_.at(key);
//    }
//
//private:
//    unordered_map<Complex, int, ComplexHash, ComplexEqual> table_; // стандартний контейнер у C++, який реалізує хеш-таблицю. Unordered_map використовує структури ComplexHash і ComplexEqual, щоб вказати, як хешувати та порівнювати комплексні числа відповідно.
//};
//
////У основній функції програма спочатку читає кількість комплексних чисел, які потрібно хешувати, від користувача, а потім читає комплексні числа від користувача
//int main() {
//    vector<Complex> keys;
//    int num_keys;
//
//    cout << "Enter the number of complex numbers: ";
//    cin >> num_keys;
//    cout<<'\n';
//
//
//    cout << "Enter the complex numbers: " << endl;
//    for (int i = 0; i < num_keys; i++) {
//        double real, imag;
//        cout << "Real part: ";
//        cin >> real;
//        cout << "Imaginary part: ";
//        cin >> imag;
//
//        keys.push_back({real, imag});
//    }
//
//    // Ініціалізувати ідеальну хеш-таблицю
//    PerfectHash ph(keys);
//    cout<<'\n';
//
//    // Знайти значення, пов'язані з кожним ключем
//    for (const auto& key : keys) {
//        cout << key.real << " + " << key.imag << "i: " << ph[key] << endl;
//    }
//    cout<<'\n';
//
//    return 0;
//}

#include <iostream>
#include <vector>
#include <complex>
#include <unordered_map>
using namespace std;

//  хеш-функція для векторів комплексних чисел . Функція приймає вектор комплексних чисел як вхідні дані та повертає хеш-значення типу size_t.
struct ComplexVectorHash {
    size_t operator()(const vector<complex<double>>& vec) const {
        size_t seed = vec.size();
        for (const auto& c : vec) {
            seed ^= hash<double>()(c.real()) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= hash<double>()(c.imag()) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};
 
//  функція рівності для векторів комплексних чисел . Функція operator() приймає два вектори комплексних чисел vec1 і vec2 і повертає логічне значення, яке вказує, чи вони рівні чи ні.
struct ComplexVectorEqual {
    bool operator()(const vector<complex<double>>& vec1, const vector<complex<double>>& vec2) const {
        if (vec1.size() != vec2.size()) {
            return false;
        }
        for (size_t i = 0; i < vec1.size(); i++) {
            if (vec1[i] != vec2[i]) {
                return false;
            }
        }
        return true;
    }
};


int main() {
    //  unordered_map визначає невпорядковану карту під назвою "таблиця", яка використовує вектори комплексних чисел як ключі та цілі числа як значення.
    unordered_map<vector<complex<double>>, int, ComplexVectorHash, ComplexVectorEqual> table;

    cout << "Enter the number of vectors: ";
    int num_vectors;
    cin >> num_vectors;

    for (int i = 0; i < num_vectors; i++) {
        vector<complex<double>> vec;

        cout << "Enter the number of complex numbers in vector " << i+1 << ": ";
        int num_complex;
        cin >> num_complex;

        for (int j = 0; j < num_complex; j++) {
            double real, imag;
            cout << "Enter the real and imaginary parts of complex number " << j+1 << ": ";
            cin >> real >> imag;
            vec.push_back(complex<double>(real, imag));
        }

        table[vec] = i;
    }

    cout << "Table contents:" << endl;
    for (const auto& pair : table) {
        cout << "Hash value " << pair.second <<" : ";
        cout << "Vector ";
        for (const auto& c : pair.first) {
            cout << "(" << c.real() << " + " << c.imag() << "i) ";
            
        }
        
        cout << endl;
    }

    return 0;
}
