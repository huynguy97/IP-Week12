#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

struct gift
{
    int price;
    string name;
};

struct wishlist
{
    int budget;
    vector<string> items;
};

vector<gift> gift_store;
wishlist list;
vector<string> list_of_gifts;

void read_giftstore (ifstream& input)
{//               
    assert (true);
  //               
  //                                         
    int price;
    string name;
    while (input)
    {
        input >> price;
        getline (input, name);
        gift gifts = {price, name};
        gift_store.push_back(gifts);
    }
    for (int i=0; i<gift_store.size(); i++)
    {
        if (gift_store[i].name[0] == 32)
            gift_store[i].name.erase(0, 1);
    }
}

void read_wishlist(ifstream& input)
{ //              
    assert (true);
  //               
  //                                      
    int budget;
    string gift;
    vector<string> gift_list;

    input >> budget;
    list.budget = budget;
    while (input)
    {
        getline (input, gift);
        list.items.push_back(gift);
    }
}

bool in_store (string store, string wishlist)
{ //              
    assert(true);
  //               
  //                                                         
    bool present = false;
    for (int i=0; i<store.length(); i++)
    {
        if (store[i] == wishlist[i] && i < store.length() && i < wishlist.length())
            present = true;
        else
            present = false;
    }
    return present;
}

int gifts (vector<gift>& giften, wishlist a, vector<string>& b, int budget, int i, int j)
{ //              
    assert(true);
  //               
  //                                         
    if (in_store(giften[i].name, a.items[j]) && i < giften.size() && j < a.items.size())
    {
        if (i<giften.size())
        {
            if (giften[i].price < budget)
            {
                budget = budget - giften[i].price;
                b.push_back(giften[i].name);
                return gifts(giften, a, b, budget, 0, j+1);
            }
        }
        else
            return gifts(giften, a, b, budget, 0, j+1);
    }
    else if (i >= giften.size())
        return gifts(giften, a, b, budget, i+1, j);
    else
        return budget;
}

int main()
{
    cout << "Input a filename for the giftstore:" << endl;
    string input_file;
    cin >> input_file;
    ifstream input_giftstore(input_file);
    read_giftstore(input_giftstore);
    cout << gift_store.size() << endl;

    cout << "Input a filename for the wishlist:" << endl;
    string wishlist;
    cin >> wishlist;
    ifstream input_wishlist(wishlist);
    read_wishlist(input_wishlist);
    cout << list.items.size() << endl;
    cout << list.budget << endl;

    gifts(gift_store, list, list_of_gifts, list.budget, 0, 0);
    for (int i=0; i<list_of_gifts.size(); i++)
    {
        cout << list_of_gifts[i] << endl;
    }

    return 0;
}
