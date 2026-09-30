#include <iostream>

using namespace std;

const int maximum = 100000;
int masiv[maximum];

int lS(int a[], int s, int t, int& c) {
    c = 0;
    for (int i = 0; i < s; i++) {
        c++;
        if (a[i] == t) {
            return i;
        }
    }
    return -1;
}


int bS(int ab[], int s, int t, int& c) {
    c = 0;
    int l = 0, r = s - 1;

    while (l <= r) {
        c++;
        int m = (l + r) / 2;

        if (ab[m] == t)
            return m;
        else if (ab[m] < t)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}

//5.1
void task1() {
    cout << "task1" << endl;
    int firstT[] = {4, 9, 2, 7};
    int keys[] = {4, 7, 100};
    for (int k : keys) {
        int c = 0;
        lS(firstT, 4, k, c);
        cout << "Key " << k << ": comparisons " << c << endl;
    }
}

//5.2
void tB(int a[], int s, int key, int expected) {
    int c = 0;
    int res = bS(a, s, key, c);
    if (res == expected)
        cout << "успішно (порівнянь: " << c << ")" << endl;
    else
        cout << "помилка: очікувано " << expected << ", отримано " << res << endl;
}

void task2() {
    cout << "task2" << endl;
    int at[] = {2, 5, 8, 11, 14, 17, 20};
    int basic[] = {8};

    tB(at, 0, 5, -1);
    tB(basic, 1, 8, 0);
    tB(basic, 1, 3, -1);
    tB(at, 7, 2, 0);
    tB(at, 7, 20, 6);
    tB(at, 7, 11, 3);
    tB(at, 7, 9, -1);
}

//5.3
void runTest(int a[], int s, int key, int t) {
    int c = 0;
    int r1 = lS(a, s, key, c);
    int r2 = bS(a, s, key, c);
    if (r1 == t && r2 == t)
        cout << "успішно" << endl;
    else
        cout << "помилка: очікувано " << t << ", прямий " << r1 << ", бінарний " << r2 << endl;
}

void task3() {
    cout << "task3" << endl;
    int at[] = {2, 5, 8, 11, 14, 17, 20};
    int basic[] = {8};
    int duo[] = {3, 7};


    runTest(basic, 1, 8, 0);
    runTest(basic, 1, 3, -1);
    runTest(at, 7, 2, 0);
    runTest(at, 7, 11, 3);
    runTest(at, 7, 20, 6);
    runTest(at, 7, 9, -1);
    runTest(at, 7, -4, -1);
    runTest(at, 7, 100, -1);
    runTest(at, 0, 5, -1);


    runTest(at, 7, 5, 1);
    runTest(at, 7, 17, 5);
    runTest(duo, 2, 7, 1);
}

// 5.4
void task4() {
    cout << "task4" << endl;
    int s[] = {10, 100, 1000, 100000};
    const char* names[] = {"A", "B", "C"};

    cout << "n Scenario Direct_search Binary_search" << endl;

    for (int n : s) {
        for (int i = 0; i < n; i++)
            masiv[i] = i;

        int keys[] = {0, n - 1, n};

        for (int k = 0; k < 3; k++) {
            int coutL, coutB;
            lS(masiv, n, keys[k], coutL);
            bS(masiv, n, keys[k], coutB);
            cout << n << " " << names[k] << " " << coutL << " " << coutB << endl;
        }
    }
}

// 5.5
void task5() {
    cout << "task5" << endl;
    int s[] = {10, 100, 1000, 100000};
    const int request = 1000;

    cout << "n Direct_avg Binary_avg" << endl;

    for (int j = 0; j < 4; j++) {
        int n = s[j];

        for (int i = 0; i < n; i++)
            masiv[i] = i;

        double sumL = 0;
        double sumB = 0;

        for (int i = 1; i <= request; i++) {
            int key = (i * 37) % n;
            int coutL, coutB;

            lS(masiv, n, key, coutL);
            bS(masiv, n, key, coutB);

            sumL += coutL;
            sumB += coutB;
        }

        cout << n << " " << sumL / request << " " << sumB / request << endl;
    }
}
//5.6
void validation(int a[], int n) {
    int errors = 0;
    for (int i = 0; i < n; i++) {
        int coutB;
        int res = bS(a, n, a[i], coutB);
        cout << "key=" << a[i] << " expected=" << i << " got=" << res << " compar=" << coutB;
        if (res == i)
            cout << " OK" << endl;
        else {
            cout << " Error" << endl;
            errors++;
        }
    }
    cout << "Errors: " << errors << " of " << n << endl;
}

void task6() {
    cout << "task6" << endl;
    int a1[] = {12, 3, 19, 5, 8, 1};
    int a2[] = {1, 3, 5, 8, 12, 19};

    cout << "Unsorted:" << endl;
    validation(a1, 6);
    cout << "Sorted:" << endl;
    validation(a2, 6);
}


void myvariant() {
    cout << "taskvar15" << endl;
    int a[]  = {20, 33, 11, 45, 16, 27, 8};
    int ab[] = {8, 11, 16, 20, 27, 33, 45};
    int keys15[] = {20, 45, 24};

    for (int i = 0; i < 3; i++) {
        int c1 = 0, c2 = 0;
        int r1 = lS(a, 7, keys15[i], c1);
        int r2 = bS(ab, 7, keys15[i], c2);
        cout << "Key " << keys15[i]
             << ": linear index " << r1 << ", comparisons " << c1
             << " | binary index " << r2 << ", comparisons " << c2 << endl;
    }
}

int main() {
    task1();
    cout << '\n';
    task2();
    cout << '\n';
    task3();
    cout << '\n';
    task4();
    cout << '\n';
    task5();
    cout << '\n';
    task6();
    cout << '\n';
    myvariant();
    return 0;
}