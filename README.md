# Shared Memory Parallelism: Pthreads and OpenMP in C/C++

This repository contains a collection of projects demonstrating various techniques for shared memory parallelism using Pthreads and OpenMP. The focus is on understanding and mitigating common challenges like race conditions and deadlocks, while achieving performance improvements on multi-core processors.

## Key Learning Outcomes & Skills:

* **Pthreads (POSIX Threads):** Manual thread creation, management, and synchronization.
* **Mutex Locks:** Protecting critical sections to ensure data integrity.
* **Race Condition Resolution:** Implementing strategies to avoid incorrect results in concurrent execution.
* **OpenMP:** Using compiler directives (`#pragma omp`) for simplified parallelization of loops and code blocks, `reduction`, `critical sections`, `atomic operations`.
* **Performance Benchmarking:** Quantitatively comparing sequential vs. parallel execution times, plotting `Speedup` and `Efficiency` graphs.
* **C/C++ Fundamentals:** Strong command over pointers, dynamic memory allocation, and data structures.
* **Data Visualization:** Integration with Python `matplotlib` for generating performance plots.

## Projects:

### 1. Multi-Threaded Variable Increment (Pthreads)
* **Description:** Explores the behavior of incrementing shared variables across multiple threads with and without mutex protection.
* **Skills Showcased:** `pthreads` for thread creation, `global variables` for shared data, `race conditions`, `mutex locks` for synchronization.
* **Source:** `CS435 Lab 03 Manual - Multi-Threading using PThreads (v2).docx` (Tasks 1, 2, 4)
* **Details:** `task1_2_multi_increment.cpp`, `task4_mutex_example.cpp`.
* **Results:** Terminal outputs showing varying results for the "unmutexed" version and consistent, correct results for the "mutexed" version.

### 2. Parallel Dot Product Calculation (Pthreads)
* **Description:** Compares sequential and multi-threaded approaches to computing the dot product of two large 1D arrays.
* **Skills Showcased:** `pthreads` for parallel task distribution, `structs` for passing multiple arguments to threads, `dynamic memory allocation`, `performance measurement (chrono library)`.
* **Source:** `PDP Lab4.pdf` (Lab Task 1)
* **Details:** `dot_product_pthreads.cpp`.
* **Results:** Screenshots of terminal output with time comparisons.

### 3. Parallel Matrix Multiplication (Pthreads)
* **Description:** Implements matrix multiplication ($C = A \times B$) using a multi-threaded Pthreads approach and compares its performance against a sequential version.
* **Skills Showcased:** `pthreads`, `2D array representation (vector<vector<int>>)`, `workload distribution (row-wise partitioning)`, `performance benchmarking`.
* **Source:** `PDP Lab4.pdf` (Lab Task 3)
* **Details:** `matrix_multiplication_pthreads.cpp`.
* **Results:** Terminal outputs comparing single-threaded and multi-threaded execution times.

### 4. Parallel 2D Convolution (Pthreads)
* **Description:** Performs 2D image convolution on a large input matrix using a multi-threaded Pthreads implementation.
* **Skills Showcased:** `pthreads`, `2D array manipulation`, `image processing fundamentals (convolution)`, `dynamic matrix allocation/deallocation`, `thread workload balancing`.
* **Source:** `PDP Lab4.pdf` (Lab Task 5)
* **Details:** `2d_convolution_pthreads.cpp`.
* **Results:** Terminal output with time comparisons.

### 5. Multi-threaded Array Summation Performance Analysis (Pthreads)
* **Description:** Analyzes the performance of multi-threaded summation of a 1D array with a repeating pattern, varying both array size and number of threads.
* **Skills Showcased:** `Pthreads for parallel summation`, `dynamic array initialization with specific patterns`, `systematic performance benchmarking`, `data export to CSV`, `Python plotting (matplotlib, pandas) for time vs. array size graphs`.
* **Source:** `Pdp Lab5.pdf` (Lab Task 2)
* **Details:** `sum_array_performance.cpp` (C++ code) and `plot_sum_performance.py` (Python script). The C++ code generates `performance_data.csv`.
* **Results:** Includes the generated `performance_plot.png` showing time taken vs. array size for different thread counts, illustrating scaling behavior.

### 6. Matrix Multiplication Performance Analysis (Pthreads)
* **Description:** Detailed performance comparison of single-threaded versus multi-threaded (Pthreads) matrix multiplication, analyzing time taken as matrix size and thread count vary.
* **Skills Showcased:** `Pthreads for matrix multiplication`, `dynamic matrix allocation/deallocation`, `systematic performance profiling`, `data visualization with Python (matplotlib)`.
* **Source:** `Pdp Lab5.pdf` (Lab Task 3)
* **Details:** `matrix_mul_performance.cpp` (C++ code) and `plot_matrix_mul_performance.py` (Python script with example data).
* **Results:** Presents a graph showing "Matrix Multiplication Performance" (Execution Time vs. Matrix Size) for single-threaded and multi-threaded (2 and 4 threads) implementations, highlighting speedup trends.

### 7. 2D Convolution Performance Analysis (Pthreads)
* **Description:** Compares the performance of single-threaded and multi-threaded (Pthreads) 2D convolution for varying matrix sizes and thread counts.
* **Skills Showcased:** `Pthreads for 2D convolution`, `dynamic matrix handling`, `performance measurement and analysis`, `Python plotting for time vs. matrix size`.
* **Source:** `Pdp Lab5.pdf` (Lab Task 4)
* **Details:** `convolution_performance.cpp` (C++ code) and `plot_convolution_performance.py` (Python script with example data).
* **Results:** Includes a graph titled "2D Convolution: Time vs. Matrix Size" comparing single-threaded, 4-threaded, and 8-threaded performance, demonstrating efficiency gains with more threads.

### 8. OpenMP Basic Operations & Array Multiplication
* **Description:** Fundamental examples of OpenMP directives, including parallel regions and `for` loop parallelization for array operations.
* **Skills Showcased:** `#pragma omp parallel`, `omp_get_thread_num()`, `omp_get_num_threads()`, `omp_get_max_threads()`, `#pragma omp for`.
* **Source:** `CS435 Lab 08 Manual - Using OpenMP to Solve Parallel Engineering Problems.pdf` (Lab Task 1, 2)
* **Details:** `openmp_basic_hello_world.cpp`, `openmp_array_multiply.cpp`, `sequential_array_multiply.cpp`.
* **Results:** Terminal outputs showing thread IDs and performance comparisons for array multiplication.

### 9. OpenMP Critical Section & Atomic Operations
* **Description:** Illustrates and resolves a race condition using `OpenMP`'s `#pragma omp critical` and demonstrates `atomic` operations for safe shared variable updates.
* **Skills Showcased:** `race conditions in OpenMP`, `critical sections`, `atomic operations`, `thread synchronization`, `reduction patterns`.
* **Source:** `CS435 Lab 08 Manual - Using OpenMP to Solve Parallel Engineering Problems.pdf` (Lab Task 3, 5)
* **Details:** `openmp_race_condition.cpp`, `openmp_critical_fixed.cpp`, `openmp_parallel_sum.cpp`.
* **Results:** Terminal outputs showing race condition effects and their resolution, and parallel summation results.

### 10. OpenMP Parallel 2D Convolution & Numerical Integration
* **Description:** Implements 2D image convolution and numerical integration using OpenMP, parallelizing nested loops and sums.
* **Skills Showcased:** `OpenMP collapse directive` for nested loops, `numerical integration (Riemann sum)`, `function pointers`, `high precision output (iomanip)`.
* **Source:** `CS435 Lab 08 Manual - Using OpenMP to Solve Parallel Engineering Problems.pdf` (Lab Task 6, 7)
* **Details:** `openmp_2d_convolution.cpp`, `openmp_numerical_integration.cpp`.
* **Results:** Printed matrices for convolution, and integral values with high precision for numerical integration.
