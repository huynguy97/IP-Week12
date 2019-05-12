#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <string>

//                                              

using namespace std;

const string Giftstore = "giftstore.txt";                                                       //                      
vector<string> wishlist_names = {"Andrew", "Belle", "Chris", "Desiree", "Edward", "Fabienne"};  //                                 

struct Gift
{
    int price;      //                           
    string name;    //                 
    bool added;     //                 
};

/*
                                                                  
*/
ostream& operator<< (ostream& out, const Gift gift)
{
    assert(true);
    if (gift.price != NULL)
        out << gift.price << ' ' << gift.name;
    else
        out << gift.name;
    return out;
}

/*
                                         
*/
void print_giftstore(vector<Gift>& giftstore)
{
    assert(giftstore.size() >= 0);

    for (int i = 0; i < giftstore.size(); i++) {
        cout << giftstore[i] << endl;
    }
}

/*
                                                        
*/
bool open_giftstore(string filename, vector<Gift>& giftstore)
{
    assert(filename.size() >= 0 &&
           giftstore.size() >= 0);

    ifstream store(filename.c_str());
    if (!store) {
        cout << "Failed to open " << filename << '.' << endl;
        return false;
    }
    while (!store.eof()) {
        Gift gift;
        store >> gift.price;
        store.ignore();
        getline(store, gift.name);
        gift.added = false;
        if(gift.name != "")
            giftstore.push_back(gift);
    }
    return true;
}

/*
                                                                    
*/
bool open_wishlist(string filename, vector<Gift>& wishlist, int& budget)
{
    assert(filename.size() >= 0 &&
           wishlist.size() >= 0);

    ifstream presents(filename.c_str());
    if (!presents) {
        cout << "Failed to open " << filename << '.' << endl;
        return false;
    }
    presents >> budget;
    while (!presents.eof()) {
        Gift gift;
        gift.price = 0;
        getline(presents, gift.name);
        gift.added = false;
        if (gift.name != "")
            wishlist.push_back(gift);
    }
    return true;
}

/*
                                                     
*/
int wishlist_price(vector<Gift>& wishlist)
{
    assert(wishlist.size() >= 0);

    int sum = 0;
    for (int i = 0; i < wishlist.size(); i++) {
        if (wishlist[i].added)
            sum += wishlist[i].price;
    }
    return sum;
}

/*
                                                                            
                                     
*/
void in_store(vector<Gift>& wishlist, vector<Gift>& giftstore)
{
    assert(wishlist.size() >= 0 &&
           giftstore.size() >= 0);

    bool temp = false;
    for (int i = 0; i < wishlist.size(); i++) {
        for (int j = 0; j < giftstore.size(); j++) {
            if (wishlist[i].name == giftstore[j].name) {
                temp = true;
            }
        }
        if (!temp) {
            wishlist.erase(wishlist.begin()+i);
            i--;
        }
        temp = false;
    }
}

/*
                                                                                          
*/
vector<Gift> gifts(vector<Gift> wishlist, vector<Gift>& giftstore, int budget, int index)
{
    assert(wishlist.size() >= 0 &&
           giftstore.size() >= 0 &&
           index >= 0);

    vector<Gift> giftadd = wishlist;
    vector<Gift> giftnot = wishlist;
    if (index < wishlist.size()) {
        for (int j = 0; j < giftstore.size(); j++) {
            if (wishlist[index].name == giftstore[j].name) {
                giftadd[index].price = giftstore[j].price;
                giftnot[index].price = giftstore[j].price;
                giftnot = gifts(giftnot, giftstore, budget, index+1);
                giftadd[index].added = true;
                if (budget - wishlist_price(giftadd) >= 0) {
                    giftadd = gifts(giftadd, giftstore, budget, index+1);
                }
            }
        }
    }
    if (wishlist_price(giftadd) > wishlist_price(giftnot) && budget - wishlist_price(giftadd) >= 0)
        return giftadd;
    return giftnot;
}

/*
                                                                        
*/
void print_optimal_spending(vector<Gift>& wishlist, int budget, string name)
{
    assert(wishlist.size() >= 0);

    cout << endl << "The items " << name << " could buy were:" << endl;
    for (int i = 0; i < wishlist.size(); i++) {
        if (wishlist[i].added)
            cout << wishlist[i].name << endl;
    }
    cout << "Total price: " << wishlist_price(wishlist) << " with a budget of " << budget << endl;
}

/*
                                                                        
                                                 
*/
void optimize_all_wishlists(vector<Gift>&giftstore)
{
    assert(giftstore.size() >= 0);

    for (int i = 0; i < wishlist_names.size(); i++) {
        vector<Gift> wishlist;
        int budget = 0;
        open_wishlist(wishlist_names[i]+".txt", wishlist, budget);
        in_store(wishlist, giftstore);
        vector<Gift> buy = gifts(wishlist, giftstore, budget, 0);
        print_optimal_spending(buy, budget, wishlist_names[i]);
    }
}

/*
                                                                 
*/
void run_December_gifting()
{
    vector<Gift> giftstore;
    open_giftstore(Giftstore, giftstore);
    optimize_all_wishlists(giftstore);
}

int main()
{
    run_December_gifting();
    return 0;
}

/*
                                
                        
                          
                                       

                               
           
              
                        
                                       

                               
                           
                                    
          
                                       

                                 
                   
                        
                          
                  
                                       

                                
                
                                 
                   
             
                          
                                                             
                                                                      
                                         

                                  
                       
                          
                             
              
                                         
*/

