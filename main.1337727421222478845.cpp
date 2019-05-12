#include <iostream>
#include <vector>
#include <string>
#include <assert.h>
#include <fstream>

//                                    
//                                    

using namespace std;

struct Gift {
	string name;
	int cost;
};
istream& operator>>(istream& in, Gift& gift) {
	in >> gift.cost;
	in.ignore(1);
	getline(in, gift.name);
	return in;
}

void print_gifts(vector<Gift> Boughtlist);
void gifts(int budget, vector<Gift>& Wishlist, vector<Gift>& Boughtlist, vector<Gift>& BestBoughtGifts, int index);
void read_shop(string shopname, vector<Gift>& giftshop);
void calculate_best_solutions(string filename, vector<Gift> giftshop);

int main() {

	//                
	//                                                     
	//                         
	//                             

	//                                                        

	//                                          
	//                             

	vector<Gift> Giftshop;
	read_shop("giftstore.txt", Giftshop);
	calculate_best_solutions("Andrew.txt", Giftshop);
	calculate_best_solutions("Belle.txt", Giftshop);
	calculate_best_solutions("Chris.txt", Giftshop);
	calculate_best_solutions("Desiree.txt", Giftshop);
	calculate_best_solutions("Edward.txt", Giftshop);
	calculate_best_solutions("Fabienne.txt", Giftshop);
	int x;
	cin >> x;
	return 0;
}

void read_shop(string shopname,vector<Gift>& giftshop) {
	//                                       
	assert(shopname != "");
	//                                                            

	ifstream f(shopname);
	while (f) {
		Gift tempgift;
		f >> tempgift;
		giftshop.push_back(tempgift);
	}
	giftshop.pop_back();
}

Gift string_to_gift(string giftname, vector<Gift> giftshop) {

	assert(true);
	for (int i = 0; i < giftshop.size(); i++) {
		if (giftshop[i].name == giftname) return giftshop[i];

	}
	//                         
	return Gift{ "",0 };
	cout << "I failed" << endl;
}

void calculate_best_solutions(string filename,vector<Gift> giftshop) {
	//                                            
	assert(filename != "");
	//              
	//                                                       

	ifstream f(filename);

	vector<Gift> wishlist;
	vector<Gift> boughtlist;
	vector<Gift> bestlist;
	int budget;

	//               
	f >> budget;
	f.ignore();

	while (f) {
		string gift;
		getline(f, gift);
		if(gift!= "") wishlist.push_back(string_to_gift(gift,giftshop));
	}
	gifts(budget,wishlist, boughtlist, bestlist, 0);
	cout << "perfect gift list for " << filename << ":" << endl;
	print_gifts(bestlist);
}

void print_gifts(vector<Gift> Boughtlist) {
	assert(true);
	//                                                                                           

	int total = 0;
	for (int i = 0; i < Boughtlist.size(); i++) {
		cout << Boughtlist[i].name << ": " << Boughtlist[i].cost << " euros"<< endl;
		total += Boughtlist[i].cost;
	}
	cout <<  "total cost: " <<total << endl;
	cout << "\n";
}

void improve_gift_list(vector<Gift>& Boughtlist, vector<Gift>& Bestlist) {
	assert(true);
	//                                                                                    
	//                        

	int totalBoughtlist = 0;
	int totalBestList = 0;

	for (int i = 0; i < Boughtlist.size(); i++) {
		totalBoughtlist += Boughtlist[i].cost;
	}
	for (int i = 0; i < Bestlist.size(); i++) {
		totalBestList += Bestlist[i].cost;
	}
	if (totalBoughtlist >= totalBestList) Bestlist = Boughtlist;
}

void gifts(int budget, vector<Gift>& Wishlist, vector<Gift>& Boughtlist,vector<Gift>& BestBoughtGifts, int index) {
	//             
	assert( index >= 0);
	//                                                                                          
	//                                                                                              

	if (budget == 0) {
		//    
		improve_gift_list(Boughtlist, BestBoughtGifts);
	}
	else if(budget<0){
		//          
	}   //                                 
	else if (index >= Wishlist.size()) {
		improve_gift_list(Boughtlist, BestBoughtGifts);
	}
	else{
		//       
		Boughtlist.push_back(Wishlist[index]);
		gifts(budget - Wishlist[index].cost,Wishlist, Boughtlist, BestBoughtGifts,index+1);
		//      
		Boughtlist.pop_back();
		gifts(budget , Wishlist, Boughtlist, BestBoughtGifts, index+1);
	}
		
}

