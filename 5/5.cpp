#include <iostream>
using namespace std;

int comparisons = 0;
int swaps = 0;
int maxDepth = 0;

// 5.2
int lomuto(int a[], int low, int high) {
    const int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparisons++;

        if (a[j] <= pivot) {
            i++;

            if (i != j) {
                swaps++;

                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }

    if (i + 1 != high) {
        swaps++;

        int temp = a[i + 1];
        a[i + 1] = a[high];
        a[high] = temp;
    }

    return i + 1;
}

// 5.3, 5.6
void quicksort(int a[], int low, int high, int s, int& calls, int depth = 1) {
    if (low >= high)
        return;

    if (depth > maxDepth)
        maxDepth = depth;

    calls++;

    int pivot = a[high];

    if (s <= 30) {
        cout << "\nCall #" << calls << " Depth: " << depth << " Range: [" << low << ", " << high << "]" << " Pivot: " << pivot << '\n';
    }

    int pivotIndex = lomuto(a, low, high);

    if (s <= 30) {
        cout << "After partition: ";

        for (int i = low; i <= high; i++)
            cout << a[i] << " ";

        cout << "\nPivot position: " << pivotIndex << '\n';
        cout << "Left range: [" << low << ", " << pivotIndex - 1 << "]\n";
        cout << "Right range: [" << pivotIndex + 1 << ", " << high << "]\n";
    }

    quicksort(a, low, pivotIndex - 1, s, calls, depth + 1);
    quicksort(a, pivotIndex + 1, high, s, calls, depth + 1);
}

// 5.4
int task4(int a[], int low, int high, int s = 10000) {
    const int pivot = a[low + (high - low) / 2];

    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
            comparisons++;
        } while (a[i] < pivot);

        do {
            j--;
            comparisons++;
        } while (a[j] > pivot);

        if (i >= j) {
            if (s <= 30) {
                cout << "Indices: i = " << i << ", j = " << j << '\n';
            }

            return j;
        }

        swaps++;

        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}

// 5.5-5.6
void quicksorttask5(int a[], int low, int high, int s, int& calls, int depth = 1) {
    if (low >= high)
        return;

    if (depth > maxDepth)
        maxDepth = depth;

    calls++;

    int pivot = a[low + (high - low) / 2];

    if (s <= 30) {
        cout << "\nCall #" << calls << " Depth: " << depth << " Range: [" << low << ", " << high << "]" << " Pivot: " << pivot << '\n';
    }

    int p = task4(a, low, high, s);

    if (s <= 30) {
        cout << "After partition: ";

        for (int i = low; i <= high; i++)
            cout << a[i] << " ";

        cout << "\nBoundary: " << p << '\n';
        cout << "Left range: [" << low << ", " << p << "]\n";
        cout << "Right range: [" << p + 1 << ", " << high << "]\n";
    }

    quicksorttask5(a, low, p, s, calls, depth + 1);
    quicksorttask5(a, p + 1, high, s, calls, depth + 1);
}

// 5.7
bool checkArray(int original[], int sorted[], int s) {
    double sum1 = 0, sum2 = 0;
    double sq1 = 0, sq2 = 0;

    for (int i = 0; i < s; i++) {
        sum1 += original[i];
        sum2 += sorted[i];

        sq1 += (double)original[i] * original[i];
        sq2 += (double)sorted[i] * sorted[i];

        if (i > 0 && sorted[i] < sorted[i - 1])
            return false;
    }

    return sum1 == sum2 && sq1 == sq2;
}

void resetStats() {
    comparisons = 0;
    swaps = 0;
    maxDepth = 0;
}

void printStats() {
    cout << "Comparisons: " << comparisons << '\n';
    cout << "Swaps: " << swaps << '\n';
    cout << "Max depth: " << maxDepth << '\n';
}

// 5.9
int passedSorts = 0;
int passedPartitions = 0;

bool sameValues(int original[], int a[], int n) {
    for (int i = 0; i < n; i++) {
        int count1 = 0;
        int count2 = 0;

        for (int j = 0; j < n; j++) {
            if (original[j] == original[i])
                count1++;

            if (a[j] == original[i])
                count2++;
        }

        if (count1 != count2)
            return false;
    }

    return true;
}

bool sortedCorrectly(int a[], int expected[], int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != expected[i])
            return false;
    }

    return true;
}

void testSort(int input[], int expected[], int n, int number) {
    int a[20];
    int b[20];

    for (int i = 0; i < n; i++) {
        a[i] = input[i];
        b[i] = input[i];
    }

    int calls1 = 0;
    quicksort(a, 0, n - 1, 10000, calls1);

    bool ok1 = sortedCorrectly(a, expected, n)
        && sameValues(input, a, n);

    int calls2 = 0;
    quicksorttask5(b, 0, n - 1, 10000, calls2);

    bool ok2 = sortedCorrectly(b, expected, n)
        && sameValues(input, b, n);

    cout << "Test " << number << " | Lomuto: " << (ok1 ? "PASS" : "FAIL") << " | Hoare: " << (ok2 ? "PASS" : "FAIL") << '\n';

    if (ok1)
        passedSorts++;

    if (ok2)
        passedSorts++;
}

bool testLomuto(int input[], int n) {
    if (n <= 0)
        return false;

    int a[20];

    for (int i = 0; i < n; i++)
        a[i] = input[i];

    int p = lomuto(a, 0, n - 1);

    cout << "Pivot index: " << p << " | Array: ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << '\n';

    if (p < 0 || p >= n)
        return false;

    for (int i = 0; i < p; i++) {
        if (a[i] > a[p])
            return false;
    }

    for (int i = p + 1; i < n; i++) {
        if (a[i] <= a[p])
            return false;
    }

    return sameValues(input, a, n);
}

bool testHoare(int input[], int n) {
    if (n < 2)
        return false;

    int a[20];

    for (int i = 0; i < n; i++)
        a[i] = input[i];

    int pivot = a[(n - 1) / 2];
    int p = task4(a, 0, n - 1, n);

    cout << "Boundary: " << p << " | Array: ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << '\n';

    if (p < 0 || p >= n - 1)
        return false;

    for (int i = 0; i <= p; i++) {
        if (a[i] > pivot)
            return false;
    }

    for (int i = p + 1; i < n; i++) {
        if (a[i] < pivot)
            return false;
    }

    return sameValues(input, a, n);
}

// 5.9 
bool controlExample() {
    int a[] = {9, 3, 7, 1, 8, 2, 6, 4};
    int original[] = {9, 3, 7, 1, 8, 2, 6, 4};
    int calls = 0;

    resetStats();
    quicksort(a, 0, 7, 10000, calls);

    cout << "Calls: " << calls << " (expected 5)\n";
    cout << "Max depth: " << maxDepth << " (expected 4)\n";
    cout << "Comparisons: " << comparisons << " (expected 15)\n";
    cout << "Swaps: " << swaps << " (expected 7)\n";

    return checkArray(original, a, 8) && calls == 5 && maxDepth == 4 && comparisons == 15 && swaps == 7;
}

bool task8() {
    int empty[1] = {};
    int one[] = {7};
    int two1[] = {1, 2};
    int two2[] = {2, 1};
    int asc[] = {1, 2, 3, 4, 5};
    int desc[] = {5, 4, 3, 2, 1};
    int mixed[] = {4, 1, 5, 2, 3};
    int repeat[] = {3, 1, 3, 2, 1};
    int negative[] = {0, -5, 8, -2, 4};
    int equal[] = {6, 6, 6, 6};
    int combined[] = {9, -1, 9, 0, -1, 5};
    int partial[] = {3, 2, 1, 4, 5};
    int own1[] = {-10, 0, 10};
    int own2[] = {5, 5, -3, 8, -3, 0};

    int e0[1] = {};
    int e1[] = {7};
    int e2[] = {1, 2};
    int e3[] = {1, 2};
    int e4[] = {1, 2, 3, 4, 5};
    int e5[] = {1, 2, 3, 4, 5};
    int e6[] = {1, 2, 3, 4, 5};
    int e7[] = {1, 1, 2, 3, 3};
    int e8[] = {-5, -2, 0, 4, 8};
    int e9[] = {6, 6, 6, 6};
    int e10[] = {-1, -1, 0, 5, 9, 9};
    int e11[] = {1, 2, 3, 4, 5};
    int e12[] = {-10, 0, 10};
    int e13[] = {-3, -3, 0, 5, 5, 8};

    passedSorts = 0;
    passedPartitions = 0;

    cout << "SORT TESTS\n";

    testSort(empty, e0, 0, 1);
    testSort(one, e1, 1, 2);
    testSort(two1, e2, 2, 3);
    testSort(two2, e3, 2, 4);
    testSort(asc, e4, 5, 5);
    testSort(desc, e5, 5, 6);
    testSort(mixed, e6, 5, 7);
    testSort(repeat, e7, 5, 8);
    testSort(negative, e8, 5, 9);
    testSort(equal, e9, 4, 10);
    testSort(combined, e10, 6, 11);
    testSort(partial, e11, 5, 12);
    testSort(own1, e12, 3, 13);
    testSort(own2, e13, 6, 14);

    cout << "\nPARTITION TESTS\n";

    int* tests[] = {asc, desc, mixed, repeat};
    int lengths[] = {5, 5, 5, 5};

    for (int i = 0; i < 4; i++) {
        bool ok = testLomuto(tests[i], lengths[i]);

        cout << "Lomuto " << i + 1 << ": "
             << (ok ? "PASS" : "FAIL") << '\n';

        if (ok)
            passedPartitions++;
    }

    for (int i = 0; i < 4; i++) {
        bool ok = testHoare(tests[i], lengths[i]);

        cout << "Hoare " << i + 1 << ": "
             << (ok ? "PASS" : "FAIL") << '\n';

        if (ok)
            passedPartitions++;
    }

    cout << "\nCONTROL EXAMPLE\n";
    bool control = controlExample();
    cout << "Control example: " << (control ? "PASS" : "FAIL") << '\n';

    cout << "\nTEST RESULT\n";
    cout << "Successful sorts: " << passedSorts << "/28\n";
    cout << "Successful partitions: " << passedPartitions << "/8\n";

    return passedSorts == 28 && passedPartitions == 8 && control;
}

// 5.1 
void runBoth(int original[], int s) {
    int a[10000];
    int b[10000];

    cout << "Original array: ";
    for (int i = 0; i < s; i++) {
        cout << original[i] << " ";
        a[i] = original[i];
        b[i] = original[i];
    }
    cout << '\n';

    // Lomuto
    resetStats();
    int calls = 0;
    quicksort(a, 0, s - 1, s, calls);

    cout << "\nLomuto:\n";
    cout << "Sorted array: ";
    for (int i = 0; i < s; i++)
        cout << a[i] << " ";
    cout << '\n';

    cout << "Check: " << (checkArray(original, a, s) ? "PASS" : "FAIL") << '\n';
    printStats();
    cout << "Calls: " << calls << '\n';

    // Hoare
    resetStats();
    calls = 0;
    quicksorttask5(b, 0, s - 1, s, calls);

    cout << "\nHoare:\n";
    cout << "Sorted array: ";
    for (int i = 0; i < s; i++)
        cout << b[i] << " ";
    cout << '\n';

    cout << "Check: " << (checkArray(original, b, s) ? "PASS" : "FAIL") << '\n';
    printStats();
    cout << "Calls: " << calls << '\n';
}

void myvariant() {
    cout << "taskvar15" << '\n';

    int a[] = {30, 9, 35, 18, 13, 38, 16, 26, 11, 33, 21, 14, 37, 8, 24};

    runBoth(a, 15);
}

// 5.1 
void inputArray() {
    int s;
    int a[10000];

    cout << "\nEnter array size (0 to skip): ";

    if (!(cin >> s) || s <= 0 || s > 10000)
        return;

    cout << "Enter " << s << " numbers: ";

    for (int i = 0; i < s; i++) {
        if (!(cin >> a[i]))
            return;
    }

    runBoth(a, s);
}

int main() {
    bool testsPassed = task8();

    cout << "\nAUTOMATIC TESTS: "
         << (testsPassed ? "ALL PASSED" : "SOME FAILED") << '\n';

    if (!testsPassed)
        return 1;

    int sizes[] = {100, 1000, 10000};
    int a[10000];
    int aw[10000];

    for (int type = 0; type < 5; type++) {
        for (int k = 0; k < 3; k++) {
            int s = sizes[k];

            for (int i = 0; i < s; i++) {
                if (type == 0)
                    aw[i] = i;
                else if (type == 1)
                    aw[i] = s - i;
                else if (type == 2)
                    aw[i] = (i * 37 + 11) % 1000;
                else if (type == 3)
                    aw[i] = i % 5;
                else
                    aw[i] = i;
            }

            if (type == 4) {
                int temp = aw[s / 2];
                aw[s / 2] = aw[s / 2 + 1];
                aw[s / 2 + 1] = temp;
            }

            cout << "\nSize: " << s << '\n';

            if (type == 0)
                cout << "Ascending\n";
            else if (type == 1)
                cout << "Descending\n";
            else if (type == 2)
                cout << "Mixed\n";
            else if (type == 3)
                cout << "Repeated values\n";
            else
                cout << "Nearly sorted\n";

            // Lomuto
            for (int i = 0; i < s; i++)
                a[i] = aw[i];

            resetStats();
            int calls = 0;
            quicksort(a, 0, s - 1, s, calls);

            cout << "Lomuto: " << (checkArray(aw, a, s) ? "PASS" : "FAIL") << '\n';
            printStats();
            cout << "Calls: " << calls << '\n';

            // Hoare
            for (int i = 0; i < s; i++)
                a[i] = aw[i];

            resetStats();
            calls = 0;
            quicksorttask5(a, 0, s - 1, s, calls);

            cout << "Hoare: " << (checkArray(aw, a, s) ? "PASS" : "FAIL") << '\n';
            printStats();
            cout << "Calls: " << calls << '\n';
        }
    }

    myvariant();
    inputArray();
    return 0;
}