//           
//
//                          
//                       
//
#include <cerrno>
#include <cassert>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

struct Gift {
    string name;
    long int price;
};

int size (vector<Gift>& gifts) {
    assert(true);
    /*                
                                              
     */
    return static_cast<int>(gifts.size());
}

int price_of(vector<Gift>& gifts) {
    assert(true);
    /*                
                                                               
     */
    long int sum = 0;
    for (int i = 0; i < size(gifts); i++) {
        sum += gifts[i].price;
    }
    return sum;
}

int gifts(vector<Gift>& gift_shop, vector<Gift>& wishlist, long int budget,
        vector<Gift>& current_solution, vector<Gift>& best_solution,
        int wishlist_pos, int& suboptimal_solutions) {
    assert(true);
    /*                
                                                                               
                                                                             
                                                  
     */
    if (budget == 0) {
        best_solution = current_solution;
        return 1;
    } else if (budget < 0) {
        return 0;
    } else if (wishlist_pos >= size(wishlist)) {
        if (price_of(current_solution) > price_of(best_solution)) {
            best_solution = current_solution;
            suboptimal_solutions++;
        }
        return 0;
    } else {
        current_solution.push_back(wishlist[wishlist_pos]);
        const int WITH_GIFT = gifts(gift_shop, wishlist,
                                    budget - wishlist[wishlist_pos].price,
                                    current_solution, best_solution,
                                    wishlist_pos + 1, suboptimal_solutions);
        current_solution.pop_back();
        const int WITHOUT_GIFT = gifts(gift_shop, wishlist,
                                    budget,
                                    current_solution, best_solution,
                                    wishlist_pos + 1, suboptimal_solutions);
        return WITH_GIFT + WITHOUT_GIFT;
    }
}

int load_giftstore(vector<Gift>& giftstore, string filename) {
    assert(true);
    /*                
                                                                              
                                                        
     */
    ifstream input;
    int c = 0;

    input.open(filename);
    if (!input) {
        return -errno;
    }

    while (input) {
        string price = "";
        Gift gift;
        getline(input, price, ' ');
        if (!(price == "\n" || price == "\r" || price == "")) {
            gift.price = stoi(price);
            getline(input, gift.name);
            giftstore.push_back(gift);
            c++;
        }
    }

    return c;
}

bool lookup_gift(string name, vector<Gift>& giftshop, Gift& gift) {
    assert(true);
    /*                
                                                                       
                                             
     */
    for (int i = 0; i < size(giftshop); i++) {
        if (giftshop[i].name == name) {
            gift = giftshop[i];
            return true;
        }
    }

    return false;
}

int load_wishlist(vector<Gift>& wishlist, vector<Gift>& giftshop,
        long int& budget, string filename) {
    assert(true);
    /*                
                                                                              
                                                                               
                                                                              
     */
    ifstream input;
    int c = 0;

    input.open(filename);
    if (!input) {
        return -errno;
    }

    string budget_string;
    getline(input, budget_string);
    budget = stoi(budget_string);

    while (input) {
        Gift gift;
        string gift_name = "";
        getline(input, gift_name);
        if (!(gift_name == "\n" || gift_name == "\r" || gift_name == "") &&
                lookup_gift(gift_name, giftshop, gift)) {
            wishlist.push_back(gift);
            c++;
        }
    }

    return c;
}

void show(vector<Gift>& giftlist) {
    assert(true);
    /*                
                                               
     */
    for (int i = 0; i < size(giftlist); i++) {
        cout << giftlist[i].name << endl;
    }
}

int main(int argc, char* argv[]) {
    assert(true);
    /*                
           
     */
    vector<Gift> giftstore, wishlist, current_solution, best_solution;
    int giftstore_count, wishlist_count,
        perfect_solutions, suboptimal_solutions;
    long int budget;

    if (argc < 3) {
        cerr << "Usage: ./a.out <giftlist> <wishlist>" << endl;
        return -1;
    }

    giftstore_count = load_giftstore(giftstore, argv[1]);
    if (giftstore_count < 0) {
        return -giftstore_count;
    }

    assert(giftstore_count == size(giftstore));
    cout << "Found " << giftstore_count << " gifts in the store." << endl;

    wishlist_count = load_wishlist(wishlist, giftstore, budget, argv[2]);
    if (wishlist_count < 0) {
        return -wishlist_count;
    }

    assert(wishlist_count == size(wishlist));
    cout << wishlist_count << " gifts in the wish list." << endl;

    perfect_solutions = gifts(giftstore, wishlist, budget,
            current_solution, best_solution, 0, suboptimal_solutions);
    cout << "There are " << perfect_solutions << " perfect solutions and "
        << suboptimal_solutions << " suboptimal solutions for this wishlist."
        << endl;
    cout << "The best solution is:" << endl;
    show(best_solution);

    return 0;
}

/*              

                                
                            
                          
                                                                           
                     
                        
                          

                               
                            
                         
                                                                           
                     
           
              
                        

                               
                            
                          
                                                                           
                     
                        
                      
          

                                 
                            
                          
                                                                           
                     
                  
                   
               
                  

                                
                            
                          
                                                                           
                     
                                    
                                       
                          
             
                                                          
                                                             

                                  
                            
                          
                                                                           
                     
                       
                          
                             
              

*/

