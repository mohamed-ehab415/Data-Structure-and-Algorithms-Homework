#include <stack>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

string revmoe(string &s) {
    stack<char> st;
    for (int i = 0; i < s.size(); ++i) {
        if (st.empty()) {
            st.push(s[i]);
        } else if (s[i] == st.top()) {
            st.pop();
        } else {
            st.push(s[i]);
        }
    }

    // Build the resulting string from the stack
    string result;
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }

    reverse(result.begin(), result.end());

    return result;
}

int main (){
    string s ="azxxzy";
    string a= revmoe(s);
    cout << a;
}