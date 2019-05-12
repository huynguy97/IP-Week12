#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

struct gift
{
    int price;
    string name;
};

gift get_product (istream& input)
{
    assert(true);
    //                                                                                           
    int n;
    string s;
    input >> n;
    input.get();
    getline(input, s);
    return (gift{n, s});
}

void read_files (int& budget, vector<gift>& giftstore, vector<gift>& wishlist, istream& store, istream& wish)
{
    assert(true);
    //                                                                            
    giftstore.erase(giftstore.begin(), giftstore.end());
    wishlist.erase(wishlist.begin(), wishlist.end());
    gift g;
    string s;
    g = get_product(store);
    while (store)
    {
        giftstore.push_back(g);
        g = get_product(store);
    }
    wish >> budget;
    getline(wish, s);
    while (wish)
    {
        wishlist.push_back(gift{0, s});
        getline(wish, s);
    }
}

int member_gift(gift& g, vector<gift> gs)
{
    assert(true);
    //                                                                  
    for (int i=0; i<gs.size(); i++)
        if (g.name == gs[i].name)
            return gs[i].price;
    return 0;
}

void compress_wishlist (vector<gift> giftstore, vector<gift>& wishlist)
{
    assert(true);
    //                                                                        
    //                                                        
    for (int i=0; i<wishlist.size(); i++)
    {
        int a = member_gift(wishlist[i], giftstore);
        if (a > 0)
            wishlist[i].price = a;
        else
        {
            wishlist.erase(wishlist.begin()+i);
            i--;
        }
    }
}

int calc_price (vector<gift>gifts, vector<bool>get)
{
    assert(gifts.size() == get.size());
    //                                                                                                         
    int n = 0;
    for (int i=0; i<gifts.size(); i++)
        if (get[i])
            n += gifts[i].price;
    return n;
}

int gen_gifts (int budget, vector<gift> gifts, int pos, vector<bool>& get)
{
    assert(budget >= 0 && pos >= 0 && gifts.size() == get.size());
    //                                                                                            
    //                                     
    if (pos >= gifts.size())
        return  calc_price(gifts, get);
    int a=0,b=0;
    vector<bool> backup;
    if (budget - gifts[pos].price >= 0)
    {
        get[pos] = true;
        a = gen_gifts(budget-gifts[pos].price, gifts, pos+1, get);
        backup = get;
    }
    get[pos] = false;
    b = gen_gifts(budget, gifts, pos+1, get);
    if (a > b)
        for (int p=0; p<get.size(); p++)
            get[p] = backup[p];
    backup.erase(backup.begin(), backup.end());
    return calc_price(gifts, get);
}

void gifts (int budget, vector<gift>& wishlist)
{
    assert (budget >= 0);
    //                                                                                                  
    vector<bool> get;
    for (int i=0; i<wishlist.size(); i++)
        get.push_back(false);
    gen_gifts(budget, wishlist, 0, get);
    for (int j=0; j<wishlist.size(); j++)
        if (!get[j])
        {
            wishlist.erase(wishlist.begin()+j);
            get.erase(get.begin()+j);
            j--;
        }
}

int main()
{
    int budget;
    vector<gift> giftstore, wishlist;
    vector<string> lists;
    lists.push_back("Andrew");
    lists.push_back("Belle");
    lists.push_back("Chris");
    lists.push_back("Desiree");
    lists.push_back("Edward");
    lists.push_back("Fabienne");
    ifstream store, wish;
    ofstream ofile;
    ofile.open("output.txt");
    for (int i=0; i<lists.size(); i++)
    {
        store.open("giftstore.txt");
        wish.open((lists[i] + ".txt"));
        read_files(budget, giftstore, wishlist, store, wish);
        compress_wishlist(giftstore, wishlist);
        gifts(budget, wishlist);
        ofile << lists[i] << endl;
        for (int j=0; j<wishlist.size(); j++)
            {
                ofile << wishlist[j].price << "\t";
                ofile << wishlist[j].name << endl;
            }
        ofile << endl;
        store.close();
        wish.close();
    }
}

/*
      
   	                        
    	                          

     
   	           
   	              
   	                        

     
   	                           
    	                                    
   	          

       
   	                   
   	                        
    	                          
    	                  

      
     	                
    	                                 
     	                   
    	             
    	                          
   	                                                             
   	                                                                      

        
     	                       
    	                          
    	                             
    	              
*/

