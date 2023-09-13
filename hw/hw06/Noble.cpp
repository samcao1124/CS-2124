//
// Created by Sam on 2021/11/3.
//

#include "Noble.h"
#include <iostream>
#include <vector>
#include <string>
#include "Warrior.h"

using namespace std;
namespace WarriorCraft {

    // output operator
    ostream& operator <<(ostream&os,const Noble& noble){
        os << noble.noble_name << " has an army of " << noble.troop.size() << endl;
        for (const Warrior* warrior: noble.troop){
            os<< *warrior;
        }
        return os;
    }

    // constructor
    Noble :: Noble(const string& noble_name):noble_name(noble_name),is_alive(true){}

    // removeWarrior from the troop
    bool Noble::removeWarrior(Warrior& warrior){
        size_t warrior_position = find_warrior(warrior);
        if(warrior_position != troop.size()){
            for (size_t each = 0; each< troop.size(); ++ each){
                troop[each] = troop[each+1];
            }
            troop.pop_back();
            double noble_strength = this -> get_noble_strength();
            noble_strength -= warrior.get_strength(); // the strength of the troop will be updated
            return true;
        } else {
            cout << warrior.getName() << " is not in the army.\n";
            return false;
        }

    }
    // check if the noble is alive or not
    bool Noble:: alive() const{return is_alive;}

    // noble hire warriors
    bool Noble::hire(Warrior& warrior){
        if (warrior.isHired() || !alive()) return false;
        troop.push_back(&warrior);
        // tell the warrior that they are hired
        warrior.set_hired(true);
        warrior.set_noble(this);
        return true;
    }
    // find warrior returns the position of the warrior
    size_t Noble:: find_warrior(const Warrior& warrior){
        for (size_t posit = 0; posit < troop.size(); ++posit) {
            if( troop[posit] == &warrior) return posit;
        }
        return troop.size();
    }

    // set noble to death
    void Noble:: set_noble_death(){ is_alive = false;}

    // noble name getter
    const string& Noble::get_noble_name() const {return noble_name;}

    // noble could fire warrior
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
    // get the noble strength
    double Noble:: get_noble_strength() const{
        double total_strength= 0;
        for (Warrior* each : troop) {
            total_strength += each->get_strength();
        }
        return total_strength;
    }

    // update the strength of the troop
    void Noble::update_troop(double ratio) {
        for (Warrior* each: troop) {
            each->set_strength(ratio);
        }
    }

    // battle function between two nobles
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
}