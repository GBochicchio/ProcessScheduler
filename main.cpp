#include <iostream>
#include <vector>
#include <ctime> // Librearia per utilizzare time()
#include <algorithm> // Per utilizzare std::sort

const int N = 20; // Numero di processi
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

void generateProcesses() {
    srand(time(nullptr)); // Imposta il seme iniziale basato sull'ora di sistema

    // Genera nuovi processi
    for (int i = 0; i < N; i++) {
        processes.emplace_back(i, rand() % 10 + 1, rand() % 3 + 1);
    }
}

void displayProcesses() {
    std::cout << "ID\tBurst Time\tPriority" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    for (int i = 0; i < N; i++) {
      std::cout << processes[i].pid << "\t" << processes[i].burst_time << "\t\t" << processes[i].priority << std::endl;
    }
}

void first_come_first_served() {
    std::vector<int> waiting_time(N, 0); // Initialize waiting time for all processes

    // Calculate waiting time for each process
    for (int i = 1; i < N; i++) {
        waiting_time[i] = waiting_time[i - 1] + processes[i - 1].burst_time;
    }

    // Calculate average waiting time
    double avg_waiting_time = 0;
    for (int i = 0; i < N; i++) {
        avg_waiting_time += waiting_time[i];
    }
    avg_waiting_time /= N;

    // Display the scheduling result
    std::cout << "FCFS Scheduling:\n";
    std::cout << "Process\tBurst Time\tPriority\tWaiting Time\n";
    for (int i = 0; i < N; i++) {
        std::cout << processes[i].pid << "\t" << processes[i].burst_time << "\t\t"
                  << processes[i].priority << "\t\t" << waiting_time[i] << "\n";
    }
    std::cout << "Average Waiting Time: " << avg_waiting_time << "\n";
}

bool compareByBurstTime(const Process& a, const Process& b) {
    return a.burst_time < b.burst_time;
}

void shortest_job_first() {
  // Creazione di una copia del vettore processes
  std::vector<Process> processes_copy = processes;

  // Ordina i processi in base alla durata di esecuzione più breve (burst_time)
  std::sort(processes_copy.begin(), processes_copy.end(), compareByBurstTime);

  std::vector<int> waiting_time(N, 0); // Inizializza il tempo di attesa per tutti i processi

  // Calcola il tempo di attesa per ciascun processo
  for (int i = 1; i < N; i++) {
      waiting_time[i] = waiting_time[i - 1] + processes_copy[i - 1].burst_time;
  }

  // Calcola il x\ di attesa medio
  double avg_waiting_time = 0;
  for (int i = 0; i < N; i++) {
      avg_waiting_time += waiting_time[i];
  }
  avg_waiting_time /= N;

  // Visualizza il risultato dello scheduling
  std::cout << "SJF Scheduling:\n";
  std::cout << "Process\tBurst Time\tPriority\tWaiting Time\n";
  for (int i = 0; i < N; i++) {
      std::cout << processes_copy[i].pid << "\t" << processes_copy[i].burst_time << "\t\t"
                << processes_copy[i].priority << "\t\t" << waiting_time[i] << "\n";
  }
  std::cout << "Average Waiting Time: " << avg_waiting_time << "\n";
}

void priority_scheduling() {
  // Creazione di una copia del vettore processes
  std::vector<Process> processes_copy = processes;

  // Ordina i processi in base alla priorità
  std::sort(processes_copy.begin(), processes_copy.end(), [](const Process& a, const Process& b) {
      return a.priority < b.priority;
  });

  std::vector<int> waiting_time(N, 0); // Inizializza il tempo di attesa per tutti i processi

  // Calcola il tempo di attesa per ciascun processo
  for (int i = 1; i < N; i++) {
      waiting_time[i] = waiting_time[i - 1] + processes_copy[i - 1].burst_time;
  }

  // Calcola il tempo di attesa medio
  double avg_waiting_time = 0;
  for (int i = 0; i < N; i++) {
      avg_waiting_time += waiting_time[i];
  }
  avg_waiting_time /= N;

  // Visualizza il risultato dello scheduling
  std::cout << "Priority Scheduling:\n";
  std::cout << "Process\tBurst Time\tPriority\tWaiting Time\n";
  for (int i = 0; i < N; i++) {
      std::cout << processes_copy[i].pid << "\t" << processes_copy[i].burst_time << "\t\t"
                << processes_copy[i].priority << "\t\t" << waiting_time[i] << "\n";
  }
  std::cout << "Average Waiting Time: " << avg_waiting_time << "\n";
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
    srand(time(nullptr)); // Imposta il seme iniziale basato sull'ora di sistema

    // Inizializzazione dei processi
    for (int i = 0; i < N; i++) {
        processes.emplace_back(i, rand() % 10 + 1, rand() % 3 + 1);
    }

  while(true){
    int choice;
    std::cout << "--------------------------------------------\n";
    std::cout << "Scegli un algoritmo di scheduling:\n";
    std::cout << "1. First Come First Served (FCFS)\n";
    std::cout << "2. Shortest Job First (SJF)\n";
    std::cout << "3. Priority Scheduling\n";
    std::cout << "4. Round Robin (RR)\n";
    std::cout << "5. Multilevel Queue Scheduling\n";
    std::cout << "6. Multilevel Feedback Queue Scheduling\n";
    std::cout << "7. Completely Fair Scheduler (CFS)\n";
    std::cout << "--\n";
    std::cout << "8. Display Processes\n";
    std::cout << "9. Clear Processes and Generate New Ones\n";
    std::cout << "0. Exit\n";
    std::cout << "--------------------------------------------\n";
    std::cout << "Enter your choice (0-9): ";
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
        case 8:
            // Mostra i processi
            displayProcesses();
            break;
        case 9:
            // Elimina
            processes.clear();
            std::cout << "Processi eliminati. ";
            //Genera nuovi processi
            generateProcesses();
            std::cout << "Nuovi processi generati.\n";
            break;
          case 0:
            std::cout << "Arrivederci.\n";
            return 0;
        default:
            std::cout << "Scelta non valida.\n";
    }
  }

    return 0;
}
