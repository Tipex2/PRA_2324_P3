#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {
private:
    BSTree<TableEntry<V>>* tree;  // ABB que gestiona las entradas clave->valor

public:
    // Constructor
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>();
    }

    // Destructor
    ~BSTreeDict() {
        delete tree;  // Liberar la memoria del ABB
    }

    // Sobrecarga de operador <<
    friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &dict) {
        out << *dict.tree;  // Delegar al operador<< del árbol
        return out;
    }

    // Sobrecarga de operador []
    V operator[](std::string key) {
        TableEntry<V> entry(key, V());  // Crear una entrada temporal con la clave
        return (*tree)[entry].getValue();  // Buscar y devolver el valor correspondiente
    }

    // Métodos de la interfaz Dict<V>
    void insert(std::string key, V value) override {
        TableEntry<V> entry(key, value);
        tree->insert(entry);
    }

    V search(std::string key) override {
        TableEntry<V> entry(key, V());
        return (*tree)[entry].getValue();
    }

    void remove(std::string key) override {
        TableEntry<V> entry(key, V());
        tree->remove(entry);
    }

    // Método para obtener todas las entradas del diccionario
    std::vector<TableEntry<V>> entries() const override {
        std::vector<TableEntry<V>> result;
        tree->print_inorder([&result](const TableEntry<V>& entry) {
            result.push_back(entry);
        });
        return result;
    }
};

#endif
