/*
  rec11.cpp
  Starting code 21F
 */

#include <iostream>
#include <vector>
using namespace std;
class Instrument {
public:
    // virtual
    virtual void makeSound() const = 0;

    // abstract
    virtual void play() const = 0;
};
void Instrument::makeSound() const {cout << "To make a sound...";}

class Brass : public Instrument{
public:
    Brass(unsigned size): size(size){}


    void makeSound() const {Instrument:: makeSound();
    cout<< " blow on a mouthpiece of size " << size << endl;}

private:
    unsigned size;

};

class Trumpet : public Brass{
public:
    Trumpet(unsigned size) : Brass(size){}
    virtual void play() const{
        cout << "Toot";
    }



};
class Trombone : public Brass{
public:
    Trombone(unsigned size) : Brass(size){}
    virtual void play() const{
        cout << "Blat";
    }
};




class String : public Instrument{
public:
    String(unsigned pitch): pitch(pitch){}

    void makeSound() const {Instrument:: makeSound();cout<< "bow a string with pitch " << pitch << endl;}
private:
    unsigned pitch;
};

class Violin : public String{
public:
    Violin(unsigned pitch) : String(pitch){
    }
     void play() const{
        cout << "Screech";
    }
};
class Cello  : public String{
public:
    Cello(unsigned pitch) : String(pitch){
    }
     void play() const{
        cout << "Squawk";
    }
};

class Percussion : public Instrument{
public:

    void makeSound() const {Instrument:: makeSound();cout<< "hit me ! " << endl;}
};

class Drum : public Percussion{
public:
     void play() const{
        cout << "Boom";
    }
};
class Cymbal : public Percussion{
public:
     void play() const{
        cout << "Crash";
    }
};


class Musician {
public:
    Musician() : instr(nullptr) {}

    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << "have no instr\n";
    }

    void play(){
        if(instr != nullptr){
            instr->play();
        }
    }


private:
    Instrument* instr;
};

class MILL{
public:
    void receiveInstr(Instrument& instrument) {
        instrument.makeSound();

        for (size_t index = 0; index< inventory.size(); index++){

            if (inventory[index] == nullptr) {
                inventory[index] = &instrument;
                return;
            }
        }
        inventory.push_back(&instrument);
    }

    void dailyTestPlay()const {
        for(size_t index = 0; index< inventory.size();++index){
            if(inventory[index] != nullptr){
                inventory[index]->makeSound();
            }
        }
    }

    Instrument* loanOut(){
        for (Instrument*& instrument: inventory){
            if (instrument != nullptr){
                Instrument* instr = instrument;
                instrument = nullptr;
                return instr;
            }
        }
        return nullptr;
    }


private:
    vector<Instrument*> inventory;


};

class Orch{
public:
    void addPlayer(Musician& musician) {
        musicians.push_back(&musician);
    }
    void play() const {
        for(size_t i = 0; i < musicians.size(); i++){
            musicians[i] -> play();
        }
        cout << endl;
    }
private:
    vector<Musician*> musicians;
};

int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ----------------------------------------\n";
     Drum drum;
     Cello cello(673);
     Cymbal cymbal;
     Trombone tbone(4);
     Trumpet trpt(12) ;
     Violin violin(567) ;

    // use the debugger to look at the mill
    cout << "Define the MILL ------------------------------------------------\n";
     MILL mill;

    cout << "Put the instruments into the MILL ------------------------------\n";
     mill.receiveInstr(trpt);
     mill.receiveInstr(violin);
     mill.receiveInstr(tbone);
     mill.receiveInstr(drum);
     mill.receiveInstr(cello);
     mill.receiveInstr(cymbal);

    cout << "Daily test -----------------------------------------------------\n"
         << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();
     cout << endl;

    cout << "Define some Musicians-------------------------------------------\n";
     Musician harpo;
     Musician groucho;

     cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
     groucho.testPlay();
     cout << endl;
     groucho.acceptInstr(mill.loanOut());
     cout << endl;
     groucho.testPlay();
     cout << endl;
     cout << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();

     cout << endl << endl;

     groucho.testPlay();
     cout << endl;
     mill.receiveInstr(*groucho.giveBackInstr());
     harpo.acceptInstr(mill.loanOut());
     groucho.acceptInstr(mill.loanOut());
     cout << endl;
     groucho.testPlay();
     cout << endl;
     harpo.testPlay();
     cout << endl;
     cout << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();

     cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";

     // fifth
     mill.receiveInstr(*groucho.giveBackInstr());
     cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
     mill.receiveInstr(*harpo.giveBackInstr());


     cout << endl;
     cout << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();
     cout << endl;

     cout << endl;


    //
    // PART TWO
    //


    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

}
