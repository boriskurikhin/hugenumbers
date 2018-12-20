#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <math.h>

using namespace std;

/*
    X < Y = TRUE;
    X >= Y = FALSE
*/
bool smaller(string str1, string str2) {
    int l1 = str1.size(), l2 = str2.size();
    if (l1 < l2) return true;
    if (l1 > l2) return false;
    for (int i = 0; i < l1; i++) {
        if (str1[i] < str2[i]) return true;
        if (str1[i] > str2[i]) return false;
    }
    return false;
}

string add(string str1, string str2) {
    if (str1.size() > str2.size()) swap(str1, str2);
    int l1 = str1.size(), l2 = str2.size(), diff = l2 - l1, carry = 0;
    string result = "";
    for (int i = l1 - 1; i >= 0; i--) {
        int col = ((str1[i] - '0') + (str2[i + diff] - '0') + carry);
        result.push_back(col % 10 + '0');
        carry = col / 10;
    }
    for (int i = diff - 1; i >= 0; i--) {
        int col = (str2[i] - '0' + carry);
        result.push_back(col % 10 + '0');
        carry = col / 10;
    }
    if (carry) result.push_back(carry + '0');
    reverse(result.begin(), result.end());
    return result;
}

int N;
string first, second, secondComp, result;

int main() {
    cin.tie(0); cin.sync_with_stdio(0);
    cin >> N;
    while(N--) {
        cin >> first >> second;
        secondComp = "";
        
        if (first[0] == '-' && second[0] == '-') {
            result = add(first.substr(1), second.substr(1));
            
            result.erase(0, result.find_first_not_of('0'));
            if (result == "") result = "0";
            
            cout << (result == "0" ? "" : "-") << result << endl;
        } else if (first[0] != '-' && second[0] != '-') {
            result = add(first, second);
            
            result.erase(0, result.find_first_not_of('0'));
            if (result == "") result = "0";
            
            cout << result << endl;
        } else {
            if (first[0] == '-') {
                first = first.substr(1);
                bool neg = false;
                if (smaller(first, second)) {
                    neg = true;
                    swap(first, second);
                }
                secondComp = "";

                for (int i = 0; i < second.size(); i++) secondComp.push_back(9 - (second[i] - '0') + '0');
                for (int i = 0; i < (first.size() - secondComp.size()); i++) secondComp= "9" + secondComp;
                
                result = add(first, secondComp);
                
                if (result.size() > first.size()) {
                    string carry = to_string(result[0] - '0');
                    result = result.substr(1);

                    result = add(carry, result);
                } else {
                    for (int i = 0; i < result.size(); i++) result[i] = (9 - (result[i] - '0') + '0');
                }

                result.erase(0, result.find_first_not_of('0'));

                if (result == "") {
                    cout << "0" << endl;
                    continue;
                }

                cout << (neg ? "" : "-") << result << endl;
            } else {
                second = second.substr(1);
                bool neg = false;
                if (smaller(first, second)) {
                    neg = true;
                    swap(first, second);
                }
                secondComp = "";
                for (int i = 0; i < second.size(); i++) secondComp.push_back(9 - (second[i] - '0') + '0');
                for (int i = 0; i < (first.size() - secondComp.size()); i++) secondComp = "9" + secondComp;
                
                result = add(first, secondComp);

                if (result.size() > first.size()) {
                    string carry = to_string(result[0] - '0');
                    result = result.substr(1);

                    result = add(carry, result);
                } else {
                    for (int i = 0; i < result.size(); i++) result[i] = (9 - (result[i] - '0') + '0');
                }

                result.erase(0, result.find_first_not_of('0'));

                if (result == "") {
                    cout << "0" << endl; 
                    continue;
                }

                cout << (neg ? "-" : "") << result << endl;
            }
        }
    }
    return 0;
}
