#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

//                                                                                       

using namespace std;

struct Gift
{
    int price;
    string name;
};

vector<Gift> giftlist;
vector<string> wishlist;

istream& operator>> (istream& in, Gift& gift)
{
    in  >> gift.price;
    in.get();
    getline(in, gift.name);

    return in;
}

ostream& operator<< (ostream& out, const Gift gift)
{
    out << gift.price;
    out << gift.name;

    return out;
}

void open_store(ifstream& inputfile, vector<Gift>& gifts)
{
    //                
    assert(inputfile.is_open());

    //                
    //                                                
    while (inputfile)
    {
        Gift gift;
        inputfile >> gift;
        gifts.push_back(gift);
    }
}

int open_wishlist(ifstream& inputfile, vector<string>& wishlist)
{
    //               
    assert(inputfile.is_open());

    //                
    //                                                      
    int money;
    inputfile >> money;
    while (inputfile)
    {
        string wish;
        getline(inputfile, wish);
        wishlist.push_back(wish);
    }
    return money;
}

int gifts(vector<Gift>& attempt, vector<Gift>& best, Gift& giftlist, int& money, int& c, int& target)
{
    //               
    assert(target >= 0 && money >= 0);

    //                
    //                                                                                 

    if (c >= giftlist.size()) //                          
    {
        attempt = best;
        return budget;
    }
    else
    {
        attempt[c] = giftlist[c];
        //                                                         
        //                                                                  
        //                                                                                                

        cout << "Sorry" << endl;
        //              
        //                                 
        //                                            
        //                                        
        //                                
        //                                     
    }
}

int main()
{
    //                    
    string filename;
    ifstream inputfile;
    ifstream giftstore;
    int money;

    //         
    giftstore.open("giftstore.txt");
    cout << "Enter wishlist: ";
    getline (cin, filename);
    inputfile.open(filename);
    open_store(giftstore, giftlist);
    money = open_wishlist(inputfile, wishlist);

    return 0;
}

