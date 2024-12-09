#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
private:
    int nelem;             // Número de elementos almacenados en el árbol
    BSNode<T>* root;       // Nodo raíz del árbol

    // Métodos privados recursivos
    BSNode<T>* search(BSNode<T>* n, T e) const;
    BSNode<T>* insert(BSNode<T>* n, T e);
    void print_inorder(std::ostream &out, BSNode<T>* n) const;
    BSNode<T>* remove(BSNode<T>* n, T e);
    T max(BSNode<T>* n) const;
    BSNode<T>* remove_max(BSNode<T>* n);
    void delete_cascade(BSNode<T>* n);

public:
    // Constructor
    BSTree();

    // Destructor
    ~BSTree();

    // Métodos públicos
    int size() const;
    T search(T e) const;
    void insert(T e);
    void remove(T e);

    // Sobrecarga del operador << para imprimir el árbol
    template <typename U>
    friend std::ostream& operator<<(std::ostream &out, const BSTree<U> &bst);

    T operator[](T e) const;
};

// Constructor
template <typename T>
BSTree<T>::BSTree() : nelem(0), root(nullptr) {}

// Destructor
template <typename T>
BSTree<T>::~BSTree() {
    delete_cascade(root);
}

// Función para obtener el número de elementos
template <typename T>
int BSTree<T>::size() const {
    return nelem;
}

// Método de búsqueda lanzadera
template <typename T>
T BSTree<T>::search(T e) const {
    BSNode<T>* node = search(root, e);
    if (node) {
        return node->elem;
    }
    throw std::runtime_error("Elemento no encontrado");
}

// Método recursivo de búsqueda
template <typename T>
BSNode<T>* BSTree<T>::search(BSNode<T>* n, T e) const {
    if (n == nullptr) {
        throw std::runtime_error("Elemento no encontrado");
    }
    if (n->elem == e) {
        return n;
    } else if (n->elem < e) {
        return search(n->right, e);
    } else {
        return search(n->left, e);
    }
}

// Sobrecarga del operador []
template <typename T>
T BSTree<T>::operator[](T e) const {
    return search(e);
}

// Método de inserción lanzadera
template <typename T>
void BSTree<T>::insert(T e) {
    root = insert(root, e);
}

// Método recursivo de inserción
template <typename T>
BSNode<T>* BSTree<T>::insert(BSNode<T>* n, T e) {
    if (n == nullptr) {
        nelem++;
        return new BSNode<T>(e);
    }
    if (n->elem == e) {
        throw std::runtime_error("Elemento duplicado");
    }
    if (n->elem < e) {
        n->right = insert(n->right, e);
    } else {
        n->left = insert(n->left, e);
    }
    return n;
}

// Método para imprimir el árbol en orden
template <typename T>
void BSTree<T>::print_inorder(std::ostream &out, BSNode<T>* n) const {
    if (n != nullptr) {
        print_inorder(out, n->left);
        out << n->elem << " ";
        print_inorder(out, n->right);
    }
}

// Sobrecarga del operador << para imprimir el árbol
template <typename T>
std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
    bst.print_inorder(out, bst.root);
    return out;
}

// Método de eliminación lanzadera
template <typename T>
void BSTree<T>::remove(T e) {
    root = remove(root, e);
}

// Método recursivo de eliminación
template <typename T>
BSNode<T>* BSTree<T>::remove(BSNode<T>* n, T e) {
    if (n == nullptr) {
        throw std::runtime_error("Elemento no encontrado");
    }
    if (n->elem == e) {
        if (n->left == nullptr && n->right == nullptr) {
            delete n;
            nelem--;
            return nullptr;
        } else if (n->left == nullptr) {
            BSNode<T>* temp = n->right;
            delete n;
            nelem--;
            return temp;
        } else if (n->right == nullptr) {
            BSNode<T>* temp = n->left;
            delete n;
            nelem--;
            return temp;
        } else {
            n->elem = max(n->left);
            n->left = remove_max(n->left);
        }
    } else if (n->elem < e) {
        n->right = remove(n->right, e);
    } else {
        n->left = remove(n->left, e);
    }
    return n;
}

// Método recursivo para encontrar el valor máximo
template <typename T>
T BSTree<T>::max(BSNode<T>* n) const {
    while (n->right != nullptr) {
        n = n->right;
    }
    return n->elem;
}

// Método recursivo para eliminar el máximo
template <typename T>
BSNode<T>* BSTree<T>::remove_max(BSNode<T>* n) {
    if (n->right == nullptr) {
        return n->left;
    }
    n->right = remove_max(n->right);
    return n;
}

// Método recursivo para liberar memoria
template <typename T>
void BSTree<T>::delete_cascade(BSNode<T>* n) {
    if (n != nullptr) {
        delete_cascade(n->left);
        delete_cascade(n->right);
        delete n;
    }
}

#endif
