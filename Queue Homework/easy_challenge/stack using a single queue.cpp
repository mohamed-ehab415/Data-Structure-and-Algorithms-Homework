#include <iostream>
#include <cassert>
using namespace std;

class Queue {
    int size { };
    int front { 0 };
    int rear { 0 };
    int added_elements { };
    int *array { };

public:
    Queue(int size) :
            size(size) {
        array = new int[size];
    }

    ~Queue() {
        delete[] array;
    }

    int next(int pos) {
        ++pos;
        if (pos == size)
            pos = 0;
        return pos;
        //return (pos + 1) % size;	//  Or shorter way
    }

    void enqueue(int value) {
        assert(!isFull());
        array[rear] = value;
        rear = next(rear);
        added_elements++;
    }

    int dequeue() {
        assert(!isEmpty());
        int value = array[front];
        front = next(front);
        --added_elements;
        return value;
    }

    int front_val() {
        assert(!isEmpty());
        return array[front];
    }

    void display() {
        cout << "Front " << front << " - rear " << rear << "\t";
        if (isFull())
            cout << "full";
        else if (isEmpty()) {
            cout << "empty\n\n";
            return;
        }
        cout << "\n";

        for (int cur = front, step = 0; step < added_elements; ++step, cur = next(cur))
            cout << array[cur] << " ";
        cout << "\n\n";
    }

    int isEmpty() {
        return added_elements == 0;
    }

    bool isFull() {
        return added_elements == size;
    }
};

class Stack{
private:
    Queue q;
    int add_elemnt={};
    void insert_front(int value){
        q.enqueue(value);
        int counter=add_elemnt;
        while (counter--)
            q.enqueue(q.dequeue());
        add_elemnt++;
    }
public:
    Stack(int size):q(size)
{

}

void push(int value){  // o(n)
    assert(!q.isFull());
    insert_front(value);

    }
    void pop(){ // o(1)
        -add_elemnt;
        q.dequeue();
    }
    int peek(){
        return q.front_val();
    }
    int isFull() {
        return q.isFull();
    }

    int isEmpty() {
        return q.isEmpty();
    }
};


int main() {
    Stack stk(3);
    stk.push(10);
    stk.push(20);
    stk.push(30);

    while (!stk.isEmpty()) {
        cout << stk.peek() << " ";
        stk.pop();
    } // 30 20 10

    return 0;
}
