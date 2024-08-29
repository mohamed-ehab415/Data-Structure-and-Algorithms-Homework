#include <iostream>
#include <cassert>
#include <climits>

#include <vector>		// for debug
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

public:

    // Below 2 deletes prevent copy and assign to avoid this mistake
    LinkedList() {
    }
    LinkedList(const LinkedList&) = delete;
    LinkedList &operator=(const LinkedList &another) = delete;

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
        cout << "************\n";
    }

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
        int len = 0;
        for (Node* cur = head; cur; cur = cur->next, len++)
            ;

        assert(length == len);
        assert(length == (int)debug_data.size());

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
        }
    }
    ////////////////////////////////////////////////////////////

    void print() {
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

        debug_add_node(item);
    }

    void delete_node(Node* node) {
        debug_remove_node(node);
        --length;
        delete node;
    }

    void insert_front(int value) {
        Node* item = new Node(value);
        ++length;
        debug_add_node(item);

        item->next = head;
        head = item;

        if(length == 1)
            tail = head;

        debug_verify_data_integrity();
    }
    ///////////////////////////////////solving////////////////////////////////////////
    void delete_even_positions() {

        if(length<=1)
            return;


        for (Node*odd=head,*even=head->next;  even ;) {
            odd->next=odd->next->next;

            if(!odd->next)
                break;

            odd=even->next;
            even->next=odd->next;
            even=odd->next;










        }

    }

};

void test1() {
    cout << "\n\ntest1\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    list.insert_end(5);
    list.delete_even_positions();
    // some actions
    list.print();

    string expected = "1 3 5";
    string result = list.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " <<
             expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test2() {
    cout << "\n\ntest2\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.insert_end(4);
    list.insert_end(5);
    list.insert_end(6);
    list.delete_even_positions();
    // some actions
    list.print();

    string expected = "1 3 5";
    string result = list.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " <<
             expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}

void test3() {
    cout << "\n\ntest3\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.delete_even_positions();
    list.print();

    string expected = "1";
    string result = list.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}


int main() {
    test1();
    test2();
    test3();

    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";

    return 0;
}

