#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

//                          
//                            
//                          

struct Gift {
	string name;
	int price;
};

vector<Gift> giftlist;
vector<Gift> wishlist;

int get_total_price(vector<Gift> gifts)
{
	//              
	assert(true);
	//               
	//                                                          
	int price = 0;
	for(Gift g : gifts) price += g.price;
	return price;
}

void improve(vector<Gift>& attempt, vector<Gift>& best)
{
	//              
	assert(true);
	//               
	//                                                                       
	//                                                  
	if(get_total_price(attempt) > get_total_price(best)) best = attempt;
}

bool contains(vector<Gift> gifts, Gift g)
{
	//              
	assert(true);
	//               
	//                                                                                
	for(Gift gi : gifts)
	{
		if(g.name == gi.name && g.price == gi.price) return true;
	}
	return false;
}

void gifts(vector<Gift>& attempt, vector<Gift>& best, vector<Gift>& giftlist, vector<Gift> wishlist, int g, int budget)
{
	//              
	int size = wishlist.size();
	assert(g >= 0 && g < size && budget > 0);
	//               
	//                                                                  
	//                                                                    
	if(budget == 0)
	{
		best = attempt;
		return;
	}
	else if(budget < 0) return;
	else if(g >= size)
	{
		improve(attempt, best);
		return;
	}

	//         
	if(contains(giftlist, wishlist[g]))
	{
		attempt.push_back(wishlist[g]);
		gifts(attempt, best, giftlist, wishlist, g + 1, budget - wishlist[g].price);
	}
	//            
	if(attempt.size() > 0) attempt.pop_back();
	gifts(attempt, best, giftlist, wishlist, g + 1, budget);
}

void show_giftlist(vector<Gift> gifts)
{
	//              
	assert(true);
	//               
	//                                                                   
	int i = 0;
	for(Gift g : gifts)
	{
		cout << i << ": " << g.name << ", " << g.price << endl;
		i++;
	}
}

void open_file(ifstream& file)
{
	//              
	assert(true);
	//               
	//                                                       
	while(!file.is_open())
	{
		cout << "Please enter the filename: " << endl;
		string filename;
		getline(cin, filename, '\n');

		file.open (filename, std::ifstream::in);

		if(!file.is_open()) cout << "Invalid file name. Please try again." << endl;
	}
}

void load_present_to_wishlist(string present)
{
	//              
	assert(true);
	//               
	//                                                                                     
	int size = giftlist.size();
	for(int i = 0; i < size; i++)
	{
		Gift g = giftlist[i];
		if(present == g.name)
		{
			wishlist.push_back(g);
			return;
		}
	}
}

int load_wishlist()
{
	//              
	assert(true);
	//               
	//                                                                                                
	ifstream file;
	open_file(file);

	cout << "Wishlist opened!" << endl;

	string budget_str;
	getline(file, budget_str, '\n');

	int budget = std::stoi(budget_str);

	while(file)
	{
		string present;
		getline(file, present, '\n');

		load_present_to_wishlist(present);
	}
	return budget;
}

bool open_giftstore_file(ifstream& file)
{
	//              
	assert(true);
	//               
	//                                     
	string filename = "giftstore.txt";

	file.open (filename, std::ifstream::in);

	if(file.is_open()) return true;
	return false;
}

void load_giftlist()
{
	//              
	assert(true);
	//               
	//                                           
	ifstream file;
	if(open_giftstore_file(file)) cout << "Loaded giftstore.txt!" << endl;
	else cout << "Failed to load giftstore.txt!" << endl;

	while(file)
	{
		string price;
		string name;
		getline(file, price, ' ');
		getline(file, name, '\n');

		if(price != "") giftlist.push_back({name, std::stoi(price)});
	}
}

int main()
{
	vector<Gift> attempt;
	vector<Gift> best;

	load_giftlist();
	int budget = load_wishlist();

	gifts(attempt, best, giftlist, wishlist, 0, budget);

	show_giftlist(best);

	//                                                        
	int i;
	cin >> i;
}

