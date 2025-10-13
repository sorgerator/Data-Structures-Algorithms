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
}

template<typename Data>
XorLinkedList<Data>::XorLinkedList(const XorLinkedList<Data> &src) {
    // your code
}

template<typename Data>
XorLinkedList<Data> &XorLinkedList<Data>::operator=(const XorLinkedList<Data> &src) {
    // your code
}

template<typename Data>
XorLinkedList<Data>::XorLinkedList(XorLinkedList<Data> &&src) noexcept {
    // your code
}

template<typename Data>
XorLinkedList<Data> &XorLinkedList<Data>::operator=(XorLinkedList<Data> &&src) noexcept {
    // your code
}

template<typename Data>
XorLinkedList<Data>::XorLinkedList(std::initializer_list<Data> list) {
    // your code
}

template<typename Data>
void XorLinkedList<Data>::add_to_front(const Data &data) {
    // your code
}

template<typename Data>
void XorLinkedList<Data>::add_to_back(const Data &data) {
    // your code
}

template<typename Data>
void XorLinkedList<Data>::remove_from_front() {
    // your code
}

template<typename Data>
void XorLinkedList<Data>::remove_from_back() {
    // your code
}

template<typename Data>
Data &XorLinkedList<Data>::get(int index) {
    // your code
}

template<typename Data>
int XorLinkedList<Data>::count() const {
    // your code
}

template<typename Data>
void XorLinkedList<Data>::reverse() {
    // your code
}

template <typename Data>
class XorLinkedList<Data>::Iterator : public std::iterator<std::forward_iterator_tag, Data> {
private:
    Node<Data>* current;
public:
    explicit Iterator(Node<Data>* current) : current(current) {}

    Data& operator*() {
        // your code
    }
    Iterator& operator++() {
        // your code
    }

    Iterator operator++(int) {
        // your code
    }

    bool operator==(const Iterator& other) const {
        // your code
    }

    bool operator!=(const Iterator& other) const {
        // your code
    }
};

template<typename Data>
typename XorLinkedList<Data>::Iterator XorLinkedList<Data>::begin() {
    // your code
}

template<typename Data>
typename XorLinkedList<Data>::Iterator XorLinkedList<Data>::end() {
    // your code
}

template<typename Data>
const Data& XorLinkedList<Data>::operator[](int index) const {
    // your code
}

template<typename Data>
Data& XorLinkedList<Data>::operator[](const int index) {
    // your code
}

#endif //XORLINKEDLIST_TPP
