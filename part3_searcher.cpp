#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <signal.h>

using namespace std;

void signal_parent() {
    pid_t parent_pid = getppid(); // Get parent process ID
    if (parent_pid > 1) { // Parent exists
        cout << "[" << getpid() << "] signaling parent " << parent_pid << endl;
        kill(parent_pid, SIGTERM); // Signal parent to terminate
    }
}

int main(int argc, char **argv) {
    if(argc != 5) {
        for(int i = 0; i < argc; i++)
            cout << argv[i] << "\n";
        return -1;
    }
    
    char *file_to_search_in = argv[1];
    char *pattern_to_search_for = argv[2];
    int search_start_position = atoi(argv[3]);
    int search_end_position = atoi(argv[4]);

    ifstream file(file_to_search_in, ios::in | ios::binary);
    if(!file.is_open()) {
        cerr << "Unable to open file: " << file_to_search_in << endl;
        return 1;
    }

    int length_to_read = search_end_position - search_start_position + 1;
    char *buffer = new char[length_to_read + 1];
    file.seekg(search_start_position, ios::beg);
    file.read(buffer, length_to_read);
    buffer[length_to_read] = '\0';
    string content(buffer);
    delete[] buffer;
    file.close();

    size_t found_pos = content.find(string(pattern_to_search_for));
    if(found_pos != string::npos) {
        int process = getpid();
        cout << "[" << process << "] found at " << (search_start_position + found_pos) << endl;
        signal_parent(); // Signal parent to terminate
        return 1;
    } else {
        cout << "[" << getpid() << "] didn't find" << endl;
        return 0;
    }
}
