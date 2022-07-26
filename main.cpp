#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int N;
pair<string, bool> a, b;

bool bigger(string A, string B) {
    return A.size() == B.size() ? A.compare(B) > 0 : A.size() > B.size();
}

string add(string A, string B) {
    int carry = 0;
    int i = A.size() - 1;
    int j = B.size() - 1;
    string ans = "";
    
    while (j >= 0 && i >= 0) {
        int temp = carry + (A[i--] - '0') + (B[j--] - '0');
        int add = temp % 10;
        carry = temp / 10;
        ans += (char) ('0' + add);
    }

    while (i >= 0) {
        int temp = carry + (A[i--] - '0');
        int add = temp % 10;
        carry = temp / 10;
        ans += (char) ('0' + add);
    }
    
    while (j >= 0) {
        int temp = carry + (B[j--] - '0');
        int add = temp % 10;
        carry = temp / 10;
        ans += (char) ('0' + add);
    }

    if (carry > 0)
        ans += (char) ('0' + carry);

    reverse(ans.begin(), ans.end());
    return ans;
}

string comp(string x) {
    string c = "";
    for (int i = 0; i < x.size(); i++)
        c += (char) ('0' + (9 - (x[i] - '0')));
    return c;
}

string t(string s) {
    while (s.size() > 1 && s[0] == '0')
        s.erase(0, 1);
    return s;
}

string sub() {
    //-a b
    if (a.second) {
        if (bigger(a.first, b.first)) {
            cout << "-";
            return t(comp(add(b.first, comp(a.first))));
        } else {
            return t(comp(add(a.first, comp(b.first))));
        }
    } else {
        if (bigger(b.first, a.first)) {
            cout << "-";
            return t(comp(add(a.first, comp(b.first))));
        } else {
            return t(comp(add(b.first, comp(a.first))));
        }
    }
}

void testcase() {
    if (a.first[0] == '-') {
        a.second = true;
        a.first.erase(0, 1);
    }
    
    if (b.first[0] == '-') {
        b.second = true;
        b.first.erase(0, 1);
    }
    
    a.first = t(a.first);
    b.first = t(b.first);

    if (a.second == b.second) {
        if (a.second) cout << "-";
        cout << add(a.first, b.first) << endl;
    } else {
        cout << sub() << endl;
    }
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(false);

    cin >> a.first >> b.first;
    a.second = false;
    b.second = false;
    testcase();
}
