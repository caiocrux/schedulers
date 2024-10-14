#include "deadlineMonotonic.h"

DeadlineMonotonic::DeadlineMonotonic(const std::vector<Task>& tasks_input)
    : m_tasks(tasks_input), m_lcm(1) {}

void DeadlineMonotonic::calculateLcmFromPeriods() {
    m_lcm = 1;
    for (const auto& task : m_tasks) {
        m_lcm = std::lcm(m_lcm, task.getT());
    }
    std::cout << "LCM: " << m_lcm << std::endl;
}

void DeadlineMonotonic::sortTasksByDeadline() {
    std::sort(m_tasks.begin(), m_tasks.end(),
              [](const Task& a, const Task& b) { return a.getD() < b.getD(); });
}

std::optional<bool> DeadlineMonotonic::isSchedulable() {
    for (size_t i = 0; i < m_tasks.size(); i++) {
        int Ri = m_tasks[i].getC();
        int prev_Ri = Ri;

        do {
            prev_Ri = Ri;
            Ri = m_tasks[i].getC();

            for (size_t j = 0; j < i; ++j) {
                Ri += std::ceil(static_cast<double>(prev_Ri) /
                                m_tasks[j].getT()) *
                      m_tasks[j].getC();
            }

            if (Ri > m_tasks[i].getD()) {
                std::cout << "Task " << m_tasks[i].getId()
                          << " is not schedulable. Response Time: " << Ri
                          << ", Deadline: " << m_tasks[i].getD() << std::endl;
                return std::optional<bool>(false);
            }

        } while (Ri != prev_Ri);

        std::cout << "Task " << m_tasks[i].getId()
                  << " is schedulable. Response Time: " << Ri
                  << ", Deadline: " << m_tasks[i].getD() << std::endl;
    }

    return std::optional<bool>(true);
}

std::vector<int> DeadlineMonotonic::runDeadlineMonotonic() {
    std::vector<int> schedule(m_lcm, -1);
    int time = 0;

    for (auto& task : m_tasks) {
        task.setRemaining(task.getC());
    }

    while (time < m_lcm) {
        Task* next_task = nullptr;

        for (auto& task : m_tasks) {
            if (time % task.getT() == 0) {
                task.setRemaining(task.getC());
            }
            if (task.getRemaining() > 0 &&
                (next_task == nullptr || task.getD() < next_task->getD())) {
                next_task = &task;
            }
        }

        if (next_task) {
            schedule[time] = next_task->getId();
            next_task->setRemaining(next_task->getRemaining() - 1);
        }

        time++;
    }

    return schedule;
}
