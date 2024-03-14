#ifndef TREE_H
#define TREE_H

#include <vector>
#include <stack>
#include "array_exception.h"

template<typename Key, typename Data>
class BST {
private:
    struct Node {
        Key key;
        Data data;
        Node* left;
        Node* right;

        Node(const Key& k, const Data& d) : key(k), data(d), left(nullptr), right(nullptr) {}
    };

    Node* root;
    size_t size;

public:
    /**
     * \brief Конструктор по умолчанию.
     * \post Дерево пустое.
    */
    BST() : root(nullptr), size(0) {}

    /**
     * \brief Конструктор копирования.
     * \param other Другое дерево.
     * \post Создана копия дерева other.
    */
    BST(const BST& other);

    /**
     * \brief Деструктор.
     * \post Дерево освобождено.
    */
    ~BST() {
        clear();
    }

    /**
     * \brief Получение размера дерева.
     * \return Размер дерева.
     * \post Дерево остаётся неизменным.
    */
    size_t get_size() const { return size; }

    /**
     * \brief Очистка дерева.
     * \post Дерево пустое.
    */
    void clear();

    /**
     * \brief Проверка дерева на пустоту.
     * \return true, если дерево пустое, иначе false.
     * \post Дерево остаётся неизменным.
    */
    bool is_empty() const { return size == 0; }

    /**
     * \brief Поиск элемента с заданным ключом.
     * \param key Ключ для поиска.
     * \return Сылка на найденный элемент, если он существует.
     * \post Дерево остаётся неизменным.
     * \throw std::runtime_error Если элемент с заданным ключом не существует в дереве.
    */
    Data& operator[](const Key& key);

    /**
     * \brief Поиск элемента с заданным ключом.
     * \param key Ключ для поиска.
     * \return Ссылка на найденный элемент, если он существует.
     * \post Дерево остаётся неизменным.
     * \throw std::runtime_error Если элемент с заданным ключом не существует в дереве.
    */
    const Data& operator[](const Key& key) const;

    /**
     * \brief Вставляет данные с заданным ключом в дерево.
     * \param key Ключ для вставки.
     * \param data Данные для вставки.
     * \pre Дерево не содержит элемента с заданным ключом.
     * \post Размер дерева увеличивается на 1.
     * \return true, если элемент был вставлен, иначе false.
    */
    bool insert(const Key& key, const Data& data);

    /**
     * \brief Удаляет элемент с заданным ключом из дерева.
     * \param key Ключ для удаления.
     * \pre Дерево содержит элемент с заданным ключом.
     * \post Размер дерева уменьшается на 1. Из дерева удаляется элемент с заданным ключом.
     * \return true, если элемент был удалён, иначе false.
    */
    bool remove(const Key& key);

    /**
     * \brief формирование списка ключей в дереве в порядке обхода узлов по схеме L -> t -> R
     * \return Список ключей дерева.
     * \post Дерево остаётся неизменным.
    */
    std::vector<Key> get_keys() const;

    /**
     * \brief Определяет длину внешнего пути дерева.
     * \return Длина внешнего пути дерева.
     * \post Дерево остаётся неизменным.
    */
    size_t get_external_path_length() const;

    /**
     * \brief Вывод структуры дерева в консоль. (обход L -> t -> R)
     * \post Дерево остаётся неизменным.
    */
    void print_tree() const;

    /**
     * \brief Опрос числа узлов дерева, просмотренных предыдущей операцией.
     * \return Число узлов дерева, просмотренных предыдущей операци
     * \post Дерево остаётся неизменным.
    */
    int print_nodes_visited() const;

    class Iterator {
    private:
        Node* current;
        std::stack<Node*> parent_stack;

        void push_left_children(Node* node);

    public:
        Iterator(Node* node);

        Data& operator*();
        const Data& operator*() const;

        Iterator& operator++();
        Iterator operator++(int);

        Iterator& operator--();
        Iterator operator--(int);

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

    Iterator begin();
    Iterator rbegin();
    Iterator end();
    Iterator rend();
};

template<typename Key, typename Data>
bool BST<Key, Data>::insert(const Key& key, const Data& data) {
    if (root == nullptr) { // дерево пустое
        root = new Node(key, data);
        ++size;
        return true;
    }

    Node* current = root;
    Node* parent = nullptr;
    while (current != nullptr) { // ищем место вставки
        parent = current;
        if (key == current->key) { // дубликаты запрещены
            return false;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    Node* new_node = new Node(key, data);

    if (key < parent->key) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }

    ++size;

    return true;
}

template <typename Key, typename Data>
bool BST<Key, Data>::remove(const Key& key) {
    Node *current = root;
    Node *parent = nullptr;

    // Поиск удаляемого узла
    while (current != nullptr && current->key != key) {
        parent = current;

        if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == nullptr) { // элемента с заданным ключом не существует
        return false;
    }

    // У удаляемого узла нет детей (это лист дерева)
    if (current->left == nullptr && current->right == nullptr) {
        if (current == root) {
            root = nullptr;
        } else if (current == parent->left) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }

        delete current;
    }

    // У удаляемого узла есть один дочерний узел
    else if (current->left == nullptr) { // левый дочерний узел
        if (current == root) {
            root = current->right;
        } else if (current == parent->left) {
            parent->left = current->right;
        } else {
            parent->right = current->right;
        }

        delete current;
    }

    else if (current->right == nullptr) { // правый дочерний узел
        if (current == root) {
            root = current->left;
        } else if (current == parent->left) {
            parent->left = current->left;
        } else {
            parent->right = current->left;
        }

        delete current;
    }

    // У удаляемого узла два дочерних узла
    else {
        Node *successor = current->right;
        Node *successor_parent = current;

        // Ищем приемника узла (это узел с минимальным ключом в правом поддереве)
        while (successor->left != nullptr) {
            successor_parent = successor;
            successor = successor->left;
        }

        // Копируем приемника в удаляемый узел
        current->key = successor->key;
        current->data = successor->data;

        // Удаляем приемника
        if (successor == successor_parent->left) {
            successor_parent->left = nullptr;
        } else {
            successor_parent->right = nullptr;
        }

        delete successor;
    }

    --size;
    return true;
}

template <typename Key, typename Data>
void BST<Key, Data>::clear() {
    if (root == nullptr) {
        return;
    }

    std::stack<Node*> node_stack;
    node_stack.push(root);

    while (!node_stack.empty()) {
        Node* current = node_stack.top();
        node_stack.pop();

        if (current->left != nullptr) {
            node_stack.push(current->left);
        }
        if (current->right != nullptr) {
            node_stack.push(current->right);
        }

        delete current;
    }

    size = 0;
    root = nullptr;
}

template <typename Key, typename Data>
Data& BST<Key, Data>::operator[](const Key& key) {
    if (root == nullptr) {
        throw Array_exception("BST is empty");
    }

    Node* current = root;

    while (current != nullptr) { // Поиск узла с заданным ключом
        if (current->key == key) {
            return current->data;
        } else if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        }
    }

    throw Array_exception("No such key in BST");
}

template <typename Key, typename Data>
void BST<Key, Data>::print_tree() const {
    // if (root == nullptr) {
    //     return;
    // }

    std::stack<Node*> parent_stack;
    Node *current = root;

    std::cout << "Tree: ";
    while (!parent_stack.empty() || current != nullptr) {
        if (current != nullptr) {
            parent_stack.push(current);
            current = current->left;
        } else {
            current = parent_stack.top();
            parent_stack.pop();
            std::cout << current->key << " ";
            current = current->right;
        }
    }
    std::cout << std::endl;
}

#endif