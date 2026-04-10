//
// Created by aldin on 26/05/2025.
//

#ifndef ENTRY_H
#define ENTRY_H
#include <string>

struct Entry {
    // add all required Entry fields
    std::string name;
    std::string street;
    std::string city;
    std::string postcode;
    std::string country;
    std::string phone;

    Entry() = default;

    Entry(const std::string& name, const std::string& street, const std::string& city, const std::string& postcode, const std::string& country, const std::string& phone)
    : name(name), street(street), city(city), postcode(postcode), country(country), phone(phone) {}

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