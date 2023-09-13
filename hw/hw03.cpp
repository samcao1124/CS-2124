// By sam Cao
// this program is designed for two warriors who has their own weapon.
// this program will display their information and their weapon info
// moreover, it also will display the battle info when they are having fights.
// which including the strength after and before the battle
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Two classes are created here. The main class is called "Warrior"
// The nested class is called weapon. the weapon class is placed in the private
// of the warrior class. We are trying to hide the data of weapons so that
// others can not make change on them.
// The warrior class initilizes warriors and has a function called battle
// Both warrior and Weapon class have some method could help to get or set
// the new strength of the weapon.
class Warrior {
    friend ostream &operator<<(ostream &os, const Warrior &soldier);

private:
    class Weapon {
        //operator printing out the weapon
        friend ostream &operator<<(ostream &os, const Weapon &weapon1) {
            os << "weapon: " << weapon1.weapon_name << ", " << weapon1.weapon_strength;
            return os;
        }

    private:
        string weapon_name;
        int weapon_strength;
    public:
        Weapon(const string &nameWeapon, int strengthWeapon) : weapon_strength(strengthWeapon),
                                                               weapon_name(nameWeapon) {}
        // set the strength of the weapon
        void set_strength(int power) {
            weapon_strength = power;
        }
        // get the name of the weapon
        string get_weapon_name() const {
            return weapon_name;
        }
        // get the strength of the weapon
        int get_strength() const {
            return weapon_strength;
        }
    };
    public:
        Warrior(string warrior_name, string weapon_name, int weaponStrength):
        warrior_name(warrior_name), weapon1(weapon_name, weaponStrength) {};

        // get the name of warrior
        string get_warrior_name() const {
            return warrior_name;
        }

        // get the weapon from the sepcific warrior.
        Weapon getWeapon() const {
            return weapon1;
        }

        // set the strength after the battle
        void set_strength2(int power) {
            weapon1.set_strength(power);
        }
        // battle command when the two warriors are fighting
        // this function shows all the stats of the battle and
        // represents all the possible situations in the fight.
        // Parameter: Warrior , soldier
        void battle_command(Warrior& soldier){
            cout << warrior_name << " battles " << soldier.warrior_name << endl;

            // when they both have same strength and die together.
            if (weapon1.get_strength() == 0 && soldier.weapon1.get_strength() == 0) {
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            }
                // two conversation situations for each winner in each situation
            else if(weapon1.get_strength() == 0) {
                cout << "He's dead,"<< soldier.warrior_name << endl;
            }
            else if(soldier.weapon1.get_strength() == 0) {
                cout << "He's dead,"<< warrior_name<< endl;
            }
                // when they both dead
            else if(weapon1.get_strength() == soldier.weapon1.get_strength()) {
                cout << "Mutual Annihilation: " << warrior_name << " and " << soldier.warrior_name
                <<" die at each other's hands" <<endl;
                weapon1.set_strength(0);
                soldier.weapon1.set_strength(0);

            }
                // two situations when two warriors are winning,
                // their strengths have to be minus the loser's strength.
            else if(weapon1.get_strength() < soldier.weapon1.get_strength()) {
                cout << soldier.warrior_name <<" defeats " << warrior_name<<endl;
                soldier.weapon1.set_strength(soldier.weapon1.get_strength() - weapon1.get_strength());
                weapon1.set_strength(0);
            }
            else if(weapon1.get_strength() > soldier.weapon1.get_strength()) {
                cout << warrior_name <<" defeats " << soldier.warrior_name<<endl;
                weapon1.set_strength(weapon1.get_strength() - soldier.weapon1.get_strength());
                soldier.weapon1.set_strength(0);
            }
        }
    private:
        string warrior_name;
        Weapon weapon1;
    };
// display the stats of the battle of the tow warriors.
// parameter:
//          vector<Warrior> soldier
void status_command(const vector<Warrior>&soldier) ;
// fillout the info of the warrior which including the name, the weapon
// from the input file
// Parameter:
//          vector<Warrior> soldier
//          ifstream,ifs
void warrior_info(vector<Warrior>& soldier, ifstream& ifs);

// this function helps us to find each two warriors are goign to find among
// the soldier vector.
// Parameter:
//      vector<Warrior> soldier
//      string warrior_name
//returns: integer .  which represents the index of the warriors
size_t find_warrior(const vector<Warrior>& soldier, const string& warrior_name);

ostream& operator<<(ostream& os, const Warrior& warrior) {
    os << "Warrior: " << warrior.warrior_name << ", " << warrior.weapon1;
    return os;
}



int main(){
    ifstream ifs("warriors.txt");// try to open the file
    if (!ifs) {
        cerr << "Could not open the file.\n";
        exit(1);
    }
    vector<Warrior> soldiers;// create a warrior vector
    warrior_info(soldiers,ifs);



}
void status_command(const vector<Warrior>&soldier){
    //display the stats of the warriors before and after the battle.
    // parameter : vector: soldier
    cout << "There are: " << soldier.size() << " warriors"<<endl;
    for (size_t position=0; position < soldier.size(); ++position){
        // we loop in the whole warrior vector
        cout << soldier[position] << endl;
    }
}
// to see if there is an vaild  warrior, if there is not,
// the function return the size of the vector.
// if the target warrior is found, return its index.
size_t find_warrior(const vector<Warrior>& soldier, const string& warrior_name){
    for(size_t index = 0; index < soldier.size(); index++){
        if (soldier[index].get_warrior_name() == warrior_name){
            return index;
        }
    }
    return soldier.size();
}

void warrior_info(vector<Warrior>& soldier, ifstream&ifs){
    string command_check;// check each command at the beginning of each line
                        // of the file.
    while (ifs >> command_check) {
        if (command_check == "Warrior") {
            string warrior_name;
            string weapon_name;
            int weapon_strength;
            ifs >> warrior_name >> weapon_name >> weapon_strength;
            // while reading the warrior's info, we could store these info
            // in a warrior vector and push back to the soldier.
            Warrior hero(warrior_name, weapon_name, weapon_strength);
            soldier.push_back(hero);
        }
        else if (command_check == "Battle"){
            string soldier1;
            string soldier2;
            ifs >> soldier1 >> soldier2;
            // find the index of the two warriors using the find function
            size_t index1 = find_warrior(soldier, soldier1);
            size_t index2 = find_warrior(soldier, soldier2);
            if(index1 != soldier.size() && index2 != soldier.size()){
                soldier[index1].battle_command(soldier[index2]);
            }
            else{// we need to check if the warrior is in the vector
                // if it is not in the vector, error pop up
                cerr << "Warrior NOT FOUND." << endl;
            }

        }
        else if (command_check == "Status"){// display the battle stats.
            status_command(soldier);
        }
    }
    ifs.close();

}