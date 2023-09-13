/*
by sam cao
 21 Fall
 */
// this program is mainly used for displaying the battle between nobles and their warriors.
// there are two classes in this program. 1. Warrior 2. Noble
// based on the last assignment, this program added the main and
// display the warriors who are not hired. the warrior could run away by themselves and they return unhired.




// Comment out these two includes for the single file solution
//#include "Noble.h"
//#include "Warrior.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Comment out this using namespace for the single file solution
//using namespace WarriorCraft;

class Noble;

class Warrior{
    // output operator for warrior class.
    friend ostream& operator <<(ostream&os,const Warrior& warriors);
public:
    // Constructor: default warrior: given name, strength, hire status = false
    Warrior(const string& warrior_name, double strength);

    // return the name of warrior
    const string& getName() const;

    // setter: set strength
    void set_strength(double strengthRatio);

    void set_hired(bool is_hired);

    // return the strength
    double get_strength() const;

    // return hire status

    bool isHired()const;

    // fire myself
    void fire(bool fire);

    // runaway function
    bool runaway();

    // set a nobel to a warrior
    void set_noble(Noble* noble);


private:
    double strength;
    string warrior_name;
    bool ishired;
    Noble* owner;
};


class Noble{
    // output operator for nobel: includes name
    friend ostream& operator <<(ostream&os,const Noble& noble);

public:
    // Constructor: given name, alive status
    Noble(const string& noble_name);

    bool removeWarrior(Warrior& warrior);
    // return alive status
    bool alive() const;


    // hire one warrior： can only hire if nobel is alive
    bool hire(Warrior& warrior);

    // Locate a warrior's position in troop.
    size_t find_warrior(const Warrior& warrior);

    // fire one warrior from the troop
    bool fire(Warrior& warrior);

    // update alive status --> death
    void set_noble_death();
    const string& get_noble_name() const;
    // sum up the strength of all warriors
    double get_noble_strength() const;

    // update strength of warriors in the troop after battle
    void update_troop(double ratio);

    // self battles enmey with three cases.
    void battle(Noble& enemy);

private:
    vector<Warrior*> troop;
    bool is_alive;
    string noble_name;
};



int main() {
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 4);
	Warrior sky("Leia", 6);
	Warrior wizard("Merlin", 9);
	Warrior jaffa("Teal'c", 9);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(jaffa);
	art.hire(cheetah);
	art.hire(wizard);
	art.hire(sky);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(nimoy);

	cout << "================ Initial Status ===============" << endl;
	cout << art << endl
	     << lance << endl
	     << jim << endl
	     << linus << endl
	     << billie << endl;
	cout << "===============================================\n\n";

	art.fire(cheetah);
	wizard.runaway();
	cout << endl << art << endl;

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);

	cout << "\n================ Final Status ===============" << endl;
	cout << art << endl
	     << lance << endl
	     << jim << endl
	     << linus << endl
	     << billie << endl;

	// Tarzan and Merlin should be unemployed
	cout << "Tarzan's Hire Status: " << boolalpha
	     << cheetah.isHired() << endl;
	cout << "Merlin's Hire Status: " << boolalpha
	     << wizard.isHired() << endl;
	cout << "===============================================\n\n";
}

ostream& operator <<(ostream&os,const Warrior& warriors){
    os << "\t"<< warriors.warrior_name << ": " << warriors.strength << endl;
    return os;
}


//constructor
Warrior::Warrior(const string& warrior_name, double strength):
        warrior_name(warrior_name), strength(strength), ishired(false){}

// name getter
const string& Warrior:: getName() const {return warrior_name;}

// strength setter
void Warrior::set_strength(double strengthRatio){strength *= strengthRatio;}

// set hired
void Warrior::set_hired(bool is_hired){this->ishired = is_hired;}

// strength getter
double Warrior::get_strength() const {return strength;}

// set ishired
bool Warrior:: isHired()const{return ishired;}

// warrior fire
void Warrior::fire(bool fire){ishired = fire;}


// a warrior could run awawy when the warrior run away, the hire condition
bool Warrior::runaway(){
    cout << warrior_name << " flees in terror, abandoning his lord, "
    << owner->get_noble_name() << endl;
    if (owner != nullptr) {
        owner->removeWarrior(*this);
        owner = nullptr;
        ishired = false;
        return ishired;
    } else {
        cerr << warrior_name << " has no noble\n";
        ishired = true;
        return ishired;
    }
}

// set noble to a warrior
void Warrior::set_noble(Noble* noble){
    if(ishired){
        owner = noble;
    }else{
        owner = nullptr;
    }
}
// output operator
ostream& operator <<(ostream&os,const Noble& noble){
    os << noble.noble_name << " has an army of " << noble.troop.size() << endl;
    for (const Warrior* warrior: noble.troop){
        os<< *warrior;
    }

    return os;
}

Noble :: Noble(const string& noble_name):noble_name(noble_name),is_alive(true){}

bool Noble::removeWarrior(Warrior& warrior){
    size_t warrior_position = find_warrior(warrior);
    if(warrior_position != troop.size()){
        for (size_t each = 0; each< troop.size(); ++ each){
            troop[each] = troop[each+1];
        }
        troop.pop_back();
        double noble_strength = this -> get_noble_strength();
        noble_strength -= warrior.get_strength();
        return true;
    } else {
        cout << warrior.getName() << " is not in the army.\n";
        return false;
    }

}

bool Noble:: alive() const{return is_alive;}

bool Noble::hire(Warrior& warrior){
    if (warrior.isHired() || !alive()) return false;
    troop.push_back(&warrior);
    // tell the warrior that they are hired
    warrior.set_hired(true);
    warrior.set_noble(this);
    return true;
}
// find the position of the warrior.
size_t Noble:: find_warrior(const Warrior& warrior){
    for (size_t posit = 0; posit < troop.size(); ++posit) {
        if( troop[posit] == &warrior) return posit;
    }
    return troop.size();
}

void Noble:: set_noble_death(){ is_alive = false;}

const string& Noble::get_noble_name() const {return noble_name;}

// a noble can fire a warrior
bool Noble::fire(Warrior& warrior) {
    if (alive() && warrior.isHired()) {
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
            warrior.set_noble(nullptr);
            return true;
        }
    }else{
        return false;
    }
}


double Noble:: get_noble_strength() const{
    double total_strength= 0;
    for (Warrior* each : troop) {
        total_strength += each->get_strength();
    }
    return total_strength;
}

// update troop
void Noble::update_troop(double ratio) {
    for (Warrior* each: troop) {
        each->set_strength(ratio);
    }
}

// battle function between nobles
void Noble ::battle(Noble& enemy){
    cout << noble_name << " battles " << enemy.noble_name << endl;
    if (alive() && !enemy.alive()) {
        cout << "He's dead, " << noble_name << endl;
    } else if (!alive() && enemy.alive()) {
        cout << "He's dead, " << enemy.noble_name << endl;
    } else if (!alive() && !enemy.alive()){
        cout << "Oh, NO!  They're both dead!  Yuck!" <<endl;
    } else {
        double self_strength = get_noble_strength();          // get self total strength
        double enemy_strength = enemy.get_noble_strength();   // get enemy total strength
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