#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>

using namespace std;

/*
                           
                      
*/

struct Product
{
 int price;
 string name;
};

int size(vector<Product>& store)
{
    return static_cast<int> (store.size());
}

int size(vector<string>& wishlist)
{
    return static_cast<int> (wishlist.size());
}

void read_wishlist (ifstream& lists, string name, int& budget, vector<string>& wishlist)
{
    //               
    assert(!lists.is_open());
    /*
                   
                                                  
    */
    lists.open(name);
    lists >> budget;
    lists.ignore();
    string temp;
    while (lists)
    {
        getline(lists, temp);
        if (temp != "")
        {
            wishlist.push_back(temp);
        }
    }
    lists.close();
}
void read_gift (ifstream& gift, vector<Product>& store)
{
    //              
    assert (!gift.is_open());
    /*
                   
                                                                                 
    */
    gift.open("giftstore.txt");
    int temp;
    string tem;
    while(gift)
    {
    gift >> temp;
    gift.ignore();
    getline(gift, tem);
    Product product ={temp,tem};
    store.push_back(product);
    }
    store.pop_back();
    gift.close();
}
bool instock(vector<Product>& a, string b, int& price)
{
    //              
    assert (true);
    /*
                   
                                                        
    */
    for (int i=0; i<size(a); i++)
    {
        if (b == a[i].name)
        {
            price = a[i].price;
            return true;
        }
    }
    return false;
}

int minimum (vector <string>& wishlist, vector <Product>& store, int c)
{
    //              
    assert (true);
    /*
                   
                                                          
    */
    int min=0;
    for (int i=c; i<size(wishlist); i++)
    {
        for (int j=0; j<size(store); j++)
        {
            if (wishlist[i] == store[j].name)
            {
                if (min == 0 || store[j].price < min)
                {
                    min = store[j].price;
                }
            }
        }
    }
    return min;
}
void improve (vector <string>& attempt, vector <string>& best, int budget, int& b)
{
    //              
    assert(true);
    /*
                                                                    
    */
    if (budget < b)
    {
        best = attempt;
        b = budget;
    }
}

void gifts(int budget, vector<Product>& store, vector<string>& attempt, vector<string>& wishlist, vector<string>& best, int c, int& b)
{
//               
assert(true);
/*
               
                                                                   
*/
if (budget < 0) {}
//                                                                                                                                        
else if (c >= size(wishlist)) {improve(attempt, best, budget, b);}

else {
    int price;
    int withc;
    if(instock(store, wishlist[c], price))
    {
    attempt.push_back (wishlist[c]);
    gifts( budget-price, store, attempt, wishlist, best, c+1, b);
    attempt.pop_back ();
    improve(attempt, best, budget, b);
    }
    gifts(budget, store, attempt, wishlist, best, c+1, b);
    improve(attempt, best, budget, b);
}
}
int main()
{
    ifstream lists;
    ifstream gift;
    int budget = 0;
    vector<string> wishlist;
    vector<Product> store;
    vector<string> attempt;
    vector<string> best;
    read_wishlist(lists, "Fabienne.txt", budget, wishlist);
    read_gift (gift, store);
    int b = budget;
    int c = 0;
    gifts(budget, store, attempt, wishlist, best, c, b);
    for (int i=0; i<size(best); i++)
    {
        cout << best[i] << endl;
    }
    cout << b << endl;

}
/*
                                           
                                  
                                
                      
                                
                                            
                              
                  
                                        
                           
                       
                          
                                                         
                                               
                                  
                     
                                                                  
                                                                     
                                                
                                  
                                     
                      

*/

