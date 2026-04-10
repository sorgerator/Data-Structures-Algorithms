//
// Created by aldin on 12/24/2025.
//

#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H
#include "SearchResult.h"
#include "SiteData.h"
#include "SearchNode.h"

class SearchEngine {
private:
    SearchNode* root{nullptr};
    bool debug_mode{false};

    // Add any additional private methods required for left-leaning red-black trees, or this class, to work
    bool isRed(SearchNode* x) const {
        if (x == nullptr) {
            return false;
        }
        return x->color == RED;
    }

    SearchNode* rotateLeft(SearchNode* h);
    SearchNode* rotateRight(SearchNode* h);
    void flipColors(SearchNode* h);
    SearchNode* put(SearchNode* h, const std::string& key, const SiteData& data);

    void destroyTree(SearchNode* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    void index(const SiteData& data);
    [[nodiscard]] SearchResult search(const std::string& keyword) const;
    void toggle_debug_mode();

    // Add any additional public methods required for left-leaning red-black trees, or this class, to work
    SearchEngine() = default;
    ~SearchEngine() {
        destroyTree(root);
    }
};

#endif //SEARCHENGINE_H