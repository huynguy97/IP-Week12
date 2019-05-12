#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
using namespace std;

//                                                            

struct Present {
    string name;
    int price; //         
};

vector<Present> giftstore;

int size(vector<Present>& presents){
    return static_cast<int>(presents.size());
}

bool findGift(Present& present){
    //              
    assert(present.name != "");
    //                                                                                       
    for (int i = 0; i < size(giftstore); i++) {
        if (giftstore[i].name == present.name) {
            present.price = giftstore[i].price;
            return true;
        }
    }
    return false;
}

int sum (vector<Present>& presents) {
    //              
    assert(true);
    //                                                          
    int s = 0;
    for (int i = 0; i < size(presents); i++ ) {
            s += presents[i].price;
    }
    return s;
}

void improve(vector<Present>& a, vector<Present>& b) {
    //              
    assert(true);
    //                                                          
    if (sum(a) > sum(b) ){
        b = a;
    }
}

int gifts ( vector<Present>& attempt,vector<Present>& best,  vector<Present>& wishlist, int c , int budget ) {
    //              
    assert(size(wishlist) > 0 );
    //                                                                                                                                                                     
    if (budget == 0) {
        best = attempt;
        return 1;
    } else if (budget < 0 ){
        return 0;
    } else if ( c == size(wishlist)) {
        improve(attempt,best);
        return 0;
    } else {
        int with_c = 0;
        if (findGift(wishlist[c])){
            attempt.push_back(wishlist[c]); //       
            with_c = gifts(attempt,best,wishlist, c+1, budget - wishlist[c].price);
            attempt.pop_back(); //      
        }
        int without_c = gifts(attempt,best,wishlist, c+1, budget);
        return with_c + without_c;
    }
}

void showPresents(vector<Present> presents) {
    //              
    assert(true);
    //                                                       
    for ( int i = 0; i < size(presents); i++ ) {
        cout << presents[i].name << " " << presents[i].price << endl;
    }
    cout << "For a total of " << sum(presents) << endl;
}

int getBudgetWishlist (string name, vector<Present>& wishlist) {
    //              
    assert(name != "" && size(wishlist) == 0);
    //                                                                              
    string fileName = name + ".txt";
    ifstream inFile(fileName);
    int budget;
    inFile >> budget;
    Present present;
    present.price = 0;
    inFile.ignore(1);
    getline(inFile,present.name, '\n');
    while ( inFile ) {
        wishlist.push_back(present);
        getline(inFile,present.name, '\n');
        //                 
    }
    return budget;
}

void getGiftstore( vector<Present>& giftstore ) {
    //              
    assert(size(giftstore) == 0);
    //                                                                     
    Present present;
    ifstream inFile("giftstore.txt") ;
    inFile >> present.price;
    inFile.ignore(1);
    getline(inFile, present.name, '\n');
    while (inFile) {
        giftstore.push_back(present);
        inFile >> present.price;
        inFile.ignore(1);
        getline(inFile,present.name, '\n');
    }
}

int main()
{
    getGiftstore(giftstore);
    vector<Present> wishlist;
    vector<Present> attempt;
    vector<Present> best;

    int budget = getBudgetWishlist("Fabienne", wishlist);
    cout << budget << endl;
    gifts(attempt, best,wishlist,0,budget);
    showPresents(best);
    return 0;
}
/*
                                       
                            
                           
              
           

                                       
               
                  
                            
           

                                         
                       
                        
                    
                       
           

                                        
                                         
                                            
                               
                   
                                                              
                                                                  
            

                                          
                             
                               
                                  
                   
            

*/

