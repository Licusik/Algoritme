#include <iostream>

using namespace std;
int pass = 0;
int pass2 = 0;

int len(const char s[]) {
    int n = 0;
    while (s[n] != '\0') n++;
    return n;
}

void show(const int a[], int n) {
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
}

bool Compmasiv(const int a[], const int b[], int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

//1 prefix function
void task1(const char p[], int m, int pi[], int &count) {
    count = 0;
    if (m == 0) return;

    pi[0] = 0;
    int k = 0;

    for (int i = 1; i < m; i++) {
        while (true) {
            count++;
            if (p[i] == p[k]) {
                k++;
                break;
            }
            if (k == 0) break;
            k = pi[k - 1];
        }
        pi[i] = k;
    }
}

void showPrefix(const char p[], int m, const int pi[]) {
    cout << "Index: ";
    for (int i = 0; i < m; i++) cout << i << ' ';
    cout << '\n' << "Char:  ";
    for (int i = 0; i < m; i++) cout << p[i] << ' ';
    cout << '\n' << "Pi:    ";
    show(pi, m);
    cout << '\n';
}

//2 check of the prefix function
bool task2(const char p[], int m, const int want[]) {
    int pi[100];
    int count;

    task1(p, m, pi, count);

    for (int i = 0; i < m; i++) {
        if (pi[i] != want[i]) {
            cout << "Mismatch: index " << i << ", char " << p[i] << ", expected " << want[i] << ", got " << pi[i] << '\n';
            return false;
        }
    }
    return true;
}

bool testPrefix() {
    const char* pats[] = {"a", "aaaa", "abcd", "ababaca", "aabaaab", "abcababcab"};
    int sizes[] = {1, 4, 4, 7, 7, 10};
    int want[6][10] = {
        {0},
        {0, 1, 2, 3},
        {0, 0, 0, 0},
        {0, 0, 1, 2, 3, 0, 1},
        {0, 1, 0, 1, 2, 2, 3},
        {0, 0, 0, 1, 2, 1, 2, 3, 4, 5}
    };

    cout << "Prefix function tests" << '\n';

    for (int i = 0; i < 6; i++) {
        cout << "Prefix test " << i + 1 << ": " << pats[i] << " - ";
        if (task2(pats[i], sizes[i], want[i])) {
            cout << "OK" << '\n';
            pass++;
        } else {
            cout << "FAIL" << '\n';
        }
    }

    cout << "Passed: " << pass << " / 6" << '\n';
    return pass == 6;
}

//3, 4, 5 KMP search; onlyFirst stops after the first match
int kmp(const char t[], int n, const char p[], int m, const int pi[],int res[], int &count, bool onlyFirst, bool trace) {
    count = 0;
    if (m == 0) return 0;

    int found = 0;
    int k = 0;
    int last = -1;

    for (int i = 0; i < n; i++) {
        if (i < last) cout << "Error: text index decreased" << '\n';
        last = i;

        while (true) {
            count++;
            bool eq = (t[i] == p[k]);

            if (trace) {
                cout << "text " << i << ", pattern " << k << ": '" << t[i] << "' vs '" << p[k] << "' - " << (eq ? "match" : "mismatch");
            }

            if (eq) {
                k++;
                if (trace) cout << ", match length " << k << '\n';
                break;
            }

            if (k == 0) {
                if (trace) cout << ", match length 0" << '\n';
                break;
            }

            k = pi[k - 1];
            if (trace) {
                cout << ", match length " << k;
                if (k > 0) cout << " (pi: no return to the start of the pattern)";
                cout << '\n';
            }
        }

        if (k == m) {
            res[found++] = i - m + 1;
            if (trace) cout << "Found at " << i - m + 1 << '\n';
            if (onlyFirst) return found;
            k = pi[m - 1];
        }
    }

    return found;
}

//3 first occurrence
int task3(const char t[], int n, const char p[], int m, const int pi[], int &count, bool trace) {
    int res[1];
    int c = kmp(t, n, p, m, pi, res, count, true, trace);
    return c > 0 ? res[0] : -1;
}

//4 all occurrences, overlapping ones included
int task4(const char t[], int n, const char p[], int m, const int pi[], int res[], int &count, bool trace) {
    return kmp(t, n, p, m, pi, res, count, false, trace);
}

//naive search (practical 8)
int naive(const char t[], int n, const char p[], int m, int res[], int &count, bool onlyFirst) {
    count = 0;
    if (m == 0) return 0;

    int found = 0;

    for (int s = 0; s + m <= n; s++) {
        int j = 0;

        while (j < m) {
            count++;
            if (t[s + j] != p[j]) break;
            j++;
        }

        if (j == m) {
            res[found++] = s;
            if (onlyFirst) return found;
        }
    }

    return found;
}

void showPos(const int a[], int n) {
    if (n == 0) {
        cout << "none";
        return;
    }
    for (int i = 0; i < n; i++) {
        cout << a[i];
        if (i + 1 < n) cout << ", ";
    }
}

//search tests
bool check(const char t[], const char p[], int wantFirst, const int want[], int wantCnt, int num) {
    int n = len(t);
    int m = len(p);
    int pi[100];
    int res[100];
    int resN[100];
    int cPi, cFirst, cAll, cNaive, cNaiveFirst;

    cout << "Search test " << num << ": text \"" << t << "\", pattern \"" << p << "\"" << '\n';

    task1(p, m, pi, cPi);
    int first = task3(t, n, p, m, pi, cFirst, false);
    int cnt = task4(t, n, p, m, pi, res, cAll, false);
    int cntN = naive(t, n, p, m, resN, cNaive, false);
    int firstN = -1;
    int tmp[1];
    if (naive(t, n, p, m, tmp, cNaiveFirst, true) > 0) firstN = tmp[0];

    cout << "First: " << first << ", all: ";
    showPos(res, cnt);
    cout << '\n';

    bool ok = first == wantFirst && cnt == wantCnt && Compmasiv(res, want, wantCnt) && firstN == first && cntN == cnt && Compmasiv(resN, res, cnt);

    cout << "Comparisons: KMP " << cPi + cAll << " (prefix " << cPi << ", search " << cAll << "), naive " << cNaive << " - " << (ok ? "OK" : "FAIL") << '\n';

    return ok;
}

bool testFind() {
    const char* texts[] = {"algorithm", "aaaa", "abababa", "abc", "mississippi", "abcabcabd", "no matches here", "", "aaaaaaab", "abracadabra"};
    const char* pats[] = {"rith", "aa", "aba", "abcd", "issi","abcabd", "xyz", "a", "aaab", "abra"};
    int first[] = {4, 0, 0, -1, 1, 3, -1, -1, 4, 0};
    int cnt[] = {1, 3, 3, 0, 2, 1, 0, 0, 1, 2};
    int all[10][3] = {
        {4}, {0, 1, 2}, {0, 2, 4}, {0}, {1, 4},
        {3}, {0}, {0}, {4}, {0, 7}
    };

    cout << "Search tests" << '\n';

    for (int i = 0; i < 10; i++) {
        if (check(texts[i], pats[i], first[i], all[i], cnt[i], i + 1)) pass2++;
    }

    cout << "Passed: " << pass2 << " / 10" << '\n';
    return pass2 == 10;
}

//one run on the given text and pattern
void run(const char t[], const char p[], bool trace) {
    int n = len(t);
    int m = len(p);
    int pi[1000];
    int res[1000];
    int resN[1000];
    int cPi, cFirst, cAll, cNaive, cNaiveFirst;

    cout << "Text: " << t << '\n';
    cout << "Pattern: " << p << '\n';

    task1(p, m, pi, cPi);
    showPrefix(p, m, pi);

    int first = task3(t, n, p, m, pi, cFirst, trace);
    cout << "First occurrence: " << first << '\n';

    int cnt = task4(t, n, p, m, pi, res, cAll, trace);
    cout << "All occurrences: ";
    showPos(res, cnt);
    cout << '\n';

    int cntN = naive(t, n, p, m, resN, cNaive, false);
    int tmp[1];
    naive(t, n, p, m, tmp, cNaiveFirst, true);

    cout << "KMP: first " << cPi + cFirst << " comparisons (prefix " << cPi << ", search " << cFirst
         << "), all " << cPi + cAll << " (prefix " << cPi << ", search " << cAll << ")" << '\n';
    cout << "Naive: first " << cNaiveFirst << " comparisons, all " << cNaive << '\n';
    cout << "Check: " << (cnt == cntN && Compmasiv(res, resN, cnt) ? "OK" : "ERROR") << '\n';
}

//variant
void myvariant(bool trace) {
    cout << "taskvar" << '\n';
    run("searchingsearchsearch", "search", trace);
}

int main() {
    char text[1001];
    char pat[101];

    cout << "enter text" << '\n';
    if (!cin.getline(text, 1001)) {
        cout << "invalid text" << '\n';
        return 0;
    }

    cout << "enter pattern" << '\n';
    if (!cin.getline(pat, 101) || len(pat) == 0) {
        cout << "invalid pattern" << '\n';
        return 0;
    }

    if (!testPrefix()) {
        cout << "Prefix tests failed; search stopped" << '\n';
        return 0;
    }

    testFind();

    int demo;
    cout << "show trace? (1/0)" << '\n';
    if (!(cin >> demo) || (demo != 0 && demo != 1)) {
        cout << "invalid choice" << '\n';
        return 0;
    }

    run(text, pat, demo == 1);

    myvariant(demo == 1);

    return 0;
}