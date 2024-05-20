//
//  BST.hpp
//  BinaryTree
//
//  Created by Vicente Cubells on 20/10/20.
//

#ifndef BST_hpp
#define BST_hpp

#include "BinaryTree.hpp"

template <class T>
class BST : public BinaryTree<T>
{
    
public:
    BST() {};
    virtual ~BST() { };
    
    TreeNode<T> * search(const T &) const;
    bool insert(const T &);
    bool insert(TreeNode<T> * );
    
    int whatlevelamI(const T &) const;
    
    TreeNode<T> * predecesor(TreeNode<T> * ) const;
    TreeNode<T> * sucesor(TreeNode<T> * ) const;
    TreeNode<T> * remove(T &);
    TreeNode<T> * remove(TreeNode<T> *);
    
    /* BEGIN TODO Actividad 3.1 */
    
    bool isBST() const;
    int height() const;
    void ancestors(T &) const;
    int count() const;
    
    /* END TODO Actividad 3.1 */

    std::vector<T> getTopN(int n) {
        std::vector<T> result;
        getTopNHelper(this->root, n, result); // 'this->root' para acceder al miembro 'root' de la clase base
        return result;
    }
    
    
    
private:
    /* Ocultar algunos métodos heredados */
    //using BinaryTree<T>::insert;

    bool isBSTU(TreeNode<T> *, T, T) const;
    int heightU(TreeNode<T> *) const;
    bool ancestorsU(TreeNode<T> *current, TreeNode<T> *target) const;
    int countU(TreeNode<T> *) const;

    void getTopNHelper(TreeNode<T> * node, int n, std::vector<T>& result) {
        if (node == nullptr || result.size() >= n) return;

        // Primero recorre el lado derecho para obtener los elementos más grandes primero
        getTopNHelper(node->getRight(), n, result);

        // Añadir el nodo actual si aún no se alcanza 'n'
        if (result.size() < n) {
            result.push_back(node->getInfo()); // Asegúrate de que el miembro que contiene la data se llama 'info'
            getTopNHelper(node->getLeft(), n, result); // Ahora el lado izquierdo
        }
    }
};

/*
 Complejidad: O(log n) si el árbol está balanceado
              O(n) si el árbol está desbalanceado
 */
template <class T>
TreeNode<T> * BST<T>::search(const T & value) const
{
    TreeNode<T> * aux = this->root;
    
    while (aux != nullptr) {
        if (aux->getInfo() == value) {
            return aux;
        }
        else {
            aux = aux->getInfo() > value ? aux->getLeft() : aux->getRight();
        }
    }
    
    return nullptr;
}

/*
 Complejidad: O(log n) si el árbol está balanceado
              O(n) si el árbol está desbalanceado
 */
template <class T>
bool BST<T>::insert(const T & value)
{
    return this->insert(new TreeNode<T>(value));
}

template <class T>
bool BST<T>::insert(TreeNode<T> * node )
{
    /* No se puede insertar un nodo NULL */
    if (node == nullptr) return false;
    
    /* Obtener la info del nodo a insertar */
    T value = node->getInfo();
    
    /* Establecer un apuntador auxiliar */
    TreeNode<T> * aux = this->root;
    
    /* Estalecer una variable para el padre */
    TreeNode<T> * parent = nullptr;
    
    /* Buscar la posición que le corresponde */
    while (aux != nullptr) {
        if (aux->getInfo() == value) {
            /* Liberar la memoria del nodo porque ya existe */
            delete node;
            
            return false;
        }
        else {
            parent = aux;
            aux = aux->getInfo() > value ? aux->getLeft() : aux->getRight();
        }
    }
    
    /* Establecer el parent del nodo a insertar */
    node->setParent(parent);
    
    /* Si el árbol está vacío, se inserta la raiz */
    if (parent == nullptr) {
        this->root = node;
    }
    else {
        /* Si el value a insertar es menor, se inserta a la izquierda */
        if ( parent->getInfo() > value ) {
            parent->setLeft(node);
        }
        /* Si el value a insertar es mayor, se inserta a la derecha */
        else {
            parent->setRight(node);
        }
    }
    
    return true;
}



/*
 Complejidad: O(log n) si el árbol está balanceado
              O(n) si el árbol está desbalanceado
 */
template <class T>
int BST<T>::whatlevelamI(const T & value) const
{
    int level = 0;
    
    TreeNode<T> * aux = this->root;
    
    while (aux != nullptr) {
        level++;
        if (aux->getInfo() == value) {
            return level;
        }
        else {
            aux = aux->getInfo() > value ? aux->getLeft() : aux->getRight();
        }
    }
    
    if (aux == nullptr) {
        level = 0;
    }
    
    return level;
}


/* Encontrar el predecesor de un nodo */
template <class T>
TreeNode<T> * BST<T>::predecesor(TreeNode<T> * actual) const
{
    TreeNode<T> * tmp = actual->getLeft();
    
    while( tmp->getRight() != nullptr) {
        tmp=tmp->getRight();
    }
    
    return tmp;
}

/* Encontrar el sucesor de un nodo */
template <class T>
TreeNode<T> * BST<T>::sucesor(TreeNode<T> * actual) const
{
    TreeNode<T> * tmp = actual->getRight();
    
    while( tmp->getLeft() != nullptr) {
        tmp=tmp->getLeft();
    }
    
    return  tmp;
}

/* Eliminar un nodo del árbol */
template <class T>
TreeNode<T> * BST<T>::remove(T & value)
{
    TreeNode<T> * node = this->search(value);
    
    return this->remove(node);
}

/* Eliminar un nodo del árbol */
template <class T>
TreeNode<T> * BST<T>::remove(TreeNode<T> * node)
{
    if (node != nullptr)
    {
        TreeNode<T> * left = node->getLeft();
        TreeNode<T> * right = node->getRight();
        TreeNode<T> * parent = node->getParent();
        
        // Verificar si tiene dos hijos
        if (left != nullptr && right != nullptr) {
            TreeNode<T> * pred = predecesor(node);
            T info = pred->getInfo();
            node->setInfo(info);
            node = remove(pred);
        }
        // Verificar si tiene un hijo a la izquierda
        else if (left != nullptr) {
            (parent != nullptr && parent->getLeft() == node) ? parent->setLeft(left) : parent->setRight(left);
            node->setLeft(nullptr);
        }
        // Verificar si tiene un hijo a la derecha
        else if (right != nullptr) {
            (parent != nullptr && parent->getLeft() == node) ? parent->setLeft(right) : parent->setRight(right);
            node->setRight(nullptr);
        }
        // No tiene hijos
        else {
            (parent != nullptr && parent->getLeft() == node) ? parent->setLeft(nullptr) : parent->setRight(nullptr);
        }
    }
    
    return node;
}


/* BEGIN TODO Actividad 3.1 */

/* Determinar si un árbol es un BST */
template <class T>
bool BST<T>::isBST() const {
    // Complejidad temporal: O(n), Complejidad espacial: O(n)
    return isBSTU(this->root, std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
}

template <class T>
bool BST<T>::isBSTU(TreeNode<T> *node, T min, T max) const {
    if (node == nullptr) return true;
    if (node->getInfo() <= min || node->getInfo() >= max) return false;
    return isBSTU(node->getLeft(), min, node->getInfo()) && isBSTU(node->getRight(), node->getInfo(), max);
}


/* Obtener la altura del árbol */
template <class T>
int BST<T>::height() const {
    // Complejidad temporal: O(n), Complejidad espacial: O(n)
    return heightU(this->root);
}

template <class T>
int BST<T>::heightU(TreeNode<T> *node) const {
    if (node == nullptr) return 0;
    return 1 + std::max(heightU(node->getLeft()), heightU(node->getRight()));
}

/* Visualizar los ancestros de un nodo */
template <class T>
void BST<T>::ancestors(T &value) const {
    // Complejidad temporal: O(n), Complejidad espacial: O(n)
    TreeNode<T> * node = this->search(value);
    if (node == nullptr) {
        std::cout << "No Ancestores encontrados" << std::endl;
    } else {
        std::cout << "Ancestros de " << value << ": ";
        ancestorsU(this->root, node);
        std::cout << std::endl;
    }
}

template <class T>
bool BST<T>::ancestorsU(TreeNode<T> *current, TreeNode<T> *target) const {
    if (current == nullptr) {
        return false;
    }

    if (current == target) {
        return true;
    }

    if (ancestorsU(current->getLeft(), target) || ancestorsU(current->getRight(), target)) {
        std::cout << current->getInfo() << " ";
        return true;
    }

    return false;
}

/* Obtener la cantidad de nodos del árbol */
template <class T>
int BST<T>::count() const {
    // Complejidad temporal: O(n), Complejidad espacial: O(n)
    return countU(this->root);
}

template <class T>
int BST<T>::countU(TreeNode<T> *node) const {
    if (node == nullptr) return 0;
    return 1 + countU(node->getLeft()) + countU(node->getRight());
}


/* END TODO Actividad 3.1 */

#endif /* BST_hpp */
