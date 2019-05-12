/*                                                                    
                                                                      
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

struct Gift
{
    int price;
    string category;
    string name;
};

struct Store
{
    int price;
    string type;
    string name;
};

int storecount = 0;
int listcount = 0;
int f_budget;
vector<Store> current;
vector<Store> best;
vector<Store> wish_list;
vector<Gift> giftstore;

int size (vector<Store>& wish_list)
{//               
    assert (true) ;
//                                                           
    return wish_list.size() ;
}

int sum(vector<Store>& wish_list, int from)
{//               
    assert(from >= 0 && from <= size(wish_list));
//                 
//                                                                                                            
    int sum = 0;
    for (int i = from; i < size(wish_list); i++)
        sum += wish_list[i].price;
    return sum;
}

int sum(vector<Store>& wish_list)
{
    return sum (wish_list, 0) ;
}

void improve(vector<Store>& current, vector<Store>& best)
{//               
    assert(true);
//                 
//                                                                 
    if (sum(current) > sum (best))
        best = current;
}

void show(vector<Store>& wish_list)
{//               
    assert(true);
//                                                                                                
	const int NO_OF_ELEMS = size(wish_list);
	cout << "{";
	if (NO_OF_ELEMS > 0)
	{
		for (int i = 0 ; i < NO_OF_ELEMS-1 ; i++)
			cout << wish_list[i].name << ", " << endl;
		cout << wish_list[NO_OF_ELEMS-1].name << endl;
	}
	cout << "}" << endl;
}

int gifts(vector<Store>& current, vector<Store>& best, vector<Store>& wish_list, int c, int budget)
{//               
    assert (0 <= c && c <= size(wish_list)) ;
//                 
//                                                                           
//                                                                     
//                                                                           
//                                  
	if (budget == 0) {
        best = current;
        return 1;
    } else if (budget < 0) {
        return 0;
    } else if (c >= size(wish_list)) {
        improve (current, best);
        return 0;
    } else {
		current.push_back(wish_list[c]);
		const int WITH_C = gifts(current, best, wish_list, c+1, budget - wish_list[c].price);
		current.pop_back () ;
		const int WITHOUT_C = gifts (current, best, wish_list, c+1, budget) ;
        return WITH_C + WITHOUT_C;
	}
}

void compare_vector (vector<Gift>& giftstore, vector<Store>& wish_list)
{//               
    assert(true);
//                 
//                                                                             
//                 
    for(int i = 0; i < listcount; i++){
        for(int j = 0; j < storecount; j++){
            if(giftstore[j].name == wish_list[i].name){
                wish_list[i].price = giftstore[j].price;
            }
        }
    }
}

void skip_to_next_newline (istream& infile)
{//               
    assert (true);
//                 
//                                                                      
    string remains;
    getline (infile, remains);
}

istream& operator>> (istream& infile, Gift& giftstore)
{//               
    assert (true);
//                 
//                                              
    infile >> giftstore.price;
    infile >> giftstore.category;
    getline(infile, giftstore.name);

    return infile;
}

istream& operator>> (istream& infile, Store& gift)
{//               
    assert (true);
//                 
//                                              
    infile >> gift.type;
    getline(infile,gift.name);

    return infile;
}

ostream& operator<< (ostream& out, Gift& giftstore)
{//               
    assert (true);
//                 
//                                              
    out << giftstore.price << ", " << giftstore.category ;
    out << ", " << giftstore.name << endl;
}

ostream& operator<< (ostream& out, Store& wish_list)
{//               
    assert (true);
//                 
//                                              
    out << wish_list.type << ", " << wish_list.name << endl;
}

void read_giftstore(ifstream& infile, vector<Gift>& giftvect)
{//              
    assert(infile.is_open());
//                
//                                              
    do {
        Gift item;
        infile >> item;
        if(infile)
        giftvect.push_back(item);
        storecount++;
    }
    while(infile);
}

void read_wishlist(ifstream& infile, vector<Store>& wish_list)
{//              
    assert(infile.is_open());
//                
//                                               
    infile >> f_budget;
    skip_to_next_newline(infile);
    do {
        Store item;
        infile >> item;
        if(infile) {
            wish_list.push_back(item);
        }
        listcount++;
    }
    while(infile);
}

int read_file(string filename)
{//               
    assert(true);
//                 
//                                     
    ifstream wish (filename.c_str());
    if (!wish){
        cout << "Could not open file!" << endl;
        return -1;
    }
    read_wishlist(wish, wish_list);
}

int main() {
    string filename;
    ifstream giftfile;
    giftfile.open("giftstore.txt");
    read_giftstore(giftfile, giftstore);
    cout << "What is the name of your wishlist file?" << endl;
    cin >> filename;
    int i = read_file(filename);
    compare_vector(giftstore, wish_list);
    giftfile.close();
    int no_of_solutions = gifts(current, best, wish_list, 0, f_budget);
    show(best);
    return 0;
}

