#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <iostream>

template <typename V>
class TableEntry {
private:
    std::string key;  // Clave de la entrada
    V value;          // Valor asociado a la clave

public:
    // Constructor
    TableEntry(std::string key, V value) : key(key), value(value) {}

    // Getters
    std::string getKey() const { return key; }
    V getValue() const { return value; }

    // Sobrecarga del operador <
    friend bool operator<(const TableEntry<V>& te1, const TableEntry<V>& te2) {
        return te1.key < te2.key;  // Comparar las claves lexicográficamente
    }

    // Sobrecarga del operador >
    friend bool operator>(const TableEntry<V>& te1, const TableEntry<V>& te2) {
        return te1.key > te2.key;  // Comparar las claves lexicográficamente
    }

    // Sobrecarga del operador <<
    friend std::ostream& operator<<(std::ostream& os, const TableEntry<V>& entry) {
        os << entry.key << ": " << entry.value;
        return os;
    }
};

#endif
