import pandas as pd
import matplotlib.pyplot as plt

# Load data from CSV
df = pd.read_csv("performance_data.csv")

# Plot
plt.figure(figsize=(10, 6))
for column in df.columns[1:]:
    plt.plot(df["Array_Size"], df[column], marker='o', label=column)

plt.xlabel("Array Size")
plt.ylabel("Time Taken (seconds)")
plt.title("Performance of Multi-threaded Summation")
plt.legend()
plt.grid()
plt.savefig("performance_plot.png")
plt.show()
