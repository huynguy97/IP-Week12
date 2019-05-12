/*
                      
                       
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <string>

using namespace std;

struct Gift {
    int price;
    string name;
};

vector<Gift> giftstore;

struct Wishlist {
    vector<Gift> gifts;
    int budget;
};

ostream &operator<<(ostream &stream, Wishlist &list) {
    //             
    assert(true);
    //              
    //                                                             

    stream << "The gifts on this list are:" << endl;
    for (int i = 0; i < list.gifts.size(); i++) {
        Gift gift = list.gifts[i];
        stream << '\t' << gift.name << ", " << gift.price << endl;
    }
    stream << "The size of this list is: " << list.gifts.size() << endl;
    stream << "The budget of this list is: " << list.budget << endl;
    return stream;
}

istream &operator>>(istream &stream, Wishlist &list) {
    //             
    assert(true);
    //              
    //                                                                                                   

    stream >> list.budget;

    while (stream) {
        Gift gift;
        gift.price = 0;
        string name;
        getline(stream, name);
        gift.name = name;
        if (!name.empty()) {
            list.gifts.push_back(gift);
        }
    }

    return stream;
}

int gifts(Wishlist list, int totalprice, int gift, Wishlist &target) {
    //             
    assert(totalprice >= 0 && gift >= 0);
    //              
    //                                                                                                                  
    //                       

    if (list.gifts.empty()) {
        //                             
        target.gifts = {};
        return totalprice;
    } else if (gift >= list.gifts.size()) {
        //    
        return totalprice;
    } else if (totalprice < list.budget) {
        //                                 
        if (list.gifts[gift].price <= list.budget - totalprice) {
            //                                
            target.gifts.push_back(list.gifts[gift]);
            return gifts(list, totalprice + list.gifts[gift].price, gift + 1, target);
        } else {
            //                                             
            return gifts(list, totalprice, gift + 1, target);
        }
    } else if (totalprice == list.budget) {
        //    
        return totalprice;
    }
    //            
    return totalprice;
}

void getGiftPrices(Wishlist &list) {
    //             
    assert(true);
    //              
    //                                                                                                             
    //                                                                                                        
    //                                                                  

    Wishlist listt = {{}, list.budget};
    for (int i = 0; i < list.gifts.size(); i++) {
        Gift gift = list.gifts[i];
        for (int j = 0; j < giftstore.size(); j++) {
            Gift giftstoregift = giftstore[j];
            if (gift.name == giftstoregift.name) {
                //                              
                listt.gifts.push_back(giftstoregift);
            }
        }
    }
    list = listt;
}

int main() {
    cout << "Enter the filepath of the giftstore" << endl;
    string toystorepath;
    while (!(cin >> toystorepath)) {
        cout << "Enter the filepath of the giftstore:" << endl;
        cin.clear();
        cin.ignore('\n', 999);
    }
    ifstream giftstorefile = ifstream(toystorepath);
    while (giftstorefile) {
        Gift gift;
        giftstorefile >> gift.price;
        //                            
        giftstorefile.seekg(1, ios_base::cur);
        string name;
        getline(giftstorefile, name);
        gift.name = name;
        if (!name.empty()) {
            giftstore.push_back(gift);
        }
    }
    for (Gift g : giftstore) {
        cout << g.price << ", " << g.name << endl;
    }
    cout << "Enter the filepath of the wishlist to read:" << endl;
    string path;
    while (!(cin >> path)) {
        cout << "Enter the filepath of the wishlist to read:" << endl;
        cin.clear();
        cin.ignore('\n', 999);
    }
    ifstream file = ifstream(path);
    Wishlist list = {{}, 0};
    if (file.is_open()) {
        file >> list;
        getGiftPrices(list);
        cout << list;

        Wishlist solution = {{}, list.budget};
        int price = gifts(list, 0, 0, solution);
        cout << solution;
        cout << "The total price of the solution is: " << price;
    } else {
        cout << "Something went wrong while trying to open that file!";
    }
    return 0;
}

/*
                

               
                          
                           
                                        
                                         
                                                          
                                                  
                                                    
                                                  
                               
                                               
                                                     
                           
                                     
                                        
                                                                       
                                                                          
                                                                                   
                            
                                 
                                         

                
                          
                           
                                         
                                         
                                                 
                                    
                                
                                 
                           
                                
                                        

              
                          
                           
                     
                        
                        
                           
                                
                                        

              
                          
                           
                                     
                                                     
                                        
                           
                                
                                        

                 
                          
                           
                                      
                                     
                                        
                                           
                           
                                 
                                         
*/
