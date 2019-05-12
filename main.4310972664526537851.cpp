#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

//                           

struct Gift {
    int price;
    string name;
};

void print_vector (vector<int> vect) {
    assert (true);
    //                                                          
    for (int i = 0; i < vect.size(); i++) {
        cout << vect[i];
        if (i < vect.size() - 1) {
            cout << ", ";
        }
    }
}

void improve (vector<int>& attempt, vector<int>& best){
    assert (true);
    //                                     
    int bst_size = best.size();
    for (int j = 0; j < bst_size; j++) {
        best.pop_back();
    }
    for (int i = 0; i < attempt.size(); i++){
        best.push_back(attempt[i]);
    }
}

int vect_sum (vector<int> vect, int index) {
    assert (index >= 0);
    //                                                                                              
    int sum = 0;
    for (int i = index; i < vect.size(); i++){
        sum = sum + vect[i];
    }
    return sum;
}

int gifts (vector<int>& wishlist_price_vect, int budget, int id, vector<int>& attempt, vector<int>& best_attempt) {
    assert(id >= 0);
    //                                                                                                                              
    if (id >= wishlist_price_vect.size()) {
        improve(attempt, best_attempt);
        return budget;
    } else {
        vector<int> next_best_attempt_with_id = {0};
        vector<int> next_best_attempt_without_id = {0};
        int budget_with_id = budget+1;
        attempt.push_back(wishlist_price_vect[id]);
        if (wishlist_price_vect[id] <= budget ) {
            budget_with_id = gifts(wishlist_price_vect, budget - wishlist_price_vect[id], id + 1, attempt, next_best_attempt_with_id);
        }
        attempt.pop_back();
        int budget_without_id = gifts(wishlist_price_vect, budget, id + 1, attempt, next_best_attempt_without_id);
        if (min(budget_with_id, budget_without_id) == budget_with_id) {
            improve(next_best_attempt_with_id, best_attempt);
        } else {
            improve(next_best_attempt_without_id, best_attempt);
        }
        return min(budget_with_id, budget_without_id);
        }

}

bool open_gift_store (ifstream& file, vector<Gift>& vect) {
    assert(true);
    //                                                                                                                          
    int counter = 0;
    string price_str = " ";
    file.open("giftstore.txt");
    while (file) {
        vect.push_back(Gift());
        file >> price_str;
        vect[counter].price = stoi(price_str);
        file.get();
        getline(file, vect[counter].name);
        counter = counter + 1;
    }
    vect.pop_back();
    if (file.is_open()) {
        return true;
    }
    return false;
}

bool open_wishlist (ifstream& file, string file_name, vector<string>& vect, int& budget) {
    assert (true);
    //                                                                                                                              
    string gift = " ";
    string budget_str = " ";
    file.open(file_name);
    getline(file, budget_str);
    budget = stoi(budget_str);
    while (file){
    getline(file, gift);
    vect.push_back(gift);
    }
    if (file.is_open()){
        return true;
    }
    return false;
}

int main()
{
    vector<int> wishlist_price_vect;
    vector<int> attempt = {0};
    vector<int> best_attempt = {0};
    vector<string> best_gifts;
    vector<Gift> gift_store_vect;
    vector<string> wishlist_vect;
    int budget;
    int budget_left = 0;
    int j = 0; //                                                                    
    ifstream gift_store_file;
    ifstream wishlist_file;
    string name = " ";
    cout << "Enter wishlist file name: ";
    cin >> name;
    cout << endl;
    if (open_wishlist(wishlist_file, name, wishlist_vect, budget)){
        cout << "Wishlist opened successfully" << endl << endl;
    } else {
        cout << "File opening failure!(wishlist)" << endl << endl;
    }
    if (open_gift_store(gift_store_file, gift_store_vect)){
        cout << "Gift store processed successfully" << endl << endl;
    } else {
        cout << "File opening failure!(gift store)" << endl << endl;
    }
    cout << "The budget is " << budget << endl << endl;
    for (int i = 0; i < wishlist_vect.size(); i++) {
        while (wishlist_vect[i] != gift_store_vect[j].name && j < gift_store_vect.size()){
            j = j + 1;
        }
        if (j != gift_store_vect.size() - 1) {
        wishlist_price_vect.push_back(gift_store_vect[j].price);
        j = 0;
        }
    }
    wishlist_price_vect.pop_back();
    cout << "Wishlist:" << endl;
    for (int k = 0; k < wishlist_price_vect.size(); k++){
        cout << wishlist_vect[k] << ' ' << "(price: " << wishlist_price_vect[k] << ')' << endl;
    }
    cout << endl << endl;
    budget_left = gifts(wishlist_price_vect, budget, 0, attempt, best_attempt);
    cout << endl;
    cout << "Final product list:" << endl;
    for (int m = 1; m < best_attempt.size(); m++) {
        for (int n = 0; n < wishlist_price_vect.size(); n++) {
            if (best_attempt[m] == wishlist_price_vect[n]) {
                cout << wishlist_vect[n] << " (cost: " << wishlist_price_vect[n] << ')' << endl;
            }
        }
    }
    cout << endl << "The remaining budget money is " << budget - vect_sum(best_attempt, 0) << endl;
    return 0;
}

/*         

       

                   
                                    
                                       

                               

      

                   
                       
                       
                          
                                    

                                 

      

                   
                                    
                                   
                      

                               

        

                   
                               
                                
                            
                               

                               

       

                   
                                                 
                                                    
                                       
                           
                                                                      
                                                                         
                                                                                  
                                                                      
                                                                         
                                                                                  

                               

         

                   
                                     
                                       
                                          
                           

                                 

*/

