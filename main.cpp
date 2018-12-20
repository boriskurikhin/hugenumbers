#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/*
    X < Y = TRUE;
    X >= Y = FALSE

    This function compares two strings, and ultimately decides where (unsigned) str1 < str2
    returns true or false given the above constraint.
*/

bool smaller(string str1, string str2) {
    //grab lengths
    int l1 = str1.size(), l2 = str2.size(); 
    //check if it's smaller just using the lengths
    if (l1 < l2) return true;
    //check if it's bigger just using the lengths
    if (l1 > l2) return false;
    //if both strings are the same length, we should iterate through and check digit by digit
    //starting with the most significant bit!
    for (int i = 0; i < l1; i++) {
        if (str1[i] < str2[i]) return true;
        if (str1[i] > str2[i]) return false;
    }
    //they're identical
    return false;
}

/*
    This is the main adder function, takes two strings and adds them into
    a new answer. Only works with positive numbers
*/
string add(string str1, string str2) {
    //Perfers having the smaller number as the denominator
    if (str1.size() > str2.size()) swap(str1, str2);
    int l1 = str1.size(), l2 = str2.size(), diff = l2 - l1, carry = 0;
    string result = "";
    //Starts with the least significant bit
    for (int i = l1 - 1; i >= 0; i--) {
        //Performs table addition and stores the carry
        int col = ((str1[i] - '0') + (str2[i + diff] - '0') + carry);
        result.push_back(col % 10 + '0');
        carry = col / 10;
    }
    //Completes the larger number
    for (int i = diff - 1; i >= 0; i--) {
        int col = (str2[i] - '0' + carry);
        result.push_back(col % 10 + '0');
        carry = col / 10;
    }
    //Checks if there's a carry
    if (carry) result.push_back(carry + '0');
    //reverses
    reverse(result.begin(), result.end());
    //returns
    return result;
}

int N;
string first, second, secondComp, result;

int main() {
    cin.tie(0); cin.sync_with_stdio(0);
    cin >> N;
    //grabs N
    while(N--) {
        cin >> first >> second;
        secondComp = "";
        
        //If both numbers are negative
        if (first[0] == '-' && second[0] == '-') {
            result = add(first.substr(1), second.substr(1));
            //remove leading 0's
            result.erase(0, result.find_first_not_of('0'));
            if (result == "") result = "0";
            //Output the sum, with negative sign
            cout << (result == "0" ? "" : "-") << result << endl;
        } else if (first[0] != '-' && second[0] != '-') {
            //If both numbers are positive
            result = add(first, second);
            result.erase(0, result.find_first_not_of('0'));
            //Remove trailing zeros
            if (result == "") result = "0";
            cout << result << endl;
        } else {
            int which = 1;
            //If the first number is negative
            if (first[0] == '-') {
                //take out negative sign
                first = first.substr(1);
            } else {
                second = second.substr(1);
                which = 2;
            }

            //If youre subtracting two equal numbers...
            if (first == second) {
                cout << "0" << endl; 
                continue;
            }

            bool neg = false;
            //Perfers bigger number in numerator
            if (smaller(first, second)) {
                neg = true;
                swap(first, second);
            }

            //Pad the smaller number with 9's
            for (int i = 0; i < (first.size() - secondComp.size()); i++) secondComp= "9" + secondComp;
            //9's complement
            for (int i = 0; i < second.size(); i++) secondComp.push_back(9 - (second[i] - '0') + '0');
            //Add complement to the first number
            result = add(first, secondComp);
            //If we have a carry
            if (result.size() > first.size()) {
                string carry = to_string(result[0] - '0');
                result = result.substr(1);
                //Remove it and add it back into the result
                result = add(carry, result);
            } else {
                //If there's no carry just do 9's complement again
                for (int i = 0; i < result.size(); i++) result[i] = (9 - (result[i] - '0') + '0');
            }

            //Remove leading 0's
            result.erase(0, result.find_first_not_of('0'));

            //0 check
            if (result == "") {
                cout << "0" << endl;
                continue;
            }

            cout << (neg ? (which == 2 ? "-" : "") : (which == 1 ? "-" : "")) << result << endl;
        }
    }
    return 0;
}
