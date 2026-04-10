//
// Created by aldin on 21/04/2025.
//

#ifndef PROCESS_H
#define PROCESS_H
#include <string>

struct Process {
    // Define id, burst_time and remaining_time
    std::string id;
    int burst_time;
    int remaining_time;
    // Define a default constructor, and a constructor taking all parameters
    Process() : id(""), burst_time(0), remaining_time(0) {};
    Process(const std::string& _id, int _burst_time) : id(_id), burts_time(_burst_time), remaining_time(_burst_time) {};
};

#endif //PROCESS_H
