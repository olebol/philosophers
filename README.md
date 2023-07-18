# Philosophers

This repository contains a program that simulates the classic Dining Philosophers problem. The objective of this project is to implement a program written solely in C without the use of global variables and completely abiding by 42 Network's *Norme*. The goal of this project is to get a basic understanding of threads and multithreading.

The Dining Philosophers problem involves a group of philosophers sitting around a circular table with a bowl of rice and a fork between each pair of adjacent philosophers. The philosophers alternate between thinking and eating, and they require two forks to eat their meal.

## Features

- Multithreading

## Getting Started

### Prerequisites

- A Unix-like operating system such as Linux or macOS.
- GCC compiler installed.

### Installing and running

1. Clone this repository:
```
git clone https://github.com/olebol/philosophers philosophers
```

2. cd into the right directory
```
cd philosophers
```

3. Run Make to compile the program
```
make
```

4. Execute the program
```
./philo amount time_to_die time_to_eat time_to_sleep [times_philosopher_must_eat]
```
### Arguments
- amount: The number of philosophers and also the number
of forks.
- time_to_die: If a philosopher didn’t start eating ***time_to_die***
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- time_to_eat: The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
- time_to_sleep: The time a philosopher will spend sleeping.
- times_philosopher_must_eat (optional argument): If all
philosophers have eaten at least ***times_philosopher_must_eat***
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.