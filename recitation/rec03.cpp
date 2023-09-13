#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Chemistry {
    vector<string> chem_formula;
    int carbon_num;
    int helium_num;
};

void user_file_input(ifstream& file_to_open);
void sort_vector(vector<Chemistry>& formula);
void fill_the_stream(ifstream& file_to_open,vector<Chemistry>& formula);
void print_formula_name(const vector<Chemistry>& Chemistry_to_print);
size_t insert_add_formula(int carbon_count,int helium_count,const vector<Chemistry>& formula);



int main(){
    vector<Chemistry> formula;
    ifstream ChemStream;
    user_file_input(ChemStream);
    fill_the_stream(ChemStream,formula);
    sort_vector(formula);
    print_formula_name(formula);
    
}

void user_file_input(ifstream& file_to_open){

    do {
        file_to_open.clear();
        cout << "Enter the filename :" <<endl;
        string file_name;
        cin >> file_name;
        file_to_open.open(file_name);
        if(!file_to_open){
            cout<< "Please Re-enter the file" << endl;
        }
        
    }while(!file_to_open);
}

void sort_vector(vector<Chemistry>& formula) {
    for(size_t h = 0;h<formula.size();++h){
        for(size_t j = 0;j<formula.size()-1-h;++j){
            if(formula[j].carbon_num > formula[j+1].carbon_num){
                Chemistry sort_compound = formula[j];
                formula[j] = formula[j+1];
                formula[j+1] = sort_compound;
            }
            else if (formula[j].carbon_num == formula[j+1].carbon_num){
                if(formula[j].helium_num > formula[j+1].helium_num){
                    Chemistry sort_compound = formula[j];
                    formula[j] = formula[j+1];
                    formula[j+1] = sort_compound;
                }
            }
        }
    }
    
}


void fill_the_stream(ifstream& file_to_open,vector<Chemistry>& formula){
    int carbon_count;
    int helium_count;
    char c,h;
    string compound;
    while(file_to_open >>compound >> c >> carbon_count >> h >> helium_count){
        size_t result = insert_add_formula(carbon_count, helium_count,formula);
        if (result == formula.size()){
            Chemistry newest_formula;
            newest_formula.carbon_num = carbon_count;
            newest_formula.helium_num = helium_count;
            
            newest_formula.chem_formula.push_back(compound);
            formula.push_back(newest_formula);
            
        }else{
            formula[insert_add_formula(carbon_count, helium_count, formula)].chem_formula.push_back(compound);
        }
    }
}



void print_formula_name(const vector<Chemistry> & formula){
    for(size_t i = 0; i < formula.size();++i){
        cout << 'C'<< formula[i].carbon_num << 'H' << formula[i].helium_num << " ";
        for(size_t j = 0; j < formula[i].chem_formula.size();++j){
            cout << formula[i].chem_formula[j] << " "   ;
        }
        cout<<endl;
    }
}

size_t insert_add_formula(int carbon_count,int helium_count,const vector<Chemistry>& formula){
    size_t index = formula.size();
    for (size_t x = 0;x < formula.size();++x){
        if ((carbon_count == formula[x].carbon_num) && (helium_count == formula[x].helium_num)){
            return x;
        }
        
    }
    return index;
}

