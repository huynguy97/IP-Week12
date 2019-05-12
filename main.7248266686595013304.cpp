//                                      

#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>
#include <string>

using namespace std;

struct Gift
{
    int price;
    string name;
};

vector<Gift> available(vector<Gift> giftlist, vector<string> wishlist, int budget)
{
    /*    */
    assert(true);
    /*     
                                                                                                                                                                          
    */

    vector<Gift> available_gifts;
    for (int i = 0; i < wishlist.size(); i++)
    {
        for (int ii = 0; ii < giftlist.size(); ii++)
        {
            if (wishlist[i] == giftlist[ii].name)
            {
                if (giftlist[ii].price <= budget)
                    available_gifts.push_back(giftlist[ii]);
                break;
            }
        }
    }
    return available_gifts;
}

vector<Gift> get_giftlist(string giftlist_filename)
{
    /*    */
    assert(true);
    /*     
                                                                                             
    */

    vector<Gift> giftlist;
    ifstream giftfile;
    giftfile.open(giftlist_filename.c_str());

    if(!giftfile)
    {
        cout << "File " << giftlist_filename << " was not opened correctly.\n";
        return giftlist;
    }

    while(!giftfile.eof())
    {
        Gift gift;
        giftfile >> gift.price;
        giftfile.ignore(1);
        getline(giftfile, gift.name);

        if (gift.name.empty())
            continue;

        giftlist.push_back(gift);
    }
    giftfile.close();
    return giftlist;
}

vector<string> get_wishlist(string wishlist_filename, int& budget)
{
    /*    */
    assert(true);
    /*     
                                                                                                                        
    */

    vector<string> wishlist;
    ifstream wishlistfile;
    wishlistfile.open(wishlist_filename.c_str());

    if(!wishlistfile)
    {
        cout << "File " << wishlist_filename << " was not opened correctly.\n";
        return wishlist;
    }

    wishlistfile >> budget;
    while(!wishlistfile.eof())
    {
        string gift;
        getline(wishlistfile, gift);

        if (gift.empty())
            continue;

        wishlist.push_back(gift);
    }
    return wishlist;
}

int sum (vector<Gift> a, int index = 0)
{
    /*    */
    assert(index >= 0);
    /*     
                                               
    */

    int total = 0;
    for(int i = index; i < a.size(); i++)
        total += a[i].price;
    return total;
}

void improve (vector<Gift> a, vector<Gift> &b)
{
    /*    */
    assert(true);
    /*     
                                            
    */

    if (sum(a) > sum(b))
        b = a;
}

void _gifts (vector<Gift> giftlist, vector<Gift>& attempt, vector<Gift>& best, int current, int budget)
{
    /*    */
    assert(current >= 0);
    /*     
                                                                 
    */

    if (budget == 0)
    {
        best = attempt;
        return;
    }

    if (budget < 0)
        return;

    if (current >= giftlist.size())
    {
        improve(attempt, best);
        return;
    }

    if (sum(attempt) + sum(giftlist, current) <= sum(best))
        return;

    attempt.push_back(giftlist[current]);
    _gifts(giftlist, attempt, best, current + 1, budget - giftlist[current].price);

    attempt.pop_back();
    _gifts(giftlist, attempt, best, current + 1, budget);
}

vector<Gift> gifts(vector<Gift> giftlist, int budget)
{
    /*    */
    assert(true);
    /*     
                                                                                                                 
    */

    vector<Gift> attempt, best;
    _gifts(giftlist, attempt, best, 0, budget);
    return best;
}

int main()
{
    string giftlist_filename = "giftstore.txt";
    vector<string> wishlist_filenames = {"Andrew.txt", "Belle.txt", "Chris.txt", "Desiree.txt", "Edward.txt", "Fabienne.txt"};

    vector<Gift> giftlist = get_giftlist(giftlist_filename);

    for (int i = 0; i < wishlist_filenames.size(); i++)
    {
        int budget;
        vector<string> wishlist = get_wishlist(wishlist_filenames[i], budget);

        vector<Gift> available_gifts = available(giftlist, wishlist, budget);

        vector<Gift> giftinglist = gifts (available_gifts, budget);

        int cost = sum(giftinglist);
        cout << "Wishlist: " << wishlist_filenames[i] << endl;
        cout << "Budget: " << budget << endl;
        cout << "Total gift cost: " << cost << endl;
        cout << "Difference: " << budget - cost << endl;
        cout << "Final wishlist:\n";
        for (int i = 0; i < giftinglist.size(); i++)
            cout << i + 1 << ". " << giftinglist[i].price << " - " << giftinglist[i].name << endl;
        cout << endl << endl;
    }

    return 0;
}

