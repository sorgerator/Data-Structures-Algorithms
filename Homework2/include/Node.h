//
// Created by aldin on 21/04/2025.
//

#ifndef NODE_H
#define NODE_H
#include <utility>

#include "Process.h"

struct Node {
    Process process{};
    Node* next{};

    Node() = default;
    explicit Node(Process process): process(std::move(process)) {}
    Node(Process process, Node* next) : process(std::move(process)), next(next) {}
};

#endif //NODE_H
