// rec14_test.cpp
//by sam cao
#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

// 8. Sorting a list
// 10. Calling the function that prints the list, using ranged-for
void printList(const list<int>& list1) {
    for (int i : list1) {
        cout << i << " ";
    }
    cout << endl;
}
// 9. Calling the function to print the list
void printListIter(const list<int>& list1) {
    for (list<int>::const_iterator iter = list1.begin(); iter != list1.end(); ++iter) {
        cout << *iter << " ";
    }
    cout << endl;
}
// 11. Calling the function that, using auto, prints alterate
// items in the list
void AutoPrintlist(const list<int>& list1) {
    for (auto iter = list1.begin(); iter != list1.end(); ++iter) {
        cout << *iter << " ";
    }
    cout << endl;
}
// 12.  Write a function find that takes a list and value to search for.
//      What should we return if not found
// 13.  Write a function find that takes a list and value to search for.
//      What should we return if not found
auto findList(const list<int>& list1, int val) {
    cout << "findList()" << endl;
    for (auto iter = list1.begin(); iter != list1.end(); ++iter) {
        if (*iter == val)
            return iter;

    }
    return list1.end();
}

// 19. Implement find as a function for lists
template <typename first, typename second>
first ourFind(first begin, first end, const second& target) {
    for (first p = begin; p != end; ++p) {
        if (*p == target) return p;
    }
    return end;
}

bool isEven(int n) { return (n % 2) == 0; }

class Even {
public:
    bool operator()(int n) const { return (n % 2) == 0; }
};

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    cout << "\n=======\n";
    vector<int>value {1,2,3,4,5,6};
    for (int i : value){
        cout << i << " ";
    }
    cout << endl;



    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> list1(value.begin(),value.end());
    for (int i : list1){
        cout << i << " ";

    }
    cout << endl;
    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(value.begin(), value.end());
    for (int i : value){
        cout << i << " ";

    }        cout << endl;
    for (int i : list1){
        cout << i << " ";

    }
    cout << endl;
    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t i = 0; i < value.size(); i += 2) {
        cout << value[i];
    }
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
//     for (size_t i = 0; i < list1.size(); i += 2) {
//         cout << list1[i];
//     }
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for(vector<int>::iterator iter = value.begin(); iter != value.end(); iter +=2){
        cout << *iter << ' ';
    }
    cout << "\n=======\n";

        // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    for (list<int>::iterator iter = list1.begin(); iter != list1.end(); ++ ++iter) {
        cout << *iter;
    }
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    list1.sort();
    printList(list1);
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    printListIter(list1);
    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    printList(list1);
    cout << "=======\n";

//    //
//    // Auto
//    //
//
    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    AutoPrintlist(list1);
    cout << "=======\n";

//
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    if (findList(list1, 3) == list1.end()){
        cout << " Not Found" << endl;
    }else{
        cout << *findList(list1, 3);
    }
    cout << "=======\n";
//
    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found

    cout << "Task 13:\n";
    if (findList(list1, 3) == list1.end()){
        cout << " Not Found" << endl;
    }else{
        cout << *findList(list1, 3);
    }
    cout << "=======\n";

//    // Generic Algorithms

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    if (find(list1.begin(), list1.end(), 3) == list1.end()){
        cout << " Not Found" << endl;
    }else{
        cout << *find(list1.begin(), list1.end(), 3);
    }
    cout << "=======\n";
//
    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    if (find_if(list1.begin(), list1.end(), isEven) == list1.end()){
        cout << " Not Found" << endl;
    }else{
        cout << *find_if(list1.begin(), list1.end(), isEven);
    }
    cout << "=======\n";
//
    // 16. Functor
    cout << "Task 16:\n";
    if (find_if(list1.begin(), list1.end(), Even()) == list1.end()){
        cout << " Not Found" << endl;
    }else{
        cout << *find_if(list1.begin(), list1.end(), Even());
    }
    cout << "=======\n";
//
    // 17. Lambda
    cout << "Task 17:\n";
    if (find_if(list1.begin(), list1.end(), [](int n) { return (n % 2) == 0; }) == list1.end()){
        cout << " Not Found" << endl;
    }else{
        cout << *find_if(list1.begin(), list1.end(), [](int n) { return (n % 2) == 0; });
    }
    cout << "=======\n";
//
//    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* array = new int[list1.size()];
    copy(list1.begin(), list1.end(), array);
    int *find_1 = find(array, array + list1.size(), 2);
    if (find_1 != array + list1.size()) {
        cout << *find_1;
    }else{
        cout << "Not Here" << endl;
    }
    for (size_t i = 0; i < list1.size(); ++i) {
        cout << array[i];
    }
    delete[] array;
    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";

    if (ourFind(list1.begin(), list1.end(), 3) == list1.end()){
        cout << " Not Found" << endl;
    }else{
        cout << *ourFind(list1.begin(), list1.end(), 3);
    }
    cout << "=======\n";
//
    // 20. Implement find as a templated function
    cout << "Task 20:\n";

    if (ourFind(list1.begin(), list1.end(), 3) == list1.end()){
        cout << " Not Found" << endl;
    }else{
        cout << *ourFind(list1.begin(), list1.end(), 3);
    }
    cout << "=======\n";
//
//    //
//    // Associative collections
//    //
//
    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    vector<string> sentence;
    ifstream File("pooh-nopunc.txt");
    string word;
    while(File >> word){
        if(find(sentence.begin(), sentence.end(), word) == sentence.end()){
            sentence.push_back(word);
        }
    }

    cout << "size: " << sentence.size() << endl;
    for(const string& result : sentence){
        cout << result << "\t";
    }
    cout << endl;
    File.close();


    cout << "\n=======\n";
//
//    // 22. Repeating previous step, but using the set
cout << "Task 22:\n";
    ifstream File2("pooh-nopunc.txt");
    set<string> track2;
    string word2;
    while(File2 >> word2){
        //if(track2.find(word2) == track2.end()){
        track2.insert(word2);
        //}
    }
    cout << "size: " << track2.size() << endl;
    for(const string& results : track2){
        cout << results << "\t";
    }
    cout << endl;
    File2.close();

        cout << "=======\n";
//
//    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    ifstream File3("pooh-nopunc.txt");
    map<string, vector<int>> wordMap;
    string word3;
    int index = 0;
    while(File3 >> word3){
        wordMap[word3].push_back(index);
        ++index;
    }
    for(const auto& words : wordMap){
        cout << words.first << " : ";
        for( auto word5 : words.second){
            cout << word5 << " ";
        }
        cout << endl;
    }
    File3.close();
    cout << "=======\n";

}
