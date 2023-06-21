#include <iostream>
#include <vector>

const int N = 5; // Numero di processi
const int QUANTUM = 1; // Quantum per l'algoritmo di Round Robin

class Process {
public:
    int pid;
    int burst_time;
    int priority;

    Process(int pid, int burst_time, int priority)
        : pid(pid), burst_time(burst_time), priority(priority) {}
};

std::vector<Process> processes;

void first_come_first_served() {
    std::cout << "FCFS non ancora implementato.\n";
}

void shortest_job_first() {
    std::cout << "Shortest Job First non ancora implementato.\n";
}

void priority_scheduling() {
    std::cout << "Priority Scheduling non ancora implementato.\n";
}

void round_robin() {
    std::cout << "Round Robin non ancora implementato.\n";
}

void multilevel_queue_scheduling() {
    std::cout << "Multilevel Queue Scheduling non ancora implementato.\n";
}

void multilevel_feedback_queue_scheduling() {
    std::cout << "Multilevel Feedback Queue Scheduling non ancora implementato.\n";
}

void completely_fair_scheduler() {
    std::cout << "Completely Fair Scheduler non ancora implementato.\n";
}

int main() {
    // Inizializzazione dei processi
    for (int i = 0; i < N; i++) {
        processes.emplace_back(i, rand() % 10 + 1, rand() % 3 + 1);
    }

    int choice;
    std::cout << "Scegli un algoritmo di scheduling:\n";
    std::cout << "1. First Come First Served (FCFS)\n";
    std::cout << "2. Shortest Job First (SJF)\n";
    std::cout << "3. Priority Scheduling\n";
    std::cout << "4. Round Robin (RR)\n";
    std::cout << "5. Multilevel Queue Scheduling\n";
    std::cout << "6. Multilevel Feedback Queue Scheduling\n";
    std::cout << "7. Completely Fair Scheduler (CFS)\n";
    std::cout << "Inserisci la tua scelta (1-7): ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            first_come_first_served();
            break;
        case 2:
            shortest_job_first();
            break;
        case 3:
            priority_scheduling();
            break;
        case 4:
            round_robin();
            break;
        case 5:
            multilevel_queue_scheduling();
            break;
        case 6:
            multilevel_feedback_queue_scheduling();
            break;
        case 7:
            completely_fair_scheduler();
            break;
        default:
            std::cout << "Scelta non valida.\n";
    }

    return 0;
}
