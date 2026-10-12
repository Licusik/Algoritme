#include <iostream>

using namespace std;

const int maxSize = 10000;
int firstPos;
int found[maxSize];
int foundCount;
int comparisons;
int checkedPositions;

int firstPass = 0;
int allPass = 0;
int testNum = 0;

//1
int textLength(const char text[]) {
    int length = 0;
    while (text[length] != '\0') length++;
    return length;
}

char lowerChar(char value) {
    if (value >= 'A' && value <= 'Z') return value - 'A' + 'a';
    return value;
}

//4
bool prepare(int n, int m) {
    firstPos = -1;
    foundCount = 0;
    comparisons = 0;
    checkedPositions = 0;

    if (m == 0) {
        firstPos = 0;
        found[0] = 0;
        foundCount = 1;
        checkedPositions = 1;
        return true;
    }

    return m > n;
}

//2, 3, 5, 6
void scan(const char text[], const char pattern[], bool ignoreCase, bool onlyFirst) {
    int n = textLength(text);
    int m = textLength(pattern);

    if (prepare(n, m)) return;

    for (int start = 0; start <= n - m; start++) {
        checkedPositions++;
        int j = 0;

        while (j < m) {
            comparisons++;
            char a = text[start + j];
            char b = pattern[j];

            if (ignoreCase) {
                a = lowerChar(a);
                b = lowerChar(b);
            }

            if (a != b) break;
            j++;
        }

        if (j == m) {
            if (foundCount == 0) firstPos = start;
            found[foundCount] = start;
            foundCount++;
            if (onlyFirst) break;
        }
    }
}

//2 
int task2(const char text[], const char pattern[], bool ignoreCase) {
    scan(text, pattern, ignoreCase, true);
    return firstPos;
}

//3 
void task3(const char text[], const char pattern[], bool ignoreCase) {
    scan(text, pattern, ignoreCase, false);
}

//4 
void task4(const int text[], int n, const int pattern[], int m, bool onlyFirst) {
    if (prepare(n, m)) return;

    for (int start = 0; start <= n - m; start++) {
        checkedPositions++;
        int j = 0;

        while (j < m) {
            comparisons++;
            if (text[start + j] != pattern[j]) break;
            j++;
        }

        if (j == m) {
            if (foundCount == 0) firstPos = start;
            found[foundCount] = start;
            foundCount++;
            if (onlyFirst) break;
        }
    }
}

//6
void show(const char label[]) {
    cout << label << ": first = " << firstPos << ", found = ";
    if (foundCount == 0) {
        cout << "none";
    } else {
        for (int i = 0; i < foundCount; i++) {
            if (i > 0) cout << ", ";
            cout << found[i];
        }
    }
    cout << ", matches = " << foundCount
         << ", comparisons = " << comparisons
         << ", positions = " << checkedPositions << '\n';
}

//8
bool sameFound(const int want[], int wantCount) {
    if (foundCount != wantCount) return false;
    for (int i = 0; i < wantCount; i++) {
        if (found[i] != want[i]) return false;
    }
    return true;
}

void report(bool firstOk, bool allOk) {
    testNum++;
    if (firstOk) firstPass++;
    if (allOk) allPass++;

    cout << "Test " << testNum << ": first " << (firstOk ? "OK" : "FAIL")<< ", all " << (allOk ? "OK" : "FAIL") << '\n';
}

void checkText(const char text[], const char pattern[], int wantFirst,const int want[], int wantCount, bool ignoreCase = false) {
    bool firstOk = task2(text, pattern, ignoreCase) == wantFirst;
    task3(text, pattern, ignoreCase);
    report(firstOk, sameFound(want, wantCount));
}

void checkNum(const int text[], int n, const int pattern[], int m,int wantFirst, const int want[], int wantCount) {
    task4(text, n, pattern, m, true);
    bool firstOk = firstPos == wantFirst;
    task4(text, n, pattern, m, false);
    report(firstOk, sameFound(want, wantCount));
}

bool task8() {
    const int none[] = {0};
    const int at0[] = {0};
    const int at4[] = {4};
    const int at6[] = {6};
    const int at5[] = {5};
    const int at48[] = {4, 8};
    const int at02[] = {0, 2};
    const int at13[] = {1, 3};
    const int at14[] = {1, 4};
    const int at0to4[] = {0, 1, 2, 3, 4};
    const int at024[] = {0, 2, 4};
    const int at0510[] = {0, 5, 10};

    const int num10[] = {1, 2, 1, 2, 1};
    const int pat10[] = {1, 2};
    const int num11[] = {4, 5, 6};
    const int pat11[] = {5, 7};
    const int num15[] = {3, 1, 3, 1, 3};
    const int pat15[] = {3, 1, 3};
    const int num16[] = {-2, 0, -2, 0};
    const int pat16[] = {-2, 0};

    firstPass = 0;
    allPass = 0;
    testNum = 0;

    cout << "AutoTest po task8" << '\n';
    checkText("algorithm", "algo", 0, at0, 1);
    checkText("algorithm", "rith", 4, at4, 1);
    checkText("algorithm", "thm", 6, at6, 1);
    checkText("algorithm", "sort", -1, none, 0);
    checkText("aaaaaa", "aa", 0, at0to4, 5);
    checkText("abababa", "aba", 0, at024, 3);
    checkText("abc", "abcd", -1, none, 0);
    checkText("Data data DATA", "data", 5, at5, 1);
    checkText("one two two", "two", 4, at48, 2);
    checkNum(num10, 5, pat10, 2, 0, at02, 2);
    checkNum(num11, 3, pat11, 2, -1, none, 0);
    checkText("", "x", -1, none, 0);


    checkText("banana", "ana", 1, at13, 2);
    checkText("mississippi", "issi", 1, at14, 2);
    checkNum(num15, 5, pat15, 3, 0, at02, 2);
    checkNum(num16, 4, pat16, 2, 0, at02, 2);


    checkText("Data data DATA", "data", 0, at0510, 3, true);
    checkText("abc", "", 0, at0, 1);
    checkText("", "", 0, at0, 1);
    checkNum(num11, 3, pat11, 0, 0, at0, 1);

    cout << "First-position tests: " << firstPass << " / " << testNum << '\n';
    cout << "All-occurrences tests: " << allPass << " / " << testNum << '\n';
    return firstPass == testNum && allPass == testNum;
}

//9
bool control() {
    task3("abababa", "aba", false);
    show("Control example");

    return firstPos == 0 && foundCount == 3
        && found[0] == 0 && found[1] == 2 && found[2] == 4
        && checkedPositions == 5 && comparisons == 11;
}

// variant 15
void myvariant() {
    const char text[] = "algorithm analysis and algorithm design";
    const char pattern[] = "algorithm";

    cout << "taskvar15" << '\n';
    cout << "Text: " << text << '\n';
    cout << "Pattern: " << pattern << '\n';

    task2(text, pattern, false);
    show("First, case-sensitive");
    task3(text, pattern, false);
    show("All, case-sensitive");
    task2(text, pattern, true);
    show("First, ignore case");
    task3(text, pattern, true);
    show("All, ignore case");

    //5 
    const char caseText[] = "Data data DATA";
    const char casePattern[] = "data";

    cout << "Case example" << '\n';
    cout << "Text: " << caseText << '\n';
    cout << "Pattern: " << casePattern << '\n';
    task3(caseText, casePattern, false);
    show("Case-sensitive");
    task3(caseText, casePattern, true);
    show("Ignore case");
}

//7
void experiment(int n, int scenario, const char* name) {
    char text[maxSize + 1];
    const char pattern[] = "aaaaab";
    int m = textLength(pattern);

    for (int i = 0; i < n; i++) text[i] = 'x';
    text[n] = '\0';

    if (scenario == 3) {
        for (int i = 0; i < n; i++) text[i] = 'a';
    } else {
        int start = 0;
        if (scenario == 1) start = (n - m) / 2;
        else if (scenario == 2) start = n - m;

        for (int i = 0; i < m; i++) text[start + i] = pattern[i];
    }

    task2(text, pattern, false);
    cout << n << '\t' << name << '\t' << firstPos << '\t'
         << comparisons << '\t' << checkedPositions << '\n';
}

void task7() {
    int sizes[] = {100, 1000, 10000};
    const char* names[] = {"A beginning", "B middle", "C end", "D absent"};

    cout << "AutoTest po task7" << '\n';
    cout << "Pattern: aaaaab, search stops at the first occurrence" << '\n';
    cout << "N\tScenario\tIndex\tComparisons\tPositions" << '\n';

    for (int k = 0; k < 3; k++) {
        for (int scenario = 0; scenario < 4; scenario++)
            experiment(sizes[k], scenario, names[scenario]);
    }

    cout << "In D every position matches five 'a' and fails on 'b', "
            "so it takes six comparisons per position." << '\n';
}

int main() {
    char text[maxSize];
    char pattern[maxSize];

    //1
    cout << "enter text" << '\n';
    if (!cin.getline(text, maxSize)) {
        cout << "invalid text" << '\n';
        return 0;
    }

    cout << "enter pattern" << '\n';
    if (!cin.getline(pattern, maxSize)) {
        cout << "invalid pattern" << '\n';
        return 0;
    }

    int n = textLength(text);
    int m = textLength(pattern);
    cout << "Text length: " << n << ", pattern length: " << m << '\n';
    cout << "Pattern fits: " << (m <= n ? "yes" : "no") << '\n';

    //8
    if (!task8()) {
        cout << "Tests failed; experiment stopped" << '\n';
        return 0;
    }

    //9
    bool ok = control();
    cout << "Control example: " << (ok ? "OK" : "ERROR") << '\n';
    if (!ok) {
        cout << "Control example failed; experiment stopped" << '\n';
        return 0;
    }

    //4
    myvariant();

    cout << "Your input" << '\n';
    task2(text, pattern, false);
    show("First, case-sensitive");
    task3(text, pattern, false);
    show("All, case-sensitive");
    task2(text, pattern, true);
    show("First, ignore case");
    task3(text, pattern, true);
    show("All, ignore case");

    task7();
    return 0;
}