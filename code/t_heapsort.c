#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// Swap function
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify a subtree rooted with node i which is an index in arr[] and n is the size of the heap
void heapify(int arr[], int n, int i)
{
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// Heap Sort function
void heap_sort(int arr[], int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// Function to read data from a CSV file
int *read_csv(const char *filename, int *size)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Error: Could not open file %s\n", filename);
        return NULL;
    }

    // Read numbers from the CSV file
    int *arr = (int *)malloc(sizeof(int) * 1000000); // Allocate a large enough array
    int num, i = 0;
    while (fscanf(file, "%d,", &num) == 1)
    {
        arr[i++] = num;
    }

    *size = i; // Set the size of the array
    fclose(file);
    return arr;
}

// Function to get high-precision time in seconds using QueryPerformanceCounter (for Windows)
double get_time_in_seconds()
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    return (double)start.QuadPart / (double)frequency.QuadPart;
}

int main()
{
    int input_sizes[] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 110000, 120000, 130000, 140000, 150000, 160000, 170000, 180000, 190000, 200000}; // Different input sizes
    int num_sizes = sizeof(input_sizes) / sizeof(input_sizes[0]);

    const char *log_files[] = {"heapsort_log_original.txt", "heapsort_log_mintomax.txt", "heapsort_log_maxtomin.txt"};
    const char *modes[] = {"original_", "mintomax_", "maxtomin_"};

    for (int mode = 0; mode < 3; mode++) // Loop through original, sorted, and reversed cases
    {
        // Open the corresponding log file
        FILE *log_file = fopen(log_files[mode], "w");
        if (!log_file)
        {
            printf("Error: Could not open log file %s\n", log_files[mode]);
            return 1;
        }

        for (int i = 0; i < num_sizes; i++)
        {
            int size;
            char filename[50];
            sprintf(filename, "../%s%d.csv", modes[mode], input_sizes[i]); // Generate filename

            // Read the CSV file
            int *arr = read_csv(filename, &size);
            if (arr == NULL)
            {
                continue; // Skip if the file can't be opened
            }

            // Measure the time taken for sorting
            double start_time = get_time_in_seconds();

            heap_sort(arr, size);

            double end_time = get_time_in_seconds();

            // Calculate the time taken
            double time_taken = end_time - start_time;

            // Log the input size and time taken
            fprintf(log_file, "%d %.9f\n", size, time_taken);

            printf("[%s] Input size: %d, Time taken: %.9f seconds\n", modes[mode], size, time_taken);

            free(arr); // Free the memory after sorting
        }

        fclose(log_file); // Close the log file
    }

    return 0;
}
