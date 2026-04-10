//
// Created by aldin on 16/06/2025.
//

#ifndef NODE_H
#define NODE_H
#include <string>
#include <vector>
#include "Entry.h"

struct Node {
    // add all required Node fields
    std::string key;
    std::vector<Entry> values;
    Node* left;
    Node* right;

    Node(const std::string& searchable_name, const Entry& entry) : key(searchable_name), left(nullptr), right(nullptr) {
        values.push_back(entry);
    }
};

#endif //NODE_H
