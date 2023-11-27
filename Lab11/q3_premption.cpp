#include <iostream>
#include <vector>

using namespace std;

const int MAX_PROCESSES = 10;
const int MAX_RESOURCES = 10;

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

int num_processes, num_resources;

bool requestResource(int process, int resource, int request) {
    if (request > need[process][resource] || request > available[resource]) {
        return false;
    }

    available[resource] -= request;
    allocation[process][resource] += request;
    need[process][resource] -= request;
    return true;
}

void releaseResource(int process, int resource) {
    available[resource] += allocation[process][resource];
    allocation[process][resource] = 0;
    need[process][resource] += maximum[process][resource];
}

bool isSafeState() {
    vector<bool> finished(num_processes, false);
    int work[MAX_RESOURCES];
    for (int i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < num_processes) {
        bool found = false;
        for (int i = 0; i < num_processes; i++) {
            if (!finished[i]) {
                bool can_allocate = true;
                for (int j = 0; j < num_resources; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate) {
                    for (int j = 0; j < num_resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    finished[i] = true;
                    found = true;
                    count++;
                }
            }
        }

        if (!found) {
            return false; // Deadlock detected
        }
    }
    return true; // System is in a safe state
}

int main() {
    cout << "Enter the number of processes: ";
    cin >> num_processes;

    cout << "Enter the number of resources: ";
    cin >> num_resources;

    cout << "Enter the available resources: ";
    for (int i = 0; i < num_resources; i++) {
        cin >> available[i];
    }

    cout << "Enter the maximum demand of each process: ";
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            cin >> maximum[i][j];
            need[i][j] = maximum[i][j];
        }
    }

    cout << "Enter the allocation of resources to each process: ";
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            cin >> allocation[i][j];
            need[i][j] -= allocation[i][j];
        }
    }

    if (isSafeState()) {
        cout << "The system is in a safe state." << endl;
    } else {
        cout << "The system is in a deadlock state." << endl;

        // Add code to preempt resources here to break the deadlock
        // You can choose a process and resource to preempt based on your strategy
        // For simplicity, you can choose the first process and resource available

        int process_to_preempt = 0;
        int resource_to_preempt = 0;

        // Preempt resources
        releaseResource(process_to_preempt, resource_to_preempt);

        if (isSafeState()) {
            cout << "Resource preemption resolved the deadlock." << endl;
        } else {
            cout << "Deadlock recovery failed." << endl;
        }
    }

    return 0;
}
