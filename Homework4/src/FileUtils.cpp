#include "../include/FileUtils.h"

BinarySearchTree FileUtils::read_file(const std::string& file_path, const int len) {
    // your code
    BinarySearchTree tree;
    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file: " << file_path << std::endl;
        return tree;
    }

    std::string line;
    if (!std::getline(file, line)) {
        std::cerr << "Error: File is empty or could not read header." << std::endl;
        return tree;
    }

    int entry_count = 0;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string segment;
        std::vector<std::string> fields;

        while (std::getline(ss, segment, ';')) {
            fields.push_back(segment);
        }

        if (fields.size() == 6) {
            Entry entry(fields[0], fields[1], fields[2], fields[3], fields[4], fields[5]);

            tree.put(entry.name, entry);
            entry_count++;
        }
    }

    std::cout << "Successfully read " << entry_count << " entries from the file." << std::endl;
    file.close();
    return tree;
}