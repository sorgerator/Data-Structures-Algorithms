#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "../include/SiteData.h"
#include "../include/SearchNode.h"
#include "../include/SearchResult.h"
#include "../include/Debug.h"
#include "../include/SearchEngine.h"
#include <sstream>
#include <vector>
#include <string>

std::vector<SiteData> generate_sample_sites() {
    return {
        {
            "SarajevoTech",
            "Technology and startup news from Sarajevo and the region.",
            "https://sarajevotech.ba",
            "en",
            {"technology", "startups", "news", "business"}
        },
        {
            "BalkanEdu",
            "Educational resources and online courses for students.",
            "https://balkanedu.com",
            "en",
            {"education", "courses", "technology", "learning"}
        },
        {
            "Dnevni Fokus",
            "Daily news covering Bosnia and Herzegovina.",
            "https://dnevnifokus.ba",
            "bs",
            {"news", "politics", "sarajevo", "society"}
        },
        {
            "Poslovni Kutak",
            "Business insights and market analysis.",
            "https://poslovnikutak.ba",
            "bs",
            {"business", "economy", "news", "finance"}
        },
        {
            "IT Akademija",
            "IT education platform for developers and engineers.",
            "https://itakademija.ba",
            "bs",
            {"education", "technology", "programming", "courses"}
        },
        {
            "Sarajevo Guide",
            "Tourist guide and city information for Sarajevo.",
            "https://sarajevoguide.com",
            "en",
            {"sarajevo", "travel", "culture", "news"}
        },
        {
            "Tech Kutija",
            "Reviews and articles about modern technology.",
            "https://techkutija.ba",
            "bs",
            {"technology", "gadgets", "reviews", "news"}
        },
        {
            "Poslovni Svijet",
            "Regional business portal covering the Balkans.",
            "https://poslovnisvijet.hr",
            "hr",
            {"business", "economy", "news", "markets"}
        },
        {
            "Obrazovanje Plus",
            "Platform for education, schools, and learning tools.",
            "https://obrazovanjeplus.hr",
            "hr",
            {"education", "online", "schools", "resources"}
        }
    };
}

TEST_CASE("StructConstructors") {
    std::vector<std::string> keywords = {"tech", "news", "startup"};
    SiteData site("TestSite", "A test description", "https://test.com", "en", keywords);

    CHECK(site.name == "TestSite");
    CHECK(site.description == "A test description");
    CHECK(site.url == "https://test.com");
    CHECK(site.language == "en");
    CHECK(site.keywords.size() == 3);
    CHECK(site.keywords[0] == "tech");
    CHECK(site.keywords[1] == "news");
    CHECK(site.keywords[2] == "startup");

    std::vector<std::string> many_keywords = {"a", "b", "c", "d", "e", "f"};
    SiteData site2("MultiKeyword", "Description", "https://multi.com", "bs", many_keywords);
    CHECK(site2.keywords.size() == 6);

    std::vector<SiteData> value = {site};
    SearchNode node("keyword", value, RED);
    CHECK(node.key == "keyword");
    CHECK(node.value.size() == 1);
    CHECK(node.value[0].name == "TestSite");
    CHECK(node.color == RED);
    CHECK(node.left == nullptr);
    CHECK(node.right == nullptr);

    Debug debug;
    CHECK(debug.red_edges == -1);
    CHECK(debug.black_edges == -1);

    Debug debug2(5, 3);
    CHECK(debug2.red_edges == 5);
    CHECK(debug2.black_edges == 3);

    SearchResult result;
    CHECK(result.keyword == "not_found");
    CHECK(result.results.empty());
    CHECK(result.debug_data.red_edges == -1);
    CHECK(result.debug_data.black_edges == -1);

    Debug debug3(2, 1);
    SearchResult result2("keyword", {site}, true, debug3);
    CHECK(result2.keyword == "keyword");
    CHECK(result2.results.size() == 1);
    CHECK(result2.debug_mode == true);
    CHECK(result2.debug_data.red_edges == 2);
    CHECK(result2.debug_data.black_edges == 1);
}

TEST_CASE("BasicIndexingAndSearch") {
    SearchEngine engine;
    SiteData site("TestSite", "Description", "https://test.com", "en", {"technology"});

    engine.index(site);
    SearchResult result = engine.search("technology");

    CHECK(result.results.size() == 1);
    CHECK(result.results[0].name == "TestSite");
    CHECK(result.results[0].url == "https://test.com");
    CHECK(result.keyword == "technology");

    SearchResult not_found = engine.search("nonexistent");
    CHECK(not_found.keyword == "nonexistent");
    CHECK(not_found.results.empty());

    SearchEngine empty_engine;
    SearchResult empty_result = empty_engine.search("anything");
    CHECK(empty_result.keyword == "anything");
    CHECK(empty_result.results.empty());

    SiteData complete_site("CompleteTest", "Full description here", "https://complete.test", "hr", {"test", "complete"});
    engine.index(complete_site);
    SearchResult test_result = engine.search("test");
    CHECK(test_result.results[0].name == "CompleteTest");
    CHECK(test_result.results[0].description == "Full description here");
    CHECK(test_result.results[0].url == "https://complete.test");
    CHECK(test_result.results[0].language == "hr");
    CHECK(test_result.results[0].keywords.size() == 2);
}

TEST_CASE("MultipleKeywordsAndAggregation") {
    SearchEngine engine;
    SiteData site("TestSite", "Description", "https://test.com", "en", {"tech", "news", "business"});

    engine.index(site);

    SearchResult tech_result = engine.search("tech");
    SearchResult news_result = engine.search("news");
    SearchResult business_result = engine.search("business");

    CHECK(tech_result.results.size() == 1);
    CHECK(tech_result.results[0].name == "TestSite");
    CHECK(news_result.results.size() == 1);
    CHECK(news_result.results[0].name == "TestSite");
    CHECK(business_result.results.size() == 1);
    CHECK(business_result.results[0].name == "TestSite");

    auto sites = generate_sample_sites();
    for (const auto& s : sites) {
        engine.index(s);
    }

    SearchResult technology_result = engine.search("technology");
    CHECK(technology_result.results.size() == 4);

    std::vector<std::string> expected_names = {"SarajevoTech", "BalkanEdu", "IT Akademija", "Tech Kutija"};
    for (const auto& expected : expected_names) {
        bool found = false;
        for (const auto& site_data : technology_result.results) {
            if (site_data.name == expected) {
                found = true;
                break;
            }
        }
        CHECK(found);
    }

    SearchResult education_result = engine.search("education");
    CHECK(education_result.results.size() == 3);

    SearchResult news_results = engine.search("news");
    CHECK(news_results.results.size() == 7);

    SearchResult sarajevo_result = engine.search("sarajevo");
    CHECK(sarajevo_result.results.size() == 2);

    SearchResult result1 = engine.search("technology");
    SearchResult result2 = engine.search("technology");
    SearchResult result3 = engine.search("technology");
    CHECK(result1.results.size() == result2.results.size());
    CHECK(result2.results.size() == result3.results.size());
}

TEST_CASE("SearchEdgeCases") {
    SearchEngine engine;

    SiteData case_site("TestSite", "Description", "https://test.com", "en", {"Technology"});
    engine.index(case_site);
    SearchResult correct_result = engine.search("Technology");
    SearchResult wrong_case_result = engine.search("technology");
    CHECK(correct_result.results.size() == 1);
    CHECK(wrong_case_result.results.empty());

    SiteData special_site("TestSite2", "Description", "https://test.com", "en", {"c++", "node.js"});
    engine.index(special_site);
    SearchResult cpp_result = engine.search("c++");
    SearchResult nodejs_result = engine.search("node.js");
    CHECK(cpp_result.results.size() == 1);
    CHECK(nodejs_result.results.size() == 1);

    SiteData empty_kw_site("EmptySite", "Description", "https://test.com", "en", {""});
    engine.index(empty_kw_site);
    SearchResult empty_result = engine.search("");
    CHECK(empty_result.results.size() == 1);

    std::string long_keyword(1000, 'a');
    SiteData long_site("LongSite", "Description", "https://test.com", "en", {long_keyword});
    engine.index(long_site);
    SearchResult long_result = engine.search(long_keyword);
    CHECK(long_result.results.size() == 1);

    SiteData no_keywords("NoKeywords", "Description", "https://test.com", "en", {});
    engine.index(no_keywords);
    SearchResult no_kw_result = engine.search("anything");
    CHECK(no_kw_result.results.empty());

    SiteData dup_site("DupSite", "Description", "https://dup.com", "en", {"dup", "dup", "dup"});
    engine.index(dup_site);
    SearchResult dup_result = engine.search("dup");
    CHECK(dup_result.results.size() == 3);
}

TEST_CASE("DebugModeToggle") {
    SearchEngine engine;
    SiteData site("TestSite", "Description", "https://test.com", "en", {"keyword"});

    engine.index(site);

    SearchResult result1 = engine.search("keyword");
    CHECK(result1.debug_mode == false);
    CHECK(result1.debug_data.red_edges == -1);
    CHECK(result1.debug_data.black_edges == -1);

    engine.toggle_debug_mode();
    SearchResult result2 = engine.search("keyword");
    CHECK(result2.debug_mode == true);
    CHECK(result2.debug_data.red_edges >= 0);
    CHECK(result2.debug_data.black_edges >= 0);

    engine.toggle_debug_mode();
    SearchResult result3 = engine.search("keyword");
    CHECK(result3.debug_mode == false);
    CHECK(result3.debug_data.red_edges == -1);
    CHECK(result3.debug_data.black_edges == -1);

    auto sites = generate_sample_sites();
    for (const auto& s : sites) {
        engine.index(s);
    }

    engine.toggle_debug_mode();
    SearchResult success_result = engine.search("technology");
    CHECK(success_result.debug_mode == true);
    CHECK(success_result.debug_data.red_edges >= 0);
    CHECK(success_result.debug_data.black_edges >= 0);
    CHECK((success_result.debug_data.red_edges + success_result.debug_data.black_edges) >= 0);

    SearchResult fail_result = engine.search("nonexistent");
    CHECK(fail_result.debug_mode == true);
    CHECK(fail_result.results.empty());
    CHECK(fail_result.debug_data.red_edges == -1);
    CHECK(fail_result.debug_data.black_edges == -1);
}

TEST_CASE("DebugModeEdgeCounting") {
    SearchEngine engine;
    engine.toggle_debug_mode();

    SiteData site1("Site1", "Desc", "https://s1.com", "en", {"m"});
    engine.index(site1);
    SearchResult r1 = engine.search("m");
    CHECK(r1.debug_data.red_edges + r1.debug_data.black_edges == 0);

    SiteData site2("Site2", "Desc", "https://s2.com", "en", {"a"});
    engine.index(site2);
    SearchResult r2 = engine.search("a");
    CHECK(r2.debug_data.red_edges + r2.debug_data.black_edges >= 0);

    SiteData site3("Site3", "Desc", "https://s3.com", "en", {"z"});
    engine.index(site3);
    SearchResult r3 = engine.search("z");
    CHECK(r3.debug_data.red_edges + r3.debug_data.black_edges >= 0);

    std::vector<std::string> keywords = {"alpha", "beta", "gamma", "delta", "epsilon"};
    for (const auto& kw : keywords) {
        SiteData site("Site_" + kw, "Description", "https://site.com", "en", {kw});
        engine.index(site);
    }

    for (const auto& kw : keywords) {
        SearchResult result = engine.search(kw);
        CHECK(result.debug_mode == true);
        CHECK(result.debug_data.red_edges >= 0);
        CHECK(result.debug_data.black_edges >= 0);
    }

    for (int i = 0; i < 5; i++) {
        SiteData site("Site" + std::to_string(i), "Description", "https://site.com", "en", {"shared"});
        engine.index(site);
    }

    SearchResult shared_result = engine.search("shared");
    CHECK(shared_result.results.size() == 5);
    CHECK(shared_result.debug_data.red_edges >= 0);
    CHECK(shared_result.debug_data.black_edges >= 0);
}

TEST_CASE("OutputOperatorSuccessful") {
    SearchEngine engine;
    SiteData site1("BalkanEdu", "Educational resources and online courses for students.",
                   "https://balkanedu.com", "en", {"education", "courses", "technology", "learning"});
    SiteData site2("IT Akademija", "IT education platform for developers and engineers.",
                   "https://itakademija.ba", "bs", {"education", "technology", "programming", "courses"});

    engine.index(site1);
    engine.index(site2);

    SearchResult result = engine.search("education");

    std::stringstream ss;
    ss << result;
    std::string output = ss.str();

    CHECK(output.find("Keyword: education") != std::string::npos);
    CHECK(output.find("Result count: 2") != std::string::npos);
    CHECK(output.find("Sites:") != std::string::npos);
    CHECK(output.find("-- Name: BalkanEdu") != std::string::npos);
    CHECK(output.find("-- URL: https://balkanedu.com") != std::string::npos);
    CHECK(output.find("-- Description: Educational resources and online courses for students.") != std::string::npos);
    CHECK(output.find("-- Language: en") != std::string::npos);
    CHECK(output.find("-- Keywords: education courses technology learning") != std::string::npos);
    CHECK(output.find("-- Name: IT Akademija") != std::string::npos);
    CHECK(output.find("-- Description: IT education platform for developers and engineers.") != std::string::npos);
    CHECK(output.find("-- URL: https://itakademija.ba") != std::string::npos);
    CHECK(output.find("-- Language: bs") != std::string::npos);
    CHECK(output.find("Debug info:") == std::string::npos);

    engine.toggle_debug_mode();
    SearchResult debug_result = engine.search("education");

    std::stringstream ss2;
    ss2 << debug_result;
    std::string debug_output = ss2.str();

    CHECK(debug_output.find("Keyword: education") != std::string::npos);
    CHECK(debug_output.find("Result count: 2") != std::string::npos);
    CHECK(debug_output.find("Debug info:") != std::string::npos);
    CHECK(debug_output.find("-- Red links:") != std::string::npos);
    CHECK(debug_output.find("-- Black links:") != std::string::npos);

    SiteData single_site("SingleSite", "A single website for testing", "https://single.com", "en", {"unique"});
    engine.index(single_site);
    SearchResult single_result = engine.search("unique");

    std::stringstream ss3;
    ss3 << single_result;
    std::string single_output = ss3.str();
    CHECK(single_output.find("Result count: 1") != std::string::npos);
    CHECK(single_output.find("-- Name: SingleSite") != std::string::npos);

    SiteData multi_kw("MultiKeyword", "Description", "https://multi.com", "en",
                      {"alpha", "beta", "gamma", "delta", "epsilon"});
    engine.index(multi_kw);
    SearchResult multi_result = engine.search("alpha");

    std::stringstream ss4;
    ss4 << multi_result;
    std::string multi_output = ss4.str();
    CHECK(multi_output.find("alpha beta gamma delta epsilon") != std::string::npos);

    SiteData special("Test & Co.", "Description with \"quotes\" and 'apostrophes'",
                     "https://test&co.com", "en", {"test"});
    engine.index(special);
    SearchResult special_result = engine.search("test");

    std::stringstream ss5;
    ss5 << special_result;
    std::string special_output = ss5.str();
    CHECK(special_output.find("Test & Co.") != std::string::npos);
}

TEST_CASE("OutputOperatorUnsuccessful") {
    SearchEngine engine;
    SiteData site("TestSite", "Description", "https://test.com", "en", {"keyword"});

    engine.index(site);
    SearchResult result = engine.search("nonexisting");

    std::stringstream ss;
    ss << result;
    std::string output = ss.str();

    CHECK(output.find("Keyword: nonexisting") != std::string::npos);
    CHECK(output.find("No results found.") != std::string::npos);
    CHECK(output.find("Debug info:") == std::string::npos);
    CHECK(output.find("Sites:") == std::string::npos);
    CHECK(output.find("Result count:") == std::string::npos);

    engine.toggle_debug_mode();
    SearchResult debug_result = engine.search("nonexisting");

    std::stringstream ss2;
    ss2 << debug_result;
    std::string debug_output = ss2.str();

    CHECK(debug_output.find("Keyword: nonexisting") != std::string::npos);
    CHECK(debug_output.find("No results found.") != std::string::npos);
    CHECK(debug_output.find("Debug info:") != std::string::npos);
    CHECK(debug_output.find("-- Red links: -1") != std::string::npos);
    CHECK(debug_output.find("-- Black links: -1") != std::string::npos);
}

TEST_CASE("RedBlackTreeProperties") {
    SearchEngine engine;
    engine.toggle_debug_mode();

    for (int i = 0; i < 20; i++) {
        SiteData site("Site" + std::to_string(i), "Description",
                      "https://site.com", "en", {"keyword_" + std::to_string(i)});
        engine.index(site);
    }

    std::vector<int> path_lengths;
    for (int i = 0; i < 20; i++) {
        SearchResult result = engine.search("keyword_" + std::to_string(i));
        int path_length = result.debug_data.red_edges + result.debug_data.black_edges;
        path_lengths.push_back(path_length);
    }

    for (int len : path_lengths) {
        CHECK(len >= 0);
    }

    SearchEngine small_engine;
    small_engine.toggle_debug_mode();
    SiteData root_site("RootSite", "Description", "https://root.com", "en", {"middle"});
    small_engine.index(root_site);
    SearchResult root_result = small_engine.search("middle");
    CHECK(root_result.debug_data.red_edges == 0);
    CHECK(root_result.debug_data.black_edges == 0);
}

TEST_CASE("IntegrationTests") {
    SearchEngine engine;
    auto sites = generate_sample_sites();

    for (const auto& site : sites) {
        engine.index(site);
    }

    SearchResult tech_result = engine.search("technology");
    CHECK(tech_result.results.size() == 4);

    SearchResult edu_result = engine.search("education");
    CHECK(edu_result.results.size() == 3);

    SearchResult biz_result = engine.search("business");
    CHECK(biz_result.results.size() == 3);

    engine.toggle_debug_mode();
    SearchResult debug_result = engine.search("news");
    CHECK(debug_result.debug_mode == true);
    CHECK(debug_result.debug_data.red_edges >= 0);
    CHECK(debug_result.debug_data.black_edges >= 0);

    std::stringstream ss;
    ss << debug_result;
    std::string output = ss.str();

    CHECK(output.find("Keyword: news") != std::string::npos);
    CHECK(output.find("Result count: 6") != std::string::npos);
    CHECK(output.find("Sites:") != std::string::npos);
    CHECK(output.find("Debug info:") != std::string::npos);
    CHECK(output.find("-- Red links:") != std::string::npos);
    CHECK(output.find("-- Black links:") != std::string::npos);

    SearchEngine persistence_engine;
    SiteData site1("Site1", "Desc1", "https://s1.com", "en", {"batch1", "common"});
    persistence_engine.index(site1);

    SearchResult result1 = persistence_engine.search("batch1");
    CHECK(result1.results.size() == 1);

    SiteData site2("Site2", "Desc2", "https://s2.com", "en", {"batch2", "common"});
    persistence_engine.index(site2);

    SearchResult result2 = persistence_engine.search("batch1");
    CHECK(result2.results.size() == 1);

    SearchResult result3 = persistence_engine.search("batch2");
    CHECK(result3.results.size() == 1);

    SearchResult result4 = persistence_engine.search("common");
    CHECK(result4.results.size() == 2);
}
