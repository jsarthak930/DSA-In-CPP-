
#include <iostream>
using namespace std;

struct Process {
    int id;
    int burstTime;
    int remainingTime;
    Process* next;
};

Process* head = NULL;

void addProcess(int id, int burst) {
    Process* newNode = new Process;
    newNode->id = id;
    newNode->burstTime = burst;
    newNode->remainingTime = burst;

    if (head == NULL) {
        head = newNode;
        newNode->next = head;
    } else {
        Process* temp = head;

        while (temp->next != head) {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->next = head;
    }
}

void roundRobin(int quantum) {
    if (head == NULL) {
        cout << "No processes available." << endl;
        return;
    }

    Process* current = head;
    int completed;

    cout << "\nProcess Execution Order:" << endl;

    do {
        completed = 1;
        Process* temp = head;

        do {
            if (temp->remainingTime > 0) {
                completed = 0;
                break;
            }
            temp = temp->next;
        } while (temp != head);

        if (completed == 1)
            break;

        if (current->remainingTime > 0) {
            cout << "P" << current->id << " executes for ";

            if (current->remainingTime > quantum) {
                cout << quantum << " units" << endl;
                current->remainingTime -= quantum;
            } else {
                cout << current->remainingTime << " units (Completed)"
                     << endl;
                current->remainingTime = 0;
            }
        }

        current = current->next;

    } while (true);

    cout << "\nAll processes completed." << endl;
}

int main() {
    int n, burst, quantum;

    cout << "Enter number of processes: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of processes." << endl;
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        cout << "Enter burst time for P" << i << ": ";
        cin >> burst;

        if (burst <= 0) {
            cout << "Burst time must be positive." << endl;
            return 0;
        }

        addProcess(i, burst);
    }

    cout << "Enter time quantum: ";
    cin >> quantum;

    if (quantum <= 0) {
        cout << "Time quantum must be positive." << endl;
        return 0;
    }

    roundRobin(quantum);

    return 0;
}

