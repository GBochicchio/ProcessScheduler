#include <iostream>
#include <vector>
#include <ctime> // Libreria per utilizzare time()
#include <algorithm> // Per utilizzare std::sort

const int QUANTUM = 4; // Quantum per l'algoritmo di Round Robin

class Process {
public:
    int pid;
    int burst_time;
    int priority;

    Process(int pid, int burst_time, int priority)
        : pid(pid), burst_time(burst_time), priority(priority) {}
};

std::vector<Process> generateProcesses(int num_processes) {
    srand(time(nullptr)); // Imposta il seme iniziale basato sull'ora di sistema
    std::vector<Process> processes;

    // Genera nuovi processi
    for (int i = 0; i < num_processes; i++) {
        processes.emplace_back(i, rand() % 20 + 1, rand() % 3 + 1);
    }

    return processes;
}

void displayProcesses(const std::vector<Process>& processes) {
    int N = processes.size(); //Numero di processi
    std::cout << "ID\tBurst Time\tPriority" << std::endl;
    std::cout << "--------------------------------" << std::endl;

    for (int i = 0; i < N; i++) {
      std::cout << processes[i].pid << "\t" << processes[i].burst_time << "\t\t" << processes[i].priority << std::endl;
    }
}

double total_burst_time(const std::vector<Process>& processes) {
    double total_burst_time = 0;
    for (const auto& process : processes) {
        total_burst_time += process.burst_time;
    }
    return total_burst_time;
}

double first_come_first_served(const std::vector<Process>& processes) {
    int N = processes.size(); //Numero di processi
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
    return avg_waiting_time;
}

bool compareByBurstTime(const Process& a, const Process& b) {
    return a.burst_time < b.burst_time;
}

double shortest_job_first(const std::vector<Process>& processes) {
  int N = processes.size(); //Numero di processi
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
  return avg_waiting_time;
}

double priority_scheduling(const std::vector<Process>& processes) {
  int N = processes.size(); //Numero di processi
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
  return avg_waiting_time;
}

double round_robin(const std::vector<Process>& processes) {
int N = processes.size(); //Numero di processi
  // Inizializza il tempo di attesa e il tempo di completamento per tutti i processi
std::vector<int> waiting_time(N, 0);
std::vector<int> completion_time(N, 0);

// Crea una copia del burst time
std::vector<int> remaining_burst_time(N);
for (int i = 0; i < N; i++) {
    remaining_burst_time[i] = processes[i].burst_time;
}

int time = 0; // L'attuale tempo di sistema

// Continua a eseguire i processi nella coda finché tutti non sono completati
while (true) {
    bool done = true;

    // Esegui tutti i processi uno per uno
    for (int i = 0; i < N; i++) {
        // Se il burst time del processo è maggiore di 0, allora il processo non è ancora completato
        if (remaining_burst_time[i] > 0) {
            done = false; // Esiste ancora un processo in attesa

            if (remaining_burst_time[i] > QUANTUM) {
                // Aumenta il tempo di sistema di un quantum di tempo
                time += QUANTUM;

                // Decrementa il burst time del processo di un quantum di tempo
                remaining_burst_time[i] -= QUANTUM;
            } else {
                // Aumenta il tempo di sistema del burst time rimanente del processo
                time += remaining_burst_time[i];

                // Il tempo di attesa è il tempo di sistema meno il burst time del processo
                waiting_time[i] = time - processes[i].burst_time;

                // Il burst time rimanente del processo diventa 0
                remaining_burst_time[i] = 0;
            }
        }
    }

    // Se tutti i processi sono completati
    if (done == true)
        break;
}

// Calcola il tempo di attesa medio
double avg_waiting_time = 0;
for (int i = 0; i < N; i++) {
    avg_waiting_time += waiting_time[i];
}
avg_waiting_time /= N;

// Visualizza il risultato dello scheduling
std::cout << "Round Robin Scheduling:\n";
std::cout << "Process\tBurst Time\tPriority\tWaiting Time\n";
for (int i = 0; i < N; i++) {
    std::cout << processes[i].pid << "\t" << processes[i].burst_time << "\t\t"
              << processes[i].priority << "\t\t" << waiting_time[i] << "\n";
}
std::cout << "Average Waiting Time: " << avg_waiting_time << "\n";
return avg_waiting_time;
}

double multilevel_queue_scheduling(const std::vector<Process>& processes) {
    int N = processes.size(); //Numero di processi
    std::vector<std::vector<Process>> queues(3); // Creazione di 3 vettori

    // Distribuzione casuale dei processi nelle code
    srand(time(nullptr)); // Imposta il seme iniziale basato sull'ora di sistema
    for (const auto& process : processes) {
        int queue_number = rand() % 3; // Genera un numero casuale tra 0 e 2
        queues[queue_number].push_back(process); // Aggiungi processo al vettore
    }

    // Esecuzione dei processi in ogni coda utilizzando un algoritmo di scheduling diverso
    // Coda 0: Round Robin
    // Coda 1: First Come First Served (FCFS)
    // Coda 2: Shortest Job First (SJF)
    std::cout << "--------------------------------------------\n";
    std::cout << "Coda 0: Round Robin.\n";
    double avg_waiting_time_0 = 0;
    avg_waiting_time_0 += round_robin(queues[0]);
    double total_burst_time_0 = total_burst_time(queues[0]); // calcola il tempo totale di burst per la coda 0
    std::cout << "--------------------------------------------\n";
    std::cout << "Coda 1: First Come First Served (FCFS).\n";
    double avg_waiting_time_1 = 0;
    avg_waiting_time_1 += first_come_first_served(queues[1]) + (total_burst_time_0 * queues[1].size()); // aggiungi il tempo totale di burst della coda 0 al tempo di attesa di ogni processo della coda 1
    std::cout << "Average Waiting Time (including the previous queue): " << avg_waiting_time_1 << "\n";
    double total_burst_time_1 = total_burst_time(queues[1]); // calcola il tempo totale di burst per la coda 1
    std::cout << "--------------------------------------------\n";
    std::cout << "Coda 2: Shortest Job First (SJF).\n";
    double avg_waiting_time_2 = 0;
    avg_waiting_time_2 += shortest_job_first(queues[2]) + (total_burst_time_0 * queues[1].size()) + (total_burst_time_1 * queues[2].size()); // aggiungi i tempi totali di burst delle code 0 e 1 al tempo di attesa della coda 2
    std::cout << "Average Waiting Time (including the previous queues): " << avg_waiting_time_2 << "\n";
    std::cout << "--------------------------------------------\n";

    double total_waiting_time = avg_waiting_time_0 + avg_waiting_time_1 + avg_waiting_time_2; // Calcola il tempo di attesa totale complessivo
    double avg_waiting_time = total_waiting_time / 3; // Calcola il tempo di attesa medio complessivo
    std::cout << "Average Waiting Time: " << avg_waiting_time << "\n";
    return avg_waiting_time;
}

int main() {
    srand(time(nullptr)); // Imposta il seme iniziale basato sull'ora di sistema

    // Inizializzazione dei processi
    std::vector<Process> processes = generateProcesses(10);

  while(true){
    int choice;
    do {
      std::cout << "\n\n";
      std::cout << "--------------------------------------------\n";
      std::cout << "Choose a scheduling algorithm:\n";
      std::cout << "1. First Come First Served (FCFS)\n";
      std::cout << "2. Shortest Job First (SJF)\n";
      std::cout << "3. Priority Scheduling\n";
      std::cout << "4. Round Robin (RR)\n";
      std::cout << "5. Multilevel Queue Scheduling\n";
      std::cout << "--\n";
      std::cout << "8. Display Processes\n";
      std::cout << "9. Clear Processes and Generate New Ones\n";
      std::cout << "0. Exit\n";
      std::cout << "--------------------------------------------\n";
      std::cout << "Enter your choice (0-9): ";
      std::cin >> choice;
      std::cout << "\n\n";

      // Controllo sull'input
      if (std::cin.fail() || choice == 6 || choice == 7 || choice < 1 || choice > 9) {
          std::cout << "Invalid option! Please enter another option, choose from the menu above.\n";

          // Pulisci lo stato di errore di std::cin
          std::cin.clear();

          // Rimuovi eventuali caratteri residui dal buffer di input
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }

    } while (std::cin.fail() || choice == 6 || choice == 7 || choice < 1 || choice > 9);

    switch (choice) {
        case 1:
            first_come_first_served(processes);
            break;
        case 2:
            shortest_job_first(processes);
            break;
        case 3:
            priority_scheduling(processes);
            break;
        case 4:
            round_robin(processes);
            break;
        case 5:
            multilevel_queue_scheduling(processes);
            break;
        case 8:
            // Mostra i processi
            displayProcesses(processes);
            break;
        case 9:
            // Elimina
            processes.clear();
            std::cout << "Processes deleted. ";
            //Genera nuovi processi
            processes = generateProcesses(10);
            std::cout << "New processes generated.\n";
            break;
          case 0:
            std::cout << "Goodbye.\n";
            return 0;
        default:
            std::cout << "Scelta non valida.\n";
    }
  }

    return 0;
}
