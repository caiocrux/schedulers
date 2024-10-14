#pragma once

#include <iostream>

class Task {
   private:
    int m_id;
    int m_executionTime;
    int m_period;
    int m_deadline;
    int m_remaining;
    int m_next_deadline;

   public:
    explicit Task(int id, int executionTime, int period, int deadline);

    // Getters
    int getId() const noexcept;
    int getC() const noexcept;
    int getT() const noexcept;
    int getD() const noexcept;
    int getRemaining() const noexcept;
    int getNextDeadline() const noexcept;

    // Setters
    void setRemaining(int r) noexcept;
    void setNextDeadline(int deadline) noexcept;

    virtual void print_task() const;
};
