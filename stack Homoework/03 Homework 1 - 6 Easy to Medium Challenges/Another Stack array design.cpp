#include <iostream>
#include <cassert>
using namespace std;

class Stack {
private:
    int size { };
    int added_elemnts =0;
    int* array { };
public:
    Stack(int size) :
            size(size) {
        array = new int[size];
    }

    ~Stack() {
        delete[] array;
    }

    bool push(int x) { //  time become o(b)
        if (isFull())
            return false;
        for (int i = added_elemnts-1; i >=0 ;i--)
            array[i+1]=array[i];
        array[0]=x;
        added_elemnts++;
            return true;


    }

    int pop() {//  time become o(b)
        if (isEmpty())
            return false;
        for (int i = 0; i <added_elemnts-1 ; ++i) {
            array[i]=array[i+1];
        }
        added_elemnts--;
    }

    int peek() {
        if (isEmpty())
            return false;
        int result=array[0];
        return true;
    }

    int isFull() {
        return added_elemnts == size ;
    }

    int isEmpty() {
        return added_elemnts == 0;
    }

    void display() {
        for (int i =0; i<added_elemnts; i++)
            cout << array[i] << " ";
        cout << "\n";
    }
};

int main() {


    Stack stk(3);
    stk.push(10);
    stk.push(20);
    stk.push(30);

    if (!stk.push(50))
        cout << "Full Stack\n";

    stk.display();	// 30 20 10


    return 0;
}
