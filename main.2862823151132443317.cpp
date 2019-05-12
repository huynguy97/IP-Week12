
/* 
                        
                                   
  
                                       
 */

#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

/*
   
 */

struct Gift{
    int price;
    string tname;
};

struct Wishlist{
    int budget;
    vector<string> wishes;
};

int find_gift(string gift, vector<Gift> giftstore, int index){
    for(int i = index -1; i > 0; i--){
        if(giftstore[i].tname == gift){
            return i;
        }
    }
    return -1;
}

Wishlist readwishlist(ifstream& infile, string filename){
    Wishlist wish1;
    infile.open(filename.c_str());
    if(!infile){
        cout << "Could not find wishlist file" << endl;
        return wish1;
    }
    int budget = -1;
    infile >> budget;
    wish1.budget = budget;
    while(infile){
        string tname;
        getline(infile, tname);
        wish1.wishes.push_back(tname);
    }
    infile.close();
    return wish1;
}

bool readgifts(ifstream& infile, vector<Gift>& gifts){
    infile.open("giftstore.txt");
    if(!infile){
        cout << "Could not find giftstore file" << endl;
        return false;
    }
    while(infile){
        int price = -1;
        infile >> price;
        string tname;
        getline(infile, tname);
        Gift g1;
        g1.price = price;
        g1.tname = tname;
        if(!(g1.price == -1)){
            gifts.push_back(g1);
        }
    }
    infile.close();
    return true;
}

//                                                                       
int gifts(int budget, Wishlist wish1, vector<Gift>& giftstore, vector<string>& gifted, int index) 
{ 
    string gift = wish1.wishes[index-1];
    cout << gift << endl;
    //           
   if (index == 0 || budget == 0) 
       return 0; 
  
   //                                                                             
   if (giftstore[index-1].tname == gift && giftstore[index-1].price  > budget)
       return gifts(budget, wish1, giftstore, gifted, index-1); 
  
   //                                   
   //                        
   //                 
    cout << giftstore[index-1].tname << " compared to" << gift << endl;
    if(giftstore[index-1].tname == gift){
        cout << " gift equal to" << endl;
        int takengift = giftstore[index-1].price + gifts(budget-giftstore[index-1].price, wish1, giftstore, gifted, index-1);
        int giftnottaken = gifts(budget, wish1,  giftstore, gifted, index-1);
        if(takengift > giftnottaken){
            gifted.push_back(giftstore[index-1].tname);
            return 1;
        } else{
            return 0;
        }
    } else {
        gifts(budget, wish1, giftstore, gifted, index-1);
    } 
}
void showresult(vector<string>& finalgifts){
    for(int i; i< finalgifts.size(); i++){
        cout << finalgifts[i] << endl;
    }
}

void showstore(vector<Gift> giftstore){
    for(int i = 0; i < giftstore.size();i++){
        cout << giftstore.at(i).price << "\t" << giftstore[i].tname << endl;
    }
}

int main(int argc, char** argv) {
    ifstream infile;
    vector<Gift> gift1;
    readgifts(infile, gift1);
    Wishlist andrew = readwishlist(infile, "Andrew.txt");
    vector<string> finalgifts;
    gifts(andrew.budget, andrew, gift1, finalgifts, andrew.wishes.size());
    showresult(finalgifts);

    return 1;
}

