#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

//                                                

struct Present {
    string name;
    int price; //         
};

vector<Present> store;

int size(vector<Present>& presents){
    return static_cast<int>(presents.size());
}

bool findGift(Present& present){
    assert (true);
    //             
    //                                              
    for (int i = 0; i < size(store); i++) {
        if (store[i].name == present.name) {
            present.price = store[i].price;
            return true;
        }
    }
    return false;
}

int sum (vector<Present>& presents) {
    assert (size(presents) > 0);
    //             
    //                              
    int s = 0;
    for (int i = 0; i < size(presents); i++ ) {
            s += presents[i].price;
    }
    return s;
}

void improve(vector<Present>& a, vector<Present>& b) {
    if (sum(a) > sum(b) ){
        b = a;
    }
}

int gifts ( vector<Present>& attempt,vector<Present>& best,  vector<Present>& wishlist, int c , int budget ) {
    assert (true);
    //             
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
    for ( int i = 0; i < size(presents); i++ ) {
        cout << presents[i].name << " " << presents[i].price << endl;
    }
    cout << "For a total of " << sum(presents) << endl;
}

int getBudgetWishlist (string name, vector<Present>& wishlist) {
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

void getstore( vector<Present>& store ) {
    Present present;
    ifstream inFile("store.txt") ;
    inFile >> present.price;
    inFile.ignore(1);
    getline(inFile, present.name, '\n');
    while (inFile) {
        store.push_back(present);
        inFile >> present.price;
        inFile.ignore(1);
        getline(inFile,present.name, '\n');
    }
}

int main()
{
    getstore(store);
    vector<Present> wishlistChris;
    getBudgetWishlist("Chris", wishlistChris);
    vector<Present> attempt;
    vector<Present> best;

    showPresents(store);
    return 0;
}

