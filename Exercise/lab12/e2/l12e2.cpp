#include <iostream>
#include <memory>

using namespace std;

int main() {
    double *p_reg = new double(5);
    shared_ptr<double> pd;
    pd = static_cast<shared_ptr<double>>(p_reg);
    cout << "*pd = " << *pd << endl;
    
    shared_ptr<double> pshared = pd;
    cout << "*pshred = " << *pshared << endl;
    
    string str("Hello World!");
    shared_ptr<string> pstr = static_cast<shared_ptr<string>>(new string(str));
    // shared_ptr<string> pstr(&str);
    cout << "*pstr = " << *pstr << endl;
    
    return 0;
}