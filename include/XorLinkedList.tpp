//
// Created by aldin on 18/03/2025.
//

#ifndef XORLINKEDLIST_TPP
#define XORLINKEDLIST_TPP

#include <cstdint>
#include <iterator>

/**
 * These methods are already implemented for you.
 */
template<typename Data>
Node<Data>* ptr_xor(Node<Data> *p, Node<Data> *q) {
    return reinterpret_cast<Node<Data>*>(reinterpret_cast<uintptr_t>(p) ^ reinterpret_cast<uintptr_t>(q));
}

template<typename Data>
Node<Data> *XorLinkedList<Data>::get_head() const {
    return head;
}


/**
 * Your implementations below this comment.
 */

template<typename Data>
XorLinkedList<Data>::~XorLinkedList() {
    // your code
    Node<Data>* prev = nullptr;
    Node<Data>* curr = head;

    while (curr != nullptr) {
        Node<Data>* next = ptr_xor<Data>(prev, curr->both);
        delete curr;
        prev = curr;
        curr = next;
    }

    head = nullptr;
    size = 0;
}

template<typename Data>
XorLinkedList<Data>::XorLinkedList(const XorLinkedList<Data> &src) {
    // your code
    head = nullptr;
    size = 0;

    Node<Data>* prev = nullptr;
    Node<Data>* curr = src.head;

    while (curr != nullptr) {
        add_to_back(curr->data);
        Node<Data>* next = ptr_xor<Data>(prev, curr->both);
        prev = curr;
        curr = next;
    }
}

template<typename Data>
XorLinkedList<Data> &XorLinkedList<Data>::operator=(const XorLinkedList<Data> &src) {
    // your code
    if (this != &src) {
        this->~XorLinkedList();

        head = nullptr;
        size = 0;

        Node<Data>* prev = nullptr;
        Node<Data>* curr = src.head;

        while (curr != nullptr) {
            add_to_back(curr->data);
            Node<Data>* next = ptr_xor<Data>(prev, curr->both);
            prev = curr;
            curr = next;
        }
    }

    return *this;
}

template<typename Data>
XorLinkedList<Data>::XorLinkedList(XorLinkedList<Data> &&src) noexcept {
    // your code
    head = src.head;
    size = src.size;

    // Leave src in empty state
    src.head = nullptr;
    src.size = 0;
}

template<typename Data>
XorLinkedList<Data> &XorLinkedList<Data>::operator=(XorLinkedList<Data> &&src) noexcept {
    // your code
    if (this != &src) {
        // Clean up current resources
        this->~XorLinkedList();

        // Steal resources
        head = src.head;
        size = src.size;

        // Leave src empty
        src.head = nullptr;
        src.size = 0;
    }

    return *this;
}

template<typename Data>
XorLinkedList<Data>::XorLinkedList(std::initializer_list<Data> list) {
    // your code
    head = nullptr;
    size = 0;

    for (const Data &d : list) {
        add_to_back(d);
    }
}

template<typename Data>
void XorLinkedList<Data>::add_to_front(const Data &data) {
    // your code
    Node<Data>* new_node = new Node<Data>();
    new_node->data = data;
    new_node->both = ptr_xor<Data>(nullptr, head);

    if (head != nullptr) {
        Node<Data>* next = ptr_xor<Data>(nullptr, head->both);
        head->both = ptr_xor<Data>(new_node, next);
    }

    head = new_node;
    ++size;
}

template<typename Data>
void XorLinkedList<Data>::add_to_back(const Data &data) {
    // your code
    if (head == nullptr) {
        Node<Data>* new_node = new Node<Data>();
        new_node->data = data;
        new_node->both = nullptr;
        head = new_node;
        size = 1;
        return;
    }

    Node<Data>* prev = nullptr;
    Node<Data>* curr = head;
    Node<Data>* next = nullptr;

    while (true) {
        next = ptr_xor<Data>(prev, curr->both);
        if (next == nullptr) {
            // curr is tail
            break;
        }
        prev = curr;
        curr = next;
    }

    Node<Data>* new_node = new Node<Data>();
    new_node->data = data;
    new_node->both = ptr_xor<Data>(curr, nullptr);
    curr->both = ptr_xor<Data>(prev, new_node);

    ++size;
}

template<typename Data>
void XorLinkedList<Data>::remove_from_front() {
    // your code
    if (head == nullptr) {
        throw std::out_of_range("List is empty");
    }

    Node<Data>* old_head = head;
    Node<Data>* second = ptr_xor<Data>(nullptr, old_head->both);

    if (second == nullptr) {
        delete old_head;
        head = nullptr;
        size = 0;
        return;
    }

    Node<Data>* next = ptr_xor<Data>(old_head, second->both);
    second->both = ptr_xor<Data>(nullptr, next);

    head = second;
    delete old_head;
    --size;
}

template<typename Data>
void XorLinkedList<Data>::remove_from_back() {
    // your code
    if (head == nullptr) {
        throw std::out_of_range("List is empty");
    }

    if (ptr_xor<Data>(nullptr, head->both) == nullptr) {
        delete head;
        head = nullptr;
        size = 0;
        return;
    }

    Node<Data>* prev = nullptr;
    Node<Data>* curr = head;
    Node<Data>* next = nullptr;

    while (true) {
        next = ptr_xor<Data>(prev, curr->both);
        if (next == nullptr) {
            break;
        }
        prev = curr;
        curr = next;
    }

    Node<Data>* prevprev = ptr_xor<Data>(curr, prev->both);
    prev->both = ptr_xor<Data>(prevprev, nullptr);

    delete curr;
    --size;
}

template<typename Data>
Data &XorLinkedList<Data>::get(int index) {
    // your code
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index is out of range");
    }

    Node<Data>* prev = nullptr;
    Node<Data>* curr = head;

    for (int i = 0; i < index; ++i) {
        Node<Data>* next = ptr_xor<Data>(prev, curr->both);
        prev = curr;
        curr = next;
    }

    return curr->data;
}

template<typename Data>
int XorLinkedList<Data>::count() const {
    // your code
    return size;
}

template<typename Data>
void XorLinkedList<Data>::reverse() {
    // your code
    if (head == nullptr || size <= 1) return;

    std::vector<Data> tmp;
    tmp.reserve(size);

    Node<Data>* prev = nullptr;
    Node<Data>* curr = head;

    while (curr != nullptr) {
        tmp.push_back(curr->data);
        Node<Data>* next = ptr_xor<Data>(prev, curr->both);
        prev = curr;
        curr = next;
    }

    this->~XorLinkedList();

    for (int i = static_cast<int>(tmp.size()) - 1; i >= 0; --i) {
        add_to_back(tmp[i]);
    }
}

template <typename Data>
class XorLinkedList<Data>::Iterator : public std::iterator<std::forward_iterator_tag, Data> {
private:
    Node<Data>* current;
    Node<Data>* prev;
public:
    explicit Iterator(Node<Data>* current, Node<Data>* prev = nullptr)
    : current(current), prev(prev) {}

    Data& operator*() {
        // your code
        if (current == nullptr) {
            throw std::out_of_range("Dereferencing end iterator");
        }

        return current->data;
    }

    Iterator& operator++() {
        // your code
        if (current == nullptr) return *this;
        Node<Data>* next = ptr_xor<Data>(prev, current->both);
        prev = current;
        current = next;
        return *this;
    }

    Iterator operator++(int) {
        // your code
        Iterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const Iterator& other) const {
        // your code
        return current == other.current;
    }

    bool operator!=(const Iterator& other) const {
        // your code
        return !(*this == other);
    }
};

template<typename Data>
typename XorLinkedList<Data>::Iterator XorLinkedList<Data>::begin() {
    // your code
    return Iterator(head, nullptr);
}

template<typename Data>
typename XorLinkedList<Data>::Iterator XorLinkedList<Data>::end() {
    // your code
    return Iterator(nullptr, nullptr);
}

template<typename Data>
const Data& XorLinkedList<Data>::operator[](int index) const {
    // your code
    return const_cast<XorLinkedList<Data>*>(this)->get(index);
}

template<typename Data>
Data& XorLinkedList<Data>::operator[](const int index) {
    // your code
    return get(index);
}

#endif //XORLINKEDLIST_TPP