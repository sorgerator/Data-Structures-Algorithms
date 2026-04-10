//
// Created by aldin on 12/24/2025.
//

#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H
#include <ostream>
#include <string>
#include <vector>

#include "Debug.h"
#include "SiteData.h"

struct SearchResult {
    // add all required SearchResult fields
    std::string keyword;
    std::vector<SiteData> results;
    bool debug_mode;
    Debug debug_data;
    // create SearchResult constructors
    SearchResult() : keyword("not_found"), debug_mode(false) {}

    SearchResult(std::string kw, std::vector<SiteData> res, bool debug, Debug dbg)
    : keyword(std::move(kw)), results(std::move(res)), debug_mode(debug), debug_data(dbg) {}
};

inline std::ostream &operator<<(std::ostream &os, const SearchResult& result) {
    // implement the output operator overload, according to README.md examples
    os << "Keyword: " << result.keyword << "\n";

    if (result.results.empty()) {
        os << "No results found.";
    } else {
        os << "Result count: " << result.results.size() << "\n";
        os << "Sites:\n";
        for (const auto& site : result.results) {
            os << "-- Name: " << site.name << "\n";
            os << "-- URL: " << site.url << "\n";
            os << "-- Description: " << site.description << "\n";
            os << "-- Language: " << site.language << "\n";
            os << "-- Keywords:";
            for (const auto& kw : site.keywords) os << " " << kw;
            os << "\n";
        }
    }

    if (result.debug_mode) {
        os << "Debug info:\n";
        os << "-- Red links: " << result.debug_data.red_edges << "\n";
        os << "-- Black links: " << result.debug_data.black_edges << "\n";
    }

    return os;
}

#endif //SEARCHRESULT_H