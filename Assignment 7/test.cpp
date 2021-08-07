//
// test.cpp
//
// Brian Mai
// 7/19/2021
// CS14E Assignment 7 
// Calculates diameter, circumference, and area of a circle and using text files for input/ output.
//

#include <iostream>
#include <fstream>

const double Pi = 3.141592653589793;
int CircleStats( double r, double &d, double &c, double &a );

using namespace std; 

int main () 
{
    ofstream fout;
    ifstream fin; 
    double r, d, c, a;  
    bool in = true; 
    bool out = true; 

    fin.open("input.txt");
    fout.open("output.txt");
    
    if (!fin) 
    {
        cout << "Error opening input file." << endl; 
        in = false; 
    } 
    if (!fout) 
    {
        cout << "Error opening output file." << endl; 
        out = false; 
    } 

    if (in == true && out == true) 
    {
        while (fin >> r) 
        {
            if (CircleStats(r, d, c, a) == 0) 
            {
                fout << "Radius: " << r << " Diameter: " << d
                << " Circumference: " << c << " Area: " << a << endl; 
            }                   
            else 
            {
                fout << "You entered " << r << " for radius."
                << " You must enter a number greater than 0." << endl; 
            }
        }
    }

    fin.close(); 
    fout.close(); 

    return 0; 
}

int CircleStats( double r, double &d, double &c, double &a )
{   
    int value; 
    
    if (r <= 0) 
    {
        value = -1;  
    } 
    else 
    {
        d = r * 2; 
        c = Pi * r * 2; 
        a = Pi * r * r;  

        value = 0;    
    }

    return value;     
}
