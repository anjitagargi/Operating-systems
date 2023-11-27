#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class ResourceAllocationGraph {
public:
    ResourceAllocationGraph(int numResources, int numProcesses) {
        this->numResources = numResources;
        this->numProcesses = numProcesses;

        // Initialize available resources
        availableResources.resize(numResources, 0);

        // Initialize maximum demand and allocation matrices
        maxDemand.resize(numProcesses, vector<int>(numResources, 0));
        allocation.resize(numProcesses, vector<int>(numResources, 0));
    }

    void initialize(int process, const vector<int>& maxDemand) {
        if (process < 0 || process >= numProcesses) {
            cout << "Invalid process ID." << endl;
            return;
        }

        this->maxDemand[process] = maxDemand;
    }

    bool requestResources(int process, const vector<int>& request) {
        if (process < 0 || process >= numProcesses) {
            cout << "Invalid process ID." << endl;
            return false;
        }

        // Check if the request is valid
        for (int i = 0; i < numResources; ++i) {
            if (request[i] > maxDemand[process][i] - allocation[process][i]) {
                cout << "Invalid request. Request exceeds maximum demand." << endl;
                return false;
            }
            if (request[i] > availableResources[i]) {
                cout << "Request denied. Not enough resources available." << endl;
                return false;
            }
        }

        // Try to allocate the resources
        for (int i = 0; i < numResources; ++i) {
            availableResources[i] -= request[i];
            allocation[process][i] += request[i];
            maxDemand[process][i] -= request[i];
        }

        // Check if the system is in a safe state
        if (isSafeState()) {
            cout << "Request granted. System is in a safe state." << endl;
            return true;
        } else {
            // Rollback the allocation
            for (int i = 0; i < numResources; ++i) {
                availableResources[i] += request[i];
                allocation[process][i] -= request[i];
                maxDemand[process][i] += request[i];
            }
            cout << "Request denied. Allocating resources would lead to an unsafe state." << endl;
            return false;
        }
    }

    void releaseResources(int process, const vector<int>& release) {
        if (process < 0 || process >= numProcesses) {
            cout << "Invalid process ID." << endl;
            return;
        }

        for (int i = 0; i < numResources; ++i) {
            if (release[i] > allocation[process][i]) {
                cout << "Invalid release. Process does not have these resources." << endl;
                return;
            }
        }

        // Release the resources
        for (int i = 0; i < numResources; ++i) {
            availableResources[i] += release[i];
            allocation[process][i] -= release[i];
            maxDemand[process][i] += release[i];
        }

        cout << "Resources released successfully." << endl;
    }

private:
    int numResources;
    int numProcesses;
    vector<int> availableResources;
    vector<vector<int>> maxDemand;
    vector<vector<int>> allocation;

    bool isSafeState() {
        vector<int> work = availableResources;
        vector<bool> finish(numProcesses, false);

        for (int i = 0; i < numProcesses; ++i) {
            if (finish[i]) continue;

            bool canAllocate = true;
            for (int j = 0; j < numResources; ++j) {
                if (maxDemand[i][j] - allocation[i][j] > work[j]) {
                    canAllocate = false;
                    break;
                }
            }

            if (canAllocate) {
                finish[i] = true;
                for (int j = 0; j < numResources; ++j) {
                    work[j] += allocation[i][j];
                }
                i = -1; // Restart the loop
            }
        }

        return all_of(finish.begin(), finish.end(), [](bool f) { return f; });
    }
};

int main() {
    int numResources = 3;
    int numProcesses = 5;
    ResourceAllocationGraph rag(numResources, numProcesses);

    rag.initialize(0, {7, 5, 3});
    rag.initialize(1, {3, 2, 2});
    rag.initialize(2, {9, 0, 2});
    rag.initialize(3, {2, 2, 2});
    rag.initialize(4, {4, 3, 3});

    rag.requestResources(0, {0, 1, 0});
    rag.requestResources(1, {2, 0, 0});
    rag.requestResources(2, {3, 0, 2});
    rag.requestResources(3, {2, 1, 1});
    rag.requestResources(4, {0, 0, 2});

    rag.releaseResources(0, {0, 1, 0});
    rag.releaseResources(1, {2, 0, 0});
    rag.releaseResources(2, {3, 0, 2});
    rag.releaseResources(3, {2, 1, 1});
    rag.releaseResources(4, {0, 0, 2});

//    ResourceAllocationGraph rag(numResources, numProcesses);

    return 0;
}

