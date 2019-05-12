//                                              
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include<fstream>

using namespace std;
typedef string Gift;
typedef string Wish;

struct product
{
    int price;
    string gift;
};

vector<product> giftstore;

istream& operator>>(istream&in,product&item)
{
    string str;
    in >> item.price;
    in.ignore();
    getline(in, str);
    item.gift=str;
}

int size (vector<Wish>& wish_list)
{//               
    assert (true) ;
//                                                            
    return static_cast<int> (wish_list.size()) ;
}

int gifts (vector<Wish>& current, vector<Wish>& wish_list, vector<Wish>& best, vector<int>& gift_price, int budget, int c)
{
    //              
    assert(c <= size(wish_list) && c >= 0);
    //                
    //                                     
    if	    ( budget == 0 )		        { return 1; }
	else if ( budget < 0 )		        { return 0; }
	else if ( c >= size(wish_list) )	{ return 0; }
    else
        {
            current.push_back ( wish_list[c] ) ;
            const int WITH_C    = gifts ( current, best, wish_list, gift_price, c+1, budget - gift_price[c] ) ;
            current.pop_back () ;
            const int WITHOUT_C = gifts ( current, best, wish_list, gift_price, c+1, budget ) ;
            return budget ;
        }
}

int main()
{
    vector<Wish> wishlist;
    string item, gift;
    int budget, price;
    string filename, storename;
    cout << "Enter wishlist: ";
    getline(cin,filename);
    ifstream infile(filename.c_str());
    if (!infile.is_open())
    {
        cout << "can't open this file!" << endl;
        return 0;
    }
    infile >> budget;
    while (getline(infile,item))
        wishlist.push_back(item);
    infile.close();
    cout << "Enter giftstore: ";
    getline(cin,storename);
    ifstream storefile(storename.c_str());
    if (!storefile.is_open())
    {
        cout << "can't open this file!" << endl;
        return 0;
    }
    /*                
                                           
                                              
                                      */
}

