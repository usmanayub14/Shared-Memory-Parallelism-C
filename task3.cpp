#include <iostream>
#include <pthread.h>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define MAX 1000  // Maximum matrix size

int **A, **B, **C;  // Matrices
int matrix_size, num_threads;

// Struct to pass arguments to threads
struct ThreadData {
    int start_row, end_row;
};

// Function for single-threaded matrix multiplication
void single_threaded_multiplication() {
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            C[i][j] = 0;
            for (int k = 0; k < matrix_size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Thread function for multi-threaded multiplication
void *multi_threaded_multiplication(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < matrix_size; j++) {
            C[i][j] = 0;
            for (int k = 0; k < matrix_size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

// Function to allocate memory for matrices
void allocate_matrices() {
    A = new int*[matrix_size];
    B = new int*[matrix_size];
    C = new int*[matrix_size];
    for (int i = 0; i < matrix_size; i++) {
        A[i] = new int[matrix_size];
        B[i] = new int[matrix_size];
        C[i] = new int[matrix_size];
    }
}

// Function to initialize matrices with random values
void initialize_matrices() {
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            A[i][j] = rand() % 10;  // Values between 0-9
            B[i][j] = rand() % 10;
        }
    }
}

// Function to deallocate memory
void free_matrices() {
    for (int i = 0; i < matrix_size; i++) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;
}

int main() {
    cout << "Enter matrix size: ";
    cin >> matrix_size;
    cout << "Enter number of threads: ";
    cin >> num_threads;

    // Allocate and initialize matrices
    allocate_matrices();
    initialize_matrices();

    // Single-threaded execution
    auto start = high_resolution_clock::now();
    single_threaded_multiplication();
    auto end = high_resolution_clock::now();
    double single_time = duration_cast<microseconds>(end - start).count() / 1e6;
    cout << "Single-threaded execution time: " << single_time << " seconds" << endl;

    // Multi-threaded execution
    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];
    int rows_per_thread = matrix_size / num_threads;

    start = high_resolution_clock::now();
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].start_row = i * rows_per_thread;
        thread_data[i].end_row = (i == num_threads - 1) ? matrix_size : (i + 1) * rows_per_thread;
        pthread_create(&threads[i], NULL, multi_threaded_multiplication, (void *)&thread_data[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    end = high_resolution_clock::now();

    double multi_time = duration_cast<microseconds>(end - start).count() / 1e6;
    cout << "Multi-threaded execution time: " << multi_time << " seconds" << endl;

    // Free allocated memory
    free_matrices();
    return 0;
}
