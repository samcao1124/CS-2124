//
// Created by Sam Cao on 2021/11/18.
//

#ifndef MAIN_CPP_NOBLE_H
#define MAIN_CPP_NOBLE_H
#include <string>
#include <iostream>
#include <vector>
#include "Protector.h"

namespace WarriorCraft {
    class Protector;
    class Noble {
    public:

        Noble(const std::string &name);         // Constructor
        const std::string& get_name() const;    // get the name of Noble
        bool alive() const;                     // return alive status
        void battle(Noble& enemy);              // self battle with enemy
        void set_noble_death();                 // set self to death
        virtual void display()=0;
        virtual double get_strength() const=0;
        virtual void set_strength(double ratio)=0;
    private:
        std::string name;
        bool is_alive;
    };



    class Lord:public Noble{
    public:
        Lord(const std::string& name);
        bool hires(Protector& warrior);
        double get_strength() const;
        void set_strength(double ratio);
        void display();
        size_t find_warrior(const Protector& warrior);
        bool fire(Protector& warrior);
        bool removeWarrior(Protector& warrior);

    private:
        std::vector<Protector*> troop;
    };

    class PersonWithStrengthToFight:public Noble{
    public:
        PersonWithStrengthToFight(const std::string& name, int strength);
        double get_strength() const;
        void set_strength(double ratio);
        void display();
    private:
        int strength;
    };


};


#endif //MAIN_CPP_NOBLE_H