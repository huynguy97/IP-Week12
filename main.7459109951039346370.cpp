//                                                                                                                                                                          
//                                                                                                          

//               
//                                               
//                                                                    
//                                                                                               
//                                                           
//                                                                 
//                                                                      
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;

struct Gift
{
    string giftname;
    int giftcost;
};

int size (vector<Gift>& list)
{
    return static_cast<int> (list.size());
}

void show_vector (vector<Gift>& toshow)
{
    int s = size(toshow);
    for (int i = 0; i < s ; i++)
    {
        Gift showed = toshow[i] ;
        if (showed.giftcost != 0)
            cout << showed.giftcost << " " ;
        cout << showed.giftname << endl;
    }
}

bool instock (vector<Gift>& wishlist, vector<Gift>& store, int c)
{//                
    assert (c <= size(wishlist) && c <= size(store));
//                  
//                                                                                                                                           
    Gift currentwish = wishlist[c];
    for (int i = 0; i < size(store); i++)
    {
        Gift check = store[i];
        if (check.giftname == currentwish.giftname)
        {
            currentwish.giftcost = check.giftcost ;
            wishlist[c] = currentwish;
            return true;
        }
    }
    return false;
}
//                                                  
int cost (vector<Gift>& wishlist, int c)
{
    Gift currentwish = wishlist[c] ;
    return currentwish.giftcost ;
}

int total (vector<Gift>& tocheck)
{
    int value = 0 ;
    for (int i = 0; i < size(tocheck); i++)
    {
        Gift calculate = tocheck[i] ;
        value = value + calculate.giftcost ;
    }
    return value;
}

void improve (vector<Gift>& best, vector<Gift>& attempt)
{
    if (total (attempt) > total(best))
        best = attempt ;
}

int gifts (vector<Gift>& wishlist, vector<Gift>& store, vector<Gift>& attempt, vector<Gift>& best, int c, int budget)
{//                
    assert (c <= size(wishlist) && c >= size(attempt)) ;
    //           
    if (budget == 0)
    {
        best = attempt ;
        return 1;
    }
    else if (budget < 0)
        return 0;
    else if (c == size(wishlist))
    {
        improve (best, attempt) ;
        return 1;
    }
    //                
    else if (!instock (wishlist, store, c))
        return gifts (wishlist, store, attempt, best, c+1, budget) ;
    else
    {
        attempt.push_back(wishlist[c]) ;
        int with = gifts (wishlist, store, attempt, best, c+1, budget - cost(wishlist, c)) ;
        attempt.pop_back() ;
        int without = gifts (wishlist, store,  attempt, best, c+1, budget) ;
        return with + without ;
    }
}

bool open_file (ifstream& infile)
{//                
    assert (true);
//                  
//                                                       
    cout << "Enter the name of the file you wish to open." << endl;
    string filename ;
    getline (cin, filename) ;
    infile.open (filename.c_str()) ;
    if (infile)
        return true ;
    else
        return false ;
}

void create_storevector (vector<Gift>& create, ifstream& infile)
{
    while (infile)
    {
        Gift added;
        infile >> added.giftcost;
        infile.ignore(1, '#'); //                                                                  
        getline(infile, added.giftname);
        create.push_back(added);
    }
    create.pop_back() ;
}

void create_listvector (vector<Gift>& create, ifstream& infile, int& budget)
{
    infile >> budget;
    while (infile)
    {
        Gift added;
        added.giftcost = 0;
        getline(infile, added.giftname);
        create.push_back(added);
    }
    create.pop_back() ;
}

int main()
{
    ifstream infile ;
    vector<Gift> storevector ;
    vector<Gift> wishlist ;
    vector<Gift> attempt ;
    vector<Gift> best ;
    cout << "Opening the giftstore" << endl;
    if (!open_file(infile))
        cout << "Could not successfully open the storefile" << endl;
    else
    {
        create_storevector (storevector, infile) ;
        show_vector (storevector) ;
        infile.close() ;
        cout << "Opening the wishlist" << endl;
        if (!open_file(infile))
            cout << "Could not successfully open the wishlist" << endl;
        else
        {
            int budget ;
            create_listvector (wishlist, infile, budget) ;
            show_vector (wishlist) ;
            infile.close() ;
            int solutions = gifts(wishlist, storevector, attempt, best, 1, budget) ;
            cout << "\n The number of solutions is " << solutions << endl;
            cout << "The solution which uses up the most of the budget is: \n" << endl;
            show_vector (best) ;
            int most = total(best) ;
            cout << " \n Which uses " << most ;
        }
    }
    return 0;
}

