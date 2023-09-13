//
// Created by Sam Cao on 12/6/21.
// This program is used for doing the arthmetic between polynomials


#include "polynomial.h"

using namespace std;

namespace Math {
    // struct constructor
    Polynomial::Term::Term(int coefficient, Term *next): coefficient(coefficient),next(next){};
    // constructor
    Polynomial::Polynomial():degree(0){
        header = new Term();
    };

    // constructor with a const vector
    Polynomial::Polynomial(const vector<int>& coe){
        degree=coe.size() - 1;
        header=new Term(coe[0]);
        Term* curr=header;
        for(size_t index=1; index < coe.size(); index++) {
            curr->next = new Term(coe[index]);
            curr = curr->next;
        }
        Term* currPtr=header;
        int count = 0;
        while (currPtr -> coefficient == 0){// clear all the zero coefficient.
            Term* next1=currPtr->next;
            delete currPtr;
            currPtr = next1;
            count += 1; // counter
        }
        degree -= count; // minus the counter
        header = currPtr; // the header needs to point to a new pointer.
    }

    // output operator
    ostream& operator<<(ostream& os, const Polynomial& rhs) {
        Polynomial::Term* curr=rhs.header;
        bool check = true;
        if(rhs.degree==0 && rhs.header -> coefficient == 0){
            os << '0';
        }
        for (size_t temp =0;  temp <=rhs.degree; ++temp ) {
            if (curr -> coefficient == 0) {
                curr = curr -> next;
            } else {
                if( !check  && curr -> coefficient > 0){
                    os << " + ";
                }
                if (!check  && curr -> coefficient < 0){
                    os << " - ";
                }
                if(curr -> coefficient != 1 || rhs.degree - temp==0){
                    os<<curr -> coefficient;
                }
                if((rhs.degree - temp )>0){
                    os<<'x';
                }
                if((rhs.degree - temp )>1){
                    os<<'^'<<rhs.degree - temp ;
                }
                curr = curr->next;
                check = false;
            }
        }
        return os;
    }

    // bool operator ==
    // pass in two polymomial objects named p1 and p2 and compare
    // if same, return true
    // if not same, return different
    bool operator==(const Polynomial & p1, const Polynomial & p2){
        if(p1.degree != p2.degree) {
            return false;
        }
        Polynomial ::Term* header1 = p1.header;
        Polynomial ::Term* header2 = p2.header;
        for(size_t index = 0 ; index< p1.degree + 1; index++){ // +1 because of the exclusive
            if(header1->coefficient != header2->coefficient) {
                return false;
            }
            header1 = header1->next;
            header2 = header2->next;
        }
        return true;
    }
    // return true when the two objects are not same, return false when two objects are same
    bool operator!=(const Polynomial & p1, const Polynomial & p2){
        return !(p1 == p2);
    }


    // this method needs a polynomial object passed in and return the sum of the two objects
    // In this method, after the addition is done, the zero coefficients needs to be cleared./
    Polynomial& Polynomial::operator+=(const Polynomial& rhs){
        if(degree >= rhs.degree){
            Term* currPtr1=header;
            Term* currPtr2=rhs.header;
            for(int index=degree; index >= 0; index--){
                if(index <= rhs.degree){
                    currPtr1->coefficient += currPtr2->coefficient;
                    currPtr2 = currPtr2->next;
                }
                currPtr1 = currPtr1 ->next;
            }
        }
        else{
            Term* orig=header;
            header=new Term(rhs.header->coefficient);
            Term* currPtr3=header;
            Term* currPtr4=rhs.header;
            for(int pos= rhs.degree - 1; pos >= 0; pos--) {
                if(pos <= degree){
                    currPtr3->next=orig;
                    currPtr3->next->coefficient+=currPtr4->next->coefficient;
                    orig=orig->next;
                }
                else{
                    currPtr3->next = new Term(currPtr4->next->coefficient);
                }
                currPtr4=currPtr4->next;
                currPtr3 = currPtr3->next;
            }
            degree=rhs.degree;
        }
        Term* currptr5 = header;
        int count=0;
        while (currptr5 -> coefficient == 0){
            Term* next = currptr5 -> next;
            delete currptr5;
            currptr5 = next;
            count += 1;
        }
        degree -= count;
        header = currptr5;
        return *this;
    }
    Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
        Polynomial result(lhs);
        return result+=rhs;
    }



    // evaluate the polynomial by the given value which named as val
    int Polynomial::evaluate(int val) const {
        int result = 0; // set a counter
        Term* curr = header;
        for(size_t iter1=0; iter1 < degree + 1; iter1++) {
            int base = 1;
            for(int iter2 = 0; iter2 < degree - iter1; iter2++){
                base *= val; // multiply
            }
            result+= (curr->coefficient) * base;
            curr=curr->next;
        }
        return result;
    }


    // copy constructor
    Polynomial::Polynomial(const Polynomial& rhs){
        degree=rhs.degree;
        header=new Term(rhs.header->coefficient);
        Term* curr=header;
        Term* curr1=rhs.header;
        for(size_t i=0; i<degree;i++) {
            curr->next = new Term(curr1->next->coefficient);
            curr = curr->next;
            curr1=curr1->next;
        }
    }

    //destructor
    Polynomial::~Polynomial() {
        Term* curr=header;
        // looping over the length of the vector and delete the pointers.
        for(size_t each_poly=0; each_poly< degree+1;each_poly++) {
            Term* old=curr;
            curr=curr->next;
            delete old;
            old=nullptr;
            // set the old pointers to nullptr avoiding memory leak.
        }
        degree=0;
    }


    // assignment operator
    Polynomial& Polynomial::operator=(const Polynomial& rhs) {
        if(this != &rhs){ // check self assignemnt
            Term *current_ptr = header;// call destructor
            for(size_t each_deg=0; each_deg < degree + 1; each_deg++) {
                Term* orig = current_ptr;
                current_ptr = current_ptr->next;
                delete orig;
                orig = nullptr;
            }
            degree = rhs.degree; // call copy constructor
            header = new Term(rhs.header -> coefficient);
            Term* temp = header;
            Term* temp1 = rhs.header;
            for(size_t each_deg2=0; each_deg2 < degree; each_deg2++) {
                temp->next = new Term(temp1->next->coefficient);
                temp = temp ->next;
                temp1= temp1->next;
            }
        }
        return *this;
    }



}