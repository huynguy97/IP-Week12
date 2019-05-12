#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <cassert>

using namespace std;

//                        
//                      

struct gift{
    string name;
    int price;
};

vector<gift> maximalPrice(vector<gift> a, vector<gift> b){
//     
    assert(true);
//                                                                       

    int priceA=0;
    int priceB=0;

    for(int i=0;i<a.size();i++){
        priceA += a[i].price;
    }
    for(int i=0;i<b.size();i++){
        priceB += b[i].price;
    }

    if(priceA>priceB){return a;}
    return b;
}

vector<gift> gifts(vector<gift> wishlist, vector<gift> bought, int budget){
//     
    assert(true);
//                                                           

    if(wishlist.empty() || budget<0){return bought;}

    gift nextGift = wishlist.back();
    wishlist.pop_back();

    vector<gift> without_g = gifts(wishlist,bought,budget);
    bought.push_back(nextGift);
    budget -= nextGift.price;
    vector<gift> with_g = gifts(wishlist,bought,budget);

    return maximalPrice(with_g,without_g);
}

void readGiftstore(vector<gift>& gifts){
//     
    assert(true);
//                                                            

    ifstream input("giftstore.txt");

    while(input){
        int price;
        input >> price;

        char emp;
        input.get(emp); //            

        string name;
        getline(input, name);
        gift g {name, price};
        gifts.push_back(g);
    }
    input.close();
}

int readWishlist(vector<gift>& wishlist, vector<gift>& store, string infile){
//     
    assert(true);
//                                                                                                                                                    

    ifstream input(infile);
    string name;
    int budget;
    input >> budget;

    while(input){
        getline(input, name);
        gift g {name, 0};

        for(int i=0;i<store.size();i++){
            if(g.name==store[i].name){
                g.price = store[i].price;
                wishlist.push_back(g);
            }
        }
    }
    input.close();
    return budget;
}

int main()
{
    vector<gift> store;
    readGiftstore(store);

    cout << "Enter the name of the person's wishlist: ";
    string infile;
    cin >> infile;

    vector<gift> wishlist;
    int budget = readWishlist(wishlist, store, infile);

    vector<gift> bought;
    bought = gifts(wishlist, bought, budget);

    for(int i = 0; i<bought.size();i++){
        cout << bought[i].name << endl;
    }

    return 0;
}

/*
                                   
                                 

                                
                          
                       

                  
                              
                                

                                    
                         
                             

                                                                      
                                                                   
                                   
                      
                            
                                          
                         

                         
                                        
                                     
                                  
*/

