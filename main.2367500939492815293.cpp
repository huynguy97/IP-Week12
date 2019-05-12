//                                              

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

struct Present {
	string name;
	int price; //    
};

istream& operator>> (istream& in, Present& present) {
    //              
    assert (true);
/*                
                                                                                 */
    Present input;
    char temp;
    in >> present.price;
    in.get(temp);
    getline(in, present.name);
    return in;
}

bool open_input_file (ifstream& infile, string infile_name) {
    //               
    assert(!infile.is_open());
    //                                                                              
    infile.open(infile_name.c_str());
    if (!infile.is_open()) {
        cout << "Error: Input file " << infile_name << " could not be opened." << endl << endl;
        return false;
    }
    cout << "The file " << infile_name << " has been opened successfully." << endl << endl;
    return true;
}

bool read_store(ifstream& infile, vector<Present>& store){
    //               
    assert(infile.is_open() && store.empty());
    //                                                                                 
    Present input;
    infile >> input;
    while (infile){
        store.push_back(input);
        infile >> input;
    }
    return !store.empty();
}

bool match_gifts(Present& gift, vector<Present>& store){
    //               
    assert ((gift.name).length() > 0);
    //                                                                                          
    if (store.empty()) return false; //                                                 
    for (unsigned int i = 0; i < store.size(); i++){
        if (gift.name == store[i].name){
            gift.price = store[i].price; //                                              
            return true;
        }
    }
    return false; //                              
}

bool read_wishlist(ifstream& infile, vector<Present>& wishlist, vector<Present>& store, int& budget){
    //               
    assert(infile.is_open() && wishlist.empty());
    /*                                                                                
                                                                                                                         */
    Present input;
    string temp;
    infile >> budget;
    getline(infile, temp);
    getline(infile, input.name);
    while (infile){
        if (match_gifts(input, store)){ //                                                                 
            wishlist.push_back(input);
        }
        getline(infile, input.name);
    }
    return !wishlist.empty();
}

bool read_input (vector<Present>& store, vector<Present>& wishlist, int& budget){
    //               
    assert(store.empty() && wishlist.empty());
    /*                                                                                                                             
                                                                      */
    ifstream input_store;
    ifstream input_wishlist;
    string filename_wishlist;
    if (open_input_file(input_store, "giftstore.txt")){
        if (read_store(input_store, store)){
            cout << "Please enter a wish list:" << endl;
            getline(cin, filename_wishlist);
            if (open_input_file(input_wishlist, filename_wishlist)){
                if (read_wishlist(input_wishlist, wishlist, store, budget)){
                    input_store.clear();
                    input_store.close();
                    input_wishlist.clear();
                    input_wishlist.close();
                    if (input_store && input_wishlist){
                        return true;
                    } else {
                        cout << "One or both of the input files could not be closed." << endl;
                        return false;
                    }
                } else {
                    cout << "No presents that are present in the gift store could be read from "
                         << filename_wishlist << "." << endl;
                    return false;
                }
            } else {
                cout << "File " << filename_wishlist << " could not be opened." << endl;
                return false;
            }
        } else {
            cout << "No presents were read from giftstore.txt" << endl;
            return false;
        }
    } else cout << "File giftstore.txt could not be opened." << endl;
    return false;
}

void update_maximum(vector<Present>& attempt, vector<Present>& wishlist, vector<bool>& chosen, int& maximum){
    //               
    assert(wishlist.size() == chosen.size());
    //                                                                                                                       
    int price = 0;
    for (int j = 0; j < static_cast<int>(attempt.size()); j++){
        price += attempt[j].price;
    }
    if (price > maximum){
        maximum = price;
        bool found;
        for (int i = 0; i < static_cast<int>(wishlist.size()); i++){
            found = false;
            for (int j = 0; j < static_cast<int>(attempt.size()); j++){
                if (attempt[j].name == wishlist[i].name){
                    found = true;
                }
            }
            chosen[i] = found; //                                                                
        }
    }
}

bool gifts(vector<Present>& wishlist, vector<Present>& attempt, vector<bool>& chosen, int& maximum, int c, int budget){
    //                
    assert(c >= 0 && wishlist.size() == chosen.size() && (!attempt.empty() || budget >= 0));

    /*                                                                                                     
                                                                                          
                                                           */
    if (budget == 0){
        update_maximum(attempt, wishlist, chosen, maximum);
        return true;
    } else if (budget < 0){
        return false;
    } else if (c >= static_cast<int>(wishlist.size())) {
        update_maximum(attempt, wishlist, chosen, maximum);
        return true;
    } else {
        attempt.push_back(wishlist[c]);
        bool with_c = gifts(wishlist, attempt, chosen, maximum, c+1, budget-wishlist[c].price);
        attempt.pop_back();
        bool without_c = gifts(wishlist, attempt, chosen, maximum, c+1, budget);
        return with_c || without_c;
    }
}

void show_solution(vector<Present> wishlist, vector<bool> chosen, int maximum, int budget){
    //               
    assert(wishlist.size() == chosen.size());
    //                 
    cout << "The maximal list of gifts with respect to budget " << budget << " is:" << endl << endl;
    for (int i = 0; i < static_cast<int>(wishlist.size()); i++){
        if (chosen[i]) cout << wishlist[i].name << endl;
    }
    cout << endl << "This list of gifts has price " << maximum << "." << endl;
}

int main() {
    vector<Present> store;
    vector<Present> wishlist;
    int budget;
    if (!read_input(store, wishlist, budget)){
        return -1;
    }
    vector<bool> chosen;
    for (int i = 0; i < static_cast<int>(wishlist.size()); i++){
        chosen.push_back(false);
    }
    vector<Present> attempt;
    int maximum = 0;
    if (gifts(wishlist, attempt, chosen, maximum, 0, budget)){
        show_solution(wishlist, chosen, maximum, budget);
    } else {
        cout << "No valid list of presents with respect to budget " << budget << "could be found." << endl << endl;
    }
    return 0;
}

/*         

       
                                                        

                             
              
                                                     

                                                             

                            
                              

                                      

      
                                                        

                             
             
                                                    

                                                             

               
                  
                            

                                      

      
                                                        

                             
             
                                                    

                                                             

                            
                          
              

                                      

        
                                                        

                             
               
                                                      

                                                             

                      
                       
                   
                      

                                      

       
                                                        

                             
              
                                                     

                                                              

                                        
                                           
                              
                 
                                                              
                                                                 

                                       

         
                                                        

                             
                
                                                       

                                                              

                           
                              
                                 
                  

                                       
*/

