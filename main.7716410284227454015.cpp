#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <string>

//                                                  
using namespace std;

typedef string toy;

struct Gift
{
    string toy;
    int cost;
};

ostream& operator<< (ostream& out, const Gift gift)
{//               
    assert (true) ;
//                                                                       
    out << gift.toy << " " << gift.cost;
    return out;
}

istream& operator>> (istream& in, Gift& gift)
{//               
    assert (true) ;
//                                                                      
    string help = " ";
    in >> gift.cost;
    getline(in, help, ' ');
    getline(in, gift.toy);
    return in;
}

void showvector(vector<toy>& a)
{
//               
    assert(true);
//                                                            
    for (int i=0; i<a.size(); i++)
    {
        cout << a[i] << endl;
    }
}

int presents (vector<toy>& wishes, vector<Gift>& giftstore, int budget, int a, int b, vector<toy>& Stnicholas, vector<toy>& best, int& storebudget)
{
//                
    assert(a <= giftstore.size() && b <= wishes.size());
/*                 
                                                                                         
                                                                               
    */
//             
    if (budget == 0)
    {
        cout << "A perfect list is: " << endl;
        showvector(Stnicholas);
        return 1;
    }
    else if (budget < 0)
        return 0;
    else if ( b >= wishes.size())
    {
        if (storebudget > budget)
        {
            storebudget = budget;
            best = Stnicholas;
        }
        return 0;
    }
//                  
    else if (wishes[b] == giftstore[a].toy)
    {
        Stnicholas.push_back(giftstore[a].toy);
        int with_toy  = presents(wishes, giftstore, budget - giftstore[a].cost, 0, b+1, Stnicholas, best, storebudget);
        Stnicholas.pop_back();
        int without_toy = presents(wishes, giftstore, budget, 0, b+1, Stnicholas, best, storebudget);
    }
    else if (a >= giftstore.size())
        int next_search = presents(wishes, giftstore, budget, 0, b+1, Stnicholas, best, storebudget);
    else
        int continue_search = presents(wishes, giftstore, budget, a+1, b, Stnicholas, best, storebudget);
}

bool readstore(vector<Gift>& store, ifstream& file)
{
//                
    assert(file);
//                                                                           
    Gift help;

    while (file)
    {
        file >> help;
        store.push_back(help);
    }

return true;
}

bool readlist(vector<toy>& wished, ifstream& wishfile, int& budget)
{
//      
    assert(wishfile);
//                                                                               
    toy helppresent;
    string dummy="";

    wishfile >> budget;
    getline(wishfile, dummy);

    do
    {
        getline(wishfile, helppresent);
        wished.push_back(helppresent);
    }
    while (wishfile);
return true;
}

int main()
{
/*                                                                                                    
                                                                                                   
                                                                                               
                     */
    ifstream Andrew ("Andrew.txt");
    ifstream Belle ("Belle.txt");
    ifstream Chris ("Chris.txt");
    ifstream Desiree ("Desiree.txt");
    ifstream Edward ("Edward.txt");
    ifstream Fabienne ("Fabienne.txt");
    ifstream Store ("giftstore.txt");
    vector<Gift> thestore;
    vector<toy> Alist;
    vector<toy> Blist;
    vector<toy> Clist;
    vector<toy> Dlist;
    vector<toy> Elist;
    vector<toy> Flist;
    int Abudget=0;
    int Bbudget=0;
    int Cbudget=0;
    int Dbudget=0;
    int Ebudget=0;
    int Fbudget=0;
    vector<toy> Perfectlist;
    vector<toy> Bestlist;

    readstore(thestore,Store);

    readlist(Alist, Andrew, Abudget);
    readlist(Blist, Belle, Bbudget);
    readlist(Clist, Chris, Cbudget);
    readlist(Dlist, Desiree, Dbudget);
    readlist(Elist, Edward, Ebudget);
    readlist(Flist, Fabienne, Fbudget);

    presents(Alist, thestore, Abudget, 0, 0, Perfectlist, Bestlist, Abudget);
    cout << "Andrew's best list is: " << endl;
    showvector(Bestlist);
    cout << "His remaining budget is: " << Abudget << endl;

    presents(Blist, thestore, Bbudget, 0, 0, Perfectlist, Bestlist, Bbudget);
    cout << endl << "Belle's best list is: " << endl;
    showvector(Bestlist);
    cout << "Her remaining budget is: " << Bbudget << endl;

    presents(Clist, thestore, Cbudget, 0, 0, Perfectlist, Bestlist, Cbudget);
    cout << endl << "Chris' best list is: " << endl;
    showvector(Bestlist);
    cout << "His remaining budget is: " << Cbudget << endl;

    presents(Dlist, thestore, Dbudget, 0, 0, Perfectlist, Bestlist, Dbudget);
    cout << endl << "Desiree's best list is: " << endl;
    showvector(Bestlist);
    cout << "Her remaining budget is: " << Dbudget << endl;

    presents(Elist, thestore, Ebudget, 0, 0, Perfectlist, Bestlist, Ebudget);
    cout << endl << "Edward's best list is: " << endl;
    showvector(Bestlist);
    cout << "His remaining budget is: " << Ebudget << endl;

    presents(Flist, thestore, Fbudget, 0, 0, Perfectlist, Bestlist, Fbudget);
    cout << endl << "Fabienne's best list is: " << endl;
    showvector(Bestlist);
    cout << "Her remaining budget is: " << Fbudget << endl;

    return 0;
}

