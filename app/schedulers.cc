/*
 * untitled.cxx
 *
 * Copyright 2024 caio felipe soares da cruz  <caio-cruz@ENCSABCAMLT0872>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */

//#include <matplotlibcpp.h>

#include <algorithm>
#include <cmath>
#include <fstream>  // for file output
#include <iostream>
#include <map>
#include <numeric>   // std::lcm
#include <optional>  // std::optional
#include <vector>
#include <Task.h> 
#include <GanttChart.h>
//namespace plt = matplotlibcpp;

class RateMonotonic {
   private:
    std::vector<Task> m_tasks;
    int m_lcm;

   public:
    // Construtor
    explicit RateMonotonic(const std::vector<Task> &tasks_input)
        : m_tasks(tasks_input), m_lcm(1) {}
    // Method to calculate LCM
    void calculateLcmFromPeriods(void) {
        m_lcm = 1;
        for (const auto &task : m_tasks) {
            // Least Common Multiple (LCM) of two numbers.
            // Only works for C++17 and above
            m_lcm = std::lcm(m_lcm, task.getT());
        }
        std::cout << "LCM: " << m_lcm << std::endl;
    }
    // Method to check if the task are schedulable
    // std::optional is a feature introduced in C++ 17 which is used to
    // represent optional values i.e. the possibility of having a value or
    // not having a value in a type-safe manner.

    std::optional<bool> isSchedulable() const {
        double U = 0;
        int n = m_tasks.size();
        // calculate Utotal
        for (const auto &task : m_tasks) {
            U += static_cast<double>(task.getC()) / task.getT();
        }
        // calculate Umax
        double bound = n * (std::pow(2.0, 1.0 / n) - 1);
        std::cout << "Utotal: " << U << std::endl;
        std::cout << "Umax: " << bound << std::endl;
        return (U <= bound) ? std::optional<bool>(true)
                            : std::optional<bool>(false);
    }
    // Sort tasks by period, using the Rate Monotonic scheduling algorithm.
    // Tasks with shorter periods have higher priority.

    void sortTasksByPeriod() {
        // smaller periods come first
        std::sort(
            m_tasks.begin(), m_tasks.end(),
            [](const Task &a, const Task &b) { return a.getT() < b.getT(); });
    }
    std::vector<int> runRateMonotonic() {
        std::vector<int> schedule(m_lcm, -1);
        int time = 0;

        for (auto &task : m_tasks) {
            task.setRemaining(task.getC());
        }
        // Simulate over time
        while (time < m_lcm) {
            Task *next_task = nullptr;
            // Check for task release and reset remaining time
            for (auto &task : m_tasks) {
                if (time % task.getT() == 0) {
                    task.setRemaining(task.getC());
                }
                if (task.getRemaining() > 0 &&
                    (next_task == nullptr || task.getT() < next_task->getT())) {
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
};

class DeadlineMonotonic {
   private:
    std::vector<Task> m_tasks;
    int m_lcm;

   public:
    explicit DeadlineMonotonic(const std::vector<Task> &tasks_input)
        : m_tasks(tasks_input), m_lcm(1) {}

    void calculateLcmFromPeriods() {
        m_lcm = 1;
        for (const auto &task : m_tasks) {
            m_lcm = std::lcm(m_lcm, task.getT());
        }
        std::cout << "LCM: " << m_lcm << std::endl;
    }

    // prioritize tasks based on their deadlines, starting with the earliest
    // deadline.

    void sortTasksByDeadline() {
        std::sort(
            m_tasks.begin(), m_tasks.end(),
            [](const Task &a, const Task &b) { return a.getD() < b.getD(); });
    }
    std::optional<bool> isSchedulable() {
        // Itera sobre cada tarefa
        for (size_t i = 0; i < m_tasks.size(); i++) {
            int Ri = m_tasks[i].getC();  // Tempo de resposta inicial é o
                                         // próprio tempo de execução
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
                    std::cout << "Tarefa " << m_tasks[i].getId()
                              << " não é escalonável. Tempo de "
                                 "resposta: "
                              << Ri << ", Deadline: " << m_tasks[i].getD()
                              << std::endl;
                    return std::optional<bool>(false);
                }

            } while (Ri != prev_Ri);

            std::cout << "Tarefa " << m_tasks[i].getId()
                      << " é escalonável. Tempo de resposta: " << Ri
                      << ", Deadline: " << m_tasks[i].getD() << std::endl;
        }

        return std::optional<bool>(true);
    }

    std::vector<int> runDeadlineMonotonic() {
        std::vector<int> schedule(m_lcm, -1);
        int time = 0;

        for (auto &task : m_tasks) {
            task.setRemaining(task.getC());
        }

        while (time < m_lcm) {
            Task *next_task = nullptr;

            for (auto &task : m_tasks) {
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
};

class EarliestDeadlineFirst {
   private:
    std::vector<Task> m_tasks;
    int m_lcm;

   public:
    explicit EarliestDeadlineFirst(const std::vector<Task> &tasks_input)
        : m_tasks(tasks_input), m_lcm(1) {}

    void calculateLcmFromPeriods() {
        m_lcm = 1;
        for (const auto &task : m_tasks) {
            m_lcm = std::lcm(m_lcm, task.getT());
        }
        std::cout << "LCM: " << m_lcm << std::endl;
    }

    // prioritize tasks based on their deadlines, starting with the earliest
    // deadline.
    void sortTasksByDeadline(int currentTime) {
        std::sort(m_tasks.begin(), m_tasks.end(),
                  [currentTime](const Task &a, const Task &b) {
                      int deadlineA = a.getT() - (currentTime % a.getT());
                      int deadlineB = b.getT() - (currentTime % b.getT());
                      return deadlineA < deadlineB;
                  });
    }
    std::optional<bool> isSchedulable() {
        double U = 0;
        char maxCore = 1;
        // calculate Utotal
        for (const auto &task : m_tasks) {
            U += static_cast<double>(task.getC()) / task.getT();
        }

        std::cout << "Utotal: " << U << std::endl;

        return (U <= maxCore) ? std::optional<bool>(true)
                              : std::optional<bool>(false);
    }

    std::vector<int> runEarliestDeadlineFirst() {
        std::vector<int> schedule(m_lcm, -1);
        int time = 0;

        for (auto &task : m_tasks) {
            task.setRemaining(task.getC());
        }

        while (time < m_lcm) {
            Task *next_task = nullptr;

            for (auto &task : m_tasks) {
                if (time % task.getT() == 0) {
                    task.setRemaining(task.getC());
                }
            }

            sortTasksByDeadline(time);

            for (auto &task : m_tasks) {
                if (task.getRemaining() > 0) {
                    next_task = &task;
                    break;
                }
            }

            if (next_task) {
                schedule[time] = next_task->getId();
                next_task->setRemaining(next_task->getRemaining() - 1);
            } else {
                schedule[time] = -1;  // Means idle
            }

            time++;
        }

        return schedule;
    }
};

class LeastLaxity {
   private:
    std::vector<Task> m_tasks;
    int m_lcm;

   public:
    explicit LeastLaxity(const std::vector<Task> &tasks_input)
        : m_tasks(tasks_input), m_lcm(1) {}

    void calculateLcmFromPeriods() {
        m_lcm = 1;
        for (const auto &task : m_tasks) {
            m_lcm = std::lcm(m_lcm, task.getT());
        }
        std::cout << "LCM: " << m_lcm << std::endl;
    }

    std::optional<bool> isSchedulable() const {
        return std::optional<bool>(true);
    }

    void sortTasksByLaxity(int currentTime) {
        std::sort(m_tasks.begin(), m_tasks.end(),
                  [currentTime](const Task &a, const Task &b) {
                      int laxityA = (a.getT() - (currentTime % a.getT())) -
                                    a.getRemaining();
                      int laxityB = (b.getT() - (currentTime % b.getT())) -
                                    b.getRemaining();
                      return laxityA < laxityB;
                  });
    }

    std::vector<int> runLeastLaxity() {
        std::vector<int> schedule(m_lcm, -1);
        int time = 0;

        for (auto &task : m_tasks) {
            task.setRemaining(task.getC());
        }

        while (time < m_lcm) {
            Task *next_task = nullptr;

            for (auto &task : m_tasks) {
                if (time % task.getT() == 0) {
                    task.setRemaining(task.getC());
                }
            }

            sortTasksByLaxity(time);

            for (auto &task : m_tasks) {
                if (task.getRemaining() > 0) {
                    next_task = &task;
                    break;
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
};
/*
class GanttChart {
   public:
    void saveToCSV(const std::vector<int> &schedule,
                   const std::string &filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        file << "Time,TaskID\n";  // CSV header
        for (size_t t = 0; t < schedule.size(); ++t) {
            file << t << "," << schedule[t] << "\n";
        }
        file.close();
    }
    // Método para desenhar o diagrama de Gantt usando matplotlib
    void drawGanttChart(const std::vector<int> &schedule, std::string tittle) {
        std::map<int, std::vector<int>>
            task_times;               // Armazena os intervalos para cada tarefa
        std::vector<int> idle_times;  // Armazena intervalos ociosos

        for (size_t t = 0; t < schedule.size(); ++t) {
            int task_id = schedule[t];
            if (task_id != -1) {
                task_times[task_id].push_back(t);
            } else {
                idle_times.push_back(t);
            }
        }

        // Desenhar cada tarefa no Gantt
        for (const auto &[task_id, times] : task_times) {
            std::vector<double> x, y;
            for (const auto &time : times) {
                x.push_back(time);
                y.push_back(task_id);
            }

            plt::scatter(x, y, 50,
                         {{"label", "Task " + std::to_string(task_id)}});
        }

        // Desenhar tempos de ociosidade (IDLE)
        if (!idle_times.empty()) {
            std::vector<double> idle_x(idle_times.begin(), idle_times.end());
            std::vector<double> idle_y(idle_times.size(),
                                       0);  // IDLE será representado em Y=0

            plt::scatter(idle_x, idle_y, 50,
                         {{"label", "IDLE"}, {"color", "gray"}});
        }

        // Definir o título e os rótulos
        plt::title(tittle);
        plt::xlabel("Time");
        plt::ylabel("Task ID");

        // Adicionar legenda
        plt::legend();
        // Save the chart to a file instead of showing it
        plt::show();
        // Clear the figure after saving (optional)
        plt::clf();
    }
};

*/
// int main(int argc, char **argv) {
int main(void) {
    //  int n;
    //  std::cout << "Digite o número de tarefas: ";
    //  std::cin >> n;

    // Tabela 1
#if 0
  std::vector<Task> tasks = {Task(1, 3, 7, 7), Task(2, 2, 12, 12),
                             Task(3, 2, 20, 20)};
  std::string task1_img = "Tabela_1.csv";
#endif

#if 0
  std::vector<Task> tasks = {Task(1, 6.25, 25, 7), Task(2, 6.25, 50, 12),
                             Task(3, 40, 100, 20)};
#endif

    // Tabela 2
#if 0
  std::vector<Task> tasks = {Task(1, 1, 4, 4), Task(2, 2, 6, 6),
                             Task(3, 3, 10, 7)};
  std::string task1_img = "Tabela_2.csv";

#endif

    // Tabela 6
#if 0
  std::vector<Task> tasks = {Task(1, 3, 10, 10), Task(2, 3, 10, 10),
                             Task(3, 3, 10, 10), Task(4, 2, 100, 100)};
  std::string task1_img = "Tabela_6.csv";
#endif

// exemplo para graficos diferentes
#if 0 
  std::vector<Task> tasks = {Task(1, 1, 4, 4), 
                             Task(2, 2, 5, 3),
                             Task(3, 2, 7, 6),
                             Task(4, 3, 12, 10)};
#endif

#if 0

std::vector<Task> tasks = {Task(1, 2, 10, 5), 
                           Task(2, 5, 20, 7),
                           Task(3, 10, 50, 10)};
#endif
    /*
      for (int i = 0; i < n; i++) {
        int C, T, D;
        std::cout << "Digite o tempo de execução (C), o período (T) e "
                  << "o deadline (D) para a tarefa " << (i + 1) << ": ";
        std::cin >> C >> T >> D;
        // Using emplace_back() to create instances of Task directly in
        // the vector avoids an additional copy and improves performance
        tasks.emplace_back(i + 1, C, T, D);
      }
    */
    // for (auto i : tasks) {
    //   i.print_task();
    // }

#if 0
  std::vector<Task> tasks = {Task(1, 1, 7, 7),
                             Task(2, 2, 9, 9),
                             Task(3, 3, 11, 11),
                             Task(4, 4, 13, 13)};
  std::string task1_img = "Tabela_1.csv";
#endif
#if 1
    std::vector<Task> tasks = {Task(1, 2, 7, 7), 
                               Task(2, 3, 12, 12),
                               Task(3, 2, 5, 5)};
//                               Task(3, 1, 20, 20)};
    // Task(4, 4, 13, 13)};
    std::string task1_img = "Tabela_1.csv";

#endif

    RateMonotonic rmScheduler(tasks);
    rmScheduler.calculateLcmFromPeriods();
    rmScheduler.sortTasksByPeriod();

    DeadlineMonotonic dmScheduler(tasks);
    dmScheduler.calculateLcmFromPeriods();
    dmScheduler.sortTasksByDeadline();

    EarliestDeadlineFirst edfScheduler(tasks);
    edfScheduler.calculateLcmFromPeriods();

    LeastLaxity llScheduler(tasks);
    llScheduler.calculateLcmFromPeriods();

    if (!rmScheduler.isSchedulable()) {
        std::cout << "Tasks can not be schedulable using Rate "
                     "Monotonic scheduler! "
                  << std::endl;
    }
    if (!dmScheduler.isSchedulable()) {
        std::cout << "Tasks can not be schedulable using DeadLine "
                     "Monotonic scheduler! "
                  << std::endl;
    }
    if (!edfScheduler.isSchedulable()) {
        std::cout << "Tasks can not be schedulable using Earliest "
                     "Deadline First scheduler! "
                  << std::endl;
    }

    auto rmSchedule = rmScheduler.runRateMonotonic();
    auto dmSchedule = dmScheduler.runDeadlineMonotonic();
    auto edfSchedule = edfScheduler.runEarliestDeadlineFirst();
    auto llSchedule = llScheduler.runLeastLaxity();
    // rmScheduler.drawGanttChart(schedule, task1_img);
    // Create GanttChart object and save to CSV
    GanttChart ganttChart;
    // ganttChart.saveToCSV(schedule, task1_img);
    ganttChart.drawGanttChart(rmSchedule, "Rate Monotonic Chart");
    ganttChart.drawGanttChart(dmSchedule, "Deadline Monotonic Chart");
    ganttChart.drawGanttChart(edfSchedule, "Earliest Deadline First Chart");
    ganttChart.drawGanttChart(llSchedule, "Least Laxity Chart");
    return 0;
}
