#ifndef TREE_H
#define TREE_H

#include <vector>
#include <stack>
#include <queue>
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

    Node* find_node(const Key& key) const;

    void show(Node* current, int level) const;

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
     * \throw Array_exception если элемент с заданным ключом не существует в дереве.
    */
    Data& operator[](const Key& key);

    /**
     * \brief Поиск элемента с заданным ключом (константная версия).
     * \param key Ключ для поиска.
     * \return Константная ссылка на найденный элемент, если он существует.
     * \post Дерево остаётся неизменным.
     * \throw Array_exception если элемент с заданным ключом не существует в дереве.
    */
    const Data& operator[](const Key& key) const;

    /**
     * \brief Поиск элемента с заданным ключом.
     * \param key Ключ для поиска.
     * \return Сылка на найденный элемент, если он существует.
     * \post Дерево остаётся неизменным.
     * \throw Array_exception если элемент с заданным ключом не существует в дереве.
    */
    Data& at(const Key& key);

    /**
     * \brief Поиск элемента с заданным ключом (константная версия).
     * \param key Ключ для поиска.
     * \return Константная ссылка на найденный элемент, если он существует.
     * \post Дерево остаётся неизменным.
     * \throw Array_exception если элемент с заданным ключом не существует в дереве.
    */
    const Data& at(const Key& key) const;

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

    /**
     * \brief Прямой итератор для обхода дерева бинарного поиска
    */
    class Iterator {
    private:
        BST<Key, Data>& cur_tree;
        Node* cur_node;

        /**
         * \brief Поиск крайнего левого узла дерева (поиск узла с наименьшим ключом)
        */
        Node* find_min(Node *node) const {
            if (node == nullptr) {
                return nullptr;
            }

            if (node->left == nullptr) {
                return node;
            }

            return find_min(node->left);
        }

        /**
         * \brief Поиск крайнего правого узла дерева (поиск узла с наибольшим ключом)
        */
        Node* find_max(Node *node) const {
            if (node == nullptr) {
                return nullptr;
            }

            while (node->right != nullptr) {
                node = node->right;
            }

            return node;
        }

        /**
         * \brief Поиск узла, узел с заданным ключом для которого является его правым потомком
        */
        Node* find_r_parent(Node *node, const Key& key) const {
            if (node == nullptr) {
                return nullptr;
            }

            if (key > node->key) { // искомый предок должен быть в правом поддереве текущего узла
                Node *r_parent = find_r_parent(node->right, key);
                if (r_parent != nullptr) { // мы нашли искомого предка в правом поддереве
                    return r_parent;
                } else { // в правом поддереве нет искомого предка
                    return node;
                }
            } else { // искомый предок должен быть в левом поддереве текущего узла
                return find_r_parent(node->left, key);
            }
        }

        /**
         * \brief Поиск узла, узел с заданным ключом для которого является его левым потомком
        */
        Node *find_l_parent(Node *node, const Key& key) const {
            if (node == nullptr) {
                return nullptr;
            }

            if (key < node->key) { // искомый предок должен быть в левом поддереве текущего узла
                Node *l_parent = find_l_parent(node->left, key);
                if (l_parent != nullptr) { // мы нашли искомого предка в левом поддереве
                    return l_parent;
                } else { // в левом поддереве нет искомого предка
                    return node;
                }
            } else { // искомый предок должен быть в правом поддереве текущего узла
                return find_l_parent(node->right, key);
            }
        }

        /**
         * \brief Поиск предыдущего узла дерева (поиск узла с наибольшим ключом меньше текущего)
        */
        Node* find_predecessor(Node *node) const {
            if (node->left != nullptr) {
                return find_max(node->left); // максимальный ключ в левом поддереве
            } else {
                return find_r_parent(cur_tree.root, node->key); // узел для которого текущий узел является правым потомком
            }
        }

        Node* find_successor(Node *node) const {
            if (node->right!= nullptr) {
                return find_min(node->right); // минимальный ключ в правом поддереве
            } else {
                return find_l_parent(cur_tree.root, node->key); // узел для которого текущий узел является левым потомком
            }
        }

    public:
        Iterator(BST<Key, Data>& tree) : cur_tree(tree), cur_node(find_min(tree.root)) {}

        Iterator(BST<Key, Data>& tree, Node* node) : cur_tree(tree), cur_node(node) {}

        Data& operator*() {
            if (cur_node == nullptr) {
                throw Array_exception("Iterator is not initialized");
            }

            return cur_node->data;
        }

        const Data& operator*() const {
            if (cur_node == nullptr) {
                throw Array_exception("Iterator is not initialized");
            }

            return cur_node->data;
        }

        /**
         * \brief Переход к следующему элементу в дереве.
        */
        Iterator& operator++() {
            if (cur_node == nullptr) {
                throw Array_exception("Cannot move past end of the tree");
            }

            cur_node = find_successor(cur_node);

            return *this;
        }

        /**
         * \brief Переход к предыдущему элементу в дереве.
        */
        Iterator& operator--() {
            if (cur_node == nullptr) {
                throw Array_exception("Cannot move past beginning of the tree");
            }

            cur_node = find_predecessor(cur_node);

            return *this;
        }

        bool operator==(const Iterator& other) const {
            return cur_node == other.cur_node;
        }

        bool operator!=(const Iterator& other) const {
            return cur_node != other.cur_node;
        }
    };

    Iterator begin() {
        return Iterator(*this);
    }

    Iterator rbegin();

    Iterator end() {
        return Iterator(*this, nullptr);
    }

    Iterator rend();
};

template <typename Key, typename Data>
BST<Key, Data>::BST(const BST& other) : BST() {
    if (other.root == nullptr) {
        return;
    }

    // стек с парами (узел, родитель)
    std::stack<std::pair<Node*, Node*>> nodes_stack;
    nodes_stack.push(std::make_pair(other.root, nullptr));

    while (!nodes_stack.empty()) {
        Node* current = nodes_stack.top().first;
        Node* parent = nodes_stack.top().second;
        nodes_stack.pop();

        Node *new_node = new Node(current->key, current->data);

        if (parent == nullptr) { // мы на корне второго дерева
            root = new_node;
        } else if (current == parent->left) { // мы в левом поддереве
            parent->left = new_node;
        } else { // мы в правом поддереве
            parent->right = new_node;
        }

        if (current->left != nullptr) {
            nodes_stack.push(std::make_pair(current->left, new_node));
        }

        if (current->right != nullptr) {
            nodes_stack.push(std::make_pair(current->right, new_node));
        }
    }
}

template <typename Key, typename Data>
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

    if (key < parent->key) { // создаем необходимые связи в дереве с новым узлом
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
typename BST<Key, Data>::Node* BST<Key, Data>::find_node(const Key& key) const {
    if (root == nullptr) {
        throw Array_exception("BST is empty");
    }

    Node* current = root;

    while (current != nullptr) { // Поиск узла с заданным ключом
        if (current->key == key) {
            return current;
        } else if (key < current->key) {
            current = current->left;
        } else if (key > current->key) {
            current = current->right;
        }
    }

    throw Array_exception("No such key in BST");
}

template <typename Key, typename Data>
Data& BST<Key, Data>::operator[](const Key& key) {
    return find_node(key)->data;
}

template <typename Key, typename Data>
const Data& BST<Key, Data>::operator[](const Key& key) const {
    return find_node(key)->data;
}

template <typename Key, typename Data>
Data& BST<Key, Data>::at(const Key& key) {
    return (*this)[key];
}

template <typename Key, typename Data>
const Data& BST<Key, Data>::at(const Key& key) const {
    return (*this)[key];
}

template <typename Key, typename Data>
void BST<Key, Data>::show(Node* current, int level) const {
    if (current == nullptr) {
        return;
    }

    show(current->right, level + 1);

    for (int i = 0; i < level; ++i) {
        std::cout << "  ";
    }

    std::cout << current->key << " " << current->data << std::endl;

    show(current->left, level + 1);
}

template <typename Key, typename Data>
void BST<Key, Data>::print_tree() const {
    if (root == nullptr) {
        std::cout << "Tree is empty" << std::endl;
    }

    show(root, 0);
}

template <typename Key, typename Data>
std::vector <Key> BST<Key, Data>::get_keys() const {
    std::vector <Key> keys;

    if (root == nullptr) {
        return keys;
    }

    std::stack<Node*> parent_stack;
    Node *current = root;

    while (!parent_stack.empty() || current != nullptr) {
        if (current != nullptr) {
            parent_stack.push(current);
            current = current->left;
        } else {
            current = parent_stack.top();
            parent_stack.pop();
            keys.push_back(current->key);
            current = current->right;
        }
    }

    return keys;
}

// Внешним  узлом является узел с одним сыном или без сыновей
// Длина внешнего пути  – сумма уровней всех внешних узлов дерева
template <typename Key, typename Data>
size_t BST<Key, Data>::get_external_path_length() const {
    if (root == nullptr) {
        return 0;
    }

    size_t path_length = 0;

    std::stack<std::pair<Node*, size_t>> node_stack;
    node_stack.push(std::make_pair(root, 0));

    while (!node_stack.empty()) {
        Node* current = node_stack.top().first;
        size_t level = node_stack.top().second;
        node_stack.pop();

        if (current->left == nullptr && current->right == nullptr) {
            path_length += level;
        } else {
            if (current->left != nullptr) {
                node_stack.push(std::make_pair(current->left, level + 1));
            }
            if (current->right != nullptr) {
                node_stack.push(std::make_pair(current->right, level + 1));
            }
        }
    }

    return path_length;
}

#endif