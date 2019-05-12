#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

/*
                            
                       
*/

typedef string gift;

struct store_item {
    int price;
    gift name;
};

int get_price(gift g, vector<store_item> giftstore)
{
    //              
    assert(true);
    //               
    //                                        
    //                                                      
    for (int i = 0; i < giftstore.size(); i++)
        if (g == giftstore[i].name)
            return giftstore[i].price;
    return -1;
}

int get_prices(vector<gift> gs, vector<store_item> giftstore)
{
    //              
    assert(true);
    //               
    //                                       
    //                              
    int total = 0;
    for (int i = 0; i < gs.size(); i++)
        total += get_price(gs[i], giftstore);
    return total;
}

vector<gift> gifts(vector<gift> wishlist, vector<store_item> giftstore, int budget, int pos) {
    //              
    assert(pos >= 0 && pos <= wishlist.size());
    //               
    //                                                              
    //                                   
    vector<gift> best = {};
    for (int i = pos; i < wishlist.size(); i++)
    {
        int price = get_price(wishlist[i], giftstore);
        if (price != -1 && (budget - price) >= 0)
        {
            vector<gift> combination = gifts(wishlist, giftstore, budget-price, i+1);
            combination.push_back(wishlist[i]);
            if (get_prices(best, giftstore) < get_prices(combination, giftstore))
                best = combination;
        }
    }
    return best;
}

void read_store(string name, vector<store_item>& store) {
    //              
    assert(true);
    //               
    //                                                     
    //                                       
    ifstream f;
    f.open(name);
    while(f) {
        store_item item;
        f >> item.price;
        f.get();
        getline(f, item.name);
        if(f)
            store.push_back(item);
    }
    f.close();
}

void read_wishlist(string name, vector<gift>& wishlist, int& budget) {
    //              
    assert(true);
    //               
    //                                                        
    //                
    ifstream f;
    f.open(name);
    f >> budget;
    string useless;
    getline(f, useless);
    while(f){
        gift wish;
        getline(f, wish);
        if(f)
            wishlist.push_back(wish);
    }
    f.close();
}

ostream& operator<< (ostream& out, const vector<gift>& v){
    //                                              
    for (int i = 0; i < v.size(); i++)
        out << v[i] << endl;
    return out;
}

int main()
{
    vector<store_item> store;
    vector<gift> Andrew;
    int budget;
    read_store("giftstore.txt", store);
    read_wishlist("Andrew.txt", Andrew, budget);
    cout << "Andrew:" << endl << gifts(Andrew, store, budget, 0) << endl << endl;
    vector<gift> Belle;
    read_wishlist("Belle.txt", Belle, budget);
    cout << "Belle:" << endl << gifts(Belle, store, budget, 0) << endl << endl;
    vector<gift> Chris;
    read_wishlist("Chris.txt", Chris, budget);
    cout << "Chris:" << endl << gifts(Chris, store, budget, 0) << endl << endl;
    vector<gift> Desiree;
    read_wishlist("Desiree.txt", Desiree, budget);
    cout << "Desiree:" << endl << gifts(Desiree, store, budget, 0) << endl << endl;
    vector<gift> Edward;
    read_wishlist("Edward.txt", Edward, budget);
    cout << "Edward:" << endl << gifts(Edward, store, budget, 0) << endl << endl;
    vector<gift> Fabienne;
    read_wishlist("Fabienne.txt", Fabienne, budget);
    cout << "Fabienne:" << endl << gifts(Fabienne, store, budget, 0) << endl << endl;
    return 0;
}

/*
       
                          
                        

      
                        
              
           

      
          
                      
                        

        
                  
               
                   
                  

       
                                                             
                                                          
             
                          
                                       
                                    

         
              
                             
                          
                       
*/

