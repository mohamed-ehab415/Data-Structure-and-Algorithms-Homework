#include <iostream>
#include <cassert>
#include <climits>

#include <vector>		// for debug
#include <algorithm>
#include <sstream>
using namespace  std;

struct Node {
    int data;
    Node*next={};
    Node*prev={};
    Node(int data):data(data){};
};

class LinkedList{
private:
    Node*head={};
    Node*tail={};
    int length=0;
    vector<Node*> debug_data;	// add/remove nodes you use

    void debug_add_node(Node* node) {
        debug_data.push_back(node);
    }
    void debug_remove_node(Node* node) {
        auto it = find(debug_data.begin(), debug_data.end(), node);
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

        if (node->prev == nullptr)
            cout << "X\t";
        else
            cout << node->prev->data << "\t";

        cout << " <= [" <<node->data << "]\t => \t";

        if (node->next == nullptr)
            cout << "X\t";
        else
            cout << node->next->data << "\t";

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
        cout << "************\n" << flush;
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
            assert(!head->prev);
            assert(!tail->next);
        }
        int len = 0;
        for (Node* cur = head; cur; cur = cur->next, len++) {
            if (len == length-1)	// make sure we end at tail
                assert(cur == tail);
        }

        assert(length == len);
        assert(length == (int )debug_data.size());

        len = 0;
        for (Node* cur = tail; cur; cur = cur->prev, len++) {
            if (len == length-1)	// make sure we end at head
                assert(cur == head);
        }
        cout << "\n";
    }



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
    // """"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

    void disply(){
        if (!head)
            cout << "empty";
        else {
            for (Node*curr= head; curr ; curr=curr->next) {
                cout << curr->data << " ";

            }
            cout << endl ;
        }

    }


    void link(Node*first,Node*second){
        if (first)
            first->next=second;
        if(second)
            second->prev=first;
    }

    void insert_end(int value){
        Node *new_node=new Node(value);
        add_node(new_node);
        if(!head)
            head=tail=new_node;
        else{
            link(tail,new_node);
            tail=new_node;
        }
    }
    void insert_front(int value){
        Node*new_node=new Node(value);
        add_node(new_node);
        if (!head)
            head=tail=new_node;
        else
        {
            link(new_node,head);
            head=new_node;
        }

    }
    void embed_after(Node*prev , int value ){
        Node*middle=new Node(value);
        add_node(middle);

        Node*after =prev->next;
        link(prev,middle);
        link(middle,after);
    }




    void insert_sorted(int value) {		// O(n) time - O(1) memory
        if (!length || value <= head->data)
            insert_front(value);
        else if (tail->data <= value)
            insert_end(value);
        else {
            // Find the node I am less than. Then I am before it
            for (Node *cur = head; cur; cur = cur->next) {
                if (value <= cur->data) {
                    embed_after(cur->prev, value);
                    break;
                }
            }
        }
        debug_verify_data_integrity();

        // This idea is used in Insertion Sort Algorithm
    }

    void delete_front(){
        if (!head)
            cout << "empty" << endl ;
        Node*curr=head->next;
        delete_node(head);
        head=curr;

        //data integrity
        if (head)
            head->prev= nullptr;
        else if (!head)
            head=tail= nullptr;
    }

    void delete_end(){
        if (!head)
            cout << "empty"<< endl;
        Node *temp=tail->prev;
        delete_node(tail);
        tail=temp;

        //data integrity
        if(tail)
            tail->next= nullptr;
        if (!length)
            head= nullptr;


    }
    Node* delete_and_link2(Node*curr){
        Node *rect=curr->prev;
        link(curr->prev , curr->next);
        delete_node(curr);
        return rect;

    }
    Node* delete_and_link(Node* cur) {

        Node* ret = cur->prev;
        link(cur->prev, cur->next);
        delete_node(cur);

        return ret;
    }

//////////////   slove problem      //////////////////////




    void delete_even_positions() {
        if (length <= 1)
            return;
        //cur is always odd and ->next is even
        for(Node *cur = head; cur && cur->next; cur = cur->next) {
            delete_and_link(cur->next);
            if (!cur->next)
                tail = cur;	// in even length, the tail will change
        }
    }

};
void test0() {
    cout << "\n\ntest0\n";
    LinkedList list;

    list.insert_end(1);
    list.insert_end(2);
    list.insert_end(3);
    list.delete_even_positions();
    // some actions
    list.print();

    string expected = "1 3";
    string result = list.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " <<
             expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    list.debug_print_list("********");
}


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



int main (){
    LinkedList list;
   // test0();
    test1(); //done
    //test2();
    test3();




}