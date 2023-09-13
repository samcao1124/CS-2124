//
// Created by Sam  2021/11/3.
//

#ifndef HW6_FILES_NOBLE_H
#define HW6_FILES_NOBLE_H

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {
    class Warrior;
    class Noble{
        // output operator for nobel: includes name
        friend std::ostream& operator <<(std::ostream&os,const Noble& noble);

    public:
        // Constructor: given name, alive status
        Noble(const std::string& noble_name);

        // removes the warrior from the troop of the noble
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
        const std::string& get_noble_name() const;
        // sum up the strength of all warriors
        double get_noble_strength() const;

        // update strength of warriors in the troop after battle
        void update_troop(double ratio);

        // self battles enmey with three cases.
        void battle(Noble& enemy);

    private:
        std::vector<Warrior*> troop;
        bool is_alive;
        std::string noble_name;
    };
};
#endif //HW6_FILES_NOBLE_H