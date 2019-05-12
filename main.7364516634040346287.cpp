#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <fstream>
#include <assert.h>

//                           
//                     

using namespace std;

struct Store
{
    int price;
    string giftname;
};
vector<Store> giftstore;
vector<string> Wishlist;

istream& operator>> (istream& in, Store& store)
{
    in >> store.price;
    in.ignore();
    getline(in, store.giftname);
    return in;
}
ostream& operator<< (ostream& out, Store& store)
{
    out << store.giftname << " has prize " << store.price << "." << endl;
    return out;
}

void read_giftstore(vector<Store>& giftstore, ifstream& infile)
{
assert(infile.is_open());

    Store store;
    while(infile){
        infile >> store;
        giftstore.push_back(store);
    }
}

int read_wishlist(vector<string>& Wishlist, ifstream& infile1)
{
assert(infile.is_open());

    int Budget = 0;
    int x;
    infile1 >> x;
    Budget = Budget + x;
    infile1.ignore(1);

    cout << "This persons wishlist contains the following items:" << endl;

    string product;
    while(infile1){
        getline(infile1, product);
        Wishlist.push_back(product);
        cout << ">" << product << endl;
    }

    return Budget;
}

void wishlist_copy(vector<string>& Wishlist, vector<Store>& giftlist, vector<Store>& giftstore){
assert(true);

    for(int i = 0; i < Wishlist.size(); i++){
        for(int j = 0; j < giftstore.size(); j++ ){
        if(Wishlist[i] == giftstore[j].giftname){
        giftlist.push_back(giftstore[j]);
        }
        }
    }
}

int gifts(vector<string>& Wishlist, vector<Store>& giftstore, int c, int budget, vector<Store>& giftlist)
{
assert(c>=0);
    wishlist_copy(Wishlist, giftlist, giftstore);

    if(budget == 0){
        return 1;
    }
    else if(budget < 0){
        return 0;
    }
    else if(c >= Wishlist.size()){
        return 0;
    }

    else{
        int with_c = gifts(Wishlist, giftstore, c+1, budget-giftlist[c].price, giftlist) ;
        int without_c = gifts(Wishlist, giftstore, c+1, budget, giftlist);
        return with_c + without_c;

}
}

int main()
{
    ifstream infile;
    infile.open("giftstore.txt");
    if(infile.is_open()){
        cout << "File opened succesfully!" << endl;
    }
    else {
        cout << "Failed to open file...";
    }
    read_giftstore(giftstore, infile);

    for(int i = 0; i < giftstore.size(); i++ ){
        cout << giftstore[i] << endl;
    }

    ifstream infile1;
    string person;
    cout << "Please enter a name of the person you want to see their wishlist of:" << endl;
    cin >> person;
    string filename = person + ".txt";
    infile1.open(filename);
    if(infile1.is_open()){
        cout << "File opened succesfully!" << '\n' << endl;
    }
    else {
        cout << "Failed to open file...";
    }
    int budget = read_wishlist(Wishlist, infile1);
    cout << person << " has a budget of " << budget << endl;

    vector<Store> giftlist;

    gifts(Wishlist, giftstore, 0, budget, giftlist);

    infile.close();
    infile1.close();
    return 0;
}

