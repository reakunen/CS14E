//
// assignment.cpp
//
// Brian Mai
// 7/25/2021
// Assignment 8 
// Finds the prime numbers using the sieve of eratosthenes algorithm
//

#include <iostream>
#include <fstream>

using namespace std; 

int main () 
{
    ofstream fout;
    fout.open("test.txt");

    if (!fout)
    {
        cout << "Error opening output file." << endl; 
        return -1; //failure
    } 
    else 
    {
        bool a[10001];
        for(int i = 2; i < 10001; i++)
        {
            a[i] = true;
        }

        a[0] = false;
        a[1] = false;
        
        const int max = 10000;
        for (int n = 2; n <= max / 2; n++)
        {
            if(a[n] == true)
            {
                for(int j = 2; j * n <= max; j++) 
                {
                    a[j * n] = false;
                }
            }
        }

        int ct = -1; //printing
        for (int i = 2; i < 10001; i++) 
        {   

            if(a[i] == true) 
            { 
                ct++;

                if (ct == 8) //fence post
                {
                    fout << endl;
                    ct = 0; 
                }  
                else if ((ct < 8) && (ct != 0)) 
                {
                    fout << "---";
                }

                fout << i;
            }
        }
        fout.close();
    }
    return 0; 
}