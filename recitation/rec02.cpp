#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
    ifstream ifs("life.txt");
    if (!ifs) {
        cerr << "Could not open the file.\n";
        exit(1);
    }
    vector<string> cells;
    string cell;
    while(ifs >> cell){
        cells.push_back(cell);
    }
    cout << "Initial world:" << endl;
    for (size_t i = 0; i < cells.size(); ++i) {
        cout << cells[i] << endl;
    }
    vector<string> newcell;
    for (int n = 1; n < 11; ++n){
        newcell = cells;
        for (size_t row = 0; row < cells.size(); ++row) {
            for (size_t col = 0; col < cells[row].size(); ++col){
                int neigbor = 0;
                if ((row > 0) && (col >0)){
                    if (cells[row -1][col-1] == '*')
                        neigbor += 1;
                }
                if (col > 0){
                    if (cells[row][col-1] == '*')
                        neigbor += 1;
                }
                if ((row > 0) && (col < cells[row].size()-1)){
                    if (cells[row-1][col+1] == '*')
                        neigbor += 1;
                }
                if (row < cells.size()-1){
                    if (cells[row+1][col] == '*')
                        neigbor += 1;
                }
                if ( (col < cells[row].size()-1)){
                    if (cells[row][col+1] == '*')
                        neigbor += 1;
                }
                if ((col < cells[row].size()-1) && (row > 0)){
                    if (cells[row+1][col-1] == '*')
                        neigbor += 1;
                }
                if ((row > 0)){
                    if (cells[row-1][col] == '*')
                        neigbor += 1;
                }
                if ((row < cells.size()-1)&& col < cells[row].size()-1){
                    if (cells[row+1][col+1] == '*')
                        neigbor += 1;
                }
                
                if ((cells[row][col] == '*') && ((neigbor > 3) || (neigbor < 2))){
                    newcell[row][col] = '-';
                }
                
                if ((neigbor == 3)&& cells[row][col] == '-'){
                    newcell[row][col] = '*';
                }
            }
        }
        cout << "====================\nGeneration:" << n << endl;
        for (size_t i = 0; i < newcell.size(); ++ i){
            cout <<newcell[i] <<endl;
        }
        cells = newcell;
        
        
    }
}

