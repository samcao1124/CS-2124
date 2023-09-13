/* by Sam Cao
	testRational.cpp
	CS2124
	Implement the class Rational, so that the following program works.
 */

#include <iostream>

// If time allows use separate compilation, otherwise just define the
// class below with the methods / functions defined after main.
//#include "Rational.h"

using namespace std;

// If time allows after implementing separate compilation, then wrap
// the class in a namespace.
//using namespace CS2124;
class Rational{
    friend ostream& operator<<(ostream&os,const Rational& frac);
    friend istream& operator>>(istream& os, Rational& frac);
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);
public:
    Rational(int numerator = 0 , int denominator = 1);
    Rational& operator++();
    Rational operator++(int dummy_int);
    Rational& operator+=(const Rational&frac);
    explicit operator bool () const;
    void normalize();
private:
    int numerator;
    int denominator;
};
int greatestCommonDivisor(int x, int y);
bool operator!=(const Rational& lhs, const Rational& rhs);
Rational operator+(const Rational&lhs,const Rational& rhs);
Rational& operator--(Rational& rhs);
Rational operator--(Rational& rhs,int dummy_int);
bool operator>(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const Rational& rhs);

int main() {
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;
//
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;

    // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;

    // How does this manage to work?
    // It does NOT require writing another == operator.
    cout << "1 == one: " << boolalpha << (1 == one) << endl;

    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing?
    //cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    }

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    }

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : "
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
}
    Rational::Rational(int num, int denomin){
        numerator = num;
        denominator = denomin;
        normalize();
    }

    ostream& operator<<(ostream& os,const Rational& frac){
        os << frac.numerator << '/' << frac.denominator <<endl;
        return os;
    }
    istream& operator>>(istream& os,Rational& frac){
        char slash = '/';
        os >> frac.numerator >> slash >> frac.denominator;
        frac.normalize();
        return os;
    }
    bool operator==(const Rational& lhs, const Rational& rhs) {
        return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
}
    Rational& Rational::operator++() {
        *this += 1;
        return *this;
}
    Rational Rational::operator++(int dummy_int) {
        Rational original(*this);
        *this += 1;
        return original;
}
    Rational& operator--(Rational& rhs) {
        rhs += -1;
        return rhs;
    }
    Rational& Rational:: operator+=(const Rational&frac){
    int new_dem = denominator * frac.denominator;
    int new_num = numerator*frac.denominator + frac.numerator*denominator;
    numerator = new_num;
    denominator = new_dem;
    normalize();
    return *this;

    }

    Rational operator--(Rational& rhs,int dummy_int){
        Rational original(rhs);
        rhs += -1;
        return original;
}

    Rational operator+(const Rational& lhs,const Rational& rhs){
        Rational result(lhs);
        result += rhs;
        return result;
}

    void Rational::normalize(){
        if( denominator < 0) {
            numerator *= -1;
            denominator *= -1;
        }
        int common_div = greatestCommonDivisor(numerator,denominator);
        numerator /= common_div;
        denominator /= common_div;
    }
    bool operator!=(const Rational& lhs, const Rational& rhs) {
        return !(lhs==rhs);
    }
    bool operator>(const Rational& lhs, const Rational& rhs){
        return !((lhs<rhs) || (lhs==rhs));
}
    bool operator<(const Rational& lhs, const Rational& rhs){
    return lhs.numerator * rhs.denominator < rhs.numerator * lhs.denominator;;
}
    bool operator>=(const Rational& lhs, const Rational& rhs){
        return lhs > rhs || lhs == rhs;
}
    bool operator<=(const Rational& lhs, const Rational& rhs){
        return lhs < rhs || lhs == rhs;
}



int greatestCommonDivisor(int x, int y) {//2 ,3
    while (y != 0) {
        int temp = x % y;//2 % 3 = 2
        x = y;
        y = temp;
    }
    return x;
}
    Rational:: operator bool ()const {
        return (numerator != 0);
    }