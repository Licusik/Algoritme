#include <iostream>

using namespace std;
int pass = 0;

//5.1
void rework(const int a[], int aw[], int n) {
    for (int i = 0; i < n; i++) aw[i] = a[i];
}

void show(const int a[], int n) {
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
}

//5.2
void step(int s) {
    int st = s / 2;

    while (st >= 1) {
        cout << st << ' ';
        st /= 2;
    }
}

//5.3 Shell, halving
void task3(int a[], int n, int &count, int &mov, bool demo = false) {
    count = 0;
    mov = 0;

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            const int temp = a[i];
            mov++;
            int j = i;

            while (j >= gap) {
                count++;
                if (a[j - gap] > temp) {
                    a[j] = a[j - gap];
                    mov++;
                    j -= gap;
                } else {
                    break;
                }
            }
            a[j] = temp;
            mov++;
        }

        if (demo) {
            cout << "After gap " << gap << ": ";
            show(a, n);
            cout << '\n';
        }
    }
}

//5.4 Shell, Knuth
void task4(int a[], int n, int &count, int &mov, bool demo = false) {
    count = 0;
    mov = 0;

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
            mov++;
            int j = i;

            while (j >= gap) {
                count++;
                if (a[j - gap] > temp) {
                    a[j] = a[j - gap];
                    mov++;
                    j -= gap;
                } else {
                    break;
                }
            }
            a[j] = temp;
            mov++;
        }

        if (demo) {
            cout << "After gap " << gap << ": ";
            show(a, n);
            cout << '\n';
        }
    }
}

void step2(int n) {
    int steps[100];
    int size = 0;
    int gap = 1;

    while (gap < n) {
        steps[size++] = gap;
        gap = gap * 3 + 1;
    }

    cout << "Generated: ";
    for (int i = 0; i < size; i++) cout << steps[i] << ' ';
    cout << gap << "; used: ";
    for (int i = size - 1; i >= 0; i--) cout << steps[i] << ' ';
}

//5.5
bool task5(const int a[], int n, const int first[], int first_size) {
    bool noerror = true;

    for (int i = 1; i < n; i++) {
        if (a[i] < a[i - 1]) {
            noerror = false;
            break;
        }
    }
    if (!noerror) {
        cout << "Not sorted" << '\n';
    } else {
        cout << "Sorted" << '\n';
    }

    if (n != first_size) {
        cout << "Element count changed" << '\n';
        noerror = false;
    }

    int sum1 = 0;
    int sum2 = 0;

    int squaresum1 = 0;
    int squaresum2 = 0;

    for (int i = 0; i < n; i++) {
        sum1 += a[i];
        squaresum1 += a[i] * a[i];
    }

    for (int i = 0; i < first_size; i++) {
        sum2 += first[i];
        squaresum2 += first[i] * first[i];
    }

    if (sum1 != sum2 || squaresum1 != squaresum2) {
        cout << "Element values changed" << '\n';
        noerror = false;
    }

    if (noerror) {
        cout << "Validation passed" << '\n';
    } else {
        cout << "Validation failed" << '\n';
    }

    return noerror;
}

//5.6
void insertion(int a[], int n, int &count, int &mov) {
    count = 0;
    mov = 0;

    for (int i = 1; i < n; i++) {
        const int key = a[i];
        mov++;
        int j = i - 1;

        while (j >= 0) {
            count++;
            if (a[j] > key) {
                a[j + 1] = a[j];
                mov++;
                j--;
            } else {
                break;
            }
        }
        a[j + 1] = key;
        mov++;
    }
}

//5.7
void fill(int a[], int n, int type) {
    for (int i = 0; i < n; i++) {
        if (type == 1) a[i] = n - i;
        else if (type == 3) a[i] = (i * 37) % n;
        else a[i] = i + 1;
    }

    if (type == 2) {
        for (int i = 0; i + 1 < n; i += 5) {
            int temp = a[i];
            a[i] = a[i + 1];
            a[i + 1] = temp;
        }
    }
}

int mini(int a, int b) {
    return a < b ? a : b;
}

void cell(int x, int min) {
    cout << '\t' << x << (x == min ? "*" : "");
}

void task7() {
    cout << "AutoTest po task7" << '\n';

    int sizes[] = {100, 1000, 10000};
    const char* names[] = {"sorted", "reverse", "nearly", "mixed"};
    int a[10000];
    int aw[10000];
    int c[3], m[3];

    cout << "N\tDataset\tShell-half C\tM\tShell-Knuth C\tM\tInsertion C\tM" << '\n';

    for (int k = 0; k < 3; k++) {
        int n = sizes[k];

        for (int type = 0; type < 4; type++) {
            fill(a, n, type);

            rework(a, aw, n);
            task3(aw, n, c[0], m[0]);
            rework(a, aw, n);
            task4(aw, n, c[1], m[1]);
            rework(a, aw, n);
            insertion(aw, n, c[2], m[2]);

            int minC = mini(c[0], mini(c[1], c[2]));
            int minM = mini(m[0], mini(m[1], m[2]));

            cout << n << '\t' << names[type];
            for (int i = 0; i < 3; i++) {
                cell(c[i], minC);
                cell(m[i], minM);
            }
            cout << '\n';
        }
    }

    cout << "* = minimum in the column for this row" << '\n';
}

//5.8
bool Compmasiv(const int a[], const int b[], int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

bool status(const int a[], const int aw[], int n) {
    if (Compmasiv(a, aw, n)) {
        cout << "OK" << '\n';
        return true;
    } else {
        cout << "FAIL" << '\n';
        return false;
    }
}

void check(const int in[], const int want[], int n, int num) {
    int aw[20];
    int count, mov;

    cout << "All sort Test " << num << '\n';

    rework(in, aw, n);
    task3(aw, n, count, mov);
    cout << "Shell halving: ";
    show(aw, n);
    if (status(aw, want, n)) pass++;
    task5(aw, n, in, n);

    rework(in, aw, n);
    task4(aw, n, count, mov);
    cout << "Shell Knuth: ";
    show(aw, n);
    if (status(aw, want, n)) pass++;
    task5(aw, n, in, n);
}

bool task8() {
    int one[1]    = {};
    int want1[1]  = {};
    int two[]     = {4};
    int want2[]   = {4};
    int three[]   = {1, 2, 3, 4, 5};
    int want3[]   = {1, 2, 3, 4, 5};
    int four[]    = {5, 4, 3, 2, 1};
    int want4[]   = {1, 2, 3, 4, 5};
    int five[]    = {7, 2, 9, 1, 5};
    int want5[]   = {1, 2, 5, 7, 9};
    int six[]     = {3, 1, 3, 2, 1};
    int want6[]   = {1, 1, 2, 3, 3};
    int seven[]   = {0, -6, 8, -2, 4};
    int want7[]   = {-6, -2, 0, 4, 8};
    int eight[]   = {6, 6, 6, 6};
    int want8[]   = {6, 6, 6, 6};
    int nine[]    = {2, 1};
    int want9[]   = {1, 2};
    int ten[]     = {1, 2, 4, 3, 5, 6};
    int want10[]  = {1, 2, 3, 4, 5, 6};
    int eleven[]  = {11, -1, 6, 3, 0, 9, 2};
    int want11[]  = {-1, 0, 2, 3, 6, 9, 11};
    int twelve[]  = {20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int want12[]  = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    check(one, want1, 0, 1);
    check(two, want2, 1, 2);
    check(three, want3, 5, 3);
    check(four, want4, 5, 4);
    check(five, want5, 5, 5);
    check(six, want6, 5, 6);
    check(seven, want7, 5, 7);
    check(eight, want8, 4, 8);
    check(nine, want9, 2, 9);
    check(ten, want10, 6, 10);
    check(eleven, want11, 7, 11);
    check(twelve, want12, 20, 12);

    cout << "Passed: " << pass << " / 24" << '\n';
    return pass == 24;
}

//4
void myvariant() {
    cout << "taskvar15" << '\n';
    int a[] = {29, 8, 34, 18, 12, 38, 15, 26, 10, 32, 21, 13, 36, 9, 24};
    int aw[15];
    int n = 15;
    int count, mov;

    int c3, m3, c4, m4;

    cout << "masiv: ";
    show(a, n);
    cout << '\n';
    cout << "Halving steps: ";
    step(n);
    cout << '\n';

    rework(a, aw, n);
    task3(aw, n, count, mov);
    c3 = count;
    m3 = mov;
    cout << "Shell halving sorted: ";
    show(aw, n);
    cout << '\n';
    task5(aw, n, a, n);

    step2(n);
    cout << '\n';

    rework(a, aw, n);
    task4(aw, n, count, mov);
    c4 = count;
    m4 = mov;
    cout << "Shell Knuth sorted: ";
    show(aw, n);
    cout << '\n';
    task5(aw, n, a, n);

    cout << "Comparison of counters" << '\n';
    cout << "Shell halving: comparisons " << c3 << ", moves " << m3 << '\n';
    cout << "Shell Knuth:   comparisons " << c4 << ", moves " << m4 << '\n';
}

int main() {
    int s;
    cout << "enter size" << '\n';
    if (!(cin >> s) || s <= 0 || s > 10000) {
        cout << "invalid size" << '\n';
        return 0;
    }

    int a[10000];
    int aw[10000];

    for (int i = 0; i < s; i++) {
        cout << "enter element" << '\n';
        if (!(cin >> a[i])) {
            cout << "invalid input" << '\n';
            return 0;
        }
    }

    if (!task8()) {
        cout << "Tests failed; experiment stopped" << '\n';
        return 0;
    }

    //5.3
    int control[] = {12, 5, 9, 1, 8, 3, 10, 2};
    int expected[] = {1, 2, 3, 5, 8, 9, 10, 12};
    int work[8];
    int controlCount, controlMov;

    rework(control, work, 8);
    task3(work, 8, controlCount, controlMov, true);
    bool valid = task5(work, 8, control, 8);

    bool ok = controlCount == 29 && controlMov == 50 && valid && Compmasiv(work, expected, 8);
    cout << "Control example: " << (ok ? "OK" : "ERROR")
         << " (comparisons " << controlCount << ", moves " << controlMov << ")" << '\n';
    if (!ok) {
        cout << "Result: ";
        show(work, 8);
        cout << '\n';
        return 0;
    }

    //4
    myvariant();

    int demo;
    cout << "show each Shell step? (1/0)" << '\n';
    if (!(cin >> demo) || (demo != 0 && demo != 1)) {
        cout << "invalid choice" << '\n';
        return 0;
    }

    int count, mov;

    rework(a, aw, s);
    insertion(aw, s, count, mov);
    cout << "Insertion sorted: ";
    show(aw, s);
    cout << '\n';
    cout << "Comparisons: " << count << '\n';
    cout << "Moves: " << mov << '\n';
    cout << "Steps: 1" << '\n';
    task5(aw, s, a, s);

    rework(a, aw, s);
    task3(aw, s, count, mov, demo == 1);
    cout << "Shell halving sorted: ";
    show(aw, s);
    cout << '\n';
    cout << "Comparisons: " << count << '\n';
    cout << "Moves: " << mov << '\n';
    cout << "Steps: ";
    step(s);
    cout << '\n';
    task5(aw, s, a, s);

    rework(a, aw, s);
    task4(aw, s, count, mov, demo == 1);
    cout << "Shell Knuth sorted: ";
    show(aw, s);
    cout << '\n';
    cout << "Comparisons: " << count << '\n';
    cout << "Moves: " << mov << '\n';
    cout << "Steps: ";
    step2(s);
    cout << '\n';
    task5(aw, s, a, s);

    task7();
    return 0;
}