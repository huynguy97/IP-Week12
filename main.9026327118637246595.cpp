//                
//                          
//                          

#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

int MAX_PRICE_LENGTH = 20;
int MAX_NAME_LENGTH = 120;
int MAX_FILENAME_LENGTH = 40;

struct Item {
    string name;
    int price;
};

struct Wishlist {
    int budget;
    vector<Item> items;
};

template <typename T>
 size(vector<T> v) {
    return static_cast<int>(v.size());
}

bool load_giftstore(string path, vector<Item> &items) {
    //   
    assert(path.length() > 0);
    //    
    //                                                                                                                                               
    ifstream giftstore(path);
    if (!giftstore.is_open()) {
        cout << "Could not open file.\n";
        return false;
    }

    Item currentItem;
    char priceString[MAX_PRICE_LENGTH];
    char nameString[MAX_NAME_LENGTH];

    while (!giftstore.eof()) {

        giftstore.get(priceString, MAX_PRICE_LENGTH, ' ');
        giftstore.getline(nameString, MAX_NAME_LENGTH);

        currentItem.price = atoi(priceString);
        currentItem.name = string(nameString);

        items.push_back(currentItem);
    }
    items.pop_back(); //                                 
    return true;
}

int getPrice(string name, vector<Item> &items) {
    //   
    assert(name.length() > 0 && size(items) != 0);
    //    
    //                                                                                                                                                      
    int price = -1;
    if (name == "") {
        return -1;
    }
    for (Item i : items) {
        if (i.name.find(name) != string::npos) {
            price = i.price;
            break;
        }
    }
    return price;
}

bool load_wishlist(string path, Wishlist &wl, vector<Item> &items) {
    //   
    assert(path.length() > 0 && size(items) > 0);
    //    
    //                                                                                                                                                          
    ifstream wishlist(path);
    if (!wishlist.is_open()) {
        cout << "Could not open file.\n";
        return false;
    }

    char budgetString[MAX_PRICE_LENGTH];
    wishlist.getline(budgetString, 200);
    wl.budget = atoi(budgetString);

    char nameString[MAX_NAME_LENGTH];
    Item currentItem;
    while (!wishlist.eof()) {
        wishlist.getline(nameString, 200);
        currentItem.name = string(nameString);
        currentItem.price = getPrice(currentItem.name, items);
        if (currentItem.price != -1) {
            wl.items.push_back(currentItem);
        }
    }
    return true;
}

int sum(vector<Item> &giftlist, int from)
{
    //   
    assert(true);
    //    
    //                                                                                   
    int sum = 0;
    for (int i = from; i < size(giftlist); i++)
        sum += giftlist[i].price;
    return sum;
}

void improve(vector<Item> &current, vector<Item> &best)
{
    //   
    assert(true);
    //    
    //                                                                                           
    if (sum(current, 0) > sum(best, 0)) {
        best = current;
    }
}

int gifts( vector<Item> &current, vector<Item> &best, vector<Item> &giftlist, int currentGiftIndex, int budget) {
    //   
    assert(size(current) <= size(best));
    //    
    //                                                                                                                                                     
    //                                                      
    if (budget == 0) {
        best = current;
        return 1;
    } else if (budget < 0) {
        return 0;
    } else if (currentGiftIndex >= size(giftlist)) {
        improve(current, best);
        return 1;
    } else {
        current.push_back(giftlist[currentGiftIndex]);
        const int with_currentGiftIndex = gifts(current, best, giftlist, currentGiftIndex+1, budget - giftlist[currentGiftIndex].price);
        current.pop_back();
        const int without_currentGiftIndex = gifts(current, best, giftlist, currentGiftIndex+1, budget);
        return with_currentGiftIndex + without_currentGiftIndex;
    }
}

int main()
{

    vector<Item> items = {};
    Wishlist wl;

    if (!load_giftstore("giftstore.txt", items)) {
        return 1;
    }

    vector<Item> current;
    vector<Item> best;

    string filename;

    cout << "Enter filename of wishlist: ";
    cin >> filename;
    if (!load_wishlist(filename, wl, items)) {
        return 1;
    }

    int solutions = gifts(current, best, wl.items, 0, wl.budget);

    cout << "Number of possible combinations: " << solutions << ".\nBest combination:\n";
    for (int i = 0; i < size(best); i++) {
        cout << best[i].name << "\t" << best[i].price << "\n";
    }
    cout << "Total cost: " << sum(best, 0) << "\n";

    return 0;
}

/*
       

                                     
                 
                                   
                                    
                                       
                                    

      
                                    
                 
                                   
                                   
                                   
                                      
                                    

      
                                    
                 
                                   
                                    
                                   
                                       
                                    

        
                                      
                 
                            
                            
                            
                            
                               
                            

       
                                       
                 
                                                                    
                                                                    
                                                                    
                                                                     
                                                                   
                                                                   
                                                                        
                                                                     

         
                                    
                 
                                     
                                    
                                    
                                    
                                        
                                     

*/

