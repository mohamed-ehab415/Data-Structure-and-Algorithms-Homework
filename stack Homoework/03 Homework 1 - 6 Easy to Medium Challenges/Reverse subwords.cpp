#include <iostream>
#include <stack>
#include <string>
using namespace std;

void reverse_subwords(string s){
    stack<char>st;
    s+=' ';  // for last subword
    for (int i = 0; i < s.size(); ++i) {
        if(s[i]!=' ')
            st.push(s[i]);
        else
        {
            while (!st.empty()){
                cout<< st.top();
                st.pop();
                }

            cout << " ";
        }


    }
}




int main (){
    string a="abc d efg xy";
    reverse_subwords(a);
}