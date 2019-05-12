#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <math.h>

/*                                              
                                                
                                                
                                              */

using namespace std;

/*                                              
                                                
                                              */

int best = 0;

void gifts (vector <int>& list_of_gifts, int budget, int maximal, int position)
{
    /*                */
    assert (budget >= 0 &&  maximal >= 0 && position >= 0);
    /*                                                                                                                             */

    if (budget == maximal)
    {
        best = maximal;
        return;
    }
    if (budget < maximal)
        return;
    if (position == list_of_gifts.size())
        return;
    if (best < maximal)
        best = maximal;

    if (budget >= maximal)
    {
        gifts(list_of_gifts, budget, maximal + list_of_gifts[position], position + 1);
        gifts(list_of_gifts, budget, maximal, position + 1);
        return;
    }
}

/*                                              
                                                
                                              */

void read_the_gift_store (vector<int>& gift_prices, vector<string>& gift_names)
{
    /*                */
    assert (true);
    /*                                                                                                                                    */
    ifstream gift_store;
    gift_store.open ("giftstore.txt");

    while (gift_store)
        {
        int price;
        gift_store >> price;
        gift_prices.push_back(price);

        string name;
        getline(gift_store, name);
        if (name.size() != 0)
        {
            name.erase(0,1);
            gift_names.push_back(name);
        }
    }
}

void read_verlanglijstje (ifstream& infile, vector<int>& wishlist_names, int& budget, vector<int>& gift_prices, vector<string>& gift_names)
{
    /*                */
    assert (true);
    /*                                                                                                                                        */

    string filename;
    cout << "Enter the name of your wishlist (for example: 'Andrew.txt'):" << endl;
    cin >> filename;
    infile.open(filename.c_str());
    while (!(infile.is_open()))
    {
        cout << "Error, please enter a valid wishlist: " << endl;
        cin >> filename;
        infile.open(filename.c_str());
    }
    if (infile)
    {
        cout << "Your wishlist will now be read by St. Nicholas (have you been a good boy/girl?) ..." << endl << endl;
        infile >> budget;
        infile.ignore();
        while (infile)
        {
            string name;
            getline(infile, name);
            for (int i = 0; i < gift_names.size(); i++)
            {
                if (name == gift_names[i])
                {
                    wishlist_names.push_back(gift_prices[i]);
                }
            }
        }
    }
}
/*                                              
                                                
                                              */

int main()
{
    vector<int> gift_prices;
    vector<string> gift_names;
    vector<int> wishlist_names;

    ifstream infile;

    int budget;
    int maximal = 0;
    int position = 0;

    read_the_gift_store(gift_prices, gift_names);
    read_verlanglijstje(infile, wishlist_names, budget, gift_prices, gift_names);
    gifts(wishlist_names, budget, maximal, position);
    cout << "The budget is: " << budget <<". St. Nicholas will spend " << best << " cents based on your wishlist, and he will have " << budget - best << " cents remaining of his budget" << endl;

}
/*                                                                         
                                                                           
                                                                         */
/*

                                                               
                                                               
                                                             
                                                               
                                                                
                                                                    
*/

