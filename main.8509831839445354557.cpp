#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <cstring>
#include <fstream>
#include <ostream>
#include <cstdlib>

using namespace std;

//                                                           

/*                                                                       
                  
                                                                       */

struct Item{
    string name;
    int worth;
};

istream& operator>> (istream& in, Item& item){
    //            
    assert(true);
    //             
    //
    char c;
    in >> item.worth;
    in.ignore(1);
    getline(in, item.name);
    return in;
}

ostream& operator<< (ostream& out, const Item item){
    //            
    assert(true);
    //             
    //                                                                 
    out << item.worth << " - " << item.name << endl;
    return out;
}

void skip_to_next_newline (istream& infile){
    //               
    assert (true) ;
/*                 
                                                                        
*/
    string remains ;
    getline (infile, remains) ;
}

void make_giftshop(ifstream& infile, vector<Item>& store){
    //            
    assert(true);
    //             
    //                                                                  
    infile.open("giftstore.txt");
    Item item;
    int i = 0;
    while(infile){
        infile >> item;
        store.push_back(item);
        i++;
    }
    infile.clear();
    infile.close();
}

int make_wish_vectors(ifstream& infile, vector <string>& names, string filename){
    //            
    assert(names.size() == 0);
    //             
    //                                                                         
    filename += ".txt";
    infile.open(filename.c_str());
    int budget;
    string name;
    int i = 0;
    infile >> budget;
    skip_to_next_newline(infile) ;
    while(infile){
        getline(infile, name);
        names.push_back(name);
        i++;
    }
    infile.clear();
    infile.close();
    return budget;
}

void give_prices(vector<string>& names, vector<Item>& store, vector<Item>& wishlist){
    //            
    assert(names.size() > 0 && wishlist.size() == 0);
    //             
    //                                                                                                                              
    //                                                                                                                                      
    Item item;
    int j = 0;
    for(int i = 0; i < names.size(); i++){
        for(int j = 0; j < store.size(); j++){
            if(names[i] == store[j].name){
                item = store[j];
                wishlist.push_back(item);
            }
        }
    }
}

void show(vector<Item>& gifts){
    //            
    assert(true);
    //             
    //                                    
    for(int i = 0; i < gifts.size(); i++){
        cout << gifts[i];
    }
}

void clear(vector<Item>& itemlist){
    //            
    assert(true);
    //             
    //                                                                                             
    while(itemlist.size() > 0){
        itemlist.pop_back();
    }
}

void clear(vector<string>& names){
    //            
    assert(true);
    //             
    //                                                                                              
    while(names.size() > 0){
        names.pop_back();
    }
}

/*                                                                       
                                                            
                                                                       */

int sum(vector<Item> wishlist, int from){
    //            
    assert(wishlist.size() >= from);
    //             
    //                                                                                            
    int sum = 0;
    for(int i = from; i < wishlist.size(); i++){
        sum += wishlist[i].worth;
    }
    return sum;
}

int sum(vector<Item> wishlist){
    //            
    assert(true);
    //             
    //                                                                         
    int sum = 0;
    for(int i = 0; i < wishlist.size(); i++){
        sum += wishlist[i].worth;
    }
    return sum;
}

void improve(vector<Item>& attempt, vector<Item>& best){
    //            
    assert(true);
    //             
    //                                                                                                                                      
    //                     
    if(sum(attempt) > sum(best)){
        best = attempt;
    }
}

int gifts(vector<Item>& wishlist, vector<Item>& best, int c, int budget, vector<Item>& attempt){
    //            
    assert(wishlist.size() > 0);
    //             
    //                                                                                                                                                                             
    //                                                         
    if(budget == 0){
        best = attempt;
        return 1;
    }else if(budget < 0){
        return 0;
    }else if(c >= wishlist.size()){
        improve(attempt, best);
        return 0;
    }else if((sum(attempt) + sum(wishlist, c)) <= sum(best)){
        return 0;
    }else{
        attempt.push_back(wishlist[c]);
        int with_c      = gifts(wishlist, best,
                                c+1, budget - wishlist[c].worth, attempt);
        attempt.pop_back();
        int without_c   = gifts(wishlist, best,
                                c+1, budget, attempt);
        return with_c + without_c;
    }
}

/*                                                                       
                       
                                                                       */

void execute(ifstream& infile, string name, vector<string>& names, vector<Item>& wishlist,vector<Item>& store, vector<Item>& attempt, vector<Item>& best){
    //            
    assert(!infile.is_open() && names.size() == 0 && wishlist.size() == 0 && store.size() > 0 && attempt.size() == 0 && best.size() == 0);
    //              
    //                                                                                                                                                  
    int consideration = 0;
    int budget = make_wish_vectors(infile, names, name);
    give_prices(names, store, wishlist);
    gifts(wishlist, best, consideration, budget, attempt);
    cout << "Name: " << name << endl;
    cout << "Budget: " << budget << endl;
    cout << "Sum of gifts: " << sum(best) << endl;
    show(best);
    cout << endl;
    clear(best);
    clear(attempt);
    clear(wishlist);
    clear(names);
}

int main()
{
    vector<string> names;
    vector<Item> wishlist;
    vector<Item> store;
    vector<Item> attempt;
    vector<Item> best;
    ifstream infile;
    make_giftshop(infile, store);

    string name = "Andrew";
    execute(infile, name, names, wishlist, store, attempt, best);

    name = "Belle";
    execute(infile, name, names, wishlist, store, attempt, best);

    name = "Chris";
    execute(infile, name, names, wishlist, store, attempt, best);

    name = "Desiree";
    execute(infile, name, names, wishlist, store, attempt, best);

    name = "Edward";
    execute(infile, name, names, wishlist, store, attempt, best);

    name = "Fabienne";
    execute(infile, name, names, wishlist, store, attempt, best);

    return 0;
}

