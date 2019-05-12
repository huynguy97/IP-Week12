//                     
//                        

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;

struct Gift
{
    string gift_name;
    int price;
};

struct Wishlist
{
    vector<Gift> possible_gifts;
    vector<string> asked_gifts;
    int budget;
};

istream& operator>> (istream& in, Gift& gift)
{
    in >> gift.price;
    getline(in, gift.gift_name);

    return in;
}

void show_gift (Gift gift)
{
    //             
    assert(true);
    /*                                                             
    */
    cout << gift.price << " " <<gift.gift_name << endl;
}

void show_gifts (vector<Gift> giftstore)
{
    //             
    assert(true);
    /*                                                          
    */
    for(int i=0; i < giftstore.size(); i++) show_gift(giftstore[i]);
}

void read_giftstore (vector<Gift>& giftstore)
{
    //             
    assert(true);
    /*                                                                                 

    */
    ifstream infile;
    infile.open("giftstore.txt");

    if(infile.is_open())
    {
        Gift gift;
        while(infile)
        {
                infile >> gift;
                gift.gift_name.erase(gift.gift_name.begin());
                if (infile) giftstore.push_back(gift);
        }
    }
    else cout << "giftstore.txt could not be opened" << endl;

}

bool read_wishlist(Wishlist& wishlist)
{
    //             
    assert(true);
    /*                                                                        
    */

    ifstream infile;
    string person;
    cout << "Give a name of the person for who you want to determine the minimum left budget: " << endl;
    cin >> person;
    person.append(".txt");

    infile.open(person);

    if (infile.is_open())
    {
        infile >> wishlist.budget;
        string gift;
        getline(infile, gift);
        while(infile)
        {
            getline(infile, gift);
            if(infile) wishlist.asked_gifts.push_back(gift);
        }
        return true;
    }
    else cout << "Person's wishlist could not be opened" << endl;
    return false;

}

void show_wishlist(Wishlist wishlist)
{
    //             
    assert(true);
    /*                                                                         
    */
    cout << wishlist.budget << endl;
    for(int i=0; i < wishlist.asked_gifts.size(); i++) cout << i << " " << wishlist.asked_gifts[i] << endl;
}

void determine_possible_gifts(Wishlist& wishlist, vector<Gift> giftstore)
{
    //             
    assert(true);
    /*                                                                                                                                        
    */
    for(int i=0; i < wishlist.asked_gifts.size(); i++)
    {
        for (int j=0; j < giftstore.size(); j++)  if (wishlist.asked_gifts[i]==giftstore[j].gift_name) wishlist.possible_gifts.push_back(giftstore[j]);
    }
}

void gifts (Wishlist wishlist, int budget, int i, int& best_option)
{
    //             
    assert(i > wishlist.possible_gifts.size());
    /*                                                                                                         
    */

    if (budget < 0 ) return;
    else if(budget < best_option) best_option = budget;

    if (i == wishlist.possible_gifts.size()) return;
    else{
        gifts(wishlist, budget - wishlist.possible_gifts[i].price, i+1, best_option);
        gifts(wishlist, budget, i+1, best_option);
    }

}

int main()
{
    vector<Gift> giftstore;
    Wishlist wishlist;

    read_giftstore(giftstore);
    if (read_wishlist(wishlist))
    {
        determine_possible_gifts(wishlist, giftstore);
        int best_option;
        gifts(wishlist, wishlist.budget, 0, best_option);
        cout << wishlist.budget-best_option << endl;

    }

    //                                                                                                       
}

