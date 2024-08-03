#include <iostream>
#include <stack>
#include <string>
using namespace std;

char match(char c){
    if (c=='(')
        return ')';
    if (c=='{')
        return '}';
    if (c=='[')
        return ']';
}

bool valid(string &s){
    stack<char>st;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i]=='(' || s[i]=='[' || s[i] == '{')
            st.push(s[i]);
        else if (match(st.top())==s[i])
            st.pop();


        }
    return st.empty();
}



int main (){
    string s="(((())))";
    cout << valid(s);

}