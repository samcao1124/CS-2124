//
// Created by Sam on 2021/11/3.
//

#ifndef HW6_FILES_WARRIOR_H
#define HW6_FILES_WARRIOR_H

#include <iostream>
#include <string>
#include <vector>


namespace WarriorCraft {
    class Noble;
    class Warrior{
        // output operator for warrior class.
        friend std::ostream& operator <<(std::ostream&os,const Warrior& warriors);
    public:
        // Constructor: default warrior: given name, strength, hire status = false
        Warrior(const std::string& warrior_name, double strength);

        // return the name of warrior
        const std::string& getName() const;

        // setter: set strength
        void set_strength(double strengthRatio);

        void set_hired(bool is_hired);

        // return the strength
        double get_strength() const;

        // return hire status

        bool isHired()const;

        // fire myself
        void fire(bool fire);

        // runaway
        bool runaway();

        // set a noble to the warrior
        void set_noble(Noble* noble);


    private:
        double strength;
        std::string warrior_name;
        bool ishired;
        Noble* owner;
    };

}


#endif //HW6_FILES_WARRIOR_H
