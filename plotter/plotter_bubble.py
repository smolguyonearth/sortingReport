# import matplotlib.pyplot as plt

# # Function to read log data from a file
# def read_log_file(filename):
#     sizes = []
#     times = []
#     with open(filename, 'r') as file:
#         for line in file:
#             size, time = line.split()
#             sizes.append(int(size))
#             times.append(float(time))
#     return sizes, times

# # File names for the log files
# log_files = [
#     "bubblesort_log_original.txt",
#     "bubblesort_log_mintomax.txt",
#     "bubblesort_log_maxtomin.txt"
# ]

# # Read data from each log file
# data = [read_log_file(log_file) for log_file in log_files]

# # Create the plot
# plt.figure(figsize=(12, 8))
# markers = ['o', 's', 'D']  # Different markers for each dataset
# colors = ['b', 'g', 'r']    # Different colors for each dataset
# labels = ['Original', 'Min to Max', 'Max to Min']  # Corresponding labels

# for i, (sizes, times) in enumerate(data):
#     plt.plot(sizes, times, marker=markers[i], color=colors[i], label=labels[i], markersize=8)

# # Add titles and labels
# plt.title('Bubble Sort Time Complexity', fontsize=16)
# plt.xlabel('Input Size (N)', fontsize=14)
# plt.ylabel('Time (seconds)', fontsize=14)

# # Set logarithmic scale for both axes
# plt.xscale('log')
# plt.yscale('log')

# # Customize ticks for better precision
# plt.xticks(ticks=[1000, 10000, 100000, 1000000], labels=['1000', '10,000', '100,000', '1,000,000'])
# plt.yticks(fontsize=12)
# plt.gca().tick_params(axis='y', which='both', labelsize=12)
# plt.gca().tick_params(axis='x', which='both', labelsize=12)

# # Adding a grid for better readability
# plt.grid(True, which='both', linestyle='--', linewidth=0.7)

# # Add a legend
# plt.legend(title='Data Type', fontsize=12)

# # Adjust layout to prevent clipping of tick-labels
# plt.tight_layout()

# # Show the plot
# plt.show()


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

# File names for the log files
log_files = [
    "log/bubblesort_log_original.txt",
    "log/bubblesort_log_mintomax.txt",
    "log/bubblesort_log_maxtomin.txt"
]

# Read data from each log file
data = [read_log_file(log_file) for log_file in log_files]

# Create the plot
plt.figure(figsize=(12, 8))
markers = ['o', '+', 'x']  # Different markers for each dataset
colors = ['b', 'g', 'r']    # Different colors for each dataset
labels = ['Original', 'Min to Max', 'Max to Min']  # Corresponding labels

for i, (sizes, times) in enumerate(data):
    if i == 0:
        plt.plot(sizes, times, marker=markers[i], color=colors[i], label=labels[i], fillstyle='none')
    else:
        plt.plot(sizes, times, marker=markers[i], color=colors[i], label=labels[i], markersize=8)

# Add titles and labels
plt.title('Bubble Sort Time Complexity (Linear Scale)', fontsize=16)
plt.xlabel('Input Size (N)', fontsize=14)
plt.ylabel('Time (seconds)', fontsize=14)

# Keep the scale linear (no need to set xscale or yscale)

# Customize ticks for better precision
plt.xticks(fontsize=12)
plt.yticks(fontsize=12)
plt.gca().tick_params(axis='y', which='both', labelsize=12)
plt.gca().tick_params(axis='x', which='both', labelsize=12)

# Adding a grid for better readability
plt.grid(True, which='both', linestyle='--', linewidth=0.7)

# Add a legend
plt.legend(title='Data Type', fontsize=12)

# Adjust layout to prevent clipping of tick-labels
plt.tight_layout()

# Show the plot
plt.show()
