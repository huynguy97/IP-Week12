
/*
                              
                          
                            
 */

#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>

using namespace std;

struct Item {
    string name;
    int price;
};

vector<Item> giftStore;

void readGiftStore(ifstream &infile) {
    //               
    assert(infile.is_open());
    //                
    //                                                                                                                            

    int c;
    while ((c = infile.get()) != EOF) { //                                        
        string priceText, name;

        //                                                        
        do {
            priceText += (char) c;
        } while ((c = infile.get()) != ' ');
        int price = stoi(priceText);

        //                                                                 
        while ((c = infile.get()) != '\n') {
            name += (char) c;
        }
        giftStore.push_back({name, price});
    }
}

vector<string> readWishlist(ifstream &infile, int &budget) {
    //               
    assert(infile.is_open());
    //                
    //                                                         
    //                                                                            

    string line;
    getline(infile, line);
    budget = stoi(line);

    vector<string> list;
    while (getline(infile, line)) {
        list.push_back(line);
    }
    return list;
}

vector<Item> gifts(vector<string> wishlist, int& budget) {
    //               
    assert(budget >= 0);
    //                
    //                                                                       
    //                                                              
    //                                                                 

    vector<Item> out;
    int best = budget;

    auto end = wishlist.end();
    for (auto it = wishlist.begin(); it != end; ++it) {
        string name = *it;

        //                                                 
        int price = -1;
        for (auto it2 = giftStore.begin(); price == -1 && it2 != giftStore.end(); ++it2) {
            if (it2->name == name) {
                price = it2->price;
            }
        }

        if (price != -1) {
            int remaining = budget - price; //                                             
            if (remaining >= 0) {
                //                                                       
                //                                                        
                //                                                                        
                //                                                       
                vector<string> sublist(it + 1, end);

                vector<Item> result = gifts(sublist, remaining);

                if (remaining < best) { //                                         
                    result.push_back({ name, price }); //                                  
                    out = result;
                    best = remaining;
                }
            }
        }
    }

    budget = best;

    return out;
}

string priceToString(int cents) {
    //               
    assert(cents >= 0);
    //                
    //                                                                               

    return "€" + to_string(cents / 100) + ((cents % 100) < 10 ? ".0" : ".") + to_string(cents % 100);
}

int main() {
    ifstream infile;
    infile.open("giftstore.txt");
    readGiftStore(infile);

    cout << "Please specify your wishlist: " << endl;

    string input;
    getline(cin, input);

    ifstream listFile;
    listFile.open(input);

    int budget;
    vector<string> wishlist = readWishlist(listFile, budget);

    cout << "Wishlist (" << wishlist.size() << "): ";

    bool first = true;
    for (string &wish : wishlist) {
        if (first)
            first = false;
        else
            cout << ", "; //                                           

        cout << wish;
    }
    cout << endl << "Total budget: " << priceToString(budget) << endl;

    vector<Item> items = gifts(wishlist, budget);

    cout << "Items to give: " << endl;
    for (Item &item : items) {
        cout << item.name << ": " << priceToString(item.price) << endl;
    }

    cout << "Remaining of budget: " << priceToString(budget) << endl;

    return 0;
}

/*

                                               

          
                                                                                                                                                                                                                                                                                                                                                                                                                       
                      
              
                                    
                                 
                            

         
                                                                                                                                                       
                      
              
                                 
                       
                    
                            

         
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
                      
              
                   
                                
                                 
                            

           
                                                                                                                                                                                                                                                                                                                                                                                                                 
                      
              
                            
                         
                             
                            
                            

          
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
                       
              
                                                                      
                                                                   
                        
                                    
                                                 
                                              
                            

            
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
                       
              
                        
                                       
                                    
                                  
                            
  
 */

