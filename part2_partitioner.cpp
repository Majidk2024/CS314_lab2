// #include <iostream>
// #include <fstream>
// #include <unistd.h>
// #include <sys/wait.h>
// #include <signal.h>

// using namespace std;


// 	//TODO
// void partition_and_search(const char* file_to_search_in, const char* pattern_to_search_for, int search_start_position, int search_end_position, int max_chunk_size){

// 	pid_t my_pid = getpid();
// 	//we have to initialize the current chunk_size for compairing with the max chunk_size we have
// 	int chunk_size = (search_end_position - search_start_position) + 1;
// 	// now we have to note the start and end positions
// 	cout << "[" << my_pid << "] start position = " << search_start_position << " ; end position = " << search_end_position << "\n";
// 	//now we will check the current chunk size is lesser to our max chunk size
// 	if(chunk_size <= max_chunk_size){
// 		pid_t searcher_pid = fork();
// 		//now after forking seacher_pid will have 0,-1 and getpid() so we will utilize it here traverse through the processes
// 		if(searcher_pid == 0){
// 			execlp("/home/majid/Desktop/lab2/src/part2_searcher.out", "./part2_searcher.out", file_to_search_in, pattern_to_search_for, to_string(search_start_position).c_str(), to_string(search_end_position).c_str(), NULL);
// 			perror("error in the first execlp call!!");
// 			exit(1);
// 		}else if(searcher_pid >= 0){
// 			// this gives information thst the child process is on execution so the parent has to wait
// 			cout<< '['<< my_pid << ']' << "forked the searcher child : " << searcher_pid << endl;
// 			int status;
// 			waitpid(searcher_pid, &status, 0 );
// 			cout<< '[' << status << ']' << "searcher child returned" << endl;
// 		}
// 	}else{
// 		// now we are going for the else part where the chunk exceeds the 32byte limit and we have to partition it for searching
// 		int middle_position = (search_start_position + search_end_position) / 2;
// 		pid_t left_child = fork();
// 		if(left_child == 0){
// 			// it means that the parent process is itself and has to handle the search process on the chunk
// 			partition_and_search(file_to_search_in, pattern_to_search_for, search_start_position, middle_position, max_chunk_size);
//             exit(0);
// 	} else if(left_child > 0){
// 		// there is another child process running and needs to wait
// 		cout << '[' << my_pid << ']' << "forked the left_child " << left_child << endl;
// 		int status;
// 		waitpid(left_child, &status, 0);
// 		cout << "left child returned with status: " << status << endl; 
// 	}else{
// 	pid_t right_child = fork();
// 	if(right_child == 0){
// 		//now the right child deals with the execution
// 		partition_and_search(file_to_search_in, pattern_to_search_for, middle_position, search_end_position, max_chunk_size);
//         exit(0);
// 	}else if(right_child > 0){
// 		// the parent again has to wait for the right child to complete
// 		int status;
// 		waitpid(right_child, &status, 0);
// 		cout << "right child returned: \n" << status << endl; 
// 	}
// 	}
	
// 	}
// }

// // 	//cout << "[" << my_pid << "] start position = " << search_start_position << " ; end position = " << search_end_position << "\n";
// // 	//cout << "[" << my_pid << "] forked left child " << my_children[0] << "\n";
// // 	//cout << "[" << my_pid << "] forked right child " << my_children[1] << "\n";
// // 	//cout << "[" << my_pid << "] left child returned\n";
// // 	//cout << "[" << my_pid << "] right child returned\n";
// // 	//cout << "[" << my_pid << "] left child returned\n";
// // 	//cout << "[" << my_pid << "] right child returned\n";*/
// // 	//cout << "[" << my_pid << "] forked searcher child " << searcher_pid << "\n";
// // 	//cout << "[" <<


// int main(int argc, char **argv)
// {
// 	if(argc != 6)
// 	{
// 		cout <<"usage: ./partitioner.out <path-to-file> <pattern> <search-start-position> <search-end-position> <max-chunk-size>\nprovided arguments:\n";
// 		for(int i = 0; i < argc; i++)
// 			cout << argv[i] << "\n";
// 		return -1;
// 	}
	
// 	char *file_to_search_in = argv[1];
// 	char *pattern_to_search_for = argv[2];
// 	int search_start_position = atoi(argv[3]);
// 	int search_end_position = atoi(argv[4]);
// 	int max_chunk_size = atoi(argv[5]);
	

// 	partition_and_search(file_to_search_in, pattern_to_search_for, search_start_position, search_start_position, max_chunk_size);
// 	return 0;
// }
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

using namespace std;

void partition_and_search(const char* file_to_search_in, const char* pattern_to_search_for, int search_start_position, int search_end_position, int max_chunk_size) {
    pid_t my_pid = getpid();
    int chunk_size = (search_end_position - search_start_position) + 1;
    
    cout << "[" << my_pid << "] start position = " << search_start_position << " ; end position = " << search_end_position << "\n";
    
    if(chunk_size <= max_chunk_size) {
        pid_t searcher_pid = fork();
        if(searcher_pid == 0) {
            execlp("./part2_searcher.out", "./part2_searcher.out", file_to_search_in, pattern_to_search_for, 
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
            int status;
            waitpid(left_child, &status, 0);
            cout << '[' << my_pid << ']' << " left child returned with status: " << status << endl;

            pid_t right_child = fork();
            if(right_child == 0) {
                partition_and_search(file_to_search_in, pattern_to_search_for, middle_position + 1, search_end_position, max_chunk_size);
                exit(0);
            } else if(right_child > 0) {
                cout << '[' << my_pid << ']' << " forked the right_child: " << right_child << endl;
                waitpid(right_child, &status, 0);
                cout << '[' << my_pid << ']' << " right child returned with status: " << status << endl;
            }
        }
    }
}

int main(int argc, char **argv) {
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
