#include <iostream>

using namespace std;
int pass = 0;

void rework(const int a[], int aw[], int n) {
    for (int i = 0; i < n; i++) aw[i] = a[i];
}

void show(const int a[], int n) {
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
}

void task2(int a[], int n, int &count, int &mov) {
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

void task3(int a[], int n, int &count, int &mov) {
    count = 0;
    mov = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            count++;
            if (a[j] < a[min]) min = j;
        }
        if (min != i) {
            int temp = a[i];
            a[i] = a[min];
            a[min] = temp;
            mov += 3;
        }
    }
}

void task4(int a[], int n, int &count, int &mov) {
    count = 0;
    mov = 0;
    for (int i = 0; i < n - 1; i++) {
        bool chan = false;
        for (int j = 0; j < n - 1 - i; j++) {
            count++;
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                mov += 3;
                chan = true;
            }
        }
        if (!chan) break;
    }
}

int task5(const int a[], int n, const int first[], int first_size){
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


    int sum1=0;
    int sum2=0;

    int squaresum1=0;
    int squaresum2=0;

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

//Auto_test
bool Compmasiv(const int a[], const int b[], int n){
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
    int aw[10];
    int count, mov;

    cout << "All sort Test " << num << '\n';

    rework(in, aw, n);
    task2(aw, n, count, mov);
    cout << "Insertion: ";
    show(aw, n);
    if (status(aw, want, n)) pass++;
    task5(aw, n, in, n);

    rework(in, aw, n);
    task3(aw, n, count, mov);
    cout << "Selection: ";
    show(aw, n);
    if (status(aw, want, n)) pass++;
    task5(aw, n, in, n);

    rework(in, aw, n);
    task4(aw, n, count, mov);
    cout << "Bubble: ";
    show(aw, n);
    if (status(aw, want, n)) pass++;
    task5(aw, n, in, n);
}


void task7() {
    cout << "AutoTest po task7" << '\n';

    int one[1]    = {};
    int want1[]   = {0};
    int two[]    = {7};
    int want2[]   = {7};
    int three[]  = {1, 2, 3, 4, 5};
    int want3[]   = {1, 2, 3, 4, 5};
    int four[]   = {5, 4, 3, 2, 1};
    int want4[]   = {1, 2, 3, 4, 5};
    int five[]   = {4, 1, 5, 2, 3};
    int want5[]   = {1, 2, 3, 4, 5};
    int six[]    = {3, 1, 3, 2, 1};
    int want6[]   = {1, 1, 2, 3, 3};
    int seven[]  = {0, -5, 8, -2, 4};
    int want7[]   = {-5, -2, 0, 4, 8};
    int eight[]  = {6, 6, 6, 6};
    int want8[]   = {6, 6, 6, 6};
    int nine[]   = {2, 1};
    int want9[]   = {1, 2};
    int ten[]    = {9, -1, 9, 0, -1, 5};
    int want10[]  = {-1, -1, 0, 5, 9, 9};
    int eleven[] = {28, 10, 35, 20, 14, 39, 17, 9, 32, 23};
    int want11[]  = {9, 10, 14, 17, 20, 23, 28, 32, 35, 39};
    int twelve[] = {10, 3, 7, 1, 9, 2, 8};
    int want12[]  = {1, 2, 3, 7, 8, 9, 10};

    check(one, want1, 1, 0);
    check(two, want2, 1, 2);
    check(three, want3, 5, 3);
    check(four, want4, 5, 4);
    check(five, want5, 5, 5);
    check(six, want6, 5, 6);
    check(seven, want7, 5, 7);
    check(eight, want8, 4, 8);
    check(nine, want9, 2, 9);
    check(ten, want10, 6, 10);
    check(eleven, want11, 10, 11);
    check(twelve, want12, 7, 12);
    cout << "Passed: " << pass << " / 36" << '\n';
}

void myvariant() {
    cout << "taskvar15" << '\n';
    int a[] = {28, 10, 35, 20, 14, 39, 17, 9, 32, 23};
    int aw[10];
    int n = 10;
    int count, mov;

    int c2, m2, c3, m3, c4, m4;

    cout << "masiv: ";
    show(a, n);

    rework(a, aw, n);
    task2(aw, n, count, mov);
    c2 = count;
    m2 = mov;
    cout << "Insertion sorted: ";
    show(aw, n);
    task5(aw, n, a, n);

    rework(a, aw, n);
    task3(aw, n, count, mov);
    c3 = count;
    m3 = mov;
    cout << "Selection sorted: ";
    show(aw, n);
    task5(aw, n, a, n);

    rework(a, aw, n);
    task4(aw, n, count, mov);
    c4 = count;
    m4 = mov;
    cout << "Bubble sorted: ";
    show(aw, n);
    task5(aw, n, a, n);

    cout << "Comparison of counters" << '\n';
    cout << "Insertion: comparisons " << c2 << ", moves " << m2 << '\n';
    cout << "Selection: comparisons " << c3 << ", moves " << m3 << '\n';
    cout << "Bubble:    comparisons " << c4 << ", moves " << m4 << '\n';
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

    int count, mov;

    rework(a, aw, s);
    task2(aw, s, count, mov);
    cout << "Insertion sorted: ";
    show(aw, s);
    cout << "Comparisons: " << count << '\n';
    cout << "Moves: " << mov << '\n';
    task5(aw, s, a, s);

    rework(a, aw, s);
    task3(aw, s, count, mov);
    cout << "Selection sorted: ";
    show(aw, s);
    cout << "Comparisons: " << count << '\n';
    cout << "Moves: " << mov << '\n';
    task5(aw, s, a, s);

    rework(a, aw, s);
    task4(aw, s, count, mov);
    cout << "Bubble sorted: ";
    show(aw, s);
    cout << "Comparisons: " << count << '\n';
    cout << "Moves: " << mov << '\n';
    task5(aw, s, a, s);

    //6
    s = 100;

    cout << "Zrostayuchyi set" << '\n';
    for (int i = 0; i < s; i++) a[i] = i + 1;

    rework(a, aw, s);
    task2(aw, s, count, mov);
    cout << "Insertion: " << count << " " << mov << '\n';
    task5(aw, s, a, s);

    rework(a, aw, s);
    task3(aw, s, count, mov);
    cout << "Selection: " << count << " " << mov << '\n';
    task5(aw, s, a, s);

    rework(a, aw, s);
    task4(aw, s, count, mov);
    cout << "Bubble: " << count << " " << mov << '\n';
    task5(aw, s, a, s);

    cout << "Spadayuchyi set" << '\n';
    for (int i = 0; i < s; i++) a[i] = 100 - i;

    rework(a, aw, s);
    task2(aw, s, count, mov);
    cout << "Insertion: " << count << " " << mov << '\n';
    task5(aw, s, a, s);

    rework(a, aw, s);
    task3(aw, s, count, mov);
    cout << "Selection: " << count << " " << mov << '\n';
    task5(aw, s, a, s);

    rework(a, aw, s);
    task4(aw, s, count, mov);
    cout << "Bubble: " << count << " " << mov << '\n';
    task5(aw, s, a, s);

    cout << "Mix set" << '\n';
    for (int i = 0; i < s; i++) a[i] = (i * 37) % 100;

    rework(a, aw, s);
    task2(aw, s, count, mov);
    cout << "Insertion: " << count << " " << mov << '\n';
    task5(aw, s, a, s);

    rework(a, aw, s);
    task3(aw, s, count, mov);
    cout << "Selection: " << count << " " << mov << '\n';
    task5(aw, s, a, s);

    rework(a, aw, s);
    task4(aw, s, count, mov);
    cout << "Bubble: " << count << " " << mov << '\n';
    task5(aw, s, a, s);



    //7
    task7();

    //var

    myvariant();
    return 0;
}