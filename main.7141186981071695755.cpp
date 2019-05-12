#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>

//                            
//                        

using namespace std;

struct Gift
{
    int cost;
    string giftname;
};

int budgetbudget ;
vector<Gift> budget;
vector<string> wishlist;
vector<Gift> data;      //     

int size (vector<string>& a)
{
    return static_cast<int> (a.size ()) ;
}

int size (vector<Gift>& budget)
{
    return static_cast<int> (budget.size ()) ;
}

istream& operator>> (istream& in, Gift& gift)
{//               
    assert (true) ;
/*                 
                                                                                 
*/
    in >> gift.cost;
    char c;
    in.get(c);
    getline(in, gift.giftname);
    return in ;
}

ostream& operator<< (ostream& out, Gift gift)
{//               
    assert (true) ;
/*                 
                                               
*/
    out << gift.cost << ' ' << gift.giftname;
	return out ;
}

int read_gifts (ifstream& infile, vector<Gift>& data)
{//               
    assert (infile.is_open ()) ;
/*                 
                                                  
                                                          
*/
    int no_of_gifts = 0 ;
    do {
        Gift gift ;
        infile >> gift ;
        if (infile)
        {

            cout << gift << endl;
            data.push_back (gift) ;
            no_of_gifts++;
        }
    }
    while (infile );
    return no_of_gifts ;
}

int read_file (string filename, vector<Gift>& data)
{//               
    assert (true) ;
/*                 
                                                                             
                                                                                           
                                        
*/
    ifstream giftsDBS (filename.c_str());
    if (!giftsDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_GIFTS = read_gifts (giftsDBS, data);
	giftsDBS.close();
	cout << "Read " << NO_OF_GIFTS << " gifts." << endl;
	return NO_OF_GIFTS;
}

int read_wishlist (string filename, vector<string>& wishlist)
{
    //               
    assert (true) ;
/*                 
                                                                                 
                                                                                               
                                        
*/
    ifstream wishes (filename.c_str());
    if (!wishes)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }

    cout << "Reading '" << filename << "'." << endl;
    wishes >> budgetbudget; //                                
        do {
        string gift ;
        getline(wishes, gift);
        cout << gift << endl;
        if (wishes)
        {
            wishlist.push_back (gift) ;
        }
    }
    while (wishes );
	wishes.close();
	cout << "Your budget is " << budgetbudget << endl;
    return budgetbudget;
}

int maximum (int a, int b)
{//               
    assert (true) ;
//                                                        
    if (a >= b)
        return a ;
    else
        return b ;
}

int sum (vector<Gift>& budget, int from)
{//               
    assert (from >= 0 && from <= size(budget)) ;
//                 
//                                                                                                              
    int sum = 0 ;
    for (int i = from ; i < size(budget) ; i++)
        sum += budget[i].cost ;
    return sum ;
}

int sum (vector<Gift>& budget)
{
    return sum (budget,0) ;
}

void show ( vector<Gift>& budget)
{//               
    assert (true) ;
//                                                                                                
	const int NO_OF_ELEMS = size (budget) ;
	cout << "{" ;
	if ( NO_OF_ELEMS > 0 )
	{
		for (int i = 0 ; i < NO_OF_ELEMS-1 ; i++)
			cout << budget[i] << "," ;
		cout << budget[NO_OF_ELEMS-1] ;
	}
	cout << "}" << endl ;
}

void improve (vector<Gift>& current, vector<Gift>& best)
{//               
    assert (true) ;
//                 
//                                                                 
    if (sum (current) > sum (best))
        best = current ;
}

bool match_giftstore(vector<Gift>& data, vector<string>& wishlist, int c, int& b)
{
    //               
    assert (c >= 0 && c < wishlist.size()) ;
/*                 
                                                                                                                                       
*/
    for(int b = 0; b< data.size(); b++)
    {
        if (wishlist[c] == data[b].giftname)
        {
            return true;
        }
    }
    return false;
}

int solution ( vector<Gift>& current, vector<Gift>& best, vector<Gift>& data, vector<string>& wishlist, int c, int target, int& no_of_prunes)
{//               
    assert (true) ;
//                 
//                                                                                                                            
//                                                                                                                 
	int b;
	if ( c >= size(wishlist) )
        {
            improve (current, best) ;
            return 0 ;
        }
    if (!match_giftstore(data, wishlist, c, b))
        {
            //                                         
            return solution ( current, best, data, wishlist, c+1, target, no_of_prunes );
        }
	if ( target == 0 )
        {
            best = current ;
            return 1 ;
        }
	if ( target < 0 )
        {
            return 0 ;
        }

	if (sum (current) + sum (data,b) <= sum (best))
        {
            no_of_prunes++ ;
            return 0 ;
        }
    else
        {
            current.push_back ( data[b] ) ;
            const int WITH_C    = solution ( current, best, data, wishlist, c+1, target - data[b].cost, no_of_prunes ) ;
            current.pop_back () ;
            const int WITHOUT_C = solution ( current, best, data, wishlist, c+1, target, no_of_prunes ) ;
            return WITH_C + WITHOUT_C ;
        }

}

void find_best_solution (vector<Gift>& budget, int value)
{//               
    assert (true) ;
//                                                                                     
//                                      
    vector<Gift> current ;
    vector<Gift> best ;
    int no_of_prunes = 0 ;
    cout << solution (current, best, budget, wishlist, 0, value, no_of_prunes) ;
    cout << endl << "One best found solution is: " << endl ;
    show (best) ;
    cout << endl << "It has value: " << sum(best) << endl;
}

int main()
{
    read_file("giftstore.txt", data);
    read_wishlist("Belle.txt", wishlist);
    int value;
    find_best_solution(budget, value);
    return 0;
}

