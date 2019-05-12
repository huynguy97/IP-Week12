#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <fstream>
#include <string>

//                                              
//                                               

using namespace std;

struct Gift
{
	int price;
	string product;
};

istream& operator>> (istream& in, Gift& gift)
{//              
    assert (true) ;
/*                                                                               
                                 
*/

    in >> gift.price;
    in.get();
    getline(in,gift.product);

    return in;
}

void read_gift_store(vector<Gift>& gift_store)
{//              
    assert (true) ;
/*                                                                             
                      
*/
    Gift gift;

    ifstream infile ("giftstore.txt");
    if (!infile.is_open())
        cout << "Opening file failed";

    vector<Gift> giftstore;

    infile >> gift;
    while(infile)
    {
        gift_store.push_back(gift);
        infile >> gift;
    }

    infile.close();

}

void read_wish_list(string filename, vector<string>& wish_list, int& budget)
{//              
    assert (true) ;
/*                                                                                    
                                                                
*/
    ifstream infile (filename.c_str());
    if (!infile.is_open())
        cout << "Opening file failed";

    infile >> budget;
    infile.get();
    string next_wish;
    getline(infile,next_wish);
    while (infile)
    {
        wish_list.push_back(next_wish);
        getline(infile,next_wish);
    }
}

int request_price(vector<Gift>& gift_store, string product)
{//             
    assert(true);
    /*                                                                              
                                                       */

    for (int i=0;(unsigned)i<gift_store.size();i++)
    {
        if(gift_store[i].product==product)
            return gift_store[i].price;
    }
    return -1;
}

int sum (vector<string>& wish_list, vector<Gift>& gift_store)
{//               
    assert (true) ;
/*                                                                             
*/
    int sum = 0 ;
    for (int i = 0 ; (unsigned)i < wish_list.size() ; i++)
        sum += request_price(gift_store, wish_list[i]) ;
    return sum ;
}

void improve (vector<string>& current, vector<string>& best, vector<Gift>& gift_store)
{//               
    assert (true) ;
//                 
//                                                                 
    if (sum (current, gift_store) > sum (best, gift_store))
        best = current ;
}

void gifts(vector<string>& wish_list, vector<string>& chosen_gifts,
           vector<string>& best_gifts, int position, int budget,
           vector<Gift>& gift_store)
{//             
    assert(position>=0 && (unsigned)position<=wish_list.size());
    /*                                                                  
                                                                           
                                                     */

    if(budget==0)
    {
        best_gifts = chosen_gifts;
    }
    else if(budget<0) {}

    else if ((unsigned)position>=wish_list.size())
    {
        improve(chosen_gifts, best_gifts, gift_store);
    }

    else
    {
        int price = request_price(gift_store, wish_list[position]);
        if(price>=0)
        {
            chosen_gifts.push_back(wish_list[position]);
            gifts(wish_list, chosen_gifts, best_gifts, position+1, budget - price, gift_store);
            chosen_gifts.pop_back();
        }

        gifts(wish_list, chosen_gifts, best_gifts, position+1, budget, gift_store);
    }

}

int main()
{
    vector<Gift> gift_store;
    read_gift_store(gift_store);

    vector<string> wish_list, chosen_list, best_list;
    int budget;
    read_wish_list("Fabienne.txt", wish_list, budget);
    gifts(wish_list, chosen_list, best_list, 0, budget, gift_store);

    for(int i=0;(unsigned)i<best_list.size();i++)
    {
        cout << best_list[i] << endl;
    }

    return 0;
}

