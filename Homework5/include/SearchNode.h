//
// Created by aldin on 12/24/2025.
//

#ifndef SEARCHNODE_H
#define SEARCHNODE_H
#include <string>
#include <vector>
#include "SiteData.h"

enum NodeColor {
    BLACK = false,
    RED = true
};

struct SearchNode {
    // add all required SearchNode fields
    std::string key;
    std::vector<SiteData> value;
    bool color;
    SearchNode *left, *right;
    // create SearchNode constructor

    SearchNode(std::string key, std::vector<SiteData> val, bool col)
    : key(std::move(key)), value(std::move(val)), color(col), left(nullptr), right(nullptr) { }

};

#endif //SEARCHNODE_H