#include <iostream>
#include <cassert>
#include <climits>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

struct Node {
    int data { };
    Node* next { };
    Node(int data) :
            data(data) {
    }

    ~Node() {
        cout << "Destroy value: " << data << "\n";
    }
};

class LinkedList {
private:
    Node *head { };
    Node *tail { };
    int length = 0;	// let's maintain how many nodes
    vector<Node*> debug_data;	// add/remove nodes you use
    void debug_add_node(Node* node) {
        debug_data.push_back(node);
    }
    void debug_remove_node(Node* node) {
        auto it = std::find(debug_data.begin(), debug_data.end(), node);
        if (it == debug_data.end())
            cout << "Node does not exist\n";
        else
            debug_data.erase(it);
    }


public:
// firt i need function to depuge my code
    void debug_print_address() {
        for (Node* cur = head; cur; cur = cur->next)
            cout << cur << "," << cur->data << "\t";
        cout << "\n";
    }
    void debug_print_node(Node* node, bool is_seperate = false) {
        if (is_seperate)
            cout << "Sep: ";
        if (node == nullptr) {
            cout << "nullptr\n";
            return;
        }
        cout << node->data << " ";
        if (node->next == nullptr)
            cout << "X ";
        else
            cout << node->next->data << " ";

        if (node == head)
            cout << "head\n";
        else if (node == tail)
            cout << "tail\n";
        else
            cout << "\n";
    }
    void debug_print_list(string msg = "") {
        if (msg != "")
            cout << msg << "\n";
        for (int i = 0; i < (int) debug_data.size(); ++i)
            debug_print_node(debug_data[i]);
        cout << "************\n"<<flush;
    }

    string debug_to_string() {
        if (length == 0)
            return "";
        ostringstream oss;
        for (Node* cur = head; cur; cur = cur->next) {
            oss << cur->data;
            if (cur->next)
                oss << " ";
        }
        return oss.str();
    }

    void debug_verify_data_integrity() {
        if (length == 0) {
            assert(head == nullptr);
            assert(tail == nullptr);
        } else {
            assert(head != nullptr);
            assert(tail != nullptr);
            if (length == 1)
                assert(head == tail);
            else
                assert(head != tail);
            assert(!tail->next);
        }
        int len = 0;
        for (Node* cur = head; cur; cur = cur->next, len++)
            assert(len < 10000);	// Consider infinite cycle?
        assert(length == len);
        assert(length == (int)debug_data.size());
    }

    void print() {
        // DON'T change head itself
        for (Node* cur = head; cur; cur = cur->next)
            cout << cur->data << " ";
        cout << "\n";
    }

    void insert_end(int value) {
        Node* item = new Node(value);
        if (!head)
            head = tail = item;
        else
            tail->next = item, tail = item;
        ++length;
    }


    void insert_front(int value){
        Node*new_node= new Node(value);
        new_node->data=value;
        if (!head)
            head= tail=new_node;
        else{
            new_node->next=head;
            head=new_node;

        }
    }

    void test1() {
        cout << "\n\ntest1\n";
        LinkedList list;

        list.insert_end(1);
        list.insert_end(2);
        list.insert_front(3);
        // some actions
        list.print();

        string expected = "3 1 2";
        string result = list.debug_to_string();
        if (expected != result) {
            cout << "no match:\nExpected: " <<
                 expected << "\nResult  : " << result << "\n";
            assert(false);
        }
        list.debug_print_list();
    }
    void test2() {
        cout << "\n\ntest2\n";
        LinkedList list;

        list.insert_front(1);
        list.insert_front(2);
        list.insert_end(3);
        list.insert_front(4);
        // some actions
        list.print();

        string expected = "4 2 1 3";
        string result = list.debug_to_string();
        if (expected != result) {
            cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
            assert(false);
        }
        list.debug_print_list();
    }

};

int main() {

    LinkedList list;
   list.test1();
   list.test2();


    return 0;
}

