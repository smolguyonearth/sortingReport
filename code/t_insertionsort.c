#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // Include Windows header for high-resolution timing

// Insertion Sort function
void insertion_sort(int arr[], int size)
{
    for (int i = 1; i < size; i++)
    {
        int key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1], that are greater than key,
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
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

// Function to reverse an array (for maxtomin)
void reverse_array(int *arr, int size)
{
    for (int i = 0; i < size / 2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = temp;
    }
}

// Function to get the current time in nanoseconds using Windows API
long long get_time()
{
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time); // Get the current time
    return time.QuadPart;           // Return the time as a high-resolution counter value
}

// Convert ticks to seconds
double convert_to_seconds(long long start, long long end, double frequency)
{
    return (double)(end - start) / frequency; // Convert ticks to seconds
}

int main()
{
    int input_sizes[] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 110000, 120000, 130000, 140000, 150000, 160000, 170000, 180000, 190000, 200000}; // different input sizes
    int num_sizes = sizeof(input_sizes) / sizeof(input_sizes[0]);

    const char *log_files[] = {"insertionsort_log_original.txt", "insertionsort_log_mintomax.txt", "insertionsort_log_maxtomin.txt"};
    const char *modes[] = {"original_", "mintomax_", "maxtomin_"};

    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency); // Get the frequency of the high-resolution counter

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
            long long start_time = get_time();
            insertion_sort(arr, size);
            long long end_time = get_time();

            // Calculate the time taken in seconds
            double time_taken = convert_to_seconds(start_time, end_time, frequency.QuadPart);

            // Log the input size and time taken
            fprintf(log_file, "%d %.9f\n", size, time_taken); // Log with high precision (9 decimal places)

            printf("[%s] Input size: %d, Time taken: %.9f seconds\n", modes[mode], size, time_taken);

            free(arr); // Free the memory after sorting
        }

        fclose(log_file); // Close the log file
    }

    return 0;
}