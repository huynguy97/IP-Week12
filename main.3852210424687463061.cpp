#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
using namespace std;

//                         
//                              

struct Gift {
    int price;
    string name;
};

ifstream& operator>> (ifstream& infile,Gift gift) {
    infile >> gift.price;
    getline(infile, gift.name);
    return infile;
}

bool read_giftstore(vector<Gift>& giftlist, string filename)
{
    Gift gift;
    ifstream infile;
    infile.open(filename.c_str());
    if (infile.good())
    {
        while(infile)
        {
            infile >> gift;
            giftlist.push_back(gift);
        }
    }
    infile.close();
}

bool read_wishlist(vector<Gift>& wishlist, string filename, int& budget)
{
    ifstream infile;
    infile.open(filename.c_str());
    if (infile.good())
    {
        infile >> budget;ifstream infile;
    infile.open(filename.c_str());
    if (infile.good())
    {
        string present;
        while(infile){
            infile >> present;
            wishlist.push_back(present);
        }
    }
}

int gifts(vector<Gift>& gift, int id, int budget, vector<Gift>& attempt, vector<Gift>& best_attempt)
{
    if (gift.size() <= id) {
        best_attempt = attempt;
    }
    else {

    }
}

int main()
{

}

