#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <string>
#include <cstdlib>
#include <assert.h>

using namespace std;

//                        
//                    
//                      

void gifts(vector<int>& wish_list, int used_budget, int index, int& budget, int& best){
    //              
    assert(used_budget >= 0 && index >= 0 && budget >= 0);
    //               
    //                                                                               
    //                                            

    //                                                                                          
    if (budget == best){
        return;
    }
    //                                                    
    else if(used_budget > budget){
        return;
    }
    //                                                                         
    else if (used_budget == budget){
        best = used_budget;
        return;
    }
    //                                 
    else if(index == wish_list.size()){
        return;
    }
    //                   
    else{
        //                       
        if (used_budget > best){
            best = used_budget;
        }

        //                                                                  
        gifts(wish_list, used_budget + wish_list[index], index + 1, budget, best);
        gifts(wish_list, used_budget, index + 1, budget, best);
        //                  
    }
}

struct Gifts{
    string product_name;
    int product_price;
};

vector<Gifts> read_giftstore(){
    //              
    assert(true); //                   
    //               
    //                                                                                              
    fstream file;
    file.open("giftstore.txt");

    vector<Gifts> gift_items;
    string line;
    while(file){
        //                                                    
        int price;
        file >> price;
        //                                     
        getline(file, line);
        //                                                         
        string name = line.substr(1, line.size());

        //                                           
        Gifts gift;
        gift.product_price = price;
        gift.product_name = name;
        gift_items.push_back(gift);
    }

    file.close();
    return gift_items;
}

int get_price(vector<Gifts>& gift_items, string item){
    //              
    assert(true);
    //               
    //                                                     
    for(int i = 0; i < gift_items.size(); i++){
        if(gift_items[i].product_name == item){
            return gift_items[i].product_price;
        }
    }
    cout << item << " cannot be found in the giftstore database." << endl;
    return 0;
}

vector<int> read_wishlist(string fname, vector<Gifts>& gift_items, int& budget){
    //              
    assert(true);
    //               
    //                                                                                                                
    fstream file;
    file.open(fname);

    //                                    
    file >> budget;
    file.ignore();

    //                                                                                       
    vector<int> wish_list;
    string line;
    while(file){
        getline(file, line);
        if (line.size() > 0){
            //                                         
            int price = get_price(gift_items, line);
            wish_list.push_back(price);
        }
    }

    file.close();
    return wish_list;
}

int main()
{
    string wish_list_fname = "Fabienne.txt";
    vector<Gifts> gift_items = read_giftstore();

    //                                       
    int budget;
    vector<int> wish_list = read_wishlist(wish_list_fname, gift_items, budget);
    int best = 0;

    //                                                                        
    gifts(wish_list, 0, 0, budget, best);
    cout << "The most that can be spent without going over the budget is " << best << endl;

    /*                                     
                                         
                                         
                                         
                                         
                                          
                                          
                                          */

    return 0;
}

