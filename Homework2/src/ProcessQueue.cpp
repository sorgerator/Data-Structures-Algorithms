//
// Created by aldin on 21/04/2025.
//
#include "../include/ProcessQueue.h"

#include <stdexcept>

/**
 * These methods are already implemented for you; do not edit them.
 */
const Node* ProcessQueue::get_head() const {
    return head;
}

const Node* ProcessQueue::get_tail() const {
    return tail;
}

/**
 * Your implementations below this comment.
 */
void ProcessQueue::enqueue(const Process& process) {
    // your code
    Node* new_node = new Node(process);

    if (head == nullptr) {
        head = node;
        tail = node;
        node->next = node;
    } else {
        tail->next = node;
        node->next = head;
        tail = node;
    }

    length++;
}

Process ProcessQueue::dequeue() {
    // your code
    if (head == nullptr) {
        throw std::runtime_error("Cannot dequeue from empty queue");
    }

    Process process = head->process;

    if (head == tail) {
        delete head;
    head = nullptr;
    tail = nullptr;
    } else {
        Node* temp = head;
        tail->next = head->next;
    head = head->next;
    delete temp;
    }

    length--;
    return process;
}

Process& ProcessQueue::peek() const {
    // your code
    return head->process;
}

bool ProcessQueue::is_empty() const {
    // your code
    if (length = 0) {
        return true;
    } else {
        return false;
    }

int ProcessQueue::size() const {
    // your code

}

ProcessQueue::~ProcessQueue() {
    // your code
}

ProcessQueue::ProcessQueue(std::initializer_list<Process> queue) {
    // your code
}

ProcessQueue::ProcessQueue(const ProcessQueue &src) {
    // your code
}

ProcessQueue& ProcessQueue::operator=(const ProcessQueue &src) {
    // your code
}

ProcessQueue::ProcessQueue(ProcessQueue &&src) noexcept {
    // your code
}

ProcessQueue& ProcessQueue::operator=(ProcessQueue &&src) noexcept {
    // your code
}

