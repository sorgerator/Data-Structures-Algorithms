#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "../include/Entry.h"
#include "../include/BinarySearchTree.h"
#include "../include/FileUtils.h"
#include <vector>
#include <string>
#include <fstream>
#include <cstdio>

#define NUM_ENTRIES 5

// Helper to generate test data
std::vector<Entry> generate_sample_entries() {
    return {
        {"Smith, John", "123 A St", "CityA", "12345", "CountryA", "123456"},
        {"Adams, Alice", "456 B St", "CityB", "23456", "CountryB", "234567"},
        {"Clerc, Agnès", "789 C St", "CityC", "34567", "CountryC", "345678"},
        {"Smith, John", "124 A St", "CityA", "12345", "CountryA", "223456"},
        {"Clerc, Agnès", "790 C St", "CityC", "34567", "CountryC", "445678"}
    };
}
TEST_CASE("FileUtils") {
    const std::string filename = "test_full_read.csv";
    auto entries = generate_sample_entries();

    std::ofstream out(filename);
    out << "name;street_address;city;postcode;country;phone_number\n";
    for (const auto& e : entries) {
        out << e.name << ";" << e.street << ";" << e.city << ";" << e.postcode << ";" << e.country << ";" << e.phone << "\n";
    }
    out.close();

    BinarySearchTree tree = FileUtils::read_file(filename, NUM_ENTRIES);

    for (const auto& e : entries) {
        auto results = tree.get(e.name);
        bool found = false;
        for (const auto& r : results) {
            if (r.street == e.street &&
                r.city == e.city &&
                r.postcode == e.postcode &&
                r.country == e.country &&
                r.phone == e.phone) {
                found = true;
                break;
                }
        }
        CHECK(found);
    }

    std::remove(filename.c_str());
}

TEST_CASE("BinarySearchTreeOperations") {
    BinarySearchTree tree;
    auto entries = generate_sample_entries();
    for (const auto& e : entries) tree.put(e.name, e);

    auto result = tree.get("Smith, John");
    CHECK(result.size() == 2);
    for (const auto& e : result) CHECK(e.name == "Smith, John");

    result = tree.get("Clerc, Agnès");
    CHECK(result.size() == 2);
    for (const auto& e : result) CHECK(e.name == "Clerc, Agnès");

    result = tree.get("Adams, Alice");
    CHECK(result.size() == 1);
    CHECK(result[0].name == "Adams, Alice");

    result = tree.get("Nonexistent, Person");
    CHECK(result.empty());
}

TEST_CASE("BinarySearchTreeEdgeCount") {
    BinarySearchTree tree;
    auto entries = generate_sample_entries();
    for (const auto& e : entries) tree.put(e.name, e);

    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    tree.get("Smith, John");

    std::cout.rdbuf(old);
    std::string output = buffer.str();

    CHECK(output.find("Edges on the path: 0") != std::string::npos);

    // Clear buffer for second test
    std::stringstream buffer2;
    old = std::cout.rdbuf(buffer2.rdbuf());
    tree.get("Clerc, Agnès");

    std::cout.rdbuf(old);
    output = buffer2.str();

    CHECK(output.find("Edges on the path: 2") != std::string::npos);
}

TEST_CASE("BinarySearchTreeInorderSort") {
    BinarySearchTree tree;
    auto entries = generate_sample_entries();
    for (const auto& e : entries) tree.put(e.name, e);

    const std::string sorted_filename = "test_sorted.csv";
    tree.inorder_sort(sorted_filename);

    std::ifstream in(sorted_filename);
    CHECK(in.is_open());

    std::string line;
    std::getline(in, line);
    CHECK(line == "name;street_address;city;postcode;country;phone_number");

    std::vector<std::string> names;
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string name;
        std::getline(ss, name, ';');
        names.push_back(name);
    }
    in.close();

    CHECK(names.size() == 5);

    for (size_t i = 0; i < names.size() - 1; i++) {
        CHECK(names[i] <= names[i + 1]);
    }

    CHECK(names[0] == "Adams, Alice");
    CHECK(names[1] == "Clerc, Agnès");
    CHECK(names[2] == "Clerc, Agnès");
    CHECK(names[3] == "Smith, John");
    CHECK(names[4] == "Smith, John");

    std::remove(sorted_filename.c_str());
}