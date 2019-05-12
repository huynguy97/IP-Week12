#include<cstdlib>
#include<iostream>
#include<vector>
#include<cassert>
#include<cmath>
#include<fstream>
using namespace std;
//                               
struct Gift {
	int price;
	string name;
};

bool operator == (Gift a, Gift b) {
	return a.name == b.name && a.price == b.price;
}

int size(vector<Gift>& gifts) { //               
	assert(true);
//                                                            
	return static_cast < int > (gifts.size());
}

Gift minimum(vector<Gift>& gifts, int from) { //               
	assert(from >= 0 && from < size(gifts));
//                 
//                                                                      
	Gift m = gifts[from];
	for (int i = from + 1; i < size(gifts); i++)
		if (gifts[i].price < m.price)
			m = gifts[i];
	return m;
}

int sum(vector<Gift>& gifts, int from = 0) {
//               
	assert(from >= 0 && from <= size(gifts));
//                 
//                                                                                                 
	int sum = 0;
	for (int i = from; i < size(gifts); i++)
		sum += gifts[i].price;
	return sum;
}

void improve(vector<Gift>& current, vector<Gift>& best) { //               
	assert(true);
//                 
//                                                                                        
	if (sum(current) > sum(best))
		best = current;
}

void show(vector<Gift>& gifts) {
//               
	assert(true);
//                                                                                                
    for (int i = 0; i <(size(gifts)-1); i++) {
		cout<<gifts[i].name<<", ";
    }
    cout<<gifts[size(gifts)-1].name<<endl;
}

void swap(vector<Gift>& gifts, int i, int j) {
//                
	assert(0 <= i && i < size(gifts) && 0 <= j && j < size(gifts));
//                                                                                    
	const Gift HELP = gifts[i];
	gifts[i] = gifts[j];
	gifts[j] = HELP;
}

bool is_selection(vector<Gift>& a, vector<Gift>& b, int c) {
//               
	assert(0 <= c && c <= size(b));
//                                                                                               
//                                                       
	for (int i = 0; i < size(a); i++) {
		bool occurs = false;
		for (int j = 0; j < c; j++) {
			if (a[i] == b[j]) {
				occurs = true;
			}
		}
		if (!occurs) {
			return false;
		}
	}
	return true;
}

bool contains(Gift el, vector < Gift > gifts) {
//                
	assert(true);
//                                                                  
	for (int i = 0; i < size(gifts); i++) {
		if (el == gifts[i]) {
			return true;
		}
	}
	return false;
}

void gifts(vector<Gift>& wishlist, vector<Gift>& current, vector<Gift>& best, vector<Gift>& store, int c, int budget) {
//               
	assert(0 <= c && c <= size(wishlist)&& is_selection(current, wishlist, c));
	assert(is_selection(best, wishlist,size(wishlist)));
//                 
//                                 
//                                                                                                     
	if (budget == 0) {
		best = current;
		return;
	} else if (budget < 0) {
		return;
	} else if (c >= size(wishlist)) {
		improve(current, best);
		return;
	} else {
		if (contains(wishlist[c], store)) {
			//                                               
			current.push_back(wishlist[c]);
			gifts(wishlist, current, best, store, c + 1, budget - wishlist[c].price);
			current.pop_back();
		}
		gifts(wishlist, current, best, store, c + 1, budget);
	}
}

//      
void read_giftlist(vector<Gift>& store){
//                
    assert(true);
//                                                                   
    ifstream storelist("giftstore.txt");
    while(storelist){
        int val=0;
        string name;
        storelist>>val;
        storelist.ignore(1);
        //                                                  
        if(storelist.peek()==EOF){
            return;
        };
        getline(storelist,name);
        store.push_back({val,name});
    }
}

int get_price(string name, vector<Gift>& store){
    for (int i = 0; i < size(store); i++){
        if(name==store[i].name){return store[i].price;}
    }
    return 0;
}

void read_wishlist(vector<Gift>& store, vector<Gift>& wishlist, int& budget){
//                
    assert(true);
//                                                                                                 
    ifstream wishlistf("Andrew.txt");
    wishlistf>>budget;
    wishlistf.ignore(1);
    while(wishlistf){
        string name;
        getline(wishlistf,name);
        //                                                  
        if(wishlistf.peek()==EOF){
            return;
        };
        int val=get_price(name,store);
        wishlist.push_back({val,name});
    }
}

string show_money(int cents){
//                
    assert(true);
//                                                                                       
//                                                                                                
    return("Euro "+to_string(cents/100)+"."+(cents%100<10?"0":"")+to_string(cents%100));
}

int main() {
    vector<Gift> store;
    vector<Gift> wishlist;
    vector<Gift> current;
    vector<Gift> best;
    int budget=0;
    read_giftlist(store);
    read_wishlist(store,wishlist,budget);
    gifts(wishlist,current,best,store,0,budget);
    cout<<"Gifts: ";
    show(best);
    cout<<"Used "<<show_money(sum(best))<<" out of "<<show_money(budget);
    cout<<", leaving "<<show_money(budget-sum(best))<<".\n";
	return 0;
}

