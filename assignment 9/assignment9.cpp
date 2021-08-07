//
// assignment9.cpp
//
// Brian Mai
// 7/30/21
// CS14E Assignment 9, Part 1
// Prompts user for menu item name & price with structs
//

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std; 

struct MenuItem 
{
    string name; 
    double price; 
}; 

void ReadItem(istream &in, MenuItem &p);
void PrintItem(ostream &out, MenuItem p);

int main () 
{
    MenuItem item1;

    ReadItem(cin, item1); 
    PrintItem(cout, item1); 

    return 0; 
}

void ReadItem(istream &in, MenuItem &p) 
{
    cout << "Enter item name: " << flush; 
    getline(in, p.name); 
    
    cout << "Enter item price: " << flush; 
    in >> p.price; 
    
    return; 
}

void PrintItem(ostream &out, MenuItem p)
{
    //2 decimals for price. 
    out << fixed << showpoint << setprecision(2); 
    out << '\n' << "| Menu Item: " << p.name << " |     |"
        << " Price: " << p.price << " |" << endl; 
    
    return; 
}

