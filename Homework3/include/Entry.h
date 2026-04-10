//
// Created by aldin on 26/05/2025.
//

#ifndef ENTRY_H
#define ENTRY_H
#include <string>

struct Entry {
    // add all required Entry fields
    std::string name;
    std::string address;
    std::string city;
    std::string postcode;
    std::string country;
    std::string phone;

    bool operator<(const Entry& other) const {
        return name < other.name;
    }

    bool operator>(const Entry& other) const {
        return name > other.name;
    }

    bool operator<=(const Entry& other) const {
        return name <= other.name;
    }

    bool operator>=(const Entry& other) const {
        return name >= other.name;
    }

    bool operator==(const Entry& other) const {
        return name == other.name;
    }

    bool operator!=(const Entry& other) const {
        return name != other.name;
    }
};

#endif //ENTRY_H
