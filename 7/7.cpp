#include <algorithm>
#include <iostream>
using namespace std;

int comparisons = 0;
int moves = 0;      
int merges = 0;
int maxDepth = 0;
bool trace = false;

int tmp[10000];    
int passedMerges = 0;
int passedSorts = 0;

void resetStats() {
    comparisons = 0;
    moves = 0;
    merges = 0;
    maxDepth = 0;
}

void show(const int a[], int l, int r) {
    cout << "{";
    for (int i = l; i <= r; i++) {
        if (i > l) cout << ", ";
        cout << a[i];
    }
    cout << "}";
}

void pad(int d) {
    for (int i = 0; i < d; i++) cout << "  ";
}

void swapInt(int &x, int &y) {
    int t = x;
    x = y;
    y = t;
}

// 5.1
void mergeParts(int a[], int l, int m, int r, int depth = 1) {
    if (trace) {
        pad(depth - 1);
        cout << "Merge: left ";
        show(a, l, m);
        cout << " + right ";
        show(a, m + 1, r);
    }

    int i = l;
    int j = m + 1;
    int k = l;

    while (i <= m && j <= r) {
        comparisons++;

        if (a[j] < a[i])         
            tmp[k++] = a[j++];
        else
            tmp[k++] = a[i++];

        moves++;
    }

    while (i <= m) {             
        tmp[k++] = a[i++];
        moves++;
    }

    while (j <= r) {              
        tmp[k++] = a[j++];
        moves++;
    }

    for (k = l; k <= r; k++) {    
        a[k] = tmp[k];
        moves++;
    }

    merges++;

    if (trace) {
        cout << " -> ";
        show(a, l, r);
        cout << '\n';
    }
}

// 5.3
void mergeSort(int a[], int l, int r, int depth) {
    if (depth > maxDepth)
        maxDepth = depth;

    if (trace) {
        pad(depth - 1);
        cout << "Split: depth " << depth << ", range [" << l << ", " << r << "] ";
        show(a, l, r);
        cout << '\n';
    }

    if (l >= r)
        return;

    int m = l + (r - l) / 2;

    mergeSort(a, l, m, depth + 1);
    mergeSort(a, m + 1, r, depth + 1);
    mergeParts(a, l, m, r, depth);
}

void mergeSortAll(int a[], int n) {
    if (n > 0)
        mergeSort(a, 0, n - 1, 1);
}

// 5.6
bool checkArray(const int original[], int n1, const int sorted[], int n2, bool report = true) {
    int expected[10000];
    for (int i = 0; i < n1; i++) {
        expected[i] = original[i];
    }
    sort(expected, expected + n1);

    bool ok = n1 == n2;
    for (int i = 0; i < n2; i++) {
        if (i > 0 && sorted[i] < sorted[i - 1])
            ok = false;
        if (i < n1 && sorted[i] != expected[i])
            ok = false;
    }

    if (!ok && report) {
        cout << "ERROR! Input: ";
        show(original, 0, n1 - 1);
        cout << " Actual: ";
        show(sorted, 0, n2 - 1);
        cout << '\n';
    }

    return ok;
}

// 5.2 
void testMerge(const int left[], int ln, const int right[], int rn, const int expected[], int number) {
    int a[40];

    for (int i = 0; i < ln; i++)
        a[i] = left[i];

    for (int i = 0; i < rn; i++)
        a[ln + i] = right[i];

    int n = ln + rn;

    mergeParts(a, 0, ln - 1, n - 1);

    bool ok = true;

    for (int i = 0; i < n; i++) {
        if (a[i] != expected[i])
            ok = false;
    }

    cout << "Merge test " << number << ": " << (ok ? "PASS" : "FAIL") << " | ";
    show(a, 0, n - 1);
    cout << '\n';

    if (ok)
        passedMerges++;
}

void testSort(const int input[], const int expected[], int n, int number) {
    int a[20];

    for (int i = 0; i < n; i++)
        a[i] = input[i];

    resetStats();
    mergeSortAll(a, n);

    bool ok = true;

    for (int i = 0; i < n; i++) {
        if (a[i] != expected[i])
            ok = false;
    }

    if (!checkArray(input, n, a, n))
        ok = false;

    cout << "Test " << number << ": " << (ok ? "PASS" : "FAIL") << '\n';

    if (ok)
        passedSorts++;
}

// 5.4
bool controlExample() {
    int a[] = {8, 3, 7, 2, 6, 1, 5, 4};
    int original[] = {8, 3, 7, 2, 6, 1, 5, 4};

    resetStats();
    trace = true;
    mergeSortAll(a, 8);
    trace = false;

    cout << "Result: ";
    show(a, 0, 7);
    cout << '\n';
    cout << "Comparisons: " << comparisons << " (expected 16)\n";
    cout << "Writes: " << moves << " (expected 48)\n";
    cout << "Merges: " << merges << " (expected 7)\n";
    cout << "Max depth: " << maxDepth << " (expected 4)\n";

    return checkArray(original, 8, a, 8)
        && comparisons == 16 && moves == 48 && merges == 7 && maxDepth == 4;
}

bool task8() {
    int emptyArr[1] = {};
    int one[] = {7};
    int two1[] = {1, 2};
    int two2[] = {2, 1};
    int asc[] = {1, 2, 3, 4, 5};
    int desc[] = {5, 4, 3, 2, 1};
    int odd[] = {4, 1, 5, 2, 3};
    int repeat[] = {3, 1, 3, 2, 1};
    int negative[] = {0, -5, 8, -2, 4};
    int equal[] = {6, 6, 6, 6};
    int combined[] = {9, -1, 9, 0, -1, 5};
    int levels[] = {8, 3, 7, 2, 6, 1, 5};
    int own1[] = {15, 3, 14, 1, 13, 5, 12, 7, 11, 9, 10, 2, 8, 4, 6};
    int own2[] = {2000000000, -2000000000, 0, 2000000000, -1, -2000000000, 1};

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
    int e11[] = {1, 2, 3, 5, 6, 7, 8};
    int e12[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int e13[] = {-2000000000, -2000000000, -1, 0, 1, 2000000000, 2000000000};

    passedMerges = 0;
    passedSorts = 0;

    cout << "MERGE TESTS\n";

    int m1l[] = {1, 3, 5},        m1r[] = {2, 4, 6},        m1e[] = {1, 2, 3, 4, 5, 6};
    int m2l[] = {1, 9},           m2r[] = {2, 3, 4, 5, 8},  m2e[] = {1, 2, 3, 4, 5, 8, 9};
    int m3r[] = {1, 2, 3};
    int m4l[] = {1, 2, 3};
    int m5l[] = {1, 2, 2, 5},     m5r[] = {2, 2, 3},        m5e[] = {1, 2, 2, 2, 2, 3, 5};
    int m6l[] = {-7, -3, 0},      m6r[] = {-5, -1, 4},      m6e[] = {-7, -5, -3, -1, 0, 4};
    int m7l[] = {10, 20, 30},     m7r[] = {1, 2, 3},        m7e[] = {1, 2, 3, 10, 20, 30};
    int m8l[] = {4, 4},           m8r[] = {4, 4, 4},        m8e[] = {4, 4, 4, 4, 4};

    testMerge(m1l, 3, m1r, 3, m1e, 1);
    testMerge(m2l, 2, m2r, 5, m2e, 2);
    testMerge(emptyArr, 0, m3r, 3, m3r, 3);
    testMerge(m4l, 3, emptyArr, 0, m4l, 4);
    testMerge(m5l, 4, m5r, 3, m5e, 5);
    testMerge(m6l, 3, m6r, 3, m6e, 6);
    testMerge(m7l, 3, m7r, 3, m7e, 7);
    testMerge(m8l, 2, m8r, 3, m8e, 8);

    cout << "\nSORT TESTS\n";

    testSort(emptyArr, e0, 0, 1);
    testSort(one, e1, 1, 2);
    testSort(two1, e2, 2, 3);
    testSort(two2, e3, 2, 4);
    testSort(asc, e4, 5, 5);
    testSort(desc, e5, 5, 6);
    testSort(odd, e6, 5, 7);
    testSort(repeat, e7, 5, 8);
    testSort(negative, e8, 5, 9);
    testSort(equal, e9, 4, 10);
    testSort(combined, e10, 6, 11);
    testSort(levels, e11, 7, 12);
    testSort(own1, e12, 15, 13);
    testSort(own2, e13, 7, 14);

    cout << "\nCONTROL EXAMPLE (trace)\n";
    bool control = controlExample();
    cout << "Control example: " << (control ? "PASS" : "FAIL") << '\n';

    cout << "\nTEST RESULT\n";
    cout << "Successful merges: " << passedMerges << "/8\n";
    cout << "Successful sorts: " << passedSorts << "/14\n";

    return passedMerges == 8 && passedSorts == 14 && control;
}

void insertion(int a[], int n) {
    for (int i = 1; i < n; i++) {
        const int key = a[i];
        moves++;
        int j = i - 1;

        while (j >= 0) {
            comparisons++;
            if (a[j] > key) {
                a[j + 1] = a[j];
                moves++;
                j--;
            } else {
                break;
            }
        }
        a[j + 1] = key;
        moves++;
    }
}

void selection(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int mn = i;

        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (a[j] < a[mn])
                mn = j;
        }

        if (mn != i) {
            swapInt(a[i], a[mn]);
            moves++;
        }
    }
}

void bubble(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool changed = false;

        for (int j = 0; j < n - 1 - i; j++) {
            comparisons++;
            if (a[j] > a[j + 1]) {
                swapInt(a[j], a[j + 1]);
                moves++;
                changed = true;
            }
        }

        if (!changed)
            break;
    }
}


void shell(int a[], int n) {
    int steps[100];
    int size = 0;
    int st = 1;

    while (st < n) {
        steps[size++] = st;
        st = st * 3 + 1;
    }

    for (int k = size - 1; k >= 0; k--) {
        const int gap = steps[k];

        for (int i = gap; i < n; i++) {
            const int temp = a[i];
            moves++;
            int j = i;

            while (j >= gap) {
                comparisons++;
                if (a[j - gap] > temp) {
                    a[j] = a[j - gap];
                    moves++;
                    j -= gap;
                } else {
                    break;
                }
            }
            a[j] = temp;
            moves++;
        }
    }
}

// QuickSort
int hoare(int a[], int low, int high) {
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

        if (i >= j)
            return j;

        swapInt(a[i], a[j]);
        moves++;
    }
}

void quick(int a[], int low, int high) {
    if (low >= high)
        return;

    int p = hoare(a, low, high);
    quick(a, low, p);
    quick(a, p + 1, high);
}

// HeapSort
void siftDown(int a[], int i, int n) {
    while (true) {
        int l = 2 * i + 1;
        if (l >= n)
            break;

        int big = l;

        if (l + 1 < n) {
            comparisons++;
            if (a[l + 1] > a[l])
                big = l + 1;
        }

        comparisons++;
        if (a[big] > a[i]) {
            swapInt(a[big], a[i]);
            moves++;
            i = big;
        } else {
            break;
        }
    }
}

void heapSort(int a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        siftDown(a, i, n);

    for (int e = n - 1; e > 0; e--) {
        swapInt(a[0], a[e]);
        moves++;
        siftDown(a, 0, e);
    }
}

int work[10000];

void rework(const int original[], int work[], int n) {
    for (int i = 0; i < n; i++)
        work[i] = original[i];
}

void row(const char* name, const int original[], int n, const char* unit, const char* memory) {
    cout << name << "\t" << comparisons << "\t" << moves << "\t" << unit << "\t" << memory
         << "\t" << (checkArray(original, n, work, n) ? "PASS" : "FAIL") << '\n';
}

void compareAll(const int original[], int n) {
    cout << "Algorithm\tComparisons\tMoves\tUnit\tMemory\tCheck\n";

    rework(original, work, n);
    resetStats();
    insertion(work, n);
    row("Insertion", original, n, "moves", "O(1)");

    rework(original, work, n);
    resetStats();
    selection(work, n);
    row("Selection", original, n, "swaps", "O(1)");

    rework(original, work, n);
    resetStats();
    bubble(work, n);
    row("Bubble", original, n, "swaps", "O(1)");

    rework(original, work, n);
    resetStats();
    shell(work, n);
    row("Shell", original, n, "moves", "O(1)");

    rework(original, work, n);
    resetStats();
    quick(work, 0, n - 1);
    row("QuickSort", original, n, "swaps", "O(log n)");

    rework(original, work, n);
    resetStats();
    heapSort(work, n);
    row("HeapSort", original, n, "swaps", "O(1)");

    rework(original, work, n);
    resetStats();
    mergeSortAll(work, n);
    row("MergeSort", original, n, "writes", "O(n)");
}

// 5.7
void myvariant() {
    cout << "taskvar15" << '\n';

    int a[] = {30, 9, 35, 18, 13, 37, 16, 26, 11, 33, 21, 14, 36, 8, 24, 29};
    int n = 16;
    int b[16];

    cout << "Original array: ";
    show(a, 0, n - 1);
    cout << "\n\n";

    for (int i = 0; i < n; i++)
        b[i] = a[i];

    resetStats();
    trace = (n <= 16);
    mergeSortAll(b, n);
    trace = false;

    cout << "\nResult: ";
    show(b, 0, n - 1);
    cout << '\n';
    cout << "Check: " << (checkArray(a, n, b, n) ? "PASS" : "FAIL") << '\n';
    cout << "Comparisons: " << comparisons << '\n';
    cout << "Writes: " << moves << '\n';
    cout << "Merges: " << merges << '\n';
    cout << "Max depth: " << maxDepth << "\n\n";

    compareAll(a, n);
}

// 5.8 
void fillData(int a[], int n, int type) {
    for (int i = 0; i < n; i++) {
        if (type == 1) a[i] = n - i;
        else if (type == 3) a[i] = (i * 37) % n;
        else a[i] = i + 1;
    }

    if (type == 2) {
        for (int i = 0; i + 1 < n; i += 5) {
            int t = a[i];
            a[i] = a[i + 1];
            a[i + 1] = t;
        }
    }
}

int bigData[10000];

void experiment() {
    int sizes[] = {100, 1000, 10000};
    const char* types[] = {"ascending", "descending", "nearly sorted", "mixed"};

    for (int k = 0; k < 3; k++) {
        for (int type = 0; type < 4; type++) {
            int n = sizes[k];
            fillData(bigData, n, type);

            cout << "\nSize: " << n << " | Dataset: " << types[type] << '\n';
            compareAll(bigData, n);
        }
    }
}

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

    int b[10000];
    for (int i = 0; i < s; i++)
        b[i] = a[i];

    resetStats();
    trace = (s <= 16);
    mergeSortAll(b, s);
    trace = false;

    cout << "Result: ";
    show(b, 0, s - 1);
    cout << '\n';
    cout << "Check: " << (checkArray(a, s, b, s) ? "PASS" : "FAIL") << '\n';
    cout << "Comparisons: " << comparisons << '\n';
    cout << "Writes: " << moves << '\n';
    cout << "Merges: " << merges << '\n';
    cout << "Max depth: " << maxDepth << '\n';
}

int main() {
    bool testsPassed = task8();

    cout << "\nAUTOMATIC TESTS: " << (testsPassed ? "ALL PASSED" : "SOME FAILED") << '\n';

    if (!testsPassed) {
        cout << "Tests failed; comparison stopped\n";
        return 1;
    }

    cout << '\n';
    myvariant();

    experiment();

    inputArray();
    return 0;
}