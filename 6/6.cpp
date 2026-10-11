#include <iostream>

using namespace std;
int pass = 0;

int cmp = 0;    
int mov = 0;    
int runs = 0;   

int bCmp, bMov, bRuns;   
int sCmp, sMov, sRuns;  

void rework(const int a[], int aw[], int n) {
    for (int i = 0; i < n; i++) aw[i] = a[i];
}

void show(const int a[], int n) {
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
}

//Task 1
int task1(const int a[], int n) {
    for (int i = 0; i < n; i++) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && a[i] < a[l]) return i;
        if (r < n && a[i] < a[r]) return i;
    }
    return -1;
}

void heapInfo(const int a[], int n) {
    int bad = task1(a, n);
    if (bad == -1) cout << "Heap is correct" << '\n';
    else cout << "Heap is broken at index " << bad << '\n';
}

//Task 2
void task2(int a[], int n, int i) {
    int big = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n) {
        cmp++;
        if (a[l] > a[big]) big = l;
    }
    if (r < n) {
        cmp++;
        if (a[r] > a[big]) big = r;
    }

    if (big != i) {
        int temp = a[i];
        a[i] = a[big];
        a[big] = temp;
        mov++;
        task2(a, n, big);
    }
}

//Task 3
void task3(int a[], int n, bool demo = false) {
    cmp = 0;
    mov = 0;
    runs = 0;

    for (int i = n / 2 - 1; i >= 0; i--) {
        task2(a, n, i);
        runs++;

        if (demo && n <= 20) {
            cout << "Node " << i << ", size " << n << ": ";
            show(a, n);
            cout << '\n';
        }
    }

    bCmp = cmp;
    bMov = mov;
    bRuns = runs;
}

//Task 4
bool task4(int a[], int n, bool demo = false) {
    cmp = 0;
    mov = 0;
    runs = 0;

    bool ok = true;
    int step = 0;

    for (int size = n; size > 1;) {
        int temp = a[0];
        a[0] = a[size - 1];
        a[size - 1] = temp;
        mov++;
        size--;

        task2(a, size, 0);
        runs++;
        step++;

        if (task1(a, size) != -1) ok = false;

        if (a[size] < a[0]) ok = false;
        for (int i = size; i < n - 1; i++) {
            if (a[i] > a[i + 1]) ok = false;
        }

        if (demo && step <= 3) {
            cout << "Step " << step << ": ";
            show(a, n);
            cout << '\n';
        }
    }

    sCmp = cmp;
    sMov = mov;
    sRuns = runs;
    return ok;
}

bool heapSort(int a[], int n, bool demo = false) {
    task3(a, n, demo);

    if (demo) {
        cout << "After build: ";
        show(a, n);
        cout << '\n';
        heapInfo(a, n);
    }

    return task4(a, n, demo);
}

//Task 5
void task5() {
    cout << "Build: comparisons " << bCmp << ", swaps " << bMov << ", heapify runs " << bRuns << '\n';
    cout << "Sort: comparisons " << sCmp << ", swaps " << sMov << ", heapify runs " << sRuns << '\n';
    cout << "Total: comparisons " << bCmp + sCmp << ", swaps " << bMov + sMov
         << ", heapify runs " << bRuns + sRuns << '\n';
}

//Task 6
bool task6(const int a[], int n, const int first[], int first_size) {
    if (n != first_size) return false;

    double sum1 = 0, sum2 = 0;
    double sq1 = 0, sq2 = 0;

    for (int i = 0; i < n; i++) {
        if (i > 0 && a[i] < a[i - 1]) return false;
        sum1 += a[i];
        sq1 += (double) a[i] * a[i];
        sum2 += first[i];
        sq2 += (double) first[i] * first[i];
    }

    return sum1 == sum2 && sq1 == sq2;
}

//Task 7
void fill(int a[], int n, int type) {
    for (int i = 0; i < n; i++) {
        if (type == 0) a[i] = i + 1;
        else if (type == 1) a[i] = n - i;
        else if (type == 2) a[i] = (i * 37) % n;
        else a[i] = (i * 7) % 10;
    }
}

void task7() {
    cout << "AutoTest po task7" << '\n';

    int sizes[] = {100, 1000, 10000};
    const char* names[] = {"sorted", "reverse", "mixed", "repeats"};
    int a[10000];
    int aw[10000];

    for (int k = 0; k < 3; k++) {
        int n = sizes[k];

        for (int type = 0; type < 4; type++) {
            fill(a, n, type);
            rework(a, aw, n);

            bool ok = heapSort(aw, n) && task6(aw, n, a, n);

            cout << n << ' ' << names[type] << ": build " << bCmp << "/" << bMov<< ", total " << bCmp + sCmp << "/" << bMov + sMov<< ", " << (ok ? "OK" : "FAIL") << '\n';
        }
    }
}

//Task 8
bool Compmasiv(const int a[], const int b[], int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

void check(const int in[], const int want[], int n, int num) {
    int aw[20];
    rework(in, aw, n);
    task3(aw, n);

    cout << "Test " << num << ": ";

    if (n >= 4) {
        int big = in[0];
        for (int i = 1; i < n; i++) {
            if (in[i] > big) big = in[i];
        }

        if (task1(aw, n) == -1 && aw[0] == big) {
            cout << "build OK, ";
            pass++;
        } else {
            cout << "build FAIL, ";
        }
    }

    task4(aw, n);

    if (Compmasiv(aw, want, n) && task6(aw, n, in, n)) {
        cout << "sort OK" << '\n';
        pass++;
    } else {
        cout << "sort FAIL" << '\n';
    }
}

void heapcheck(const int a[], int n, int want, int num) {
    cout << "Heap property test " << num << ": ";
    if (task1(a, n) == want) {
        cout << "OK" << '\n';
        pass++;
    } else {
        cout << "FAIL" << '\n';
    }
}

bool task8() {
    int one[1]     = {};
    int want1[1]   = {};
    int two[]      = {7};
    int want2[]    = {7};
    int three[]    = {1, 2};
    int want3[]    = {1, 2};
    int four[]     = {2, 1};
    int want4[]    = {1, 2};
    int five[]     = {1, 2, 3, 4, 5};
    int want5[]    = {1, 2, 3, 4, 5};
    int six[]      = {5, 4, 3, 2, 1};
    int want6[]    = {1, 2, 3, 4, 5};
    int seven[]    = {4, 1, 5, 2, 3};
    int want7[]    = {1, 2, 3, 4, 5};
    int eight[]    = {3, 1, 3, 2, 1};
    int want8[]    = {1, 1, 2, 3, 3};
    int nine[]     = {0, -5, 8, -2, 4};
    int want9[]    = {-5, -2, 0, 4, 8};
    int ten[]      = {6, 6, 6, 6};
    int want10[]   = {6, 6, 6, 6};
    int eleven[]   = {9, -1, 9, 0, -1, 5};
    int want11[]   = {-1, -1, 0, 5, 9, 9};
    int twelve[]   = {10, 7, 8, 4, 2, 1, 3};
    int want12[]   = {1, 2, 3, 4, 7, 8, 10};
    int own1[]     = {100, 50, 75, 25, 60, 10};
    int wantown1[] = {10, 25, 50, 60, 75, 100};
    int own2[]     = {-3, -3, 7, 0, 7, -1, 2};
    int wantown2[] = {-3, -3, -1, 0, 2, 7, 7};

    check(one, want1, 0, 1);
    check(two, want2, 1, 2);
    check(three, want3, 2, 3);
    check(four, want4, 2, 4);
    check(five, want5, 5, 5);
    check(six, want6, 5, 6);
    check(seven, want7, 5, 7);
    check(eight, want8, 5, 8);
    check(nine, want9, 5, 9);
    check(ten, want10, 4, 10);
    check(eleven, want11, 6, 11);
    check(twelve, want12, 7, 12);
    check(own1, wantown1, 6, 13);
    check(own2, wantown2, 7, 14);

    int h1[] = {9, 7, 6, 5, 3, 2, 1};
    int h2[] = {10, 10, 10};
    int h3[] = {8, 5, 7, 1, 2};
    int h4[] = {1, 2, 3};
    int h5[] = {9, 7, 6, 5, 8, 2, 1};
    int h6[] = {9, 8, 7, 6, 5, 4, 10};

    heapcheck(h1, 7, -1, 1);
    heapcheck(h2, 3, -1, 2);
    heapcheck(h3, 5, -1, 3);
    heapcheck(h4, 3, 0, 4);
    heapcheck(h5, 7, 1, 5);
    heapcheck(h6, 7, 2, 6);

    cout << "Passed: " << pass << " / 30" << '\n';
    return pass == 30;
}

//4
void myvariant() {
    cout << "taskvar15" << '\n';
    int a[] = {30, 9, 35, 18, 13, 37, 16, 26, 11, 33, 21, 14, 36, 8, 24};
    int aw[15];
    int n = 15;

    cout << "masiv: ";
    show(a, n);
    cout << '\n';

    rework(a, aw, n);
    heapSort(aw, n, true);

    cout << "Result: ";
    show(aw, n);
    cout << '\n';
    cout << "Check: " << (task6(aw, n, a, n) ? "OK" : "FAIL") << '\n';
    task5();
}

int main() {
    if (!task8()) {
        cout << "Tests failed; experiment stopped" << '\n';
        return 0;
    }

    int control[] = {4, 10, 3, 5, 1, 8, 2};
    int expected[] = {1, 2, 3, 4, 5, 8, 10};
    int work[7];

    rework(control, work, 7);
    bool ok = heapSort(work, 7) && Compmasiv(work, expected, 7);
    ok = ok && bCmp == 8 && bMov == 3 && bRuns == 3 && sRuns == 6;
    ok = ok && bCmp + sCmp == 21 && bMov + sMov == 17;

    cout << "Control example: " << (ok ? "OK" : "ERROR") << '\n';
    task5();
    if (!ok) return 0;

    //4
    myvariant();

    task7();
    return 0;
}