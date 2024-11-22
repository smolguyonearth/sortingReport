# import matplotlib.pyplot as plt
# import numpy as np

# # Log files generated from heap sort
# log_files = ["heapsort_log_original.txt", "heapsort_log_mintomax.txt", "heapsort_log_maxtomin.txt"]
# colors = ['blue', 'green', 'red']  # Colors for each plot
# markers = ['o', 's', '^']  # Different markers for each line

# plt.figure(figsize=(10, 6))

# for i, log_file in enumerate(log_files):
#     sizes = []
#     times = []

#     # Read data from log file
#     with open(log_file, "r") as file:
#         for line in file:
#             size, time = map(float, line.strip().split())
#             sizes.append(size)
#             times.append(time)
    
#     # Plot log-log graph
#     plt.plot(sizes, times, marker=markers[i], color=colors[i], label=log_file.split('_')[2].replace('.txt', '').capitalize(), markersize=8)

# # Log scale for both axes
# plt.xscale('log')
# plt.yscale('log')

# # Labels and title
# plt.xlabel('Input Size (log scale)', fontsize=12)
# plt.ylabel('Time Taken (seconds, log scale)', fontsize=12)
# plt.title('Heap Sort Time Complexity on Different Inputs (Log-Log Scale)', fontsize=14)

# # Display legend
# plt.legend()

# # Show grid for better readability
# plt.grid(True, which="both", ls="--")

# # Display the plot
# plt.tight_layout()
# plt.show()

import matplotlib.pyplot as plt
import numpy as np

# Log files generated from heap sort
log_files = ["log/heapsort_log_original.txt", "log/heapsort_log_mintomax.txt", "log/heapsort_log_maxtomin.txt"]
colors = ['blue', 'green', 'red']  # Colors for each plot
markers = ['o', '+', 'x']  # Different markers for each line

plt.figure(figsize=(10, 6))

for i, log_file in enumerate(log_files):
    sizes = []
    times = []

    # Read data from log file
    with open(log_file, "r") as file:
        for line in file:
            size, time = map(float, line.strip().split())
            sizes.append(size)
            times.append(time)
    
    # Plot normal graph (linear scale)
    if i == 0:
        plt.plot(sizes, times, marker=markers[i], color=colors[i], label=log_file.split('_')[2].replace('.txt', '').capitalize(), fillstyle='none')
    else:
        plt.plot(sizes, times, marker=markers[i], color=colors[i], label=log_file.split('_')[2].replace('.txt', '').capitalize(), markersize=8)

# Normal scale for both axes (linear plot)
plt.xlabel('Input Size', fontsize=12)
plt.ylabel('Time Taken (seconds)', fontsize=12)
plt.title('Heap Sort Time Complexity on Different Inputs (Linear Scale)', fontsize=14)

# Display legend
plt.legend()

# Show grid for better readability
plt.grid(True)

# Display the plot
plt.tight_layout()
plt.show()
