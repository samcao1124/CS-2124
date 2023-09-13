//
// Created by Sam on 2021/11/3.
//
#include <iostream>
#include <string>
#include <vector>
#include "Noble.h"
#include "Warrior.h"

using namespace std;
namespace WarriorCraft {
    // output operator
    ostream& operator <<(ostream&os,const Warrior& warriors){
        os << "\t"<< warriors.warrior_name << ": " << warriors.strength << endl;
        return os;
    }

    // constructor
    Warrior::Warrior(const string& warrior_name, double strength):
            warrior_name(warrior_name), strength(strength), ishired(false){}

    // name getter
    const string& Warrior:: getName() const {return warrior_name;}

    // set strength
    void Warrior::set_strength(double strengthRatio){strength *= strengthRatio;}

    // change the hired
    void Warrior::set_hired(bool is_hired){this->ishired = is_hired;}

    // the strength getter
    double Warrior::get_strength() const {return strength;}

    // to see if the warrior is hired
    bool Warrior:: isHired()const{return ishired;}

    // the warrior could be fired
    void Warrior::fire(bool fire){ishired = fire;}

    // the function could run away
    bool Warrior::runaway(){
        cout << warrior_name << " flees in terror, abandoning his lord, " << (owner->get_noble_name()) << endl;
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

    // set a warrior a noble
    void Warrior::set_noble(Noble* noble){
        if(ishired){
            owner = noble;
        }else{
            owner = nullptr;
        }
    }
}