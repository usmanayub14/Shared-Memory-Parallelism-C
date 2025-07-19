#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

// Struct to pass data to threads
struct ThreadData {
    int** input;
    int** filter;
    int** output;
    int N;
    int startRow;
    int endRow;
};

// Function to allocate a matrix dynamically
int** allocate_matrix(int N) {
    int** matrix = new int*[N];
    for (int i = 0; i < N; i++) {
        matrix[i] = new int[N];
    }
    return matrix;
}

// Function to initialize a matrix with a specific value
void initialize_matrix(int** matrix, int N, int value) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = value;
        }
    }
}

// Function to free dynamically allocated memory
void free_matrix(int** matrix, int N) {
    for (int i = 0; i < N; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Single-threaded convolution function
void single_threaded_convolution(int** input, int** filter, int** output, int N) {
    for (int i = 1; i < N - 1; i++) {
        for (int j = 1; j < N - 1; j++) {
            int sum = 0;
            for (int fi = 0; fi < 3; fi++) {
                for (int fj = 0; fj < 3; fj++) {
                    sum += input[i + fi - 1][j + fj - 1] * filter[fi][fj];
                }
            }
            output[i][j] = sum;
        }
    }
}

// Function to perform convolution for a part of the matrix in multi-threading
void convolve_section(ThreadData data) {
    for (int i = data.startRow; i < data.endRow; i++) {
        for (int j = 1; j < data.N - 1; j++) {
            int sum = 0;
            for (int fi = 0; fi < 3; fi++) {
                for (int fj = 0; fj < 3; fj++) {
                    sum += data.input[i + fi - 1][j + fj - 1] * data.filter[fi][fj];
                }
            }
            data.output[i][j] = sum;
        }
    }
}

// Multi-threaded convolution function
void multi_threaded_convolution(int** input, int** filter, int** output, int N, int numThreads) {
    vector<thread> threads;
    vector<ThreadData> threadData(numThreads);

    int rowsPerThread = (N - 2) / numThreads;
    int extraRows = (N - 2) % numThreads;
    int startRow = 1;

    for (int i = 0; i < numThreads; i++) {
        int endRow = startRow + rowsPerThread + (i < extraRows ? 1 : 0);

        threadData[i] = {input, filter, output, N, startRow, endRow};
        threads.push_back(thread(convolve_section, threadData[i]));

        startRow = endRow;
    }

    for (auto& t : threads) {
        t.join();
    }
}

int main() {
    int N, numThreads;

    // User input for matrix size and thread count
    cout << "Enter matrix size (N x N): ";
    cin >> N;
    cout << "Enter number of threads: ";
    cin >> numThreads;

    // Allocate matrices
    int** input = allocate_matrix(N);
    int** filter = allocate_matrix(3);
    int** output_single = allocate_matrix(N);
    int** output_multi = allocate_matrix(N);

    // Define a 3x3 filter (Sobel-like)
    int filter_values[3][3] = {{1, 0, -1}, {1, 0, -1}, {1, 0, -1}};

    // Initialize matrices
    initialize_matrix(input, N, 1);  // Fill input with 1s
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            filter[i][j] = filter_values[i][j];
        }
    }

    // Measure single-threaded execution time
    auto start = high_resolution_clock::now();
    single_threaded_convolution(input, filter, output_single, N);
    auto end = high_resolution_clock::now();
    double single_time = duration<double>(end - start).count();
    cout << "Single-threaded Time: " << single_time << " sec\n";

    // Measure multi-threaded execution time
    start = high_resolution_clock::now();
    multi_threaded_convolution(input, filter, output_multi, N, numThreads);
    end = high_resolution_clock::now();
    double multi_time = duration<double>(end - start).count();
    cout << "Multi-threaded Time: " << multi_time << " sec\n";

    // Free allocated memory
    free_matrix(input, N);
    free_matrix(filter, 3);
    free_matrix(output_single, N);
    free_matrix(output_multi, N);

    return 0;
}
