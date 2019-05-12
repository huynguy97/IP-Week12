#include <iostream>
#include<cassert>
#include<string>
#include<cmath>
#include<vector>
//                                
//                         

using namespace std;

struct wlist
    {
        string gift;
        int price;
    };

bool is_in_list(string a, vector<wlist>& store)
{
    //            
    assert(true);
    //                                                      
    for(int unsigned i=0; i< store.size(); i++)
    {
        if(a==store[i].gift)
            return true;
    }
    return false;
}

int get_index(string a , vector<wlist>& store)
{
    //            
    assert(true);
    //                                                          

    for(int unsigned i=0; i< store.size(); i++)
    {
        if(a==store[i].gift)
            return i;
    }

    return -1;
}

void show_solution(vector<string>& solution)
{
    //            
    assert(true);
    //                                                    

    for(int unsigned i=0;i<solution.size();i++)
    {
        cout<<solution[i]<<", ";
    }
}

void gifts(vector<string>& wishlist, vector<wlist>& store, vector<string>& solution,vector<string>& best, int unsigned budget,int unsigned index)
{
    //            
    assert(index>=0 && index <= wishlist.size());
    //                                                                                             
    int j=get_index(wishlist[index],store);

    if(is_in_list(wishlist[index],store) && budget>store[j].price)
    {
        solution.push_back(wishlist[index]);
        gifts(wishlist, store, solution,best,budget-store[j].price,index+1);
        //              
    }

    else if(index==wishlist.size())
    {
        show_solution(solution);
    }

    else
    {
        show_solution(solution);
        gifts(wishlist,store,solution,best,budget,index+1);
    }
}

ostream& operator<< (ostream& out, const wlist store)
{
    //             
    assert(true);
    //                                                       
    out<<store.gift<<" "<<store.price<<endl;
}

int main()
{

    vector<int> price={10,20,30};
    vector<string> store_items = {"book","car","pen"};
    vector<wlist> store;
    wlist tmp;
    for(int k=0;k<store_items.size();k++)
    {
        tmp.gift=(store_items[k]);
        tmp.price=price[k];
        store.push_back(tmp);
    }

    vector<string> wishlist={"book","car"};
    vector<string> solution;
    vector<string> best;
    gifts(wishlist,store,solution,best,30,0);
    return 0;
}

