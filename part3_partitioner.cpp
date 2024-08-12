#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

using namespace std;

void terminate(int sig) {
    cout << "[" << getpid() << "] received SIGTERM" << endl;
    // Terminate all children
    kill(0, SIGTERM);  // Send SIGTERM to all processes in the process group
    exit(0); // Terminate this process
}

void partition_and_search(const char* file_to_search_in, const char* pattern_to_search_for, int search_start_position, int search_end_position, int max_chunk_size) {
    pid_t my_pid = getpid();
    int chunk_size = (search_end_position - search_start_position) + 1;

    cout << "[" << my_pid << "] start position = " << search_start_position << " ; end position = " << search_end_position << "\n";

    if(chunk_size <= max_chunk_size) {
        pid_t searcher_pid = fork();
        if(searcher_pid == 0) {
            execlp("./part3_searcher.out", "./part3_searcher.out", file_to_search_in, pattern_to_search_for, 
                   to_string(search_start_position).c_str(), to_string(search_end_position).c_str(), NULL);
            perror("error in execlp call!!");
            exit(1);
        } else if(searcher_pid > 0) {
            cout << '[' << my_pid << ']' << " forked the searcher child: " << searcher_pid << endl;
            int status;
            waitpid(searcher_pid, &status, 0);
            cout << '[' << my_pid << ']' << " searcher child returned with status: " << status << endl;
        }
    } else {
        int middle_position = (search_start_position + search_end_position) / 2;
        pid_t left_child = fork();
        if(left_child == 0) {
            partition_and_search(file_to_search_in, pattern_to_search_for, search_start_position, middle_position, max_chunk_size);
            exit(0);
        } else if(left_child > 0) {
            cout << '[' << my_pid << ']' << " forked the left_child: " << left_child << endl;

            pid_t right_child = fork();
            if(right_child == 0) {
                partition_and_search(file_to_search_in, pattern_to_search_for, middle_position + 1, search_end_position, max_chunk_size);
                exit(0);
            } else if(right_child > 0) {
                cout << '[' << my_pid << ']' << " forked the right_child: " << right_child << endl;

                int status;
                while ((waitpid(left_child, &status, WNOHANG)) == 0 && (waitpid(right_child, &status, WNOHANG)) == 0) {
                    // Do nothing, just wait for children to terminate or receive SIGTERM
                }
                waitpid(left_child, &status, 0);
                cout << '[' << my_pid << ']' << " left child returned with status: " << status << endl;

                waitpid(right_child, &status, 0);
                cout << '[' << my_pid << ']' << " right child returned with status: " << status << endl;
            }
        }
    }
}

int main(int argc, char **argv) {
    signal(SIGTERM, terminate); // Register signal handler for the SIGTERM signal

    if(argc != 6) {
        cout << "usage: ./partitioner.out <path-to-file> <pattern> <search-start-position> <search-end-position> <max-chunk-size>\nprovided arguments:\n";
        for(int i = 0; i < argc; i++)
            cout << argv[i] << "\n";
        return -1;
    }

    char *file_to_search_in = argv[1];
    char *pattern_to_search_for = argv[2];
    int search_start_position = atoi(argv[3]);
    int search_end_position = atoi(argv[4]);
    int max_chunk_size = atoi(argv[5]);

    partition_and_search(file_to_search_in, pattern_to_search_for, search_start_position, search_end_position, max_chunk_size);
    return 0;
}
