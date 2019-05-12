#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

//                                                        
//                                                  

using namespace std;

struct product
{
    int price;
    string gift;
};

void show_store (product istore)
{
    //                                                      
    cout<<istore.price<<" "<<istore.gift<<endl;
}

istream& operator>>(istream& in, product& istore)
{
    in>> istore.price;
    in.ignore();
    getline(in,istore.gift);
    return in;
}

int sum (vector<product>& wishlist_with_price, int from)
{
    //              
//                
//                                                                                                            
    int sum = 0 ;
    for (int i=from; i<wishlist_with_price.size(); i++)
        sum += wishlist_with_price[i].price;
    return sum ;
}

int sum (vector<product>& wishlist_with_price)
{
    return sum(wishlist_with_price,0);
}

void improve (vector<product>& current, vector<product>& best)
{
//              
    assert (true) ;
//               
//                                                                
    if (sum (current) > sum (best))
        best = current ;
}

void get_price_wishlist (vector<string>&  wish_list, vector<product>& gift_store, vector<product>& wishlist_with_price)
{
    //             
    assert(wish_list.size()>0 && gift_store.size()>0 && wishlist_with_price.size()==0);
    //                                                                                                                             

    product p;
    for(int i=0; i<wish_list.size()-1 ; i++)
    {
        p.gift = wish_list[i];
        for(int j=0; j<gift_store.size(); j++)
            if(wish_list[i]==gift_store[j].gift)
            {
                p.price=gift_store[j].price;
                wishlist_with_price.push_back(p);
            }
    }
}

int gifts (vector<product>& attempt,vector<product>& best,vector<product>& wishlist_with_price, int c, int budget)
{
    //              
    assert(wishlist_with_price.size()>0 && c>=0 && c<=wishlist_with_price.size());
    //                                                                                                                                 
    if(budget == 0)
    {
        best=attempt;
        return 1 ;
    }
    else if(budget  < 0)
        return 0 ;
    else if(c >=wishlist_with_price.size())
    {
        improve(attempt, best);
        return 0 ;
    }
    else if(sum(attempt) + sum(wishlist_with_price,c) <= sum(best))
    {
        return 0 ;
    }
    else
    {
        attempt.push_back(wishlist_with_price[c]) ;
        int with_c=gifts(attempt,best,wishlist_with_price,c+1,budget-wishlist_with_price[c].price) ;
        attempt.pop_back() ;
        int without_c=gifts(attempt,best,wishlist_with_price,c+1,budget) ;
        return with_c+without_c;
    }
}

int main()
{
    vector<product> gift_store, wishlist_with_price;
    product istore;
    ifstream infile("giftstore.txt");
    while (infile)
    {
        infile>>istore;
        gift_store.push_back(istore);
    }
    int buget;
    vector<string> wish_list;
    string gift_name;
    string name_kid;
    cout<<"Enter the name of the kid:"<<endl;
    cin>> name_kid;
    name_kid+=".txt";
    ifstream inputfile (name_kid.c_str());
    inputfile>>buget;
    inputfile.ignore();
    while(inputfile)
    {
        getline(inputfile,gift_name);
        wish_list.push_back(gift_name);
    }
    get_price_wishlist(wish_list,gift_store,wishlist_with_price);
    vector<product> attempt,best;
    int x=gifts(attempt,best,wishlist_with_price,0,buget);

    for(int i=0; i<best.size(); i++)
        show_store(best[i]);
    return 0;
}

