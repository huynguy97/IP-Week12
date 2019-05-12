//                      
//                     

#define NDEBUG
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cmath>

using namespace std;

struct Wishlist{
    string gift;
    int price;
};

vector<Wishlist> gift;

int size(vector<Wishlist>& gift){
    return static_cast<int> (gift.size());
}

int sum (vector<Wishlist>& gift, int i, int s){
    if (i < size (gift)){
        i++;
        s += gift[i].price;
        return sum (gift, i, s);
    }
    return s;
}

void improve (vector<Wishlist>& current, vector<Wishlist>& best)
{
    if (sum(current, 0, 0) > sum(best, 0, 0)){
        current = best;
    }
}

bool select (Wishlist& gifts){
    for (int i = 0; i < size(gift); i++){
        if (gift[i].gift == gifts.gift){
            gifts.price = gift[i].price;
            return true;
        }
    }
    return false;
}

int solutions (vector<Wishlist>& current, vector<Wishlist>& best, vector<Wishlist>& m, int c, int budget){
    int with_c = 0;
    if (budget == 0){
        best = current;
        return 1;
    }
    else if (budget < 0){
        return 0;
    }
    else if (c >= size(m)){
        improve (current, best);
        return 0;
    }
    else{
        if (select (m[c])){
            current.push_back (m[c]);
            int with_c = solutions(current, best, m, c+1, budget - m[c].price);
            current.pop_back ();
        }
        int without_c = solutions(current, best, m, c+1, budget);
        return with_c + without_c;
    }
}

void read_giftstore (vector<Wishlist>& giftstore){
    Wishlist gift;
    ifstream infile ("giftstore.txt");
    infile >> gift.price;
    infile.ignore (1);
    getline (infile, gift.gift);
    while (infile) {
        giftstore.push_back (gift);
        infile >> gift.price;
        infile.ignore(1);
        getline (infile, gift.gift);
    }
}

void read_wishlist (vector<Wishlist>& wishlist, string filename, int budget){
    ifstream infile (filename);
    infile >> budget;
    Wishlist gift;
    gift.price = 0;
    infile.ignore (1);
    getline (infile, gift.gift);
    while (infile){
        wishlist.push_back(gift);
    }
}

void show_all_gifts (vector<Wishlist>& gift)
{
    for (int i = 0; i < size(gift); i++)
        cout << gift[i].gift << endl;
}

int main (){
    read_giftstore (gift);
    vector<Wishlist> wishlist;
    int budget = 0;
    read_wishlist (wishlist, "Belle.txt", budget);
    show_all_gifts (wishlist);
    return 0;
}

