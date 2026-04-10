//
// Created by aldin on 28/05/2025.
//

#include "../include/Entry.h"
#include "../include/FileUtils.h"
#include "../include/BinarySearchTree.h"
#include <iostream>
#include <string>
#include <vector>

#define NUM_ENTRIES 1000000
#define FILE_PATH "../raw_phonebook_data.csv"

void print_entry(const Entry& entry) {
    std::cout << "\tName:        " << entry.name << std::endl;
    std::cout << "\tStreet:      " << entry.street << std
    ::endl;
    std::cout << "\tCity:        " << entry.city << std::endl;
    std::cout << "\tPostcode:    " << entry.postcode << std::endl;
    std::cout << "\tCountry:     " << entry.country << std::endl;
    std::cout << "\tPhone:       " << entry.phone << std::endl;
    std::cout << "------------------------------------------" << std::endl;
}

int main() {
    // your code
    std::cout << "--- Phonebook System with Binary Search Tree ---" << std::endl;

    std::cout << "Loading file: " << FILE_PATH << "..." << std::endl;
    BinarySearchTree phonebook_tree = FileUtils::read_file(FILE_PATH, NUM_ENTRIES);
    std::cout << "Loading complete." << std::endl;

    std::string search_name;

    while (true) {
        std::cout << "\nEnter a 'Surname, Name' combination to find, or type -1 to close the program: " << std::endl;

        if (!std::getline(std::cin, search_name)) {
            break;
        }

        if (search_name == "-1") {
            std::cout << "\nTerminating the application. Goodbye!" << std::endl;
            break;
        }

        if (search_name.empty()) {
            continue;
        }

        std::cout << "\nSearching for: '" << search_name << "'..." << std::endl;

        std::vector<Entry> results = phonebook_tree.get(search_name);

        if (!results.empty()) {
            std::cout << "FOUND! " << results.size() << " entry(ies) found for '" << search_name << "':" << std::endl;
            std::cout << "------------------------------------------" << std::endl;

            for (const auto& entry : results) {
                print_entry(entry);
            }
        } else {

            std::cout << "ERROR: Entry for '" << search_name << "' not found in the phonebook." << std::endl;
        }
    }

    return 0;
}
