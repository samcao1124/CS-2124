// by sam cao
// this program is mainly used for displaying the battle between nobles and their warriors.
// there are two classes in this program. 1. Warrior 2. Noble

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Warrior{
    // output operator for warrior class.
    friend ostream& operator <<(ostream&os,const Warrior& warriors){
        os << "\t"<< warriors.warrior_name << ": " << warriors.strength << endl;
        return os;
    }
public:
    // Constructor: default warrior: given name, strength, hire status = false
    Warrior(const string& warrior_name, int strength):
            warrior_name(warrior_name),strength(strength),hire_or_fire(false){}

    // return the name of warrior
    string getName() const {return warrior_name;}

    // setter: set strength
    void set_strength(double strengthRatio){ strength *= strengthRatio; }

    // return the strength
    int get_strength(){return strength;}

    // return hire status
    bool hire()const{return hire_or_fire;}

    // fire myself
    void fire(const bool fire){hire_or_fire = fire;}

private:
    double strength;
    string warrior_name;
    bool hire_or_fire;
};


class Noble{
    // output operator for nobel: includes name
    friend ostream& operator <<(ostream&os,const Noble& noble){
        os << noble.noble_name << " has an army of " << noble.troop.size() << endl;
        for (Warrior* warrior: noble.troop){
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
        return true;
    }

    // Locate a warrior's position in troop.
    size_t find_warrior(Warrior&warrior){
        int posit = 0;
        for (; posit < troop.size(); ++posit) {
            if( troop[posit] == &warrior) break;
        }
        return posit;
    }

    // fire one warrior from the troop
    bool fire(Warrior& warrior){
        int position;
        position = find_warrior(warrior);
        cout << "You don't work for me anymore " << warrior.getName()
        << "! -- " << noble_name << "." << endl;
        if (position == troop.size()) return false;
        troop[position] = troop[troop.size()-1];
        troop[troop.size() - 1] = troop[position];
        troop.pop_back();
        return true;
    }

    // update alive status --> death
    void set_noble_death(){ is_alive = false;}

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
                cout << "Mutual Annihalation: " << noble_name << "and" << enemy.noble_name
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


int main() {

    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);

    cout << "==========\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

    art.fire(cheetah);
    cout << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

}