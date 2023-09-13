// Sam Cao
// this program is to de-code the specific content in the file with specific steps which is the number at the first line in the file, and the final decoded lines need to be printed out with reverse order.
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void print_result(const vector<string>& result);// function to print out the result
char translate_text(int steps,const char& letter );// to translate each character in the eachline in the file, and return a char.
void reverse_line(const vector<string>& result, vector<string>& final_code, int steps);// the function  reverse the order of the lines in the vector by creating a new vector and adding the translated lines into it. return nothing.

int main(){
    ifstream ifs("encrypted.txt");// to check if the file can be opened
    if (!ifs) {
        cerr << "Could not open the file.\n";
        exit(1);// if the file cant be opened, then print the error and exit.
    }
    
    int steps;
    ifs>>steps; // read the integer from the file and define as steps.
    vector<string> result;
    vector<string> final_code;
    string each_line = "";// an empty string was created for storing each line from the file.
    
    while (getline(ifs,each_line)){ // using getline to locate each line in the file.
        result.push_back(each_line);// the each line from the file is stored in the result vector.
    }
    
    reverse_line(result, final_code,steps);// step1 : translate the lines and reverse their order.
    print_result(final_code);// step2 : print out the result vector
    ifs.close();// close the file
}




// the translate_text function is to translate each character in each line
//into correct character with the specific steps.
// parameter : integer steps: the first number from the file which represent how each character move in the file.
//             char letter : each character in the file except for the first number.

char translate_text(int steps,const char& letter ){
    char after;
    after = letter - steps;
    if (after  < 'a'){
        after = after + 26;
    } else if (after > 'z'){
        after = letter - 26;
    }
    return after;
}




// It will reverse the order of translated lines and store these into the result and return nothing.
// parameter: result: the result vector contains each line in the file.
//            steps: an integer first number in the file, how many steps the letters move.
//            final_code: the vector contains the final corrected lines of code.

void reverse_line(const vector<string>& result,vector<string>& final_code,int steps){
    string new_line;
    for(size_t index = result.size() - 1; index > 0; -- index){
        // this loop is iteriting in the result vector from the end to the front, by doing so,
        // it is easier for us to reverse the order of translated characters.
        new_line = result[index];
        for (size_t line_index = 0; line_index < new_line.size(); ++ line_index){
            // this loop is iteriting in the line in the result vector which helps us to access
            // each character in the line and translate them.
            // In  the end, push back these correct code in to the vector again.
            if ((new_line[line_index] >= 'a') && (new_line[line_index] <= 'z')){
                new_line[line_index] = translate_text(steps,new_line[line_index]);
            }
        }
        final_code.push_back(new_line);// store these correct lines in the final_code vector.
    }
}




// print_result is basically printing out the result.
// parameter: result: a vector contains all the correct lines.
// This funtion returns nothing.

void print_result(const vector<string>& result){
    for (size_t position = 0; position < result.size(); ++ position){
        // loop in the vector of the result which accessing each line in the vector and print out the lines
        cout << result[position] << endl;}
    
}






