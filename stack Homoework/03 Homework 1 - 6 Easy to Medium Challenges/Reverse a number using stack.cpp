#include <iostream>
#include <stack>
#include <string>
using namespace std;


// i will do two ways

int reverse_number1(int num){
    if (num==0)
        return 0;
    stack<int> st;
    while (num){
        st.push(num%10);
        num/=10;
    }
    int tense=1;
    while (!st.empty()){
        num+=tense*st.top();
        tense*=10;
        st.pop();
    }
    return num;
}



void reverse_number2(int n){
    string str= to_string(n);
stack<char> st;
    for (int i = 0; i < str.size(); ++i) {
        st.push(str[i]);
    }
    for (int i = 0;  !st.empty() ; ++i) {
        cout << st.top();
        st.pop();

    }
}



int main (){
    int num=1234;
    int target=reverse_number1(num);
    cout << target;
}