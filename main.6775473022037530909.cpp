/*                                                                    
                                                     
                                                     
                                                                     */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

using namespace std;

/*                                                            
                                                            
                                                            */

struct Gift
{
    int price;
    string name;
};

istream& operator>> (istream& in, Gift& wish)
{
    in >> wish.price;
    in.ignore(1, ' ');
    getline(in, wish.name);
    return in;
}

ostream& operator<< (ostream& out, Gift& wish)
{
    out << wish.price << endl;
    out << wish.name << endl;
    return out;
}

/*                                                            
                                   
                                                            */

int sum (vector<Gift>& attempt, int from)
{
//                
    assert (from >= 0 && from <= attempt.size()) ;
//                 
//                                                                                       
//                                          
    int sum = 0 ;
    for (int i = from ; i < attempt.size() ; i++)
        sum += attempt[i].price ;
    return sum ;
}

int sum (vector<Gift>& attempt)
{
//                
    assert(true);
//                 
//                                                         
    return sum (attempt,0) ;
}

void improve (vector<Gift>& attempt, vector<Gift>& best)
{
//                
    assert (true) ;
//                 
//                                                                 
    if (sum (attempt) > sum (best))
        best = attempt ;
}

void common_values (vector<Gift>& giftstore, vector<string>& wishlist, vector<Gift>& common_gifts)
{
//                
    assert (true);
//                 
//                                                                                            
//                                                                                         
    for (int i = 0; i < giftstore.size(); i++)
        for (int j = 0; j < wishlist.size(); j++)
            if (giftstore[i].name == wishlist[j])
                common_gifts.push_back(giftstore[i]);
}

int gifts ( vector<Gift>& current, vector<Gift>& best, vector<Gift>& price_wishlist, int c, int budget)
{
//                
    assert (c >= 0);
//                 
//                                                                                             
//                                                                                                 
//                                                                                                      
	if ( budget == 0 )                     { best = current ; return 1 ; }
	else if ( budget < 0 )                 { return 0 ; }
	else if ( c >= price_wishlist.size() ) { improve (current, best) ; return 0 ; }
	else if (sum (current) + sum (price_wishlist,c) <= sum (best))
                                           { return 0 ; }
	else {
		current.push_back(price_wishlist[c]) ;
		const int WITH_C    = gifts ( current, best, price_wishlist, c+1, budget - price_wishlist[c].price ) ;
		current.pop_back () ;
		const int WITHOUT_C = gifts ( current, best, price_wishlist, c+1, budget) ;
		return WITH_C + WITHOUT_C ;
	}
}

void show_gifts (vector<Gift>& best)
{
//                
    assert (true);
//                 
//                                                                 
    for (int i = 0; i < best.size(); i++)
        cout << best[i].name << endl;
}

/*                                                            
                      
                                                            */

void read_giftstore (vector<Gift>& giftstore, ifstream& input)
{
//                
    assert (input.is_open());
//                 
//                                                                                
    Gift product;
    while (input >> product)
        giftstore.push_back(product);
}

void read_wishlist (vector<string>& wishlist, ifstream& input, int& budget)
{
//                
    assert (input.is_open());
//                 
//                                                                                             
    input >> budget;
    input.ignore(1, '\n');

    string title;
    while (getline(input, title))
        wishlist.push_back(title);
}

void open_wishlist (vector<string>& wishlist, ifstream& input, int& budget)
{
//                
    assert (true);
//                 
//                                                                                                  
//                                                     
    string filename;
    cout << "Please enter a wishlist text file" << endl;
    cin >> filename;
    input.open(filename.c_str() );
    if (input.is_open())
    {
        cout << "File opened succesfully" << endl;
        read_wishlist(wishlist, input, budget);
    }
}

int main()
{
    vector<Gift> giftstore;
    vector<string> wishlist;
    vector<Gift> common_wishes;

    vector<Gift> attempt;
    vector<Gift> best;
    int budget;

    ifstream input_giftstore ("giftstore.txt");
    read_giftstore(giftstore, input_giftstore);
    ifstream input_wishlist;
    open_wishlist(wishlist, input_wishlist, budget);
    common_values(giftstore, wishlist, common_wishes);

    cout << "The gifts you should get for the most optimal use of the budget are:" << endl;
    gifts(attempt, best, common_wishes, 0, budget);
    show_gifts(best);
    cout << "The budget was: " << budget << " and the total price of all the gifts is: " << sum(best) << endl;

    input_giftstore.close();
    input_wishlist.close();

    return 0;
}

