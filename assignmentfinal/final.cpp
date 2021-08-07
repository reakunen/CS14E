//
// final.cpp
//
// Brian Mai
// 8/5/2021
// Final Assignment
// Program that reads account and transaction data from a text file 
//

#include <iostream> 
#include <iomanip>
#include <fstream>

using namespace std; 

const int MAX = 100; 

struct Account 
{
    string name; 
    int accountNum; 
    double balance; 
    double creditAmount; 
};

void readRecord(ostream &out, istream &in, Account &p);
void printData(ostream &out, Account p);
void postPayment(ostream &out, Account &p, double payment);
void postCharge(ostream &out, Account &p, double charge); 
int findAccount(Account customers[], int amount, int accnum); 
void exchange(Account &a, Account &b); 
void BubbleSort( Account customers[], int n ); 
void failPayment(ostream &out, double payment, int a);
void failCharge( ostream &out, double charge, int a); 
void addAccount(ostream &out, int num, string name, double balance, double credit);
void oldPayment(ostream &out, Account p, int a, double b); 
void oldCharge(ostream &out, Account p, int a, double b);

int main () 
{
    //initialize files.
    ifstream fin; 
    ofstream fout; 
    string inputFile, outputFile; 

    cout << "Enter input file name: " << flush; 
    cin >> inputFile; 
    cout << "Enter output file name: " << flush; 
    cin >> outputFile; 

    fin.open(inputFile); 
    fout.open(outputFile); 
    
    if (!fin) 
    {
        cout << "Error opening input data." << endl; 
        fin.clear(); 
        return -1; 
    }

    if (!fout) 
    {
        cout << "Error opening output data." << endl;
        fout.clear(); 
        return -1; 
    }

    Account customers[MAX]; 
    char type; 
    int num = -1, accountNum, index; 
    double charge, payment; 

    while (fin >> type) 
    {
        switch(type) 
        {
            case 'A':
                num++; 
                readRecord(fout, fin, customers[num]); 
                BubbleSort(customers, num);
                break; 

            case 'P': 
                fout << "---- Payment ----" << endl; 
                fin >> accountNum >> payment; 
                index = findAccount(customers, num, accountNum); 
                if (index > -1) 
                {
                    oldPayment(fout, customers[index], accountNum, payment); 
                    postPayment(fout, customers[index], payment); 
                } 
                else if (index == -1)
                {
                    failPayment(fout, payment, accountNum); 
                }
                fout << '\n'; 
                break;
                
            case 'C':
                fout << "---- Charge ----" << endl; 
                fin >> accountNum >> charge; 
                index = findAccount(customers, num, accountNum);

                if (index > -1) 
                {
                    oldCharge(fout, customers[index], accountNum, charge); 
                    postCharge(fout, customers[index], charge); 
                }
                else if (index == -1)
                {   
                    failCharge(fout, charge, accountNum);
                }
                fout << '\n'; 
                break;

            case 'Q':
                fout << "---- Query ----\n" << endl;
                //prints out all the customers & info in the array
                for (int i = 0; i <= num; i++)
                {
                    printData(fout, customers[i]);
                }
                fout << '\n';
                break; 
        }
    }
    fin.close();
    fout.close(); 

    return 0; 
}
void oldPayment(ostream &out, Account p, int a, double b)
{

    out << "Account #" << a << " has paid $" << b << '\n' << endl;

    out << "Pre Payment: " << endl;
    out << "Account: #" << setw(3) << p.accountNum  << fixed << 
    showpoint << setprecision(2) << setw(18) << "Name: " << 
    setw(8) << p.name << endl;
    out << "Balance: $" << setw(9) << p.balance << setw(15) << 
    "Credit: $" << setw(8) << p.creditAmount << '\n' << endl;
}

void oldCharge(ostream &out, Account p, int a, double b)
{
    out << "Account #" << a << " has been charged $" << b << '\n' <<endl;

    out << "Pre Charge: " << endl;
    out << "Account: #" << setw(3) << p.accountNum  << fixed << 
    showpoint << setprecision(2) << setw(18) << "Name: " << 
    setw(8) << p.name << endl;
    out << "Balance: $" << setw(9) << p.balance << setw(15) << 
    "Credit: $" << setw(8) << p.creditAmount << '\n' << endl;
}


void failPayment(ostream &out, double payment, int a) 
{   
    out << fixed << showpoint << setprecision(2);
    out << "Account: #" << a << " was not found."
    " Failure to pay: $" << payment << endl;
}
void failCharge( ostream &out, double charge, int a)
{
    out << fixed << showpoint << setprecision(2);
    out << "Account: #" << a << " was not found." <<
    " Failure to charge : $" << charge <<  endl;

} 

void postPayment(ostream &out, Account &p, double payment) 
{
    //payment, subtracts from balance (debt)
    p.balance -= payment;

    out << "Post Payment: " << endl;
    out << "Account: #" << setw(3) << p.accountNum  << fixed << 
    showpoint << setprecision(2) << setw(18) << "Name: " << 
    setw(8) << p.name << endl;
    out << "Balance: $" << setw(9) << p.balance << setw(15) << 
    "Credit: $" << setw(8) << p.creditAmount << endl;
}

void postCharge(ostream &out, Account &p, double charge)
{
    //positive balance = in debt, negative = overpayment, no debt.
    //charge adds debt (add to balance)
    double mayCharge; 
    mayCharge = p.creditAmount - p.balance;
    
    if (charge > mayCharge) 
    {
        out << "ERROR: This account is unable to charge $" << charge << '\n' <<endl; 
        out << "Post Charge: " << endl; 

        out << "Account: #" << setw(3) << p.accountNum  << fixed << 
        showpoint << setprecision(2) << setw(18) << "Name: " << 
        setw(8) << p.name << endl;
        out << "Balance: $" << setw(9) << p.balance << setw(15) << 
        "Credit: $" << setw(8) << p.creditAmount << endl;
        
    }
    else 
    {
        p.balance = p.balance + charge;
        
        out << "Post Charge: " << endl; 

        out << "Account: #" << setw(3) << p.accountNum  << fixed << 
        showpoint << setprecision(2) << setw(18) << "Name: " << 
        setw(8) << p.name << endl;
        out << "Balance: $" << setw(9) << p.balance << setw(15) << 
        "Credit: $" << setw(8) << p.creditAmount << endl;
    }
}

int findAccount(Account customers[], int amount, int accnum) 
{   
    //when found accnum in array, return the array index & break
    int i;
    bool found = false; 
    for (i = 0; i <= amount; i++) 
    {
        if ((customers[i].accountNum) == accnum) {
            found = true; 
            break;    
        }
    }

    if (found) 
    {
        return i; 
    }
    else 
    {
        return -1; 
    }

}

void readRecord(ostream &out, istream &in, Account &p)
{
    //after reading account, print.
    in >> p.accountNum >> p.name >> p.balance >> p.creditAmount;

    addAccount(out, p.accountNum, p.name, p.balance, p.creditAmount); 

}

void addAccount(ostream &out, int num, string name, double balance, double credit)
{
    //helper function for readRecord
    out << "---- New Account ----\n" << endl; 

    out << "Account: #" << setw(3) << num  << fixed << 
    showpoint << setprecision(2) << setw(18) << "Name: " << setw(8) << name
    << endl;
    out << "Balance: $" << setw(9) << balance << setw(15) << 
    "Credit: $" << setw(8) << credit << '\n' << endl;
   
}

void printData(ostream &out, Account p) 
{
    out << "Account: #" << setw(3) << p.accountNum  << fixed << 
    showpoint << setprecision(2) << setw(10) << "Name: " << setw(8) <<p.name 
    << setw(14) << "Balance: $" <<  setw(10) << p.balance 
    << setw(14) << "Credit: $" << setw(8) << p.creditAmount << endl;
    
}

void exchange( Account &a, Account &b )
{
    Account t = a;
    a = b;
    b = t;
    return;
}

void BubbleSort (Account customers[], int n )
{
    int i;
    bool sort = false;
    while( !sort )
    {
        sort = true;
        for( i = 0; i < n; i++ )
        {
            if( customers[i].accountNum > customers[i+1].accountNum )
            {
                sort = false;
                exchange( customers[i], customers[i+1] );
            }
        }
    }
    return;
}
