#pragma once

#include <Task.h>

#include <iostream>
#include <memory>
#include <optional>
#include <vector>

// Base class for all scheduling algorithms
class Scheduler {
   protected:
    std::vector<Task> m_tasks;
    int m_lcm;

   public:
    explicit Scheduler(const std::vector<Task>& tasks_input)
        : m_tasks(tasks_input), m_lcm(1) {}

    virtual void calculateLcmFromPeriods() = 0;
    virtual std::optional<bool> isSchedulable() = 0;
    virtual std::vector<int> run() = 0;
    virtual ~Scheduler() = default;
};

// Factory function to create the appropriate scheduling algorithm
std::unique_ptr<Scheduler> createScheduler(const std::string& type,
                                           const std::vector<Task>& tasks);
