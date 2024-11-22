plt.figure(figsize=(12, 8))
markers = ['o', '+', 'x']  # Different markers for each dataset
colors = ['b', 'g', 'r']    # Different colors for each dataset
labels = ['Original', 'Min to Max', 'Max to Min']  # Corresponding labels

for i, (sizes, times) in enumerate(data):
    if i == 0:
        plt.plot(sizes, times, marker=markers[i], color=colors[i], label=labels[i], fillstyle='none')
    else:
        plt.plot(sizes, times, marker=markers[i], color=colors[i], label=labels[i], markersize=8)