//
// assignment9p2.cpp
//
// Brian Mai
// 7/30/21
// CS14E Assignment 9, Part 2
// Reads & Writes array of 10 MenuItem structs
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

bool ReadItem(istream &in, MenuItem &p);
void PrintItem(ostream &out, MenuItem p);

int main ()
{
    ifstream fin("input.txt"); 
    ofstream fout("output.txt"); 

    if (!fin) 
    {
        cout << "Error opening input file." << endl;
        return -1;
    }
    if (!fout) 
    {
        cout << "Error opening output file." << endl;
        return -1;
    }

    MenuItem array[10];

    for (int i = 0; i < 10; i++) 
    {
        
        ReadItem(fin, array[i]);
        if (ReadItem(fin, array[i]) == true) {
            PrintItem(fout, array[i]); 

        } else {
            cout << "error."; 
        }
         
    }

    fin.close();
    fout.close(); 

    return 0; 
}

bool ReadItem(istream &in, MenuItem &p) 
{
    getline(in, p.name); 
    cout << p.name << endl; 
    in >> p.price; 
    in.ignore(99999, '\n'); 

    return true; 
}

void PrintItem(ostream &out, MenuItem p)
{
    out << fixed << showpoint << setprecision(2);
    out << setw(26) << p.name  << setw(23) << p.price << endl; 
    
    return; 
}