#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*                                                                   
                 
                                 
                              
                                                                   */

struct Gift {
  int price;
  string name;
};

struct WishList {
  int budget;
  vector<string> giftNames;
};

int size(vector<Gift> gifts) { return static_cast<int>(gifts.size()); }
int size(vector<string> str) { return static_cast<int>(str.size()); }

vector<Gift> availableGifts;

istream &operator>>(istream &in, Gift &gift) {
  assert(true);
  //                        
  char x;
  in >> gift.price;
  in >> x;
  getline(in, gift.name);
  gift.name = x + gift.name;
  return in;
}

ostream &operator<<(ostream &out, Gift &gift) {
  assert(true);
  //                                                   
  out << gift.price << " ";
  out << gift.name << endl;
  return out;
}

vector<Gift> readGifts(ifstream &input_file) {
  assert(input_file);
  //                                                         
  //                                                        
  vector<Gift> gifts;
  do {
    Gift i = {-1, ""};
    input_file >> i;
    if (i.price != -1) {
      gifts.push_back(i);
    }
  } while (input_file);
  return gifts;
}

WishList readWishlist(string file) {
  assert(file != "");
  //                                                                
  //                                                 
  WishList list;

  ifstream input_file;
  input_file.open(file);
  if (input_file) {
    input_file >> list.budget;
    cout << list.budget << endl;
    while (input_file) {
      string giftName = "";
      getline(input_file, giftName);
      if (giftName != "") {
        list.giftNames.push_back(giftName);
      }
    }
  } else {
    cout << "Cannot open file " << file << endl;
  }
  return list;
}

void readStore() {
  assert(true);
  //                                                       
  //                                    
  ifstream input_file;
  input_file.open("giftstore.txt");
  availableGifts = readGifts(input_file);
}

void printGifts(vector<Gift> &gifts) {
  assert(true);
  //                                             
  for (int i = 0; i < size(gifts); i++) {
    cout << gifts[i];
  }
}

void printWishList(WishList &list) {
  assert(true);
  //                                                
  cout << "Wishlist's maximum budget: " << list.budget << endl;
  for (int i = 0; i < size(list.giftNames); i++) {
    cout << list.giftNames[i] << endl;
  }
}

int findPrice(string name){
    assert(true);
    //                                                                                                                  
    for(int i = 0; i < availableGifts.size(); i++){
        if(availableGifts[i].name == name){
            return availableGifts[i].price;
        }
    }
    return -1;
}

void printVector(vector<string>& v){
    assert(true);
    //                                          
    for(int i = 0; i < v.size(); i++){
        cout << v[i] << endl;
    }
}

void gifts(vector<string> giftnames, int budget, int i, vector<string>& best, vector<string>& attempt,int& bestBudget){
    assert(i >= 0);
    //                                                                                                    

    int newbudget = budget - findPrice(giftnames[i]);
    if(newbudget < 0){
        if(budget < bestBudget){
           best = attempt;
           bestBudget = budget;
        }
        return;
    }
    if(i >= giftnames.size()){
        return;
    }
    attempt.push_back(giftnames[i]);
    gifts(giftnames, newbudget, i + 1, best, attempt, bestBudget);
    attempt.pop_back();
    gifts(giftnames, budget, i + 1, best, attempt, bestBudget);
}

int main(int argc, char const *argv[]) {
  readStore();
  //                           
  WishList list = readWishlist("Fabienne.txt");
  printWishList(list);
  int best = list.budget;
  vector<string> b, a;
  gifts(list.giftNames, list.budget, 0, b, a, best);
  cout << endl << "Best solution remaining budget: " << best << endl;
  cout << "Solution consists of the following items:" << endl;
  printVector(b);
  while (true) {
    string test;
    cin >> test;
  }
  return 0;
}

