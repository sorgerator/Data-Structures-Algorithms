//
// Created by aldin on 21/04/2025.
//

#ifndef ROUNDROBINSCHEDULER_H
#define ROUNDROBINSCHEDULER_H
#include "ProcessQueue.h"
#include <string>

class RoundRobinScheduler {
private:
    ProcessQueue *processes{};
    int quantum{};
    int total_time{};
public:
    explicit RoundRobinScheduler(int quantum);
    ~RoundRobinScheduler();
    void add_process(const std::string& id, int burst_time) const;
    void set_quantum(int _quantum);
    int get_total_time() const;
    void run();
};

#endif //ROUNDROBINSCHEDULER_H
