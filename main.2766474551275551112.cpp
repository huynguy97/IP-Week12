//                                                    
#include <iostream>
#include <vector>
#include <fstream>
#include <assert.h>

using namespace std;

string WISHLIST_FILES[] = {"Andrew.txt", "Belle.txt", "Chris.txt", "Desiree.txt", "Edward.txt", "Fabienne.txt"};
const int NO_OF_WISHLISTS = 6;

struct wishlist {
	vector<string> items;
	int budget;
};

struct gift {
	string name;
	int price;
};

vector<string> gifts_used;

bool onWishlist(wishlist w, gift g){
	//              
	assert(true);
	//                                                                                    
	for(int x=0; x<w.items.size(); x++){
	//	                                            
		if(w.items[x]==g.name)
			return true;
	}
	return false;
}

int find_gifts(int budget_used, vector<gift> gifts_used, wishlist person, int gift_i, vector<gift>& available, vector<gift>& best_gifts_used, int& best_budget_used){
	//              
	assert(true);
	//               
	//                                                                                                                                                                                     
//	                                                                                                 
	if(budget_used>best_budget_used){
		best_budget_used=budget_used;
		best_gifts_used = gifts_used;
	}
	if(gift_i>=available.size()){
		//                                       
		return 0;
	}
	//                                                    
	int ans = find_gifts(budget_used, gifts_used, person, gift_i+1, available, best_gifts_used, best_budget_used);
	if(onWishlist(person, available[gift_i])){
//		                                       
		if(budget_used+available[gift_i].price<=person.budget){
			//                                                                                                                                 
			gifts_used.push_back(available[gift_i]);
			ans = max(ans, available[gift_i].price+find_gifts(budget_used+available[gift_i].price, gifts_used, person, gift_i+1, available, best_gifts_used, best_budget_used));
		}
	}
	return ans;
}

ifstream& open_file(ifstream& in, string filename){
	//              
	assert(true);
	//                                                                
	in.open(filename);
}

void readAvailableGifts(vector<gift>& available, string input_file){
	//              
	assert(true);
	//                                                                       
	ifstream in;
	open_file(in, input_file);
	int price; string name;
	while(in>>price){
		getline(in, name);
		//                               
		name = name.substr(1);
		gift g;
		g.name = name;
		g.price = price;
		available.push_back(g);
	}
}

void readWishlist(wishlist& list, string input_file){
	//              
	assert(true);
	//                                                                       
	ifstream in;
	open_file(in, input_file);
	string name;
	in>>list.budget;
	getline(in, name); //               
	while(getline(in, name)){
		list.items.push_back(name);
	}
}

int main(){
/*
	                              
                                            
                
                        
                          

                                           
                
           
              
                        

                                           
                
                      
                        
          

                                             
                
                   
                        
                          
                  

                                            
                 
                                       
                                                             
                                                                      
                                    
             
                          

                                              
                 
                             
                          
              
                       

 */

	vector<gift> available;
	string available_file = "giftstore.txt";
	readAvailableGifts(available, available_file);
	for(int n=0; n<NO_OF_WISHLISTS; n++){
		wishlist list;
		readWishlist(list, WISHLIST_FILES[n]);
		cout << "BEST OPTION FOR WISHLIST GIVEN BY " << WISHLIST_FILES[n] << endl;
		vector<gift> gifts_used, best_gifts_used; int best_budget_used = 0;
		find_gifts(0, gifts_used, list, 0, available, best_gifts_used, best_budget_used);
		cout << "total cost: " << best_budget_used << endl;
		for(int x=0; x<best_gifts_used.size(); x++){
			cout << best_gifts_used[x].name << endl;
		}
		cout << endl;
	}
	return 0;
}

