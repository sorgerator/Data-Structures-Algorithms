#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "../include/Entry.h"
#include "../include/Operations.h"
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

TEST_CASE("DualPivotQuicksort") {
    std::vector<Entry> entries = generate_sample_entries();
    Operations::sort(entries.data(), entries.size());

    for (size_t i = 1; i < entries.size(); ++i) {
        CHECK(entries[i - 1].name <= entries[i].name);
    }
}

TEST_CASE("BinarySearchSuccessMulti") {
    std::vector<Entry> entries = generate_sample_entries();
    Operations::sort(entries.data(), entries.size());

    int* result = Operations::search(entries.data(), entries.size(), "Smith, John");
    REQUIRE(result != nullptr);
    CHECK(result[1] - result[0] + 1 == 2);
    CHECK(entries[result[0]].name == "Smith, John");
    CHECK(entries[result[1]].name == "Smith, John");
    delete[] result;
}

TEST_CASE("BinarySearchFail") {
    std::vector<Entry> entries = generate_sample_entries();
    Operations::sort(entries.data(), entries.size());

    int* result = Operations::search(entries.data(), entries.size(), "Nonexistent, User");
    CHECK(result == nullptr);
}

TEST_CASE("BinarySearchSuccessSingle") {
    std::vector<Entry> entries = generate_sample_entries();
    Operations::sort(entries.data(), entries.size());

    int* result = Operations::search(entries.data(), entries.size(), "Adams, Alice");
    REQUIRE(result != nullptr);
    CHECK(result[0] == result[1]);
    CHECK(entries[result[0]].name == "Adams, Alice");
    delete[] result;
}

TEST_CASE("FileUtils") {
    std::vector<Entry> original = generate_sample_entries();
    const std::string test_file = "test_output.csv";

    FileUtils::write_to_file(original.data(), test_file, NUM_ENTRIES);
    Entry* read_entries = FileUtils::read_file(test_file, NUM_ENTRIES);

    for (size_t i = 0; i < original.size(); ++i) {
        CHECK(original[i].name == read_entries[i].name);
        CHECK(original[i].address == read_entries[i].address);
        CHECK(original[i].city == read_entries[i].city);
        CHECK(original[i].postcode == read_entries[i].postcode);
        CHECK(original[i].country == read_entries[i].country);
        CHECK(original[i].phone == read_entries[i].phone);
    }

    delete[] read_entries;
    std::remove(test_file.c_str());
}