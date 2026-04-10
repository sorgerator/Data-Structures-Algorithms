//
// Created by aldin on 12/24/2025.
//

#ifndef SITEDATA_H
#define SITEDATA_H
#include <string>
#include <vector>

struct SiteData {
    // add all required SiteData fields
    std::string name;
    std::string description;
    std::string url;
    std::string language;
    std::vector<std::string> keywords;

    // create SiteData constructor
    SiteData(std::string name, std::string desc, std::string url, std::string lang, std::vector<std::string> keywords)
    : name(std::move(name)), description(std::move(desc)), url(std::move(url)), language(std::move(lang)), keywords(std::move(keywords)) {}
};

#endif //SITEDATA_H