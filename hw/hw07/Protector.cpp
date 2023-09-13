//
// Created by Sam Cao on 2021/11/18.
//

#include "Protector.h"

#include "Noble.h"

using namespace std;

namespace WarriorCraft{
    Protector::Protector(const string& name, double strength):name(name),strength(strength), is_hired(false),owner(nullptr), is_alive(true){}//constructor of warrior

    // change the hired condition
    void Protector::set_hired(bool status){is_hired = status;}
    bool Protector::isHired() const{
        return is_hired;
    } //return the warrior is employed or not


    const string& Protector::getName ()const{
        return name;
    }//return warrior name getter
    void Protector::set_noble(Noble& noble){
        owner = &noble;
    }

    void Protector::fired(){
        owner=nullptr;
    }//set its noble to nullptr;

    int Protector::getStrength()const{
        return strength;
    }

    void Protector::set_strength(double strengthRatio){
        strength *= strengthRatio;
        if(strength == 0){
            is_alive=false;
        }
    }

    bool Protector::alive()const {
        return is_alive;
    }

    const string& Protector::noble_name() const{
        return owner->get_name();

    }



    Warrior::Warrior(const string& name, double strength):Protector(name,strength){}
    void Warrior::display() const{
        cout<<getName()<<" says: Take that in the name of my lord, "<<noble_name()<<endl;
    }



    Wizard::Wizard(const string& name, double strength):Protector(name,strength){}
    void Wizard::display() const {
        if (alive()) {
            cout << "POOF! " << endl;
        }
    }



    Archer::Archer(const string& name, double strength):Warrior(name,strength){}
    void Archer::display() const{
        if(alive()) {
            cout << "TWANG! ";
            Warrior::display();
        }
    }


    Swordsman::Swordsman(const string& name, double strength):Warrior(name,strength){}
    void Swordsman::display() const{
        if(alive()) {
            cout << "CLANG! ";
            Warrior::display();
        }
    }

}