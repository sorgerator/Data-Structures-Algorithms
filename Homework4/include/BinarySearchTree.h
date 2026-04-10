//
// Created by aldin on 26/05/2025.
//

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <string>
#include <vector>
#include "Entry.h"
#include "Node.h"

class BinarySearchTree {
public:
    BinarySearchTree();
    ~BinarySearchTree();

    std::vector<Entry> get(std::string searchable_name);
    void put(std::string searchable_name, Entry entry);
    void inorder_sort(const std::string& file_path);
    // Add any additional public methods required for binary search trees to work

private:
    // Add any additional private methods required for binary search trees to work
    Node* root;

    void put_recursive(Node*& current_node, const std::string& searchable_name, const Entry& entry);

    std::vector<Entry> get_recursive(Node* current_node, const std::string& searchable_name, int& edges_count) const;

    void inorder_recursive(Node* current_node, std::ofstream& file) const;

    void delete_recursive(Node* current_node);
};

#endif //BINARYSEARCHTREE_H
