/*
NAME: AHAN BANDYOPADHYAY
ROLL NO.: 211210008

Question 2:
Implement a solution to the dining philosopher problem in C or C++ using
semaphores, with the following additional requirements:
1. The philosophers must be able to eat in a specific order, specified by
an input array.
2. The philosophers must be able to terminate gracefully, even if some
philosophers are still in the middle of eating.
3. The philosophers must be able to avoid starvation, where one
philosopher is never able to eat because other philosophers are
always eating.
4. The philosophers must be able to eat in parallel, meaning that
multiple philosophers can be eating at the same time.
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <semaphore.h>
#include <atomic>

const int num_philosophers = 5;
const int max_eating = 2; // Maximum philosophers eating in parallel

std::vector<sem_t> forks(num_philosophers);
std::vector<std::thread> philosophers(num_philosophers);
std::mutex print_mutex;
std::atomic<bool> exit_program(false);

void think(int philosopher_id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));  // Thinking
}

void eat(int philosopher_id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));  // Eating
}

void philosopher(int philosopher_id, const std::vector<int>& philosopher_order) {
    while (!exit_program) {
        think(philosopher_id);

        int left_fork = philosopher_order[philosopher_id];
        int right_fork = philosopher_order[(philosopher_id + 1) % num_philosophers];

        // Acquire left and right forks with a maximum number of philosophers eating
        sem_wait(&forks[left_fork]);
        sem_wait(&forks[right_fork]);

        if (exit_program) {
            sem_post(&forks[left_fork]);
            sem_post(&forks[right_fork]);
            break;
        }

        // Eat
        {
            std::lock_guard<std::mutex> lock(print_mutex);
            std::cout << "Philosopher " << philosopher_id << " is eating." << std::endl;
        }
        eat(philosopher_id);

        // Release left and right forks
        sem_post(&forks[left_fork]);
        sem_post(&forks[right_fork]);
    }
}

int main() {
    // Initialize forks
    for (int i = 0; i < num_philosophers; ++i) {
        sem_init(&forks[i], 0, max_eating);
    }

    // Specify the order in which philosophers eat
    std::vector<int> philosopher_order = {0, 1, 2, 3, 4};

    // Create philosopher threads
    for (int i = 0; i < num_philosophers; ++i) {
        philosophers[i] = std::thread(philosopher, i, philosopher_order);
    }

    // Wait for user input to terminate gracefully
    std::cout << "Press Enter to terminate..." << std::endl;
    std::cin.get();

    // Set the exit_program flag and wait for philosophers to finish
    exit_program = true;
    for (int i = 0; i < num_philosophers; ++i) {
        philosophers[i].join();
    }

    // Clean up
    for (int i = 0; i < num_philosophers; ++i) {
        sem_destroy(&forks[i]);
    }

    return 0;
}

