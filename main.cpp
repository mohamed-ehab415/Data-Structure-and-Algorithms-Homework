#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;

class vector {
private:
    int *arr;
    int size;
    int capcity ;
    void expend_ccapcity(){
        capcity*=2;
        int *arr2=new int[capcity]{};
        for (int i = 0; i <size ; ++i) {
            arr2[i]=arr[i];
        }
        swap(arr,arr2);
        delete[] arr2;
    }
public:
    vector(int size): size(size){
        if (size==0)
            size=1;
        capcity=size+10;
        arr=new int[capcity]{};

    }


    ~vector(){
        delete[] arr;
        arr= nullptr;

    }
    int get_size(){
        return size;
    }
    int get(int idx){
        assert(0<=idx && idx <size);
        return arr[idx];
    }
    void set(int idx,int val){
        assert(0<=idx && idx <size);
        arr[idx]=val;

    }
    void print() {
        for (int i = 0; i < size; ++i)
            cout << arr[i] << " ";
        cout << "\n";
    }
    int find(int value){
        for (int i = 0; i < size; ++i) {
            if (arr[i]==value)
                return value;

        }
        return -1;
    }
    int get_front(){
        return arr[0];
    }
    int get_back(){
        return arr[size-1];
    }
    void push_back(int value){
        if (capcity==size)
            expend_ccapcity();
        arr[size++]=value;
    }
    void insert (int idx , int value ){
        assert(0<=idx && idx<size);
        if (capcity==size)
            expend_ccapcity();
        for (int i = size-1; i >=idx ; --i) {
            arr[i+1]=arr[i];

        }
        arr[idx]=value;
        ++size;

    }
    void Right_rotation(){
        if (size <= 1)
            return;
        int last=arr[size-1];
        int idx=size-2;
        for (int i = idx; i >=0 ; --i) {
            arr[i+1]=arr[i];

        }
        arr[0]=last;



    }

    void left_rotation(){
        if (size<=1)
            return;
        int first_elemnt=arr[0];
        int idx=1;
        for (int i = idx; i <=size-1 ; ++i) {
            arr[i-1]=arr[i];

        }
        arr[size-1]=first_elemnt;
    }

    void right_rotate_time(int times) {
        while (times--)
            Right_rotation();
    }
    int pop(int idx){

        int value= arr[idx];
        for (int i =idx+1; i <size ; ++i) {
            arr[i-1]=arr[i];

        }
        return value;

    }
    int find_transposition(int value){
        for (int i = 0; i < size; ++i) {
            if (arr[i] == value) {
                if (i == 0)
                    return 0;
                swap(arr[i-1],arr[i]);
                return i-1;
            }

        }
        return -1;
    }
};



int main(){


}