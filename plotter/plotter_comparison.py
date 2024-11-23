import matplotlib.pyplot as plt

# Function to read log data from a file
def read_log_file(filename):
    sizes = []
    times = []
    with open(filename, 'r') as file:
        for line in file:
            size, time = line.split()
            sizes.append(int(size))
            times.append(float(time))
    return sizes, times

# File names for the log files (adjust paths as necessary)
log_files = [
    "comparison_count_log_original.txt",
    "comparison_count_log_mintomax.txt",
    "comparison_count_log_maxtomin.txt"
]

# Read data from each log file
data = [read_log_file(log_file) for log_file in log_files]

# Create the plot
plt.figure(figsize=(12, 8))
markers = ['o', '+', 'x']  # Different markers for each dataset
colors = ['b', 'g', 'r']    # Different colors for each dataset
labels = ['Random', 'Min to Max', 'Max to Min']  # Corresponding labels

for i, (sizes, times) in enumerate(data):
    plt.plot(sizes, times, marker=markers[i], color=colors[i], label=labels[i], fillstyle='none')

# Add titles and labels
plt.title('ComparisonCounting Sort Time Complexity (Linear Scale)', fontsize=16)
plt.xlabel('Input Size (N)', fontsize=14)
plt.ylabel('Time (seconds)', fontsize=14)

# Customize ticks for better precision
plt.xticks(fontsize=12)
plt.yticks(fontsize=12)

# Adding a grid for better readability
plt.grid(True, which='both', linestyle='--', linewidth=0.7)

# Add a legend
plt.legend(title='Data Type', fontsize=12)

# Adjust layout to prevent clipping of tick labels
plt.tight_layout()

# Show the plot
plt.show()
