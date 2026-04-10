#include "../include/FileUtils.h"

Entry* FileUtils::read_file(const std::string& file_path, const int len) {
    // your code
    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Error: Can't open fail" << file_path << std::endl;
        return nullptr;
    }

    const int num_entries = len;
    Entry* entries = new Entry[num_entries];

    std::string line;
    std::getline(file, line);

    int i = 0;
    while (i < num_entries && std::getline(file, line)) {
        Entry entry;
        std::stringstream ss(line);
        std::string segment;
        int col_index = 0;

        while (std::getline(ss, segment, ';')) {
            switch (col_index) {
                case 0:
                    entry.name = segment;
                    break;
                case 1:
                    entry.address = segment;
                    break;
                case 2:
                    entry.city = segment;
                    break;
                case 3:
                    entry.postcode = segment;
                    break;
                case 4:
                    entry.country = segment;
                    break;
                case 5:
                    entry.phone = segment;
                    break;
                default:
                    break;
            }
            col_index++;
        }

        entries[i] = entry;
        i++;
    }

    file.close();
    return entries;
}

void FileUtils::write_to_file(const Entry* entries, const std::string& file_path, const int len) {
    // your code
    std::ofstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Error: Can't create fail" << file_path << std::endl;
        return;
    }

    file << "Surname, Name;Address;City;Postcode;Country;Phone" << std::endl;

    for (int i = 0; i < len; i++) {
        file << entries[i].name << ";"
        << entries[i].address << ";"
        << entries[i].city << ";"
        << entries[i].postcode << ";"
        << entries[i].country << ";"
        << entries[i].phone << std::endl;
    }

    file.close();
}
