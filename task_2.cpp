#include <iostream>
#include <pthread.h>
#include <vector>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

struct ThreadData {
    int *arr;
    long long sum;
    int start;
    int end;
};

// Function to initialize the array with a repeating pattern [1,2,3,4,5,4,3,2,1]
void initializeArray(int *arr, int size) {
    int pattern[] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
    int pattern_size = sizeof(pattern) / sizeof(pattern[0]);

    for (int i = 0; i < size; i++) {
        arr[i] = pattern[i % pattern_size];
    }
}

// Function executed by each thread
void *partialSum(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    data->sum = 0;

    for (int i = data->start; i < data->end; i++) {
        data->sum += data->arr[i];
    }

    return nullptr;
}

int main() {
    vector<int> array_sizes = {100, 500, 1000, 5000, 10000, 50000, 100000};
    vector<int> num_threads_list = {1, 2, 4, 8, 16}; 

    ofstream file("performance_data.csv");
    file << "Array_Size";
    for (int threads : num_threads_list) file << ",Threads_" << threads;
    file << "\n";

    for (int size : array_sizes) {
        file << size;

        int *arr = new int[size];
        initializeArray(arr, size);

        for (int num_threads : num_threads_list) {
            pthread_t threads[num_threads];
            ThreadData thread_data[num_threads];

            int chunk_size = size / num_threads;
            auto start_time = high_resolution_clock::now();

            // Creating threads
            for (int i = 0; i < num_threads; i++) {
                thread_data[i].arr = arr;
                thread_data[i].start = i * chunk_size;
                thread_data[i].end = (i == num_threads - 1) ? size : (i + 1) * chunk_size;
                pthread_create(&threads[i], nullptr, partialSum, (void *)&thread_data[i]);
            }

            // Joining threads and summing results
            long long total_sum = 0;
            for (int i = 0; i < num_threads; i++) {
                pthread_join(threads[i], nullptr);
                total_sum += thread_data[i].sum;
            }

            auto end_time = high_resolution_clock::now();
            double duration = std::chrono::duration<double>(end_time - start_time).count();
            file << "," << duration;
        }

        file << "\n";
        delete[] arr;
    }

    file.close();
    cout << "Performance data saved to performance_data.csv\n";
    return 0;
}
