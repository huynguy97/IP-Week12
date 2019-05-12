#include <iostream>
#include <vector>
#include <cassert>
#include <cstring>
#include <fstream>

/*                                                                                                                                                                                                                                                                                              
                        
       
                       
                         
      
           
              
                       
      
                       
                       
         
        
                  
                   
               
                
      
                                     
                                   
                                      
                         
                 
                                                         
                                                            
         
                     
                         
                                   
                                
                                      
                                        
                              
            
*/

using namespace std;

struct Item {int prize1; string type1; string name1;};
struct Wish {string type2; string name2;};
struct Wishlist {int prize3; string name3;};

vector<Item> store;
vector<Wish> wishlist;
vector<string> shoppinglist;
vector<string> best_shoppinglist;
vector<Wishlist> better_wishlist;

int find_present (string name)
{
    for (int k = 0; k < store.size(); k++)
        if (store[k].name1 == name)
            return store[k].prize1;
}

void improve_wishlist ()
{
    for (int i = 0; i < wishlist.size(); i++)
        better_wishlist.push_back({find_present(wishlist[i].name2), wishlist[i].name2});
}

void gifts (vector<Wishlist>& better_wishlist, vector<string>& shoppinglist, vector<string>& best_shoppinglist, int& best_available_budget, int available_budget, int c)
{
    //    
    assert(c >= 0);
    //                                                                                                             
    //           
    if (available_budget < best_available_budget && available_budget>=0)
    {
        best_shoppinglist = shoppinglist;
        best_available_budget = available_budget;
    }
    if ((available_budget < 0) || (c == better_wishlist.size()-1))
        return;
    //                
    else
    {
        shoppinglist.push_back(better_wishlist[c].name3);
        available_budget -= better_wishlist[c].prize3;
        //            
        gifts(better_wishlist, shoppinglist, best_shoppinglist, best_available_budget, available_budget, c+1);
        //               
        shoppinglist.pop_back();
        //                                              
        gifts(better_wishlist, shoppinglist, best_shoppinglist, best_available_budget, available_budget + better_wishlist[c].prize3, c+1);
        return;
    }

}

void read_store_file (ifstream& infile)
{
    int prizetag;
    string word;
    string item;
    while (infile)
    {
        infile >> prizetag;
        infile.ignore();
        infile >> word;
        infile.ignore();
        getline(infile, item);
        store.push_back({prizetag, word, item});
    }
}

int read_wishlist_file (ifstream& infile)
{
    int budget;
    infile >> budget;
    string word;
    string item;
    while (infile)
    {
        infile >> word;
        infile.ignore();
        getline(infile, item);
        wishlist.push_back({word, item});
    }
    return budget;
}

int main()
{
    ifstream store_file("giftstore.txt");
    if (!store_file.is_open())
        cout << "Error: file not found. (101)" << endl;
    read_store_file(store_file);
    store_file.close();

    string wishlist_name;
    cout << "Please input your filename (including .txt)" << endl;
    cin >> wishlist_name;

    ifstream wishlist_file(wishlist_name.c_str());
    if (!wishlist_file.is_open())
        cout << "Error: file not found. (404)" << endl;
    int start_budget;
    start_budget = read_wishlist_file(wishlist_file);
    wishlist_file.close();

    improve_wishlist();

    int best_available_budget = start_budget;
    gifts(better_wishlist, shoppinglist, best_shoppinglist, best_available_budget, start_budget, 0);

    for (int i = 0; i < best_shoppinglist.size(); i++)
        cout << best_shoppinglist[i] << endl;
    return 0;
}

