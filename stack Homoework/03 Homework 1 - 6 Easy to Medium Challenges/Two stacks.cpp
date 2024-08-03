#include <iostream>
#include <cassert>
using namespace std;

class Stack {
private:
    int size { };
    int top1 { };
    int top2  { };
    int* array { };
public:
    Stack(int size) :
            size(size), top1(-1),top2(size) {
        array = new int[size];
    }

    ~Stack() {
        delete[] array;
    }

    void push(int id, int value ) {
        assert(!isFull());
        if (id==1)
            array[++top1]=value;
        else
            array[--top2]=value;
    }

    int pop(int id) {
        assert(!isEmpty(id));
        if (id==1)
            return array[top1--];
        if(id==2)
            return  array[top2++];

    }

    int peek(int id) {
        assert(!isEmpty(id));
        if (id==1)
            return array[top1];
        if (id==2)
            return array[top2];
    }

    int isFull() {
        return top1 + 1 >= top2;
    }

    int isEmpty(int id) {
        if (id == 1)
            return top1 == -1;
        return top2 == size;
    }

    void display() {
        for (int i = top1; i >= 0; i--)
            cout << array[i] << " ";
        cout << "\n";
        for (int i = top2; i < size; i++)
            cout << array[i] << " ";
        cout << "\n";
    }


};

int main() {

    Stack stk(10);
    stk.push(2, 5);
    stk.push(2, 6);
    stk.pop(2);
    stk.push(2, 7);
    stk.push(2, 9);

    stk.push(1, 4);
    stk.push(1, 6);
    stk.push(1, 8);
    stk.display();

    return 0;
}
