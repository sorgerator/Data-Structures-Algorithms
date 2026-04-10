//
// Created by aldin on 21/04/2025.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/ProcessQueue.h"
#include "../include/RoundRobinScheduler.h"
#include <doctest/doctest.h>

std::string capture_output(const std::function<void()>& fn) {
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
    fn();
    std::cout.rdbuf(old);
    return buffer.str();
}

std::vector<std::string> split_lines(const std::string& str) {
    std::stringstream ss(str);
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(ss, line)) {
        lines.push_back(line);
    }
    return lines;
}

TEST_CASE("ProcessQueueBasicOperations") {
    SUBCASE("ProcessQueue basic enqueue and dequeue") {
        ProcessQueue q;

        CHECK(q.is_empty());
        CHECK(q.size() == 0);

        q.enqueue(Process("P1", 5, 5));
        CHECK_FALSE(q.is_empty());
        CHECK(q.size() == 1);
        CHECK(q.peek().id == "P1");

        q.enqueue(Process("P2", 3, 3));
        CHECK(q.size() == 2);
        CHECK(q.peek().id == "P1");

        Process p = q.dequeue();
        CHECK(p.id == "P1");
        CHECK(q.size() == 1);
        CHECK(q.peek().id == "P2");

        p = q.dequeue();
        CHECK(p.id == "P2");
        CHECK(q.is_empty());
    }

    SUBCASE("ProcessQueue circular link check") {
        ProcessQueue q;
        q.enqueue(Process("A", 10, 10));
        q.enqueue(Process("B", 5, 5));
        q.enqueue(Process("C", 2, 2));

        const Node* head = q.get_head();
        const Node* tail = q.get_tail();

        CHECK(head != nullptr);
        CHECK(tail != nullptr);
        CHECK(tail->next == head); // Circular structure
    }

    SUBCASE("ProcessQueue throws on empty peek and dequeue") {
        ProcessQueue q;
        CHECK_THROWS_AS(q.peek(), std::out_of_range);
        CHECK_THROWS_AS(q.dequeue(), std::out_of_range);
    }

    SUBCASE("Initializer list constructor works") {
        ProcessQueue q = { Process("X", 7, 7), Process("Y", 8, 8) };
        CHECK(q.size() == 2);
        CHECK(q.peek().id == "X");
        CHECK(q.dequeue().id == "X");
        CHECK(q.dequeue().id == "Y");
    }

    SUBCASE("Copy constructor creates a deep copy") {
        ProcessQueue original;
        original.enqueue(Process("P1", 1, 1));
        original.enqueue(Process("P2", 2, 2));

        ProcessQueue copy = original;

        CHECK(copy.size() == original.size());
        CHECK(copy.peek().id == original.peek().id);

        // Modifying original shouldn't affect copy
        original.dequeue();
        CHECK(copy.size() == 2);
        CHECK(copy.peek().id == "P1");
    }

    SUBCASE("Copy assignment works") {
        ProcessQueue a;
        a.enqueue(Process("X", 3, 3));

        ProcessQueue b;
        b.enqueue(Process("Y", 5, 5));
        b = a;

        CHECK(b.size() == 1);
        CHECK(b.peek().id == "X");
    }

    SUBCASE("Move constructor transfers ownership") {
        ProcessQueue original;
        original.enqueue(Process("A", 4, 4));

        ProcessQueue moved = std::move(original);

        CHECK(moved.size() == 1);
        CHECK(moved.peek().id == "A");
        CHECK(original.is_empty());
    }

    SUBCASE("Move assignment transfers ownership") {
        ProcessQueue a;
        a.enqueue(Process("Q", 6, 6));

        ProcessQueue b;
        b = std::move(a);

        CHECK(b.size() == 1);
        CHECK(b.peek().id == "Q");
        CHECK(a.is_empty());
    }
}

TEST_CASE("RoundRobinScheduler1") {
    RoundRobinScheduler scheduler(4);
    scheduler.add_process("P1", 10);
    scheduler.add_process("P2", 4);
    scheduler.add_process("P3", 6);

    std::string output = capture_output([&] {
        scheduler.run();
    });

    std::vector<std::string> expected = {
        "Process P1 executed for 4 units. Remaining: 6",
        "Process P2 executed for 4 units. Remaining: 0",
        "Process P3 executed for 4 units. Remaining: 2",
        "Process P1 executed for 4 units. Remaining: 2",
        "Process P3 executed for 2 units. Remaining: 0",
        "Process P1 executed for 2 units. Remaining: 0",
        "All processes completed. Total time: 20",
    };

    auto actual = split_lines(output);
    CHECK_EQ(actual, expected);
}

TEST_CASE("RoundRobinScheduler2") {
    RoundRobinScheduler scheduler(3);
    scheduler.add_process("P1", 5);
    scheduler.add_process("P2", 3);
    scheduler.add_process("P3", 7);

    std::string output = capture_output([&] {
        scheduler.run();
    });

    std::vector<std::string> expected = {
        "Process P1 executed for 3 units. Remaining: 2",
        "Process P2 executed for 3 units. Remaining: 0",
        "Process P3 executed for 3 units. Remaining: 4",
        "Process P1 executed for 2 units. Remaining: 0",
        "Process P3 executed for 3 units. Remaining: 1",
        "Process P3 executed for 1 units. Remaining: 0",
        "All processes completed. Total time: 15"
    };

    auto actual = split_lines(output);
    CHECK_EQ(actual, expected);
}

TEST_CASE("RoundRobinScheduler3") {
    RoundRobinScheduler scheduler(4);
    scheduler.add_process("P1", 12);
    scheduler.add_process("P2", 5);
    scheduler.add_process("P3", 8);
    scheduler.add_process("P4", 3);

    std::string output = capture_output([&] {
        scheduler.run();
    });

    std::vector<std::string> expected = {
        "Process P1 executed for 4 units. Remaining: 8",
        "Process P2 executed for 4 units. Remaining: 1",
        "Process P3 executed for 4 units. Remaining: 4",
        "Process P4 executed for 3 units. Remaining: 0",
        "Process P1 executed for 4 units. Remaining: 4",
        "Process P2 executed for 1 units. Remaining: 0",
        "Process P3 executed for 4 units. Remaining: 0",
        "Process P1 executed for 4 units. Remaining: 0",
        "All processes completed. Total time: 28",
    };

    auto actual = split_lines(output);
    CHECK_EQ(actual, expected);
}

TEST_CASE("RoundRobinScheduler4") {
    RoundRobinScheduler scheduler(3);
    scheduler.add_process("P1", 10);
    scheduler.add_process("P2", 6);
    scheduler.add_process("P3", 4);
    scheduler.add_process("P4", 8);

    std::string output = capture_output([&] {
        scheduler.run();
    });

    std::vector<std::string> expected = {
        "Process P1 executed for 3 units. Remaining: 7",
        "Process P2 executed for 3 units. Remaining: 3",
        "Process P3 executed for 3 units. Remaining: 1",
        "Process P4 executed for 3 units. Remaining: 5",
        "Process P1 executed for 3 units. Remaining: 4",
        "Process P2 executed for 3 units. Remaining: 0",
        "Process P3 executed for 1 units. Remaining: 0",
        "Process P4 executed for 3 units. Remaining: 2",
        "Process P1 executed for 3 units. Remaining: 1",
        "Process P4 executed for 2 units. Remaining: 0",
        "Process P1 executed for 1 units. Remaining: 0",
        "All processes completed. Total time: 28",
    };

    auto actual = split_lines(output);
    CHECK_EQ(actual, expected);
}

TEST_CASE("RoundRobinScheduler5") {
    RoundRobinScheduler scheduler(5);
    scheduler.add_process("P1", 9);
    scheduler.add_process("P2", 7);
    scheduler.add_process("P3", 11);
    scheduler.add_process("P4", 4);

    std::string output = capture_output([&] {
        scheduler.run();
    });

    std::vector<std::string> expected = {
        "Process P1 executed for 5 units. Remaining: 4",
        "Process P2 executed for 5 units. Remaining: 2",
        "Process P3 executed for 5 units. Remaining: 6",
        "Process P4 executed for 4 units. Remaining: 0",
        "Process P1 executed for 4 units. Remaining: 0",
        "Process P2 executed for 2 units. Remaining: 0",
        "Process P3 executed for 5 units. Remaining: 1",
        "Process P3 executed for 1 units. Remaining: 0",
        "All processes completed. Total time: 31",
    };

    auto actual = split_lines(output);
    CHECK_EQ(actual, expected);
}

TEST_CASE("RoundRobinScheduler6") {
    RoundRobinScheduler scheduler(4);
    scheduler.add_process("P1", 13);
    scheduler.add_process("P2", 7);
    scheduler.add_process("P3", 9);
    scheduler.add_process("P4", 6);

    std::string output = capture_output([&] {
        scheduler.run();
    });

    std::vector<std::string> expected = {
        "Process P1 executed for 4 units. Remaining: 9",
        "Process P2 executed for 4 units. Remaining: 3",
        "Process P3 executed for 4 units. Remaining: 5",
        "Process P4 executed for 4 units. Remaining: 2",
        "Process P1 executed for 4 units. Remaining: 5",
        "Process P2 executed for 3 units. Remaining: 0",
        "Process P3 executed for 4 units. Remaining: 1",
        "Process P4 executed for 2 units. Remaining: 0",
        "Process P1 executed for 4 units. Remaining: 1",
        "Process P3 executed for 1 units. Remaining: 0",
        "Process P1 executed for 1 units. Remaining: 0",
        "All processes completed. Total time: 35",
    };

    auto actual = split_lines(output);
    CHECK_EQ(actual, expected);
}

TEST_CASE("RoundRobinScheduler7") {
    RoundRobinScheduler scheduler(6);
    scheduler.add_process("P1", 18);
    scheduler.add_process("P2", 7);
    scheduler.add_process("P3", 12);
    scheduler.add_process("P4", 5);

    std::string output = capture_output([&] {
        scheduler.run();
    });

    std::vector<std::string> expected = {
        "Process P1 executed for 6 units. Remaining: 12",
        "Process P2 executed for 6 units. Remaining: 1",
        "Process P3 executed for 6 units. Remaining: 6",
        "Process P4 executed for 5 units. Remaining: 0",
        "Process P1 executed for 6 units. Remaining: 6",
        "Process P2 executed for 1 units. Remaining: 0",
        "Process P3 executed for 6 units. Remaining: 0",
        "Process P1 executed for 6 units. Remaining: 0",
        "All processes completed. Total time: 42",
    };

    auto actual = split_lines(output);
    CHECK_EQ(actual, expected);
}

TEST_CASE("RoundRobinScheduler8") {
    RoundRobinScheduler scheduler(2);
    scheduler.add_process("P1", 10);
    scheduler.add_process("P2", 5);
    scheduler.add_process("P3", 8);
    scheduler.add_process("P4", 3);

    std::string output = capture_output([&] {
        scheduler.run();
    });

    std::vector<std::string> expected = {
        "Process P1 executed for 2 units. Remaining: 8",
        "Process P2 executed for 2 units. Remaining: 3",
        "Process P3 executed for 2 units. Remaining: 6",
        "Process P4 executed for 2 units. Remaining: 1",
        "Process P1 executed for 2 units. Remaining: 6",
        "Process P2 executed for 2 units. Remaining: 1",
        "Process P3 executed for 2 units. Remaining: 4",
        "Process P4 executed for 1 units. Remaining: 0",
        "Process P1 executed for 2 units. Remaining: 4",
        "Process P2 executed for 1 units. Remaining: 0",
        "Process P3 executed for 2 units. Remaining: 2",
        "Process P1 executed for 2 units. Remaining: 2",
        "Process P3 executed for 2 units. Remaining: 0",
        "Process P1 executed for 2 units. Remaining: 0",
        "All processes completed. Total time: 26",
    };

    auto actual = split_lines(output);
    CHECK_EQ(actual, expected);
}

TEST_CASE("RoundRobinScheduler9") {
    RoundRobinScheduler scheduler(7);
    scheduler.add_process("P1", 6);
    scheduler.add_process("P2", 11);
    scheduler.add_process("P3", 9);
    scheduler.add_process("P4", 21);
    scheduler.add_process("P5", 38);
    scheduler.add_process("P6", 17);
    scheduler.add_process("P7", 29);

    std::string output = capture_output([&] {
        scheduler.run();
    });

    std::vector<std::string> expected = {
        "Process P1 executed for 6 units. Remaining: 0",
        "Process P2 executed for 7 units. Remaining: 4",
        "Process P3 executed for 7 units. Remaining: 2",
        "Process P4 executed for 7 units. Remaining: 14",
        "Process P5 executed for 7 units. Remaining: 31",
        "Process P6 executed for 7 units. Remaining: 10",
        "Process P7 executed for 7 units. Remaining: 22",
        "Process P2 executed for 4 units. Remaining: 0",
        "Process P3 executed for 2 units. Remaining: 0",
        "Process P4 executed for 7 units. Remaining: 7",
        "Process P5 executed for 7 units. Remaining: 24",
        "Process P6 executed for 7 units. Remaining: 3",
        "Process P7 executed for 7 units. Remaining: 15",
        "Process P4 executed for 7 units. Remaining: 0",
        "Process P5 executed for 7 units. Remaining: 17",
        "Process P6 executed for 3 units. Remaining: 0",
        "Process P7 executed for 7 units. Remaining: 8",
        "Process P5 executed for 7 units. Remaining: 10",
        "Process P7 executed for 7 units. Remaining: 1",
        "Process P5 executed for 7 units. Remaining: 3",
        "Process P7 executed for 1 units. Remaining: 0",
        "Process P5 executed for 3 units. Remaining: 0",
        "All processes completed. Total time: 131",
    };

    auto actual = split_lines(output);
    CHECK_EQ(actual, expected);
}