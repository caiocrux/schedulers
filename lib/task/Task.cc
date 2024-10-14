#include "Task.h"

Task::Task(int id, int executionTime, int period, int deadline)
    : m_id(id),
      m_executionTime(executionTime),
      m_period(period),
      m_deadline(deadline),
      m_remaining(0),
      m_next_deadline(deadline) {}

// Getters
int Task::getId() const noexcept { return m_id; }
int Task::getC() const noexcept { return m_executionTime; }
int Task::getT() const noexcept { return m_period; }
int Task::getD() const noexcept { return m_deadline; }
int Task::getRemaining() const noexcept { return m_remaining; }
int Task::getNextDeadline() const noexcept { return m_next_deadline; }

// Setters
void Task::setRemaining(int r) noexcept { m_remaining = r; }
void Task::setNextDeadline(int deadline) noexcept {
    m_next_deadline = deadline;
}

void Task::print_task() const {
    std::cout << "Task ID: " << m_id << ", C: " << m_executionTime
              << ", P: " << m_period << ", D: " << m_deadline << "\n";
}
