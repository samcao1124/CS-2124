// By Sam Cao
// This following program was designed like a ""warrior""game. When two warriors are fighting,
//the one who with lower strength dead. This program illustrates the starting strength and the
// result of the strength of the warriors in the file.
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
// two variables need to be structed. the warriors' names and strength.
// the names are strings
// the strength are ints
struct Warriors{
    string name;
    int strength;
};

void warriors_command(ifstream& ifs, vector<Warriors>& soldier);
// the warriors command is to read the warriors information from the file,
// which are names and strengths,and store these information in the vector.
void status_command(const vector<Warriors>& soldier);
// the status commnad is to display the status parts of the battle. It only need the warrior vector.
// for example, it will print out how many warriors and updating their strength.
void battle_command(vector<Warriors>& soldier,string& soldier1, string& soldier2);
// The battle command accepts a warrior vector and two strings. these strings are the
// name of the two warriors in a battle. In this part, we can get the results of the battle.
// the calculation of the strength could be made in this part.
size_t find_soldier(const string& warrior_name, const vector<Warriors>& soldier);
// this find soldier is designed to help us to find the index of the warriors
// who in the specific battle. When we located the index of the warrior in the vector,
// we could play with its strength by using its index.

int main(){
    ifstream ifs("warriors.txt");// try to open the file
    if (!ifs) {
        cerr << "Could not open the file.\n";
        exit(1);
    }
    vector<Warriors> soldier;// create a warrior vector and ready to pass it into the later function.
    warriors_command(ifs,soldier);
    // the warrior command function includes all three commands in this program.

}
// parameter: ifstream: ifs (the input file)
//             vector: soldier

void warriors_command(ifstream& ifs, vector<Warriors>& soldier){
    string warrior_name;
    int warrior_strength;
    string command_check;
    while(ifs>>command_check){
        // here we are going to check specificlly which command are we going to play with.
        if(command_check == "Warrior"){// we need to check the first word in the line(which is the command)
            ifs >> warrior_name >> warrior_strength;
            // we create a warrior vector and push into soilder big vector with name and strength
            Warriors battle_man;
            battle_man.name = warrior_name;
            battle_man.strength = warrior_strength;
            soldier.push_back(battle_man);
        }
        else if (command_check == "Status"){
            status_command(soldier); // if it is status command, we call the display stats function.
        }
        else if (command_check == "Battle"){
            string soldier1;// if it is the battle command, we call the battle function which has all the
            string soldier2;// strength calculation done there.
            ifs >> soldier1 >> soldier2;
            battle_command( soldier,soldier1,soldier2);

        }

    }

}

void status_command(const vector<Warriors>&soldier){
    //display the stats of the warriors before and after the battle.
    // parameter : vector: soldier
    cout << "There are: " << soldier.size() << " warriors"<<endl;
    for (size_t each_soldier = 0; each_soldier <soldier.size(); ++ each_soldier){
        // we loop in the whole warrior vector
        cout << "Warriors: " << soldier[each_soldier].name << "," << " strength: "
        <<soldier[each_soldier].strength << endl;
    }
}
// this is a helper to help us to locate the index of the current warriors in the battle.
// we are going to use the index it returned to do the calculation in the battle.
// parameter: string: warrior name
//            vector: soldier
size_t find_soldier(const string& warrior_name, const vector<Warriors>& soldier) {
    for (size_t each_man = 0; each_man < soldier.size(); ++each_man) {
        if (soldier[each_man].name == warrior_name) {
            return each_man;
        }
    }
}
// the battle command has all the batttle information here.
// we have to consider if they both die and the conversation for the winner.
// parameter: string : soldier1 & soldier2
            // vector: soldier
void battle_command(vector<Warriors> &soldier, string &soldier1, string &soldier2) {
    cout << soldier1 << " battles " << soldier2 << endl;
    size_t position_soldier1 = find_soldier(soldier1, soldier);
    size_t position_soldier2 = find_soldier(soldier2, soldier);
    // when they both have same strength and die together.
    if (soldier[position_soldier1].strength == 0 && soldier[position_soldier2].strength == 0) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    // two conversation situations for each winner in each situation
    else if(soldier[position_soldier1].strength == 0) {
        cout << "He's dead,"<< soldier[position_soldier2].name << endl;
    }
    else if(soldier[position_soldier2].strength == 0) {
        cout << "He's dead,"<< soldier[position_soldier1].name<< endl;
    }
    // when they both dead
    else if(soldier[position_soldier1].strength == soldier[position_soldier2].strength) {
        cout << "Mutual Annihilation: " << soldier1 << " and " << soldier2 <<" die at each other's hands" <<endl;
        soldier[position_soldier1].strength = 0;
        soldier[position_soldier2].strength = 0;
    }
    // two situations when two warriors are winning,
    // their strengths have to be minus the loser's strength.
    else if(soldier[position_soldier1].strength < soldier[position_soldier2].strength) {
        cout << soldier2 <<" defeats " << soldier1<<endl;
        soldier[position_soldier2].strength = soldier[position_soldier2].strength - soldier[position_soldier1].strength;
        soldier[position_soldier1].strength = 0;
    }
    else if(soldier[position_soldier1].strength > soldier[position_soldier2].strength) {
        cout << soldier1 <<" defeats " << soldier2<<endl;
        soldier[position_soldier1].strength = soldier[position_soldier1].strength -soldier [position_soldier2].strength;
        soldier[position_soldier2].strength = 0;
    }
}
