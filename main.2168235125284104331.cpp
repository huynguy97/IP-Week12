#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>

using namespace std;
/*
             

                            
                       
*/

struct Giftstore
{
    int price;
    string item;
};

void show_giftset(vector<Giftstore>& giftset)
{
    //              
    assert(true);
    /*                                                                              
    */
    int i;
    int length = giftset.size();
    for(i = 0; i < length-1; i++)
        cout << giftset[i].item << '\n';
    cout << giftset[i].item;
}

void show_wishlist(vector<string>& wishlist)
{
    //              
    assert(true);
    /*                                                                               
    */
    int i;
    int length = wishlist.size();
    for(i = 0; i < length-1; i++)
        cout << wishlist[i] << '\n';
    cout << wishlist[i];
}

bool in_giftstore(string gift, vector<Giftstore>& giftstore, int& price)
{
    //              
    assert(true);
    /*                                                                                 
    */
    int length = giftstore.size();
    for(int i = 0; i < length; i++)
    {
        if(gift == giftstore[i].item)
        {
            price = giftstore[i].price;
            return true;
        }
    }
    return false;
}

void copy_giftset(vector<Giftstore>& a, vector<Giftstore>& b)
{
    //              
    assert(true);
    /*                                                                                                            
    */
    int length_a = a.size();
    for(int i = 0; i < length_a; i++)
        a.pop_back();
    int length_b = b.size();
    for(int i = 0; i < length_b; i++)
        a.push_back(b[i]);
}

int sum(vector<Giftstore> a)
{
    //              
    assert(true);
    /*                                                                              
    */
    int sum = 0;
    int length = a.size();
    for(int i = 0; i < length; i++)
        sum = sum + a[i].price;
    return sum;
}

void improve(vector<Giftstore>& a, vector<Giftstore>& b)
{
    //              
    assert(true);
    /*                                                                                                                     
                  
    */
    if(sum(a) > sum(b))
        copy_giftset(b, a);
}

int gifts(int budget, vector<string>& wishlist, int i, vector<Giftstore>& giftstore, vector<Giftstore>& giftset, vector<Giftstore>& best)
{
    //              
    assert(i >= 0 && i <= wishlist.size());
    /*                                                                                                                       
                                                                                                                             
                                                                                                
                                                                                                      
    */
    if(budget == 0)
    {
        copy_giftset(best, giftset);
        return 1;
    }
    else if(budget < 0)
        return 0;
    else if(i == wishlist.size())
    {
        improve(giftset, best);
        return 0;
    }
    else
    {
        int price;
        if(in_giftstore(wishlist[i], giftstore, price))
        {
            Giftstore gift = {price, wishlist[i]};
            giftset.push_back(gift);
            int with_gift = gifts(budget - price, wishlist, i+1, giftstore, giftset, best);
            giftset.pop_back();
            int without_gift = gifts(budget, wishlist, i+1, giftstore, giftset, best);
            return with_gift + without_gift;
        }
        else
            return gifts(budget, wishlist, i+1, giftstore, giftset, best);
    }
}

istream& operator>>(istream& in, Giftstore& giftstore)
{
    //              
    assert(true);
    /*                                                                        
    */
    in >> giftstore.price;
    in.get();
    getline(in, giftstore.item, '\n');
    return in;
}

void read_giftstore(string filename, vector<Giftstore>& giftstore)
{
    //              
    assert(true);
    /*                                                                                       
    */
    ifstream giftstore_file (filename);
    Giftstore item;
    if(giftstore_file)
    {
       while(giftstore_file)
       {
           giftstore_file >> item;
           giftstore.push_back(item);
       }
    }
    else
        cout << "The giftstore file could not be opened...";
}

void read_wishlist(string filename, int& budget, vector<string>& wishlist)
{
    //              
    assert(true);
    /*                                                                                      
    */
    ifstream wishlist_file (filename);
    wishlist_file >> budget;
    wishlist_file.get();
    string item;
    if(wishlist_file)
    {
        while(wishlist_file)
        {
            getline(wishlist_file, item, '\n');
            wishlist.push_back(item);
        }
    }
    else
        cout << "The wishlist file could not be opened...";
}

int main()
{
    cout << "Hello world!" << endl;
    string giftstore_file;
    cout << "Please enter the filename of the giftstore: ";
    cin >> giftstore_file;
    string wishlist_file;
    cout << "Please enter the filename of the wishlist: ";
    cin >> wishlist_file;
    vector<Giftstore> giftstore;
    read_giftstore(giftstore_file, giftstore);
    vector<string> wishlist;
    int budget;
    read_wishlist(wishlist_file, budget, wishlist);
    /*                               
                            
                                    
                            */
    vector<Giftstore> giftset;
    vector<Giftstore> best;
    gifts(budget, wishlist, 0, giftstore, giftset, best);
    cout << "\nThe best giftset is:\n\n";
    show_giftset(best);
    cout << "\n";
    return 0;
}

/*
        

       
                    
                        
                          

      
                    
           
              
                        

      
                    
                        
                      
          

        
                    
                  
                   
               
                  

       
                    
                                    
                                       
                          
             
                                                          
                                                             

         
                    
                       
                          
                             
              
*/

