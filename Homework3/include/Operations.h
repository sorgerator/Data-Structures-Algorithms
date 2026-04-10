//
// Created by aldin on 26/05/2025.
//

#ifndef OPERATIONS_H
#define OPERATIONS_H
#include <string>
#include "Entry.h"

namespace Operations {
    int* search(Entry* entries, int len, std::string searchable_name);
    void sort(Entry* entries, int len);

    // Add any additional methods required for dual-pivot quick sort to work
    void dual_pivot_partition(Entry* entries, int left, int right, int &lp, int &rp);
    void quick_sort_recursive(Entry *entries, int left, int right);
    int find_any_index(const Entry* entries, int len, const std::string &searchable_name);
};

#endif //OPERATIONS_H
