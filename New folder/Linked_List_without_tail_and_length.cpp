#include <iostream>
#include <cassert>
#include <climits>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;


struct  Node{
    int data;
    Node *next;
    Node(int data):data(data){}


};

class Linkedlist{
private:
    Node*head={};
public:
void add_element(int value){
    Node *new_node=new Node(value);

        new_node->next=head;
        head=new_node;

}

void print(){
    if (!head)
        cout << 'Empty' << endl;
    for (Node*curr = head;  curr ; curr=curr->next) {
        cout << curr->data << " ";

    }
    cout << endl;
}

Node*get_tail(){
    if(!head)
        return nullptr;

    Node *curr=head;
    for (;curr->next  ;curr=curr->next) {
    }
    return curr;
}
};

int main(){

    Linkedlist list;

    list.add_element(10);
    list.add_element(20);
    list.add_element(30);
    list.add_element(40);
    list.add_element(50);
    list.add_element(60);

    list.print();	// 60 50 40 30 20 10
    cout<<list.get_tail()->data;	// 10


}