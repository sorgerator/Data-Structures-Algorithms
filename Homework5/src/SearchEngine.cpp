//
// Created by aldin on 12/24/2025.
//

#include "../include/SearchEngine.h"

SearchResult SearchEngine::search(const std::string &keyword) const {
    // your code
    SearchNode* curr = root;
    int red = 0;
    int black = 0;

    while (curr != nullptr) {
        if (keyword == curr->key) {
            return SearchResult(keyword, curr->value, debug_mode, debug_mode ? Debug(red, black) : Debug());
        }

        SearchNode* next = (keyword < curr->key) ? curr->left : curr->right;

        if (next != nullptr) {
            if (isRed(next)) {
                red++;
            } else {
                black++;
            }
        }
        curr = next;
    }

    return SearchResult(keyword, {}, debug_mode, Debug(-1, -1));
}

void SearchEngine::index(const SiteData &data) {
    // your code
    for (const auto& keyword : data.keywords) {
        root = put(root, keyword, data);
        if (root) {
            root->color = BLACK;
        }
    }
}

void SearchEngine::toggle_debug_mode() {
    // your code
    debug_mode = !debug_mode;
}

// Add any additional methods required for left-leaning red-black trees, or this class, to work
bool isRed(SearchNode* x) {
    if (x == nullptr) {
        return false;
    }
    return x->color == RED;
}

SearchNode *SearchEngine::rotateLeft(SearchNode *h) {
    SearchNode* x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

SearchNode *SearchEngine::rotateRight(SearchNode* h) {
    SearchNode* x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

void SearchEngine::flipColors(SearchNode *h) {
    h->color = RED;
    if (h->left) {
        h->left->color = BLACK;
    }
    if (h->right) {
        h->right->color = BLACK;
    }
}

SearchNode* SearchEngine::put(SearchNode* h, const std::string& key, const SiteData& data) {
    if (h == nullptr) {
        return new SearchNode(key, {data}, RED);
    }

    if (key < h->key) {
        h->left = put(h->left, key, data);
    } else if (key > h->key) {
        h->right = put(h->right, key, data);
    } else {
        h->value.push_back(data);
    }

    if (isRed(h->right) && !isRed(h->left)) {
        h = rotateLeft(h);
    }
    if (isRed(h->left) && isRed(h->left->left)) {
        h = rotateRight(h);
    }
    if (isRed(h->left) && isRed(h->right)) {
        flipColors(h);
    }

    return h;
}