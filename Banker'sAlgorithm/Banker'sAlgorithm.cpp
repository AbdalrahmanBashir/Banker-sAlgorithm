// Banker'sAlgorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm>

// Define a struct to store information about the system's state.
struct BankerData {
    int num_processes = 0; // The number of processes in the system.
    int num_resources = 0; // The number of different types of resources in the system.
    std::vector<int> available; // A vector representing the available instances of each resource type.
    std::vector<std::vector<int>> allocation; // A 2D vector representing the resources currently allocated to each 
    std::vector<std::vector<int>> max; // A 2D vector representing the maximum resources each process may need.
    std::vector<std::vector<int>> need; //  A 2D vector representing the remaining resources each process needs
   
};

void initializeData(BankerData& data);
bool isSafe(const BankerData& data);


int main()
{
    BankerData data;
    initializeData(data);
    if (!isSafe(data)) {
        std::cout << "System is in an unsafe state." << std::endl;
    }

}
// Function to initialize the data for the system.
void initializeData(BankerData& data) {
    std::cout << "Enter the number of processes: ";
    std::cin >> data.num_processes;
    std::cout << "Enter the number of resources: ";
    std::cin >> data.num_resources;

    // Resize vectors to store data for each process and resource
    data.available.resize(data.num_resources);
    data.allocation.resize(data.num_processes, std::vector<int>(data.num_resources));
    data.max.resize(data.num_processes, std::vector<int>(data.num_resources));
    data.need.resize(data.num_processes, std::vector<int>(data.num_resources));

    // Initialize available resources
    std::cout << "Enter the available resources:" << std::endl;
    for (int i = 0; i < data.num_resources; i++) {
        std::cin >> data.available[i];
    }

    // Initialize allocation matrix
    std::cout << "Enter the allocation matrix:" << std::endl;
    for (int i = 0; i < data.num_processes; i++) {
        std::cout << "For Process " << i << ":" << std::endl;
        for (int j = 0; j < data.num_resources; j++) {
            std::cin >> data.allocation[i][j];
        }
       
    }

    // Initialize max matrix
    std::cout << "Enter the max matrix:" << std::endl;
    for (int i = 0; i < data.num_processes; i++) {
        std::cout << "For Process " << i << ":" << std::endl;
        for (int j = 0; j < data.num_resources; j++) {
            std::cin >> data.max[i][j];
            data.need[i][j] = data.max[i][j] - data.allocation[i][j];
        }
    }
}

// Function to check if the system is in a safe state using Banker's algorithm.
bool isSafe(const BankerData& data) {
    std::vector<int> work(data.available);
    std::vector<bool> finish(data.num_processes, false);
    std::vector<int> safe_sequence;
    int count = 0;
    // Iterate until all processes are marked as finished or no safe sequence is found.
    while (count < data.num_processes) {
        bool is_sequence_found = false;
        for (int i = 0; i < data.num_processes; i++) {
            if (!finish[i]) {
                bool is_possible_to_allocation_resource = true;
                // Check if resources can be allocated to the process
                for (int j = 0; j < data.num_resources; j++) {
                    if (data.need[i][j] > work[j]) {
                        is_possible_to_allocation_resource = false;
                        break;
                    }
                }
                // If resources can be allocated, update work vector and mark the process as finished.
                if (is_possible_to_allocation_resource) {
                    for (int j = 0; j < data.num_resources; j++) {
                        work[j] += data.allocation[i][j];
                    }
                    finish[i] = true;
                    is_sequence_found = true;
                    safe_sequence.push_back(i);
                    count++;

                }
            }
        }
        // If no safe sequence is found, return false
        if (!is_sequence_found) {
            return false;
        }


    }
    std::cout << "System is in a safe state. Safe sequence: ";
    for (int i = 0; i < data.num_processes - 1; i++) {
        std::cout << "P" << safe_sequence[i] << " -> ";
    }
    std::cout << "P" << safe_sequence[data.num_processes - 1] << std::endl;
    return true;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
