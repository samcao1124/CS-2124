//
// Created by Sam Cao on 2021/11/18.
//

#include "Protector.h"
#include "Noble.h"
using namespace std;
namespace WarriorCraft{
    Noble::Noble(const string &name) : name(name), is_alive(true) {}
    const string& Noble::get_name() const{return name;}
    bool Noble::alive() const{return is_alive;}

    // battle function between two nobles
    void Noble ::battle(Noble& enemy){
        cout << get_name() << " battles " << enemy.get_name() << endl;
        display();
        enemy.display();
        if (alive() && !enemy.alive()) {
            cout << "He's dead, " << get_name() << endl;
        } else if (!alive() && enemy.alive()) {
            cout << "He's dead, " << enemy.get_name() << endl;
        } else if (!alive() && !enemy.alive()){
            cout << "Oh, NO!  They're both dead!  Yuck!" <<endl;
        } else {
            double self_strength = get_strength();          // get self total strength
            double enemy_strength = enemy.get_strength();   // get enemy total strength
            double ratio = self_strength / enemy_strength;  // calculate ratio

            // Case # 1: my strength < enemy strength --> lose
            if (ratio < 1) {
                set_noble_death();
                set_strength(0);
                enemy.set_strength(1 - ratio);
                cout << enemy.get_name() << " defeats " << get_name() << endl;
            }
                // Case # 2: my strength = enemy strength --> tie
            else if (ratio == 1) {
                set_noble_death();
                enemy.set_noble_death();
                set_strength(0);
                enemy.set_strength(0);
                cout << "Mutual Annihalation: " << get_name() << " and " << enemy.get_name()
                     << "die at each other's hands" << endl;
            }
                // Case # 3: my strength > enemy strength --> win
            else {
                enemy.set_noble_death();
                set_strength(1 - 1 / ratio);
                enemy.set_strength(0);
                cout << get_name() << " defeats " << enemy.get_name() << endl;
            }
        }
    }

    // set noble to death
    void Noble:: set_noble_death(){ is_alive = false;}


    Lord::Lord(const string& name):Noble(name){}

    // noble hire warriors
    bool Lord::hires(Protector& warrior){
        if (warrior.isHired() || !alive()) return false;
        troop.push_back(&warrior);
        // tell the warrior that they are hired
        warrior.set_hired(true);
        warrior.set_noble(*this);
        return true;
    }

    double Lord::get_strength() const{
        int total=0;
        for(size_t i=0; i<troop.size();i++){
            total+=troop[i]->getStrength();
        }
        return total;
    }

    // update the strength of the troop
    void Lord::set_strength(double ratio) {
        for(size_t i=0; i<troop.size();i++){
            troop[i]->set_strength(ratio);
        }
    }

    void Lord::display(){
        if(alive()) {
            for (size_t i = 0; i < troop.size(); i++) {
                troop[i]->display();
            }
        }
    }

    // find warrior returns the position of the warrior
    size_t Lord:: find_warrior(const Protector& warrior){
        for (size_t posit = 0; posit < troop.size(); ++posit) {
            if( troop[posit] == &warrior) return posit;
        }
        return troop.size();
    }

    // noble could fire warrior
    bool Lord::fire(Protector& warrior) {
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
                     << "! -- " << get_name() << "." << endl;
                warrior.set_hired(false);
                warrior.fired();
                return true;
            }
        }else{
            return false;
        }
    }

    // removeWarrior from the troop
    bool Lord::removeWarrior(Protector& warrior){
        size_t warrior_position = find_warrior(warrior);
        if(warrior_position != troop.size()){
            for (size_t each = 0; each< troop.size(); ++ each){
                troop[each] = troop[each+1];
            }
            troop.pop_back();
            double noble_strength = this -> get_strength();
            noble_strength -= warrior.getStrength(); // the strength of the troop will be updated
            return true;
        } else {
            cout << warrior.getName() << " is not in the army.\n";
            return false;
        }

    }

    PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name, int strength):Noble(name),strength(strength){}
    double PersonWithStrengthToFight::get_strength() const{return strength;}
    void PersonWithStrengthToFight::set_strength(double ratio){strength *= ratio;}
    void PersonWithStrengthToFight::display() {
        if (alive()) {
            cout << "Ugh!" << endl;
        }
    }

}