#include<cstdlib>
#include<iostream>
#include<vector>
#include<cassert>
#include<fstream>
#include<string>

//                                              

using namespace std;

struct item_store
{
    double price;
    string name;
};

struct item_wishlist
{
    double budget;
    vector <string> name;
};

typedef item_wishlist presents;
typedef vector <item_store> giftstore;

istream& operator>>(ifstream& in, item_store& present)
{
    in >> present.price;
    in.get();
    getline(in, present.name);
    return in;
}

void read_giftstore (ifstream& infile, giftstore& store)
{
    infile.open("giftstore.txt");
    item_store a;
    infile >> a;
    store.push_back(a);
    while (infile)
    {
        infile >> a;
        store.push_back(a);
    }
    infile.close();

}

void read_wishlist (ifstream& infile, item_wishlist& wish)
{
    infile.open("Andrew.txt");
    infile >> wish.budget;
    infile.get();
    string a;
    while (infile)
    {
        getline(infile, a);
        wish.name.push_back(a);
    }
    infile.close();
}

int size (vector<item_store>& v)
{
    return static_cast<int> (v.size());
}

int size_wishlist (vector<string>& v)
{
    return static_cast<int> (v.size());
}

int in_giftstore (item_wishlist& items, giftstore& gstore, int c)
{
    for (int i = 0; i <= size(gstore); i++)
    {
        if (gstore[i].name == items.name[c])
        {
            return i;
        }
    }
    return -1;
}

void copy_vector (presents& best, presents& attempt)
{
    best.name.clear();
    best.budget = attempt.budget;
    for (int i = 0; i <= size_wishlist(attempt.name); i++)
    {
        best.name.push_back(attempt.name[i]);
    }
}

void gifts (giftstore& store, item_wishlist& wish, presents& attempt, presents& best, int c)
{
    if (attempt.budget < 0)
        return;
    else if (c == size_wishlist(wish.name))
        return;
    else if (attempt.budget == 0)
        return;
    else
    {
        if (attempt.budget < best.budget)
              copy_vector(best, attempt);
        if (in_giftstore(wish, store, c)!= -1)
        {
            attempt.name.push_back(wish.name[c]);
            attempt.budget -= store[in_giftstore(wish, store, c)].price;
            gifts(store, wish, attempt, best, c+1);
            attempt.name.pop_back();
            attempt.budget += store[in_giftstore(wish, store, c)].price;
        }
        gifts(store, wish, attempt, best, c+1);
    }

}

int main()
{
    ifstream infile;
    giftstore store;
    presents best;
    presents attempt;
    item_wishlist wl;

    read_giftstore(infile, store);
    read_wishlist(infile, wl);

    attempt.budget = wl.budget;
    best.budget = wl.budget;

    gifts(store, wl, attempt, best, 0);
    cout << "Budget: " << wl.budget << endl;
    cout <<"Money spent: "<< wl.budget-best.budget << endl;
    return 0;
}

