#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <locale> //                     

//                               
//                               

using namespace std;

struct product {
    vector<int> price;
    vector<string> item;
};

template <typename El>
int size (vector<El>& vec) {
//               
    assert (true) ;
//                                                                
    return static_cast<int> (vec.size());
}

int sum (vector<int>& coins, int from) {
//               
    assert (from >= 0 && from <= size(coins));
//                 
//                                 
    int sum = 0 ;
    for (int i = from; i < size(coins); i++)
        sum += coins[i];
    return sum;
}

int sum (vector<int>& coins) {
//               
    assert (true) ;
//                                                 
    return sum (coins,0);
}

void improve (vector<int>& current, vector<int>& best) {
//               
    assert (true);
//                 
//                                                                 
    if (sum (current) > sum (best))
        best = current;
}

int gifts (vector<int>& attempt, vector<int>& best, product& wishlist, int c, int budget) {
//                   
    assert(c >= 0);
//                                                                    
    if (budget == 0) {
        best = attempt;
        return 1;
    }
    else if (budget <= 0) {
        return 0;
    }
    else if (c >= size(wishlist.price)) {
        improve(attempt,best);
        return 1;
    }
    else if (sum(attempt) + sum(wishlist.price,c) <= sum(best)) {
        return 1;
    }
    else {
        attempt.push_back(wishlist.price[c]);
        int with_c = gifts(attempt,best,wishlist,c+1, budget - wishlist.price[c]);
        attempt.pop_back();
        int without_c = gifts(attempt,best,wishlist,c+1,budget);
        return with_c + without_c;
    }
}

void print_gifts(vector<int>& best, vector<string>& list) {
//                   
    assert(true);
//                                                                                   
    int total = 0;
    for (int i = 0; i < size(best); i++) {
        cout << best[i] << " - " << list[i] << endl;
        total += best[i];
    }
    cout << total << " in total." << endl;
}

void index_giftstore(product& giftstore) {
//                   
    assert(true);
//                                                                             
    ifstream infile;
    infile.open("giftstore.txt");
    assert(infile.is_open());
    int price = 0;
    char garbage;
    string item = "";
    while(infile) {
        infile >> price;
        infile.get(garbage);
        getline(infile, item);
        giftstore.item.push_back(item);
        giftstore.price.push_back(price);
    }

    infile.clear();
    infile.close();
}

void index_wishlist (product& giftstore, product& wishlist, string filename, int& budget) {
//                   
    assert(true);
//                                                                
    ifstream infile;
    //                                                                  
    if (filename.find(".txt") == string::npos) {
        filename += ".txt";
    }
    if(islower(filename[0])) {
        filename[0] = toupper(filename[0]);
    }
    
    infile.open(filename);
    
    if(!infile.is_open()) {
        cout << "Invalid name" << endl;
        return;
    }

    string item = "";
    string budget_str = "";
    getline(infile, budget_str);
    budget = stoi(budget_str);
    while(infile) {
        getline(infile, item);
        for (int i = 0; i < size(giftstore.item); i++) {
            if(giftstore.item[i] == item) {
                wishlist.item.push_back(item);
            }
        }
    }
    infile.clear();
    infile.close();
    
    for (int i = 0; i < size(wishlist.item); i++) {
        for (int j = 0; j < size(giftstore.item); j++) {
            if (giftstore.item[j] == wishlist.item[i]) {
                wishlist.price.push_back(giftstore.price[j]);
            }
        }
    }    
}

int main() {
    product giftstore, wishlist;
    vector<int> attempt, best;
    vector<string> list;
    int budget = 0;

    index_giftstore(giftstore);

    string filename = "";
    cout << "Enter a name:" << endl;
    cin >> filename;

    index_wishlist(giftstore, wishlist, filename, budget);

    cout << "The number of possible solutions is: " << gifts(attempt, best, wishlist, 0, budget) << endl;
    string item;
    for (int j = 0; j < size(best); j++) {
        for (int i = 0; i < size(wishlist.price); i++) {
            if (wishlist.price[i] == best[j]) {
                item = wishlist.item[i];
                list.push_back(item);
            }
        }
    }
    print_gifts(best, list);
}
/*
       
                           
                                  
                                     
                  
      
                                       
                     
                     
                        
                  
      
                                       
                                  
                                 
                    
                  
        
                                         
                             
                              
                          
                             
                  
       
                                         
                                               
                                                  
                                     
                         
                                                                    
                                                                       
                   
         
                                       
                                   
                                     
                                        
                         
                   
*/
