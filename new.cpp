// #include <iostream>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <cstdlib>
// #include <cstring>

// using namespace std;

// void print_status(pid_t my_pid, const char* msg) {
//     cout << "[" << my_pid << "] " << msg << endl;
// }

// int main(int argc, char **argv) {
//     if (argc != 6) {
//         cout << "usage: ./partitioner.out <path-to-file> <pattern> <search-start-position> <search-end-position> <max-chunk-size>\n";
//         return -1;
//     }

//     char *file_to_search_in = argv[1];
//     char *pattern_to_search_for = argv[2];
//     int search_start_position = atoi(argv[3]);
//     int search_end_position = atoi(argv[4]);
//     int max_chunk_size = atoi(argv[5]);
//     pid_t my_pid = getpid();

//     int chunk_size = (search_end_position - search_start_position) + 1;
//     print_status(my_pid, ("start position = " + to_string(search_start_position) + " ; end position = " + to_string(search_end_position)).c_str());

//     if (chunk_size <= max_chunk_size) {
//         pid_t searcher_pid = fork();
//         if (searcher_pid == 0) {
//             // In child process
//             if (execlp("./part2_searcher.out", "part2_searcher.out", file_to_search_in, pattern_to_search_for, to_string(search_start_position).c_str(), to_string(search_end_position).c_str(), NULL) == -1) {
//                 perror("execlp failed");
//                 exit(1);
//             }
//         } else if (searcher_pid > 0) {
//             // In parent process
//             print_status(my_pid, ("forked searcher child " + to_string(searcher_pid)).c_str());
//             int status;
//             waitpid(searcher_pid, &status, 0);
//             if (WIFEXITED(status)) {
//                 print_status(my_pid, "searcher child returned");
//             } else {
//                 print_status(my_pid, "searcher child terminated abnormally");
//             }
//         } else {
//             perror("fork failed");
//         }
//     } else {
//         int middle_position = (search_start_position + search_end_position) / 2;

//         pid_t left_child = fork();
//         if (left_child == 0) {
//             // Left child
//             if (execlp("./part2_searcher.out", "part2_searcher.out", file_to_search_in, pattern_to_search_for, to_string(search_start_position).c_str(), to_string(middle_position).c_str(), NULL) == -1) {
//                 perror("execlp failed");
//                 exit(1);
//             }
//         } else if (left_child > 0) {
//             print_status(my_pid, ("forked left child " + to_string(left_child)).c_str());
//             pid_t right_child = fork();
//             if (right_child == 0) {
//                 // Right child
//                 if (execlp("./part2_searcher.out", "part2_searcher.out", file_to_search_in, pattern_to_search_for, to_string(middle_position + 1).c_str(), to_string(search_end_position).c_str(), NULL) == -1) {
//                     perror("execlp failed");
//                     exit(1);
//                 }
//             } else if (right_child > 0) {
//                 print_status(my_pid, ("forked right child " + to_string(right_child)).c_str());
                
//                 int status;
//                 waitpid(left_child, &status, 0);
//                 if (WIFEXITED(status)) {
//                     print_status(my_pid, "left child returned");
//                 } else {
//                     print_status(my_pid, "left child terminated abnormally");
//                 }

//                 waitpid(right_child, &status, 0);
//                 if (WIFEXITED(status)) {
//                     print_status(my_pid, "right child returned");
//                 } else {
//                     print_status(my_pid, "right child terminated abnormally");
//                 }
//             } else {
//                 perror("fork failed");
//             }
//         } else {
//             perror("fork failed");
//         }
//     }
//     return 0;
// }
//  my_pid << "] searcher child returned \n";
// 	//cout << "[" << my_pid << "] received SIGTERM\n"; //applicable for Part III of the assignment
// 	}
// 	return 0;
// }


// #include <iostream>
// #include <fstream>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <cstring>
// #include <cstdlib>

// using namespace std;

// int main(int argc, char **argv)
// {
//     if (argc != 6) {
//         cout << "usage: ./partitioner.out <path-to-file> <pattern> <search-start-position> <search-end-position> <max-chunk-size>\n";
//         return -1;
//     }

//     char *file_to_search_in = argv[1];
//     char *pattern_to_search_for = argv[2];
//     int search_start_position = atoi(argv[3]);
//     int search_end_position = atoi(argv[4]);
//     int max_chunk_size = atoi(argv[5]);
//     pid_t my_pid = getpid();
    
//     int chunk_size = (search_end_position - search_start_position) + 1;

//     if (chunk_size <= max_chunk_size) {
//         pid_t searcher_pid = fork();
//         if (searcher_pid == 0) {
//             // In child process
//             if (execlp("./part2_searcher.out", "part2_searcher.out", file_to_search_in, pattern_to_search_for, to_string(search_start_position).c_str(), to_string(search_end_position).c_str(), NULL) == -1) {
//                 perror("execlp failed");
//                 exit(1);
//             }
//         } else if (searcher_pid > 0) {
//             // In parent process
//             cout << "[" << my_pid << "] forked searcher child " << searcher_pid << "\n";
//             int status;
//             waitpid(searcher_pid, &status, 0);
//             if (WIFEXITED(status)) {
//                 cout << "[" << my_pid << "] searcher child exited with status " << WEXITSTATUS(status) << "\n";
//             } else {
//                 cout << "[" << my_pid << "] searcher child terminated abnormally\n";
//             }
//         } else {
//             perror("fork failed");
//         }
//     } else {
//         int middle_position = (search_start_position + search_end_position) / 2;
        
//         pid_t left_child = fork();
//         if (left_child == 0) {
//             // Left child
//             if (execlp("./part2_searcher.out", "part2_searcher.out", file_to_search_in, pattern_to_search_for, to_string(search_start_position).c_str(), to_string(middle_position).c_str(), NULL) == -1) {
//                 perror("execlp failed");
//                 exit(1);
//             }
//         } else if (left_child > 0) {
//             cout << "[" << my_pid << "] forked left child " << left_child << "\n";
//             int status;
//             waitpid(left_child, &status, 0);
//             if (WIFEXITED(status)) {
//                 cout << "[" << my_pid << "] left child exited with status " << WEXITSTATUS(status) << "\n";
//             } else {
//                 cout << "[" << my_pid << "] left child terminated abnormally\n";
//             }

//             pid_t right_child = fork();
//             if (right_child == 0) {
//                 // Right child
//                 if (execlp("./part2_searcher.out", "part2_searcher.out", file_to_search_in, pattern_to_search_for, to_string(middle_position + 1).c_str(), to_string(search_end_position).c_str(), NULL) == -1) {
//                     perror("execlp failed");
//                     exit(1);
//                 }
//             } else if (right_child > 0) {
//                 cout << "[" << my_pid << "] forked right child " << right_child << "\n";
//                 waitpid(right_child, &status, 0);
//                 if (WIFEXITED(status)) {
//                     cout << "[" << my_pid << "] right child exited with status " << WEXITSTATUS(status) << "\n";
//                 } else {
//                     cout << "[" << my_pid << "] right child terminated abnormally\n";
//                 }
//             } else {
//                 perror("fork failed");
//             }
//         } else {
//             perror("fork failed");
//         }
//     }
//     return 0;
// }

// #include <iostream>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <cstdlib>
// #include <cstring>

// using namespace std;

// void print_status(pid_t my_pid, const char* msg) {
//     cout << "[" << my_pid << "] " << msg << endl;
// }

// int main(int argc, char **argv) {
//     if (argc != 6) {
//         cout << "usage: ./partitioner.out <path-to-file> <pattern> <search-start-position> <search-end-position> <max-chunk-size>\n";
//         return -1;
//     }

//     char *file_to_search_in = argv[1];
//     char *pattern_to_search_for = argv[2];
//     int search_start_position = atoi(argv[3]);
//     int search_end_position = atoi(argv[4]);
//     int max_chunk_size = atoi(argv[5]);
//     pid_t my_pid = getpid();

//     int chunk_size = (search_end_position - search_start_position) + 1;
//     print_status(my_pid, ("start position = " + to_string(search_start_position) + " ; end position = " + to_string(search_end_position)).c_str());

//     if (chunk_size <= max_chunk_size) {
//         pid_t searcher_pid = fork();
//         if (searcher_pid == 0) {
//             // In child process
//             if (execlp("./part2_searcher.out", "part2_searcher.out", file_to_search_in, pattern_to_search_for, to_string(search_start_position).c_str(), to_string(search_end_position).c_str(), NULL) == -1) {
//                 perror("execlp failed");
//                 exit(1);
//             }
//         } else if (searcher_pid > 0) {
//             // In parent process
//             print_status(my_pid, ("forked searcher child " + to_string(searcher_pid)).c_str());
//             int status;
//             waitpid(searcher_pid, &status, 0);
//             if (WIFEXITED(status)) {
//                 print_status(my_pid, "searcher child returned");
//             } else {
//                 print_status(my_pid, "searcher child terminated abnormally");
//             }
//         } else {
//             perror("fork failed");
//         }
//     } else {
//         int middle_position = (search_start_position + search_end_position) / 2;

//         pid_t left_child = fork();
//         if (left_child == 0) {
//             // Left child
//             if (execlp("./part2_searcher.out", "part2_searcher.out", file_to_search_in, pattern_to_search_for, to_string(search_start_position).c_str(), to_string(middle_position).c_str(), NULL) == -1) {
//                 perror("execlp failed");
//                 exit(1);
//             }
//         } else if (left_child > 0) {
//             print_status(my_pid, ("forked left child " + to_string(left_child)).c_str());
//             pid_t right_child = fork();
//             if (right_child == 0) {
//                 // Right child
//                 if (execlp("./part2_searcher.out", "part2_searcher.out", file_to_search_in, pattern_to_search_for, to_string(middle_position + 1).c_str(), to_string(search_end_position).c_str(), NULL) == -1) {
//                     perror("execlp failed");
//                     exit(1);
//                 }
//             } else if (right_child > 0) {
//                 print_status(my_pid, ("forked right child " + to_string(right_child)).c_str());
                
//                 int status;
//                 waitpid(left_child, &status, 0);
//                 if (WIFEXITED(status)) {
//                     print_status(my_pid, "left child returned");
//                 } else {
//                     print_status(my_pid, "left child terminated abnormally");
//                 }

//                 waitpid(right_child, &status, 0);
//                 if (WIFEXITED(status)) {
//                     print_status(my_pid, "right child returned");
//                 } else {
//                     print_status(my_pid, "right child terminated abnormally");
//                 }
//             } else {
//                 perror("fork failed");
//             }
//         } else {
//             perror("fork failed");
//         }
//     }
//     return 0;
// }

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <cstring>

using namespace std;

void print_status(pid_t my_pid, const char* msg) {
    cout << "[" << my_pid << "] " << msg << endl;
}

int main(int argc, char **argv) {
    if (argc != 6) {
        cout << "usage: ./partitioner.out <path-to-file> <pattern> <search-start-position> <search-end-position> <max-chunk-size>\n";
        return -1;
    }

    char *file_to_search_in = argv[1];
    char *pattern_to_search_for = argv[2];
    int search_start_position = atoi(argv[3]);
    int search_end_position = atoi(argv[4]);
    int max_chunk_size = atoi(argv[5]);
    pid_t my_pid = getpid();

    int chunk_size = (search_end_position - search_start_position) + 1;
    print_status(my_pid, ("start position = " + to_string(search_start_position) + " ; end position = " + to_string(search_end_position)).c_str());

    if (chunk_size <= max_chunk_size) {
        pid_t searcher_pid = fork();
        if (searcher_pid == 0) {
            // In child process
            if (execlp("./part2_searcher.out", "part2_searcher.out", file_to_search_in, pattern_to_search_for, to_string(search_start_position).c_str(), to_string(search_end_position).c_str(), NULL) == -1) {
                perror("execlp failed");
                exit(1);
            }
        } else if (searcher_pid > 0) {
            // In parent process
            print_status(my_pid, ("forked searcher child " + to_string(searcher_pid)).c_str());
            int status;
            waitpid(searcher_pid, &status, 0);
            if (WIFEXITED(status)) {
                print_status(my_pid, "searcher child returned");
            } else {
                print_status(my_pid, "searcher child terminated abnormally");
            }
        } else {
            perror("fork failed");
        }
    } else {
        int middle_position = (search_start_position + search_end_position) / 2;

        pid_t left_child = fork();
        if (left_child == 0) {
            // Left child
            if (execlp("./part2_searcher.out", "part2_searcher.out", file_to_search_in, pattern_to_search_for, to_string(search_start_position).c_str(), to_string(middle_position).c_str(), NULL) == -1) {
                perror("execlp failed");
                exit(1);
            }
        } else if (left_child > 0) {
            print_status(my_pid, ("forked left child " + to_string(left_child)).c_str());
            pid_t right_child = fork();
            if (right_child == 0) {
                // Right child
                if (execlp("./part2_searcher.out", "part2_searcher.out", file_to_search_in, pattern_to_search_for, to_string(middle_position + 1).c_str(), to_string(search_end_position).c_str(), NULL) == -1) {
                    perror("execlp failed");
                    exit(1);
                }
            } else if (right_child > 0) {
                print_status(my_pid, ("forked right child " + to_string(right_child)).c_str());
                
                int status;
                waitpid(left_child, &status, 0);
                if (WIFEXITED(status)) {
                    print_status(my_pid, "left child returned");
                } else {
                    print_status(my_pid, "left child terminated abnormally");
                }

                waitpid(right_child, &status, 0);
                if (WIFEXITED(status)) {
                    print_status(my_pid, "right child returned");
                } else {
                    print_status(my_pid, "right child terminated abnormally");
                }
            } else {
                perror("fork failed");
            }
        } else {
            perror("fork failed");
        }
    }
    return 0;
}
