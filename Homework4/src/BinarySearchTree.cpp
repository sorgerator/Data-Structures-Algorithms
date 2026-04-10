#include "../include/BinarySearchTree.h"
#include "../include/FileUtils.h"

std::vector<Entry> BinarySearchTree::get(std::string searchable_name) {
    // your code
    int edges_count = 0;
    return get_recursive(root, searchable_name, edges_count);
}

void BinarySearchTree::put(std::string searchable_name, Entry entry) {
    // your code
    put_recursive(root, searchable_name, entry);
}

void BinarySearchTree::inorder_sort(const std::string& file_path) {
    // your code
    std::ofstream output_file(file_path);

    if (output_file.is_open()) {
        output_file << "name;street_address;city;postcode;country;phone_number\n";

        inorder_recursive(root, output_file);

        output_file.close();
    } else {
        std::cerr << "Error: Could not open file for sorting: " << file_path << std::endl;
    }
}

void BinarySearchTree::delete_recursive(Node *current_node) {
    if (current_node) {
        delete_recursive(current_node->left);
        delete_recursive(current_node->right);
        delete current_node;
    }
}

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
    delete_recursive(root);
}

void BinarySearchTree::put_recursive(Node *&current_node, const std::string &searchable_name, const Entry &entry) {
    if (current_node == nullptr) {
        current_node = new Node(searchable_name, entry);
        return;
    }

    if (searchable_name < current_node->key) {
        put_recursive(current_node->left, searchable_name, entry);
    } else if (searchable_name > current_node->key) {
        put_recursive(current_node->right, searchable_name, entry);
    } else {
        current_node->values.push_back(entry);
    }
}

std::vector<Entry> BinarySearchTree::get_recursive(Node* current_node, const std::string &searchable_name, int& edges_count) const {
    if (current_node == nullptr) {
        return {};
    }

    if (searchable_name == current_node->key) {
        std::cout << "Edges on the path: " << edges_count << std::endl;
        return current_node->values;
    } else if (searchable_name < current_node->key) {
        edges_count++;
        return get_recursive(current_node->left, searchable_name, edges_count);
    } else {
        edges_count++;
        return get_recursive(current_node->right, searchable_name, edges_count);
    }
}

void BinarySearchTree::inorder_recursive(Node *current_node, std::ofstream &file) const {
    if (current_node == nullptr) {
        return;
    }

    inorder_recursive(current_node->left, file);

    for (const auto& entry : current_node->values) {
        file << entry.name << ";" << entry.street << ";" << entry.city << ";" << entry.postcode << ";" << entry.country << ";" << entry.phone << "\n";
    }

    inorder_recursive(current_node->right, file);
}
