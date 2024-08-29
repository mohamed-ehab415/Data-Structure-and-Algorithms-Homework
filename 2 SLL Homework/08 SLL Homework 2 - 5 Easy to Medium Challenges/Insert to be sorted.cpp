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
    Node(int data) : data(data) {}
    ~Node() {
        cout << "Destroy value: " << data <<" at address "<< this<< "\n";
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
        Node* prev = nullptr;
        for (Node* cur = head; cur; prev = cur, cur = cur->next, len++)
            assert(len < 10000);	// Consider infinite cycle?
        assert(tail == prev);
        assert(length == len);
        assert(length == (int)debug_data.size());
    }

    ////////////////////////////////////////////////////////////
    void print() {
        for (Node* cur = head; cur; cur = cur->next)
            cout << cur->data << " ";
        cout << "\n";
    }


    // These 2 simple functions just to not forget changing the vector and length
    void delete_node(Node* node) {
        debug_remove_node(node);
        --length;
        delete node;
    }

    void add_node(Node* node) {
        debug_add_node(node);
        ++length;
    }


    ////////////////////////////////////////////////////////////



    ////////////////////////////////////////////////////////////



    ////////////////////////////////////////////////////////////
    void insert_front(int value) {		// O(1) time - O(1) memory
        Node* item = new Node(value);
        add_node(item);

        item->next = head;
        head = item;

        if(length == 1)
            tail = head;

        debug_verify_data_integrity();
    }
    void insert_end(int value) {
        Node* item = new Node(value);
        add_node(item);

        if (!head)
            head = tail = item;
        else
            tail->next = item, tail = item;
    }
    void embed_after(Node* node, int value) {
        // Add a node with value between node and its next
        Node* item = new Node(value);
        ++length;
        debug_add_node(item);

        item->next = node->next;
        node->next = item;
    }

    void insert_sorted(int value){

        if (!length||head->data >= value)
                insert_front(value);
        else if (tail->data <= value)
                insert_end(value);
        else {


            for (Node *curr = head, *prev = nullptr; curr; prev = curr, curr = curr->next) {
                if (value <= curr->data) {
                    embed_after(prev, value);
                    break;

                }
            }
        }
            debug_verify_data_integrity();


    }


    void insert_sorted1(int value) {		// O(n) time - O(1) memory
        // 3 special cases for simplicity
        if (!length || value <= head->data)
            insert_front(value);
        else if (tail->data <= value)
            insert_end(value);
        else {
            // Find the node I am less than. Then I am before it
            for (Node *cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next) {
                if (value <= cur->data) {
                    embed_after(prv, value);
                    break;
                }
            }
        }
        debug_verify_data_integrity();

        // This idea is used in Insertion Sort Algorithm
    }

};

void test1() {
    cout << "test1\n";
    LinkedList list;

    list.insert_sorted(10);
    list.insert_sorted(2);
    list.insert_sorted(30);
    list.insert_sorted(4);
    // some actions
    list.print();

    string expected = "2 4 10 30";
    string result = list.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}
int main() {
    test1();

    cout << "bye\n";		// must see it, otherwise RTE
    return 0;
}
