#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <string>
#include <cassert>

using namespace std;
//                        

struct GiftStore{
    int cost_gift;
    string gift;
};

struct WishList{
    string gift;
};

istream& operator>> (istream& infile, GiftStore& g){
    infile >> g.cost_gift;
    infile.ignore(1);
    getline(infile, g.gift);
    return infile;
}

istream& operator>> (istream& infile, WishList& w){
    getline(infile, w.gift);
    return infile;
}

ostream& operator<< (ostream& out, GiftStore w){
    out << w.cost_gift << ", ";
    out << w.gift;
    out << endl;
    return out;
}

void show(vector<string> gifts){
    //             
    assert(true);
    //              
    //                                                                
    const int NO_OF_ELEMENTS = gifts.size();
	cout << "{" ;
    if(NO_OF_ELEMENTS > 0){
        for(int i = 0; i < NO_OF_ELEMENTS-1; i++){
            cout << gifts[i] << ", ";
        }
        cout << gifts[NO_OF_ELEMENTS-1];
	cout << "}" << endl;
    }
}
int gifts(vector<WishList> wishes, vector<int>& gifts_costs, vector<string>& temporary_solution, vector<string>& best_solution, int amount_gifts, int budget, int& best_budget, int bg){
    //             
    assert(bg > 0;
    //              
    //                                                                                                                                                                          
    //                                                                                                                                                                         
    if(budget >= 0 && budget <= bg/10){
        if(budget < best_budget){
            best_solution = temporary_solution;
            best_budget = budget;
        }
        return 1;
    }

    if(budget < 0){
        return 0;
    }

    if(amount_gifts <= 0 && budget >= 1){
        return 0;
    }
    temporary_solution.push_back(wishes[amount_gifts-1].gift);
    int a = gifts(wishes, gifts_costs, temporary_solution, best_solution, amount_gifts - 1, budget - gifts_costs[amount_gifts-1], best_budget,bg);
    temporary_solution.pop_back();
    int b = gifts(wishes, gifts_costs, temporary_solution, best_solution, amount_gifts - 1, budget, best_budget,bg);
    return a+b;
}

bool open_file(ifstream& infile, string filename)
{
    //             
    assert(true);
    //              
    //             
    infile.open(filename.c_str());
    return infile.is_open();
}

void giftstore_to_vector(ifstream& infile, vector<GiftStore>& store)
{
    //             
    assert(true);
    //              
    //                                                                                    
    GiftStore item;
    while(infile)
    {
        infile >> item;
        store.push_back(item);
    }
}

void wishlist_to_vector(ifstream& infile, vector<WishList>& wl)
{
    //             
    assert(true);
    //              
    //                                                                                  
    WishList w;
    while(infile)
    {
        infile >> w;
        wl.push_back(w);
    }
}

int main()
{
    ifstream infile;
    ifstream infile2;

    vector<int> gift_costs;
    if(open_file(infile, "giftstore.txt")){
        cout << "Giftstore succesfully openend" << endl;
    }

    if(open_file(infile2, "Fabienne.txt")){
        cout << "Wishlist succesfully openend" << endl;
    }

    vector<GiftStore> store;
    vector<WishList> wlist;
    vector<string> Final_Wishlist;

    giftstore_to_vector(infile, store);
    wishlist_to_vector(infile2, wlist);

    vector<string> solution;
    vector<string> best;

    for(int i = 1; i <= wlist.size(); i++){
        for(int j = 0; j < store.size(); j++){
            if(store[j].gift == wlist[i].gift){
                gift_costs.push_back(store[i].cost_gift);
            }
        }
    }

    int budget = stoi(wlist[0].gift);

    cout << gifts(wlist, gift_costs, solution, best, gift_costs.size(), budget, budget, budget) << " Possible combinations" << endl;
    show(best);

    return 0;
}

//                                                                                                                                                                                                      
//                                       
//                                                                                        
//                                                                                                                                                                               
//      
//        

