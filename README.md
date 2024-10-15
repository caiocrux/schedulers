# Schedulers

A collection of scheduling algorithms implemented in C++. This repository provides implementations and examples of popular real-time scheduling algorithms for use in embedded systems, real-time systems, or as learning resources.

## Table of Contents

- [About the Project](#about-the-project)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Algorithms](#algorithms)
- [Contributing](#contributing)
- [License](#license)

## About the Project

The **Schedulers** repository includes several real-time scheduling algorithms implemented in modern C++. This collection is designed to help developers understand and experiment with different scheduling methods, particularly in real-time and embedded systems.

## Features

- **Rate Monotonic Scheduling (RMS)**
- **Deadline Monotonic Scheduling (DM)**
- **Earliest Deadline First (EDF)**
- **Least Laxity First (LLF)**
## Installation

To clone and build this project, ensure you have `git` and a C++ compiler (supporting C++17 or later) installed.

1. Clone the repository:
   ```bash
   git clone https://github.com/caiocrux/schedulers.git
   cd schedulers
   ```

2. Build the project:

    ```bash
    mkdir build && cd build
    cmake ..
    make
    ``` 

##  Algorithms

This repository currently supports the following scheduling algorithms:

- **Rate Monotonic Scheduling (RMS)**: Prioritizes tasks based on their periodicity, ideal for fixed-priority tasks.
- **Deadline Monotonic Scheduling (DM)**: A fixed-priority algorithm suitable for systems where tasks have specific deadlines.
- **Earliest Deadline First (EDF)**: A dynamic priority algorithm that schedules tasks based on the closest deadline.
- **Least Laxity First (LLF)**: Prioritizes tasks based on the minimum laxity (slack) time.
- **Least Slack Time (LST)**: Focuses on minimizing slack time to ensure real-time constraints are met.

Each algorithm’s implementation is contained within its corresponding source file, with comments explaining the logic and parameters.

### Usage

To run the scheduler program, specify the desired scheduling algorithm and the tasks to be scheduled.

#### Required Options:
- `--algorithm`: Specifies the scheduling algorithm to use. Available options include:
  - `RateMonotonic`
  - `DeadlineMonotonic`
  - `EarliestDeadlineFirst`
  - `LeastLaxity`

- `--tasks`: Defines the tasks to be scheduled, provided in a specific format. Each task should follow the format `id,cpu_time,period,deadline`. Multiple tasks should be separated by a semicolon (`;`).

#### Example Command
```bash
./build/app/scheduler --algorithm RateMonotonic --tasks "1,3,7,7;2,2,12,12;3,2,20,20"
```

In this example:

1,3,7,7 defines a task with id = 1, cpu_time = 3, period = 7, and deadline = 7.

2,2,12,12 defines a second task with id = 2, cpu_time = 2, period = 12, and deadline = 12.

3,2,20,20 defines a third task with id = 3, cpu_time = 2, period = 20, and deadline = 20.
