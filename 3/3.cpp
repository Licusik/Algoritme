#include <iostream>

using namespace std;


//checker
bool checker(const int res[], const int orig[], int n) {
    int sumRes = 0, sumOrig = 0;
    int sqRes = 0, sqOrig = 0;

    for (int i = 0; i < n; i++) {
        if (i < n - 1 && res[i] > res[i + 1])
            return false;

        sumRes += res[i];
        sumOrig += orig[i];

        sqRes += res[i] * res[i];
        sqOrig += orig[i] * orig[i];
    }

    return sumRes == sumOrig && sqRes == sqOrig;
}

void rework(const int a[], int aw[], int n) {
    for (int i = 0; i < n; i++)
        aw[i] = a[i];
}

void show(const int a[], int n) {
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
}


//2
int findpos(const int a[], int n, int key, int &count) {
    int l = 0, r = n;

    while (l < r) {
        const int m = (l + r) / 2;
        count++;

        if (a[m] <= key)
            l = m + 1;
        else
            r = m;
    }

    return l;
}

bool checkPart(const int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1])
            return false;
    }

    return true;
}

// insertion
void insertion(int a[], int n, int &count, int &mov) {
    count = 0;
    mov = 0;

    for (int i = 1; i < n; i++) {
        int key = a[i];
        mov++;

        int j = i - 1;

        while (j >= 0) {
            count++;

            if (a[j] <= key)
                break;

            a[j + 1] = a[j];
            mov++;
            j--;
        }

        a[j + 1] = key;
        mov++;
    }
}

// binary insertion
void task2(int a[], int n, int &count, int &mov) {
    count = 0;
    mov = 0;

    for (int i = 1; i < n; i++) {
        int key = a[i];
        mov++;

        int l = findpos(a, i, key, count);

        for (int j = i; j > l; j--) {
            a[j] = a[j - 1];
            mov++;
        }

        a[l] = key;
        mov++;

        if (!checkPart(a, i + 1))
            cout << "Error: part is not sorted" << '\n';
    }
}

// bubble
void bubble(int a[], int n, int &count, int &mov, int &pas) {
    count = 0;
    mov = 0;
    pas = 0;

    for (int i = 0; i < n - 1; i++) {
        bool change = false;

        for (int j = 0; j < n - 1 - i; j++) {
            count++;

            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;

                mov += 3;
                change = true;
            }
        }

        pas++;

        if (!change)
            break;
    }
}

//4
void task4(int a[], int n, int &count, int &mov, int &pas) {
    count = 0;
    mov = 0;
    pas = 0;

    int l = 0, r = n;
    bool change = true;

    while (l < r && change) {
        change = false;

        for (int i = l; i < r - 1; i++) {
            count++;

            if (a[i] > a[i + 1]) {
                int temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;

                mov += 3;
                change = true;
            }
        }

        pas++;
        r--;

        if (!change)
            break;

        change = false;

        for (int i = r - 1; i > l; i--) {
            count++;

            if (a[i] < a[i - 1]) {
                int temp = a[i];
                a[i] = a[i - 1];
                a[i - 1] = temp;

                mov += 3;
                change = true;
            }
        }

        pas++;
        l++;
    }
}


//test findpos
void testFindPos() {
    int t[] = {1, 3, 3, 5, 7};
    int keys[] = {0, 4, 9, 3, 1};
    int want[] = {0, 3, 5, 3, 1};
    int ok = 0;

    for (int i = 0; i < 5; i++) {
        int c = 0;
        int pos = findpos(t, 5, keys[i], c);

        cout << "key = " << keys[i] << ", position = " << pos << ", expected = " << want[i];

        if (pos == want[i]) {
            cout << " - ok" << '\n';
            ok++;
        }
        else {
            cout << " - error" << '\n';
        }
    }

    cout << "Result: " << ok << " of 5 ok" << '\n';
}

bool Compmasiv(const int a[], const int b[], int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i])
            return false;
    }

    return true;
}

void fillmavis(int a[], int n, int type) {
    if (type == 0) {
        for (int i = 0; i < n; i++)
            a[i] = i + 1;
    }
    else if (type == 1) {
        for (int i = 0; i < n; i++)
            a[i] = n - i;
    }
    else if (type == 2) {
        for (int i = 0; i < n; i++)
            a[i] = i + 1;

        if (n >= 3) {
            int temp = a[1];
            a[1] = a[2];
            a[2] = temp;
        }

        if (n >= 7) {
            int temp = a[5];
            a[5] = a[6];
            a[6] = temp;
        }
    }
    else {
        for (int i = 0; i < n; i++)
            a[i] = (i * 7) % 10;
    }
}



//7
void task7() {
    cout << "AutoTest po task7" << '\n';

    int sizes[] = {10, 100, 1000};

    const char* names[] = {
        "Ascending",
        "Descending",
        "Almost sorted",
        "Mixed"
    };

    int a[1000];
    int aw[1000];

    for (int k = 0; k < 3; k++) {
        int n = sizes[k];

        for (int type = 0; type < 4; type++) {
            fillmavis(a, n, type);

            int count1, mov1;
            int count2, mov2;
            int count3, mov3, pas3;
            int count4, mov4, pas4;

            cout << '\n';
            cout << "n = " << n << ", Type: " << names[type] << '\n';

            // insertion
            rework(a, aw, n);
            insertion(aw, n, count1, mov1);

            cout << "Insertion: ";
            cout << "Comparisons = " << count1 << ", Moves = " << mov1 << ", Passes = " << n - 1 << '\n';

            bool ok = checker(aw, a, n);
            cout << "Status: " << (ok ? "ok" : "error") << '\n';

            // binary insertion
            rework(a, aw, n);
            task2(aw, n, count2, mov2);

            cout << "Binary insertion: ";
            cout << "Comparisons = " << count2 << ", Moves = " << mov2 << ", Passes = " << n - 1 << '\n';

            ok = checker(aw, a, n);
            cout << "Status: " << (ok ? "ok" : "error") << '\n';

            // bubble
            rework(a, aw, n);
            bubble(aw, n, count3, mov3, pas3);

            cout << "Bubble: ";
            cout << "Comparisons = " << count3 << ", Moves = " << mov3 << ", Passes = " << pas3 << '\n';

            ok = checker(aw, a, n);
            cout << "Status: " << (ok ? "ok" : "error") << '\n';

            // shaker
            rework(a, aw, n);
            task4(aw, n, count4, mov4, pas4);

            cout << "Shaker: ";
            cout << "Comparisons = " << count4 << ", Moves = " << mov4 << ", Passes = " << pas4 << '\n';

            ok = checker(aw, a, n);
            cout << "Status: " << (ok ? "ok" : "error") << '\n';

            cout << '\n';

            cout << "Pair 1 - insertion / binary insertion:" << '\n';
            cout << "Comparisons: " << count1 << " / " << count2 << '\n';
            cout << "Shifts: " << mov1 - 2 * (n - 1) << " / " << mov2 - 2 * (n - 1) << '\n';

            cout << "Pair 2 - bubble / shaker:" << '\n';
            cout << "Comparisons: " << count3 << " / " << count4 << '\n';
            cout << "Swaps: " << mov3 / 3 << " / " << mov4 / 3 << '\n';
            cout << "Passes: " << pas3 << " / " << pas4 << '\n';
        }
    }
}

//8
void check(const int in[], const int want[], int n, int num, int &ok) {
    int aw[1000];
    int count, mov, pas;

    cout << "All sort Test " << num << '\n';

    // binary insertion
    rework(in, aw, n);
    task2(aw, n, count, mov);

    cout << "Binary insertion: ";
    show(aw, n);

    if (Compmasiv(aw, want, n) && checker(aw, in, n)) {
        cout << "OK" << '\n';
        ok++;
    }
    else {
        cout << "FAIL" << '\n';
    }

    // shaker
    rework(in, aw, n);
    task4(aw, n, count, mov, pas);

    cout << "Shaker: ";
    show(aw, n);

    if (Compmasiv(aw, want, n) && checker(aw, in, n)) {
        cout << "OK" << '\n';
        ok++;
    }
    else {
        cout << "FAIL" << '\n';
    }
}

void task8() {
    int one[1] = {};
    int want1[1] = {};

    int two[] = {5};
    int want2[] = {5};

    int three[] = {1, 2, 3, 4, 5};
    int want3[] = {1, 2, 3, 4, 5};

    int four[] = {5, 4, 3, 2, 1};
    int want4[] = {1, 2, 3, 4, 5};

    int five[] = {4, 2, 5, 1, 3};
    int want5[] = {1, 2, 3, 4, 5};

    int six[] = {3, 1, 3, 2, 1};
    int want6[] = {1, 1, 2, 3, 3};

    int seven[] = {0, -4, 7, -1, 3};
    int want7[] = {-4, -1, 0, 3, 7};

    int eight[] = {8, 8, 8, 8};
    int want8[] = {8, 8, 8, 8};

    int nine[] = {2, 1};
    int want9[] = {1, 2};

    int ten[] = {1, 2, 3, 5, 4, 6};
    int want10[] = {1, 2, 3, 4, 5, 6};

    int eleven[] = {28, 10, 35, 20, 14, 39, 17, 9, 32, 23};
    int want11[] = {9, 10, 14, 17, 20, 23, 28, 32, 35, 39};

    int twelve[] = {10, 3, 7, 1, 9, 2, 8};
    int want12[] = {1, 2, 3, 7, 8, 9, 10};
    int ok = 0;

    check(one, want1, 0, 1, ok);
    check(two, want2, 1, 2, ok);
    check(three, want3, 5, 3, ok);
    check(four, want4, 5, 4, ok);
    check(five, want5, 5, 5, ok);
    check(six, want6, 5, 6, ok);
    check(seven, want7, 5, 7, ok);
    check(eight, want8, 4, 8, ok);
    check(nine, want9, 2, 9, ok);
    check(ten, want10, 6, 10, ok);
    check(eleven, want11, 10, 11, ok);
    check(twelve, want12, 7, 12, ok);

    cout << '\n';
    cout << "Sorting tests: " << ok << " of 24 ok" << '\n';

    testFindPos();
}

void runVariant() {
    int v[] = {27, 9, 36, 15, 23, 11, 32, 19, 8, 38, 13, 25};
    int n = 12;
    int w[12];
    int count, mov, pas;

    cout << "Variant 15" << '\n';
    cout << "Original: ";
    show(v, n);
    cout << '\n';

    rework(v, w, n);
    task2(w, n, count, mov);
    cout << "Binary insertion: ";
    show(w, n);
    cout << '\n';
    cout << "Comparisons: " << count << ", Moves: " << mov << ", Status: " << (checker(w, v, n) ? "ok" : "error") << '\n';

    rework(v, w, n);
    task4(w, n, count, mov, pas);
    cout << "Shaker: ";
    show(w, n);
    cout << '\n';
    cout << "Comparisons: " << count << ", Moves: " << mov << ", Passes: " << pas<< ", Status: " << (checker(w, v, n) ? "ok" : "error") << '\n';
}

void checkExample() {
    int v[] = {8, 3, 7, 2, 6, 1};
    int w[6];
    int count, mov;

    rework(v, w, 6);
    task2(w, 6, count, mov);

    cout << "Example check: ";
    if (count == 10 && mov == 22 && checker(w, v, 6))
        cout << "ok" << '\n';
    else
        cout << "error" << '\n';
}

int main() {
    int s;

    cout << "enter size" << '\n';

    if (!(cin >> s) || s <= 0 || s > 1000) {
        cout << "invalid size" << '\n';
        return 0;
    }

    int a[1000];
    int aw[1000];

    for (int i = 0; i < s; i++) {
        cout << "enter element" << '\n';

        if (!(cin >> a[i])) {
            cout << "invalid input" << '\n';
            return 0;
        }
    }

    cout << "Original: ";
    show(a, s);
    cout << '\n';

    int count = 0, mov = 0, pas = 0;

    rework(a, aw, s);
    task2(aw, s, count, mov);

    cout << "Binary insertion: ";
    show(aw, s);
    cout << '\n';

    bool ok = checker(aw, a, s);
    cout << "Status: " << (ok ? "ok" : "error") << '\n';
    cout << "Comparisons: " << count << ", Moves: " << mov << ", Passes: " << s - 1 << '\n';

    rework(a, aw, s);
    task4(aw, s, count, mov, pas);

    cout << "Shaker: ";
    show(aw, s);
    cout << '\n';

    ok = checker(aw, a, s);
    cout << "Status: " << (ok ? "ok" : "error") << '\n';
    cout << "Comparisons: " << count << ", Moves: " << mov << ", Passes: " << pas << '\n';

    cout << '\n';

    runVariant();

    cout << '\n';
    checkExample();

    cout << '\n';

    task7();

    cout << '\n';

    task8();

    return 0;
}
