/*
Name: Duyen Vu
Date: 10/01/2023
Description: Recitation 3
*/
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <ctime>

using namespace std;

// Initialize a struct to present ticket information 
struct Ticket {
    string title;
    int urgency;
    double tps;
    time_t runningTime;

    // Constructor 
    Ticket(string T, int U, double score, time_t time)
    : title(T), urgency(U), tps(score), runningTime(time) {}
};

// Define a class to implement a priority queue for support tickets
class priorityQueue {
private:
    vector<Ticket> heap;

    // Max heap function is used after inserting an element
    void heapifyMax() {
        int current;
        current = heap.size() - 1;
        while (current > 0) {
            int root; 
            root = (current - 1) / 2;
            // Compare current tps with root tps, if curr is greater then swap current with root
            if (heap[current].tps <= heap[root].tps) {
                break;
            } else {
                swap(heap[current], heap[root]);
                current = root;
            }
        }
    }

    // Min heap function is used after resolving an element
    void heapifyMin() {
        int current = 0;
        
        while (current < heap.size()) {
            int leftChild;
            int rightChild;
            leftChild = 2 * current + 1;
            rightChild = 2 * current + 2;
            int parentRoot = current;

            if (leftChild < heap.size() && heap[leftChild].tps > heap[parentRoot].tps) {
                parentRoot = leftChild;
            }

            if (rightChild < heap.size() && heap[rightChild].tps > heap[parentRoot].tps) {
                parentRoot = rightChild;
            }

            if (parentRoot == current) {
                break;
            } else {
                swap(heap[current], heap[parentRoot]);
                current = parentRoot;
            }
        }
    }

public:
    // Insert function is used to insert a ticket
    void insert(Ticket ticket) {
        heap.push_back(ticket);
        heapifyMax();
    }

    // Function to remove the highest index
    void resolve() {
        if (heap.size() == 0) {
            printf("No tickets to resolve.\n");
            return;
        }

        Ticket resolvedTicket = heap[0];
        std::cout << "The ticket with the title" << resolvedTicket.title << " is now resolved.\n" << std::endl;

        heap[0] = heap.back();
        heap.pop_back();

        heapifyMin();
    }

    // List all the tickets
    void listTickets() {
        // Print no ticket if the heap is empty
        if (heap.empty()) { 
            printf("No tickets to display.\n");
            return;
        }

        // Else, print title, urgency, and tps of all pending tickets
        printf("List of all pending tickets:\n");
        for (const Ticket& ticket : heap) {
            cout << "Title: " << ticket.title << ", Urgency: " << ticket.urgency << ", TPS: " << ticket.tps << endl;
        }
    }
};

// Function to calculate tps
double calculateTPS(int urgency, time_t runningTime) {
    time_t currentTime = time(nullptr);
    runningTime = currentTime - runningTime;
    double TPS = ceil(pow(urgency, 3) / runningTime);
    return TPS;
}

int main() {
    priorityQueue ticketQueue;
    string title;
    int urgency;
    double tps;
    int choice;
    time_t startTime = time(nullptr);

    // Automatically print the choices until user enter 4
    while (true) {
        printf("Welcome to customer support tickets!\n");
        printf("1. Create a ticket\n");
        printf("2. Resolve a ticket\n");
        printf("3. List all tickets\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice); // Print user's choice

        switch (choice) {
            // Create a ticket
            case 1: {
                cout << "Enter ticket title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter level of urgency (1-7): ";
                cin >> urgency;

                tps = calculateTPS(urgency, startTime);
                Ticket newTicket(title, urgency, tps, startTime);
                ticketQueue.insert(newTicket);

                cout << "Ticket created and added to the queue.\n";
                break;
            }
            // Resolve a ticket
            case 2:
                ticketQueue.resolve();
                break;
            // List all pending tickets
            case 3:
                ticketQueue.listTickets();
                break;
            // Exit 
            case 4:
                cout << "Exiting the program.\n";
                return 0;
            // Else, print invalid
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}




