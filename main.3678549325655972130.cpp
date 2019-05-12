#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>

using namespace std;

struct Gift {
    int price;
    string name;
};

/*
                         
                  

                     
                  
*/

//                                                                                                

void read_gifts(ifstream &giftfile, vector<Gift>& gift_store) {
    //               
    assert(giftfile.is_open());
    //                
    //                                                              
    Gift gift;
    char s = ' ';
    while(giftfile) {
        giftfile >> gift.price;
        giftfile.get(s);
        getline(giftfile, gift.name);
        gift_store.push_back(gift);
    }
}

int read_wishlist(ifstream &wishfile, vector<string> &wish_list) {
    //               
    assert(wishfile.is_open());
    //                
    //                                                                                                       
    int budget = 0;
    string name = " ";
    wishfile >> budget;
    getline(wishfile, name);
    while(wishfile) {
        getline(wishfile,name);
        wish_list.push_back(name);
    }
    return budget;
}

string enter_wishlist() {
    //               
    assert(true);
    //                
    //                                                             
    string wishfile = " ";
    cout << "Please enter a wish list: ";
    getline(cin,wishfile);
    return wishfile;
}

vector<string> gifts (vector<string>& wish_list, vector<Gift>& gift_store, int i, int j, vector<string>& current_gifts, vector<string>& best_gifts,
                      int best_budget, int budget);

int get_price(vector<string>& wish_list, vector<Gift>& gift_store, int i) {
    //               
    assert(i >= 0 && i < wish_list.size());
    //              
    //                                                                   
    for(int j = 0; j < gift_store.size(); j++) if(wish_list[i] == gift_store[j].name) return gift_store[j].price;
}

/*                                                                                 
                                                                                      
                        
                     
                   
                      
                                                                                     
                                                
                     
                        
                                   
                          
     
                                          
                                   
                             
                                   
                          
     
          
                                                            
                                                  
                                                                                                    
                                     
         
                                                                                          
                          
 */

int find_gift(vector<string>& wish_list, vector<Gift>& gift_store, int n) {
    //               
    assert(n >= 0 && n < wish_list.size());
    //                
    //                                              
    int i = 0;
    while (wish_list[n] != gift_store[i].name) i++;
    return gift_store[i].price;
}

int recursive(vector<string>& wish_list, vector<Gift>& gift_store, int n, int budget, vector<string>& current_gifts, vector<string>& best_gifts){
    /*                                           */
    //               
    assert(n >= 0);
    //                
    //                                                    
    if (n > wish_list.size()-1) return budget;
    int price = find_gift(wish_list, gift_store, n);
    if ((budget - price) > 0) {
        current_gifts.push_back(wish_list[n]);
        int with_purchase = recursive(wish_list, gift_store, n+1, budget-price, current_gifts, best_gifts);
        current_gifts.pop_back();
        int without_purchase = recursive(wish_list, gift_store, n+1, budget, current_gifts, best_gifts);
        if (with_purchase < without_purchase) {
            best_gifts.push_back(wish_list[n]);
            return recursive(wish_list, gift_store, n+1, budget-price, current_gifts, best_gifts);
        }
    }
    return recursive(wish_list, gift_store, n+1, budget, current_gifts, best_gifts);
}

int main()
{
    ifstream giftfile("giftstore.txt");
    ifstream wishfile;
    vector<Gift> gift_store;
    vector<string> wish_list;
    vector<string> current_gifts;
    vector<string> best_gifts;
    read_gifts(giftfile,gift_store);
    string filename = enter_wishlist();
    wishfile.open(filename);
    int budget = read_wishlist(wishfile,wish_list);
    //                                                                     
    cout << recursive(wish_list, gift_store, 0, budget, current_gifts, best_gifts) << endl;
    //                                                                                             
    return 0;
}

