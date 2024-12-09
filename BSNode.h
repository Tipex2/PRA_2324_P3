#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T> 
class BSNode {
public:
    // Atributos
    T elem;                    // El elemento almacenado en el nodo (tipo T)
    BSNode<T>* left;           // Puntero al hijo izquierdo
    BSNode<T>* right;          // Puntero al hijo derecho

    // Constructor
    BSNode(T elem, BSNode<T>* left = nullptr, BSNode<T>* right = nullptr)
        : elem(elem), left(left), right(right) {}

    // Sobrecarga del operador << para imprimir el nodo
    friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn) {
        out << bsn.elem;   // Solo imprimimos el elemento del nodo
        return out;
    }
};

#endif
