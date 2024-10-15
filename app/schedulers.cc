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

#include <GanttChart.h>
#include <Task.h>
#include <deadlineMonotonic.h>
#include <earliestDeadlineFirst.h>
#include <leastLaxity.h>
#include <rateMonotonic.h>

#include <algorithm>
#include <cmath>
#include <cxxopts.hpp>
#include <fstream>  // for file output
#include <iostream>
#include <map>
#include <numeric>   // std::lcm
#include <optional>  // std::optional
#include <vector>

int main(int argc, char **argv) {
    // int main(void) {
    cxxopts::Options options(
        "Scheduler", "A program to schedule tasks using various algorithms");

    options.add_options()(
        "algorithm",
        "Specify the scheduling algorithm (RateMonotonic, DeadlineMonotonic, "
        "EarliestDeadlineFirst, LeastLaxity)",
        cxxopts::value<std::string>())(
        "tasks", "Specify the tasks in the format: 'id,cpu_time,period,dealine'",
        cxxopts::value<std::string>())
        ("help", "Show help");
    
    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    if (!result.count("algorithm") || !result.count("tasks")) {
        std::cerr << "Error: Algorithm and tasks must be specified."
                  << std::endl;
        std::cerr << options.help() << std::endl;
        return 1;
    }

    std::string algorithmType = result["algorithm"].as<std::string>();
    std::cout << "Selected algorithm: " << algorithmType << std::endl;

    std::vector<Task> tasks;
    //auto taskStrings = result["tasks"].as<std::vector<std::string>>();
    std::string taskStrings = result["tasks"].as<std::string>();


    // Split tasks by semicolon
    std::istringstream taskStream(taskStrings);
    std::string task_str;
    while (std::getline(taskStream, task_str, ';')) {
        std::cout << "Parsing task: " << task_str << std::endl;
        int id, cpu_time, period, deadline;
        char comma1, comma2, comma3;
        std::istringstream iss(task_str);

        if (iss >> id >> comma1 >> cpu_time >> comma2 >> period >> comma3 >> deadline &&
            comma1 == ',' && comma2 == ',' && comma3 == ',') {
            tasks.emplace_back(id, cpu_time, period, deadline);
            std::cout << "Added task: ID=" << id << ", CPU Time=" << cpu_time << ", Period=" << period << ", Deadline=" << deadline << std::endl;
        } else {
            std::cerr << "Invalid task format: " << task_str << std::endl;
            return 1;
        }
    }

    std::cout << "Total tasks parsed: " << tasks.size() << std::endl;

    // Parse the tasks from the command line
/*    for (const auto &task_str :
        result["tasks"].as<std::vector<std::string>>()) {
        int id, cpu_time, period, deadline;
        char comma;  // For parsing commas
        std::istringstream iss(task_str);
        if (iss >> id >> comma >> cpu_time >> comma >> period >> comma >>
            deadline) {
            tasks.emplace_back(id, cpu_time, period, deadline);
        } else {
            std::cerr << "Invalid task format: " << task_str << std::endl;
            return 1;
        }
    }
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
#if 0
    std::vector<Task> tasks = {Task(1, 2, 7, 7), Task(2, 3, 12, 12),
                               Task(3, 2, 5, 5)};
    //                               Task(3, 1, 20, 20)};
    // Task(4, 4, 13, 13)};
    std::string task1_img = "Tabela_1.csv";

#endif

    auto scheduler = createScheduler(algorithmType, tasks);
    if (scheduler) {
        scheduler->calculateLcmFromPeriods();
        scheduler->sortTasksByPeriod();
        if (scheduler->isSchedulable().value_or(false)) {
            std::vector<int> schedule = scheduler->run();
            for (int id : schedule) {
                std::cout << "Task ID: " << id << std::endl;
            }
        } else {
            std::cout << "The tasks are not schedulable." << std::endl;
        }
    }

/*
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

    auto rmSchedule = rmScheduler.run();
    auto dmSchedule = dmScheduler.run();
    auto edfSchedule = edfScheduler.run();
    auto llSchedule = llScheduler.run();

    GanttChart ganttChart;

    ganttChart.drawGanttChart(rmSchedule, "Rate Monotonic Chart");
    ganttChart.drawGanttChart(dmSchedule, "Deadline Monotonic Chart");
    ganttChart.drawGanttChart(edfSchedule, "Earliest Deadline First Chart");
    ganttChart.drawGanttChart(llSchedule, "Least Laxity Chart");
    return 0;
    */
}
