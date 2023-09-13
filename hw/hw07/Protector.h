
// Created by Sam Cao on 2021/11/18.
//

#ifndef MAIN_CPP_PROTECTOR_H
#define MAIN_CPP_PROTECTOR_H
#include <string>
#include <iostream>
#include <vector>
#include "Noble.h"

namespace WarriorCraft {

    class Noble;
    class Protector {
    public:
        Protector(const std::string &name, double strength);
        const std::string &getName() const;
        void set_hired(bool status);        // set to hired status
        bool isHired() const;               // return the warrior is employed or not
        void set_noble(Noble &noble1);      // assign owner;
        void fired();                       // set owner to nullptr;
        int getStrength() const;            //return warrior strength
        void set_strength(double strengthRatio);
        bool alive() const;
        virtual void display() const=0;
        const std::string &noble_name() const;

    private:
        std::string name;
        int strength;
        bool is_hired;
        Noble *owner;
        bool is_alive;
    };

    class Warrior : public Protector {
    public:
        Warrior(const std::string &name, double strength);
        virtual void display() const;

    };

    class Wizard : public Protector {
    public:
        Wizard(const std::string &name, double strength);
        void display() const;
    };

    class Archer : public Warrior {
    public:
        Archer(const std::string &name, double strength);
        void display() const;
    };

    class Swordsman : public Warrior {
    public:
        Swordsman(const std::string &name, double strength);
        void display() const;
    };

}

#endif //MAIN_CPP_PROTECTOR_H