import matplotlib.pyplot as plt
import numpy as np

matrix_sizes = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
times_single = [0.03, 0.09, 0.21, 0.42, 0.85, 1.37, 2.05, 2.98, 3.97, 5.10]
times_multi_2 = [0.02, 0.05, 0.12, 0.26, 0.52, 0.78, 1.12, 1.49, 1.98, 2.45]
times_multi_4 = [0.01, 0.03, 0.07, 0.14, 0.29, 0.39, 0.57, 0.72, 1.02, 1.30]

plt.plot(matrix_sizes, times_single, label="Single-threaded", marker="o")
plt.plot(matrix_sizes, times_multi_2, label="Multi-threaded (2 threads)", marker="s")
plt.plot(matrix_sizes, times_multi_4, label="Multi-threaded (4 threads)", marker="^")

plt.xlabel("Matrix Size (N x N)")
plt.ylabel("Execution Time (seconds)")
plt.title("Matrix Multiplication Performance")
plt.legend()
plt.grid()
plt.show()
