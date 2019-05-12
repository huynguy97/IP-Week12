#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;

/*             
                               
                       
*/

typedef string Gift;

struct Store_gift
{
    int price;
    Gift name;
};

vector<Store_gift> giftstore;

int size (vector<Gift>& data)
{
    return static_cast<int>(data.size());
}

int size (vector<Store_gift>& data)
{
    return static_cast<int>(data.size());
}

void show(vector<Gift> data)
{
    assert(true);
    /*         
                                
    */

    for(int i = 0; i < size(data); i++)
    {
        cout << data[i] << endl;
    }
}

void read_giftstore ()
{
    assert(true);
    /*         
                                                                           
    */

    ifstream input_file;
    input_file.open("giftstore.txt");

    while(input_file)
    {
        Store_gift temp;
        input_file >> temp.price;
        char c;
        input_file.get(c);
        getline(input_file, temp.name);
        if (input_file)
        {
            giftstore.push_back(temp);
        }
    }
}

void read_wishlist (vector<Gift>& wishlist, int& budget)
{
    assert(true);
    /*         
                                                                         
    */

    ifstream input_file;
    string name;

    cout << "Give a wishlist name: ";
    cin >> name;
    input_file.open(name);

    input_file >> budget;
    char c;
    input_file.get(c);
    while(input_file)
    {
        string temp;
        getline(input_file, temp);
        if (input_file)
        {
            wishlist.push_back(temp);
        }
    }
}

int in_giftstore(Gift present)
{
    assert(true);
    /*         
                                                                
                                                             
    */

    for(int i = 0; i < size(giftstore); i++)
    {
        if(present == giftstore[i].name)
        {
            return giftstore[i].price;
        }
    }
    return -1;
}

void gifts (vector<Gift>& best, vector<Gift>& attempt, vector<Gift>& wishlist, int c, int budget, int& best_budget)
{
    assert(c >= 0);
    /*         
                                                                                                             
    */
    if (budget == 0)
    {
        best = attempt;
        best_budget = 0;
        return;
    }
    else if (budget < 0)
    {
        return;
    }
    else if (c >= size(wishlist))
    {
        if(budget < best_budget)
        {
            best = attempt;
            best_budget = budget;
        }
        return;
    }

    else
    {
        int value = in_giftstore(wishlist[c]);
        if(value >= 0)
        {
            attempt.push_back (wishlist[c]);
            gifts(best, attempt, wishlist, c + 1, budget - value, best_budget);
            attempt.pop_back ();
        }
        gifts(best, attempt, wishlist, c + 1, budget, best_budget);
    }

}

int main()
{
    vector<Gift> wishlist;
    vector<Gift> attempt;
    vector<Gift> best;
    int budget;

    read_giftstore();
    read_wishlist(wishlist, budget);
    int best_budget = budget + 1;
    gifts(best, attempt, wishlist, 0, budget, best_budget);
    show(best);
}

