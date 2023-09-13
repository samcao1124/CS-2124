// by Sam Cao

// Doubly linked list

//  Test code

#include <cstdlib>
#include <iostream>
using namespace std;


class List {

private:
    struct Node{
        Node(int data = 0, Node* prior = nullptr,Node* next = nullptr):data(data),
                                                                       prior(prior),next(next){}
        int data;
        Node* prior;
        Node* next;

    };
    int size1;
    Node* header;
    Node* trailer;

    friend ostream& operator<<(ostream& os, const List& rhs) {
        const Node* curr = rhs.header -> next;
        while(curr != rhs.trailer){
            os << curr -> data << " ";
            curr = curr -> next;
        }
        return os;
    }
public:

    List():size1(0),header(new Node()),trailer(new Node()){
        header->next=trailer;
        trailer->prior=header;
    }
    //push_back(int data)
    void push_back(int data){
        size1 ++;
        Node* old=trailer->prior;
        Node* newptr=new Node(data, old, trailer);
        trailer->prior=newptr;
        old->next =newptr;

    }
    void pop_back(){
        size1--;
        Node* orig = trailer -> prior;
        trailer->prior = orig->prior;
        orig-> prior -> next = trailer;
        delete orig;
    }
    int& front(){return header -> next -> data;}
    int front()const{return header -> next -> data;}
    int& back(){return trailer -> prior -> data;}
    int back()const{return trailer -> prior -> data;}
    int size() const {return size1;}

    void push_front(int data){
        size1 ++;
        Node* old = header->next;
        Node* newptr=new Node(data, header, old);
        old->prior=newptr;
        header->next =newptr;


    }
    void pop_front(){
        size1--;
        Node* orig = header -> next;
        header->next = orig -> next ;
        orig-> next -> prior = header;
        delete orig;
    }

    void clear(){
        while(size1){
            pop_back();
        }
    }




    int operator[](size_t index) const {
        const Node* curr = header;
        if(index <= size1 - 1){
            for (size_t i = 0; i <= index; ++i ){
                curr = curr->next;
            }
        }
        return curr -> data;

    }

    int& operator[](size_t index) {
        Node* curr = header;
        if(index <= size1 - 1){
            for (int i = 0; i <= index; ++i ){
                curr = curr->next;
            }

        }
        return curr -> data;
    }

    class Iterator{
        friend List;
        friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
            return (lhs.nodePtr == rhs.nodePtr);
        }
        friend bool operator!=(const Iterator& lhs, const Iterator& rhs){
            return (lhs.nodePtr != rhs.nodePtr);
        }
    public:
        Iterator(Node* nodePtr):nodePtr(nodePtr){}
        Iterator& operator++() {
            if(nodePtr && nodePtr->next){
                nodePtr = nodePtr -> next;
            }
            return *this;
        }


        Iterator& operator--() {
            if(nodePtr && nodePtr->prior){
                nodePtr = nodePtr -> prior;
            }
            return *this;
        }

        int& operator*() { // dereference operator
            return nodePtr -> data;
        }

        int operator*() const { // dereference operator
            return nodePtr -> data;
        }

    private:
        Node* nodePtr;

    };
    Iterator begin() {

        return Iterator(header->next);
    }

    Iterator end() {

        return Iterator(trailer);
    }

    Iterator insert(const Iterator& iter, int value){
        size1++;
        Node* orig=iter.nodePtr->prior;
        Node* node=new Node(value,orig,iter.nodePtr);
        orig->next=node;
        iter.nodePtr->prior=node;
        Iterator result(node);
        return Iterator(node);// Iterator(node)

    }
    Iterator erase(const Iterator& iter){
        size1--;
        Node* orig=iter.nodePtr;
        orig->prior->next=orig->next;
        orig->next->prior=orig->prior;
        delete iter.nodePtr;
        return Iterator (iter.nodePtr->next);
    }

};





// Task 1
void printListInfo(const List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList){
//     theList.front() = 17;
//     theList.back() = 42;
// }

void changeFrontAndBack(List& theList){
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}
//
//// Task 8
//void doNothing(List aList) {
//    cout << "In doNothing\n";
//    printListInfo(aList);
//    cout << endl;
//    cout << "Leaving doNothing\n";
//}

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";

    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    printListInfo(myList);
    cout << "===================\n";

//    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);


    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";
//
//    // Task 8
//    cout << "\n------Task Eight------\n";
//    cout << "Copy control\n";
//    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
//    myList.clear();
//    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
//    printListInfo(myList);
//    cout << "Calling doNothing(myList)\n";
//    doNothing(myList);
//    cout << "Back from doNothing(myList)\n";
//    printListInfo(myList);
//
//    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
//    List listTwo;
//    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
//    printListInfo(listTwo);
//    cout << "listTwo = myList\n";
//    listTwo = myList;
//    cout << "myList: ";
//    printListInfo(myList);
//    cout << "listTwo: ";
//    printListInfo(listTwo);
//    cout << "===================\n";
}
