#include "../include/Operations.h"

#include "../include/FileUtils.h"
#include <algorithm>

void Operations::sort(Entry *entries, int len) {
    // your code
    if (len <= 1) {
        return;
    }

    quick_sort_recursive(entries, 0, len - 1);
}

int* Operations::search(Entry *entries, int len, std::string searchable_name) {
    // your code
    int any_index = find_any_index(entries, len, searchable_name);

    if (any_index == -1) {
        return nullptr;
    }

    int start_index = any_index;
    while (start_index >= 0 && entries[start_index].name == searchable_name) {
        start_index--;
    }
    start_index++;

    int end_index = any_index;
    while (end_index < len && entries[end_index].name == searchable_name) {
        end_index++;
    }
    end_index--;

    int* result = new int[2];
    result[0] = start_index;
    result[1] = end_index;

    return result;
}

void Operations::dual_pivot_partition(Entry *entries, int left, int right, int &lp, int &rp) {
    if (entries[left] > entries[right]) {
        std::swap(entries[left], entries[right]);
    }

    const Entry pivot1 = entries[left];
    const Entry pivot2 = entries[right];

    int k = left + 1;
    int less = left + 1;
    int great = right - 1;

    while (k <= great) {
        if (entries[k] < pivot1) {
            std::swap(entries[k], entries[less]);
            less++;
        } else if (entries[k] > pivot2) {
            while (k < great && entries[great] > pivot2) {
                great--;
            }

            std::swap(entries[k], entries[great]);
            great--;

            if (entries[k] < pivot1) {
                std::swap(entries[k], entries[less]);
                less++;
            }
        }

        k++;
    }

    less--;
    std::swap(entries[left], entries[less]);

    great++;
    std::swap(entries[right], entries[great]);

    lp = less;
    rp = great;
}

void Operations::quick_sort_recursive(Entry *entries, int left, int right) {
    if (left < right) {
        int lp;
        int rp;

        dual_pivot_partition(entries, left, right, lp, rp);

        quick_sort_recursive(entries, left, lp - 1);
        quick_sort_recursive(entries, lp + 1, rp - 1);
        quick_sort_recursive(entries, rp + 1, right);
    }
}

int Operations::find_any_index(const Entry* entries, int len, const std::string &searchable_name) {
    int low = 0;
    int high = len - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (entries[mid].name == searchable_name) {
            return mid;
        } else if (entries[mid].name < searchable_name) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

