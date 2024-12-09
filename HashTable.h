#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "../PRA_2324_P1/ListLinked.h"


template <typename V>
class HashTable : public Dict<V> {

private:
    int n;             // Número de elementos almacenados actualmente en la tabla
    int max;           // Tamaño de la tabla hash (número total de cubetas)
    ListLinked<TableEntry<V>>* table;  // Array de punteros a listas enlazadas de TableEntry<V>

    // Función hash
    int h(std::string key) {
        int sum = 0;
        for (char c : key) {
            sum += int(c);  // Sumar los valores ASCII de los caracteres
        }
        return sum % max;  // Modulo con el tamaño de la tabla
    }

public:
    // Constructor
    HashTable(int size) : n(0), max(size) {
        table = new ListLinked<TableEntry<V>>[max];  // Crear la tabla con el tamaño especificado
    }

    // Destructor
    ~HashTable() {
        delete[] table;  // Liberar la memoria dinámica de la tabla
    }

    // Devuelve el número total de cubetas
    int capacity() {
        return max;
    }

    // Sobrecarga del operador << para imprimir la tabla hash
    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
        for (int i = 0; i < th.max; ++i) {
            out << "[" << i << "]: ";
            for (auto& entry : th.table[i]) {  // Recorrer la lista en cada cubeta
                out << entry << " ";  // Imprimir cada entrada (clave->valor)
            }
            out << std::endl;
        }
        return out;
    }

    // Sobrecarga del operador [] para acceder a un valor por su clave
    V operator[](std::string key) {
        int index = h(key);  // Obtener la cubeta usando la función hash
        for (auto& entry : table[index]) {  // Buscar en la lista enlazada de la cubeta
            if (entry.key == key) {
                return entry.value;  // Devolver el valor asociado a la clave
            }
        }
        throw std::runtime_error("Clave no encontrada");  // Si no se encuentra la clave
    }

    // Implementación de insert (Método heredado de Dict<V>)
    void insert(std::string key, V value) override {
        int index = h(key);  // Obtener la cubeta usando la función hash
        for (auto& entry : table[index]) {  // Comprobar si la clave ya existe
            if (entry.key == key) {
                throw std::runtime_error("La clave ya existe en el diccionario");
            }
        }
        table[index].push_back(TableEntry<V>(key, value));  // Insertar el nuevo par clave-valor
        n++;  // Incrementar el número de elementos
    }

    // Implementación de search (Método heredado de Dict<V>)
    V search(std::string key) override {
        return (*this)[key];  // Usar el operador [] para buscar y devolver el valor
    }

    // Implementación de remove (Método heredado de Dict<V>)
    void remove(std::string key) override {
        int index = h(key);  // Obtener la cubeta usando la función hash
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->key == key) {
                table[index].erase(it);  // Eliminar el par clave-valor de la lista
                n--;  // Decrementar el número de elementos
                return;
            }
        }
        throw std::runtime_error("Clave no encontrada para eliminar");  // Si no se encuentra la clave
    }

    // Devuelve el número de elementos almacenados en la tabla
    int entries() override {
        return n;
    }
};

#endif
