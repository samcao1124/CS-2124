// by sam cao
// this program is mainly used for displaying the battle between nobles and their warriors.
// there are two classes in this program. 1. Warrior 2. Noble
// based on the last assignment, this program added the main and
//display the warriors who are not hired.
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Warrior{
    // output operator for warrior class.
    friend ostream& operator <<(ostream&os,const Warrior& warriors){
        os << "\t"<< warriors.warrior_name << ": " << warriors.strength << endl;
        return os;
    }
public:
    // Constructor: default warrior: given name, strength, hire status = false
    Warrior(const string& warrior_name, double strength):
            warrior_name(warrior_name), strength(strength), ishired(false){}

    // return the name of warrior
    const string& getName() const {return warrior_name;}

    // setter: set strength
    void set_strength(double strengthRatio){strength *= strengthRatio;}

    void set_hired(bool is_hired){this->ishired = is_hired;}

    // return the strength
    double get_strength() const {return strength;}

    // return hire status

    bool hire()const{return ishired;}

    // fire myself
    void fire(bool fire){ishired = fire;}


private:
    double strength;
    string warrior_name;
    bool ishired;
};


class Noble{
    // output operator for nobel: includes name
    friend ostream& operator <<(ostream&os,const Noble& noble){
        os << noble.noble_name << " has an army of " << noble.troop.size() << endl;
        for (const Warrior* warrior: noble.troop){
            os<< *warrior;
        }

        return os;
    }

public:
    // Constructor: given name, alive status
    Noble(const string& noble_name):noble_name(noble_name),is_alive(true){}

    // return alive status
    bool alive() const{return is_alive;}


    // hire one warrior： can only hire if nobel is alive
    bool hire(Warrior& warrior){
        if (warrior.hire() || !alive()) return false;
        troop.push_back(&warrior);
        // tell the warrior that they are hired
        warrior.set_hired(true);
        return true;
    }

    // Locate a warrior's position in troop.
    size_t find_warrior(const Warrior& warrior){
        for (size_t posit = 0; posit < troop.size(); ++posit) {
            if( troop[posit] == &warrior) return posit;
        }
        return troop.size();
    }

    // fire one warrior from the troop
    bool fire(Warrior& warrior) {
        if (alive() && warrior.hire()) {
            size_t position = find_warrior(warrior);

            if (position == troop.size()) {
                return false;
            } else {
                for (size_t i = position; i < troop.size() - 1; ++i) {
                    troop[i] = troop[i + 1];
                }
                troop.pop_back();
                cout << "You don't work for me anymore " << warrior.getName()
                     << "! -- " << noble_name << "." << endl;
                warrior.set_hired(false);
                return true;
            }
        }else{
            return false;
        }
    }

    // update alive status --> death
    void set_noble_death(){ is_alive = false;}
    const string& get_noble_name() const {return noble_name;}
    // sum up the strength of all warriors
    double get_strength() const{
        double total_strength= 0;
        for (Warrior* each : troop) {
            total_strength += each->get_strength();
        }
        return total_strength;
    }

    // update strength of warriors in the troop after battle
    void update_troop(double ratio) {
        for (Warrior* each: troop) {
            each->set_strength(ratio);
        }
    }

    // self battles enmey with three cases.
    void battle(Noble& enemy){
        cout << noble_name << " battles " << enemy.noble_name << endl;
        if (alive() && !enemy.alive()) {
            cout << "He's dead, " << noble_name << endl;
        } else if (!alive() && enemy.alive()) {
            cout << "He's dead, " << enemy.noble_name << endl;
        } else if (!alive() && !enemy.alive()){
            cout << "Oh, NO!  They're both dead!  Yuck!" <<endl;
        } else {
            double self_strength = get_strength();          // get self total strength
            double enemy_strength = enemy.get_strength();   // get enemy total strength
            double ratio = self_strength / enemy_strength;  // calculate ratio

            // Case # 1: my strength < enemy strength --> lose
            if (ratio < 1) {
                set_noble_death();
                update_troop(0);
                enemy.update_troop(1 - ratio);
                cout << enemy.noble_name << " defeats " << noble_name << endl;
            }
                // Case # 2: my strength = enemy strength --> tie
            else if (ratio == 1) {
                set_noble_death();
                enemy.set_noble_death();
                update_troop(0);
                enemy.update_troop(0);
                cout << "Mutual Annihalation: " << noble_name << " and " << enemy.noble_name
                     << "die at each other's hands" << endl;
            }
                // Case # 3: my strength > enemy strength --> win
            else {
                enemy.set_noble_death();
                update_troop(1 - 1 / ratio);
                enemy.update_troop(0);
                cout << noble_name << " defeats " << enemy.noble_name << endl;
            }
        }
    }

private:
    vector<Warrior*> troop;
    bool is_alive;
    string noble_name;
};


// Prototypes
// two methods need to add
void clear(vector<Noble*>&noble,vector<Warrior*>&warrior);
void stats(const vector<Noble*>& noble,const vector<Warrior*>& warrior);

// functions need to add
size_t locate_noble(const vector<Noble*>& noble,const string& noble_name);// find the index of the noble
size_t locate_warrior(const vector<Warrior*>& warrior,const string& warrior_name);// find the index of the warrior




int main() {
    // read the file
    ifstream file("nobleWarriors.txt");
    if (!file){
        cerr << "Could not open the file.\n";
        exit(1);// print error when the file cant be opened
    }
    string command;
    string noble_name;
    string warrior_name;
    double warrior_strength;
    vector<Noble*> noble;
    vector<Warrior*> warrior;

    // read the command from the file
    while (file >> command){
        if (command == "Noble"){ // when the command is noble, create the noble
            file >> noble_name; // read into the noble name and find the noble with its warriors.
            size_t noble_position = locate_noble(noble,noble_name);
            if (noble_position < noble.size()){
                // when the noble's name is already in the vector (already exist)
                cout << "This Noble is already here" << endl;
            }else{
                // add the noble on the heap
                noble.emplace_back(new Noble(noble_name)); // add on the heap
            }
        }
        else if(command == "Warrior"){
            file >> warrior_name; // warrior name created
            file >> warrior_strength;
            size_t warrior_positon = locate_warrior(warrior,warrior_name);
            //a Warrior with a given name already exists
            if (warrior_positon < warrior.size()){
                cout << "This warrior is already here, cant hire twice" << endl;
            }else{
                // add the warrior on the heap
                warrior.emplace_back(new Warrior(warrior_name,warrior_strength)); // add on the heap
            }
        }
        else if(command == "Hire"){// to hire the warriors
            // If a Noble tries to hire a Warrior and either of them do not exist or the Warrior is already hired.
            size_t noble_position;
            size_t warrior_position;
            file >> noble_name >>warrior_name;
            noble_position = locate_noble(noble,noble_name); // find the noble
            warrior_position = locate_warrior(warrior,warrior_name);// find the warrior
            // case 1 ---> if the warrior name is not in the vector, error rarised
            if(noble_position == noble.size() || warrior_position == warrior.size()){
                cout << "Attempting to hire using unknown warrior:" << warrior_name << endl;
            }
                // if the warrior and the noble are both not dead, the noble can hire the warrior
            else if (warrior[warrior_position]->get_strength()!= 0 && noble[noble_position]->alive()){
                noble[noble_position]->hire(*warrior[warrior_position]);
            }
        }
        else if(command == "Fire"){ // fire command
            size_t noble_position;
            size_t warrior_position;
            file >> noble_name >>warrior_name;
            noble_position = locate_noble(noble,noble_name);// find the warrior and the noble
            warrior_position = locate_warrior(warrior,warrior_name);

            // same with the hire, warrior and noble have to be both alive to do the fire.
            if (warrior[warrior_position]->get_strength()!= 0 && noble[noble_position]->alive()){
                noble[noble_position]->fire(*warrior[warrior_position]);
            //  when the warrior not in the vector, error raised
            }else if(noble_position == noble.size() || warrior_position == warrior.size()){
                cout << "Attempting to fire using unknown warrior:" << endl;
            }
        }
        else if (command == "Battle"){
            string noble_1;
            string noble_2;
            file >> noble_1 >> noble_2;
            // find the two nobles will be in the battle
            size_t noble_1_position = locate_noble(noble,noble_1);
            size_t noble_2_position = locate_noble(noble,noble_2);
            // case1 ----> when the noble is not found in the vector, the error raised
            if (noble_1_position == noble.size() ||noble_2_position == noble.size()){
                cout << "ONE OF THE NOBLE DOES NOT EXIST, CANT FIGHT" << endl;
            }else{ // case 2 ----> else, we can battle
                noble[noble_1_position]->battle(*noble[noble_2_position]);
            }
        }
        else if (command == "Status"){ // stats command
            stats(noble,warrior);

        }
        else if (command == "Clear"){// clear command
            clear(noble,warrior);
        }
    }
    file.close();// close the file
}

// in order to create the noble and put the correct warrior in the noble
// a locate noble and a locate warrior function need to be created.
// return size_t ----> index of the noble
size_t locate_noble(const vector<Noble*>& noble,const string& noble_name){
    size_t noble_index = noble.size();
    for (size_t each_noble = 0; each_noble < noble.size(); ++ each_noble){
        if(noble[each_noble]->get_noble_name() == noble_name){
            noble_index = each_noble;
        }
    }
    return noble_index;
}
// to find the index of the warrior
// return ---> size_t index of the warrior
size_t locate_warrior(const vector<Warrior*>& warrior,const string& warrior_name) {
    // find the index of the warrior
    size_t warrior_index = warrior.size();
    for (size_t each_warrior = 0; each_warrior < warrior.size();++ each_warrior){
        if(warrior[each_warrior]->getName() == warrior_name){
            warrior_index = each_warrior;

        }
    }
    return warrior_index;
}

// a fumction to display the information of the battle. the hired information etc.
// return nothing
// parameter : const vector<Noble*>& noble,const vector<Warrior*>& warrior
void stats(const vector<Noble*>& noble,const vector<Warrior*>& warrior){
    cout << "Status" << endl;
    cout << "======"<< endl;
    cout <<"Nobles:" << endl;
    if (noble.size() > 0){
        for(Noble* each_noble:noble){
            cout << *each_noble;
        }

    }else{
        cout << "NONE" << endl;
    }
    cout << endl;
    cout << "Unemployed Warriors:" << endl;
    int unemployed_war = 0; // set a counter for the free warrior
    for(Warrior* each_warrior : warrior){
        if(!each_warrior->hire()){
            unemployed_war ++;// if the warrior is not hired, the counter increament by 1
            cout<< *each_warrior;
        }
    }
    if (unemployed_war == 0){ // if the counter = 0, print none which represents all warriors
        // are hired
        cout << "NONE" << endl;
    }
}
// the clear function
// returns nothing
// parameter : vector<Noble*>&noble,vector<Warrior*>&warrior
void clear(vector<Noble*>&noble,vector<Warrior*>&warrior){
    for(Noble* posit : noble) {// clear the noble
        delete posit;
    }
    noble.clear();
    for(Warrior* war_posit : warrior) {// clear the warrior
        delete war_posit;
    }
    warrior.clear();
}
