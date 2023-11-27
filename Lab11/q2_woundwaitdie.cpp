    #include <iostream>
    #include <vector>
    #include <algorithm>

    using namespace std;

    class Resource {
    public:
        int available;

        Resource(int initial) : available(initial) {}

        bool allocate(int request) {
            if (available >= request) {
                available -= request;
                return true;
            }
            return false;
        }

        void deallocate(int release) {
            available += release;
        }
    };

    class Process {
    public:
        int id;

        Process(int pid) : id(pid) {}

        bool requestResource(Resource& resource, int request) {
            if (resource.allocate(request)) {
                cout << "Process P" << id << " has acquired the resource." << endl;
                return true;
            }
            cout << "Process P" << id << " is waiting for the resource." << endl;
            return false;
        }

        void releaseResource(Resource& resource, int release) {
            resource.deallocate(release);
            cout << "Process P" << id << " has released the resource." << endl;
        }
    };

    int main() {
        Resource resource(1);
        vector<Process> processes;

        processes.emplace_back(1);
        processes.emplace_back(2);
        processes.emplace_back(3);

        // Process 2 requests the resource
        if (!processes[1].requestResource(resource, 1)) {
            // Process 2 is waiting, while younger Process 1 requests the resource
            if (!processes[0].requestResource(resource, 1)) {
                // Process 1 is aborted because it's younger
                cout << "Process P1 is aborted." << endl;
                processes[1].releaseResource(resource, 1); // Release the resource acquired by Process 2
            }
        }

        return 0;
    }

