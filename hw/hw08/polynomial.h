//
// Created by Sam Cao on 12/6/21.
//

#include <iostream>
#include <vector>

#ifndef HW08_POLYNOMIAL_H
#define HW08_POLYNOMIAL_H


namespace Math {

    class Polynomial {
        struct Term;
        friend bool operator==(const Polynomial &p1, const Polynomial &p2);// ok
        friend std::ostream &operator<<(std::ostream &os, const Polynomial &rhs);
    public:
        Polynomial();// ok
        Polynomial(const std::vector<int> &coe);//half
        ~Polynomial();//ok
        Polynomial(const Polynomial &rhs);//ok
        Polynomial &operator+=(const Polynomial &rhs);
        Polynomial &operator=(const Polynomial &rhs);
        int evaluate(int val) const;



    private:
        struct Term {
            Term(int coefficient = 0, Term *next = nullptr);
            int coefficient;
            Term *next;

        };

        Term *header;
        int degree = 0;
    };

    // non-member functions
    bool operator!=(const Polynomial &p1, const Polynomial &p2);//ok
    Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);//ok
}
#endif //HW08_POLYNOMIAL_H
