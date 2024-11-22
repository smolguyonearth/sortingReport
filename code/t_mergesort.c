#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h> // Include Windows header for high-resolution timing

// Function to merge two halves
void merge(int arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1; // Size of left subarray
    int n2 = right - mid;    // Size of right subarray

    // Create temporary arrays
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // Copy data to temporary arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    i = 0;    // Initial index of first subarray
    j = 0;    // Initial index of second subarray
    k = left; // Initial index of merged subarray

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of L[] if any
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements of R[] if any
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Free temporary arrays
    free(L);
    free(R);
}

// Merge Sort function
void merge_sort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
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

// Function to get the current time in nanoseconds
long long get_time()
{
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time); // Get the current time
    return time.QuadPart;           // Return the time as a high-resolution counter value
}

double convert_to_seconds(long long start, long long end, double frequency)
{
    return (double)(end - start) / frequency; // Convert to seconds
}

int main()
{
    int input_sizes[] = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 110000, 120000, 130000, 140000, 150000, 160000, 170000, 180000, 190000, 200000}; // different input sizes
    int num_sizes = sizeof(input_sizes) / sizeof(input_sizes[0]);

    const char *log_files[] = {"mergesort_log_original.txt", "mergesort_log_mintomax.txt", "mergesort_log_maxtomin.txt"};
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
            sprintf(filename, "../%s%d.csv", mode == 0 ? "original_" : mode == 1 ? "mintomax_"
                                                                                 : "maxtomin_",
                    input_sizes[i]); // Generate filename

            // Read the CSV file
            int *arr = read_csv(filename, &size);
            if (arr == NULL)
            {
                continue; // Skip if the file can't be opened
            }

            // Measure the time taken for sorting
            long long start_time = get_time();
            merge_sort(arr, 0, size - 1);
            long long end_time = get_time();

            // Calculate the time taken in seconds
            double time_taken = convert_to_seconds(start_time, end_time, frequency.QuadPart);

            // Log the input size and time taken
            fprintf(log_file, "%d %.9f\n", size, time_taken); // More precision in the output

            printf("[%s] Input size: %d, Time taken: %.9f seconds\n", modes[mode], size, time_taken);

            free(arr); // Free the memory after sorting
        }

        fclose(log_file); // Close the log file
    }

    return 0;
}
