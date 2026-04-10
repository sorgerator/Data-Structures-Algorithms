//
// Created by aldin on 21/04/2025.
//

#ifndef PROCESSQUEUE_H
#define PROCESSQUEUE_H
#include "Node.h"
#include "Process.h"

class ProcessQueue {
private:
    Node* head{};
    Node* tail{};
    int length{0};
public:
    // constructors
    ProcessQueue() = default;
    ProcessQueue(std::initializer_list<Process> queue);
    // copy semantics
    ProcessQueue(const ProcessQueue& src);
    ProcessQueue& operator=(const ProcessQueue& src);
    // move semantics
    ProcessQueue(ProcessQueue&& src) noexcept;
    ProcessQueue& operator=(ProcessQueue&& src) noexcept;
    // destructor
    ~ProcessQueue();

    void enqueue(const Process& process);
    Process dequeue();
    bool is_empty() const;
    int size() const;
    Process& peek() const;

    // Already implemented, do not remove or edit
    const Node* get_head() const;
    const Node* get_tail() const;
};

#endif //PROCESSQUEUE_H
