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


