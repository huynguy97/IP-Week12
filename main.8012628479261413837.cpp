#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include<fstream>

using namespace std;

//                                 

/*       

                                                                                                                                                     

                                                                                                                                             
                                                                                                                                                                    
                                                                                                                                                                                             
                                                                                                                                                    

                                                                                                                                                 
                                                                                                                    

                                                          

       
*/

struct Gift
{
    int price;              //              
    string name;            //             
};

vector<Gift> best;
vector<Gift> attempt;
vector<Gift> store;
vector<Gift> wishlist;

int size (vector<Gift>& v)
{
    //                
    assert (true);
    //                 
    //                                                       
    return static_cast<int> (v.size());
}

istream& operator>> (istream& infile, Gift& gift)
{
    //               
    assert(true);
    /*                
                                  */
    infile >> gift.price;
    infile.ignore(1, '\n');
    getline(infile, gift.name);
    return infile;
}

ostream& operator<< (ostream& out, Gift present)
{
    //              
    assert(true);
    /*                
                                                      */

    cout << "Price: " << present.price << ".\tName: " << present.name << '.' << endl;
    return out;
}

int sum (vector<Gift>& a)
{
    //              
    assert (size(a) >= 0);
    /*                
                                                              */

    int total = 0;
    Gift current_gift;
    for (int i = 0; i < size(a); i++)
    {
        current_gift = a[i];
        total = total + current_gift.price;
    }
    return total;
}

void improve (vector<Gift>& a, vector<Gift>& b)
{
    //               
    assert (size(a) >= 0 && size(b) >= 0);
    /*                
                                                                */

    if (sum(a) > sum(b))
        b = a;
}

//                                                                                  
int gifts (vector<Gift>& attempt, vector<Gift>& best, vector<Gift>& wishlist, int c, int budget)
{
    //               
    assert(size(attempt) >= 0 && size(best) >= 0 && size(wishlist) >= 0 && c >= 0 && c <= size(wishlist));
    /*                
                                                                                                                   
                                                  */
    if(budget == 0)
    {
        best = attempt;
        return 1;
    }

    else if(budget < 0)
    {
        return 0;
    }

    else if(c >= size(wishlist))
    {
        improve(attempt, best);
        return 0;
    }

    else
    {
        Gift current_gift = wishlist[c];                        //                                                                                                               
        attempt.push_back(current_gift) ;                       //        
        int with_c = gifts(attempt, best, wishlist, c+1, budget - current_gift.price);
        attempt.pop_back() ;                                    //       

        int without_c = gifts(attempt, best, wishlist, c+1, budget) ;
        return with_c + without_c;
    }
}

bool read_giftstore (vector<Gift>& storage)
{
    //               
    assert (size(storage) >= 0);
    /*                
                                                                            */
    cout << "Please enter a store filename, including file extension .txt. The contents are stored in vector store." << endl;
    string filename;
    cin >> filename;
    ifstream store_in (filename.c_str());

    if (!store_in.is_open())
    {
        cout << "ERROR: something went wrong. Did you enter an invalid filename?" << endl;
        return false;
    }

    Gift present;
    store_in >> present;

    while(store_in)
    {
        storage.push_back(present);
        store_in >> present;
    }
    store_in.clear();
    store_in.close();
    if (!store_in)
    {
        cout << "WARNING: File was not closed properly." << endl;
        return false;
    }
    cout << "Done reading" << endl;
    return true;
}

//                                                                                                         
int in_stock (vector<Gift>& storage, string present)
{
    //               
    assert(size(storage) >= 0);
    /*                
                                                                                                                 */

    Gift test;
    for (int i = 0; i < size(storage); i++)
    {
        test = storage[i];
        if (test.name == present)
            return i;
    }
    return -1;
}

bool read_wishlist (vector<Gift>& shop, vector<Gift>& wishlist, int& budget)
{
    //               
    assert (size(wishlist) >= 0 && size(shop) >= 0);
    /*                
                                                                                                                                       */
    cout << "WARNING: It is advised to have already created your shop before reading wishlists." << endl;
    cout << "Please enter a wishlist filename, including file extension .txt. The contents are stored in vector wishlist." << endl;
    string filename;
    cin >> filename;
    ifstream wish_in (filename.c_str());

    if (!wish_in.is_open())
    {
        cout << "ERROR: something went wrong. Did you enter an invalid filename?" << endl;
        return false;
    }

    wish_in >> budget;
    wish_in.ignore(1, '\n');
    string name;
    getline(wish_in, name);

    while(wish_in)
    {
        int stock = in_stock(shop, name);
        if (stock >= 0)
            wishlist.push_back(shop[stock]);        //                                                                                          
        getline(wish_in, name);
    }
    wish_in.clear();
    wish_in.close();
    if (!wish_in)
    {
        cout << "WARNING: File was not closed properly." << endl;
        return false;
    }
    cout << "Done reading" << endl;
    return true;
}

void show_vector (vector<Gift>& a)
{
    //              
    assert(size(a) >= 0);
    /*                
                                                                                                                          */

    int total = 0;
    Gift b;
    for (int i; i < size(a); i++)
    {
        b = a[i];
        cout << b;
        total = total + b.price;
    }
    cout << "Total value: " << total << '.' << endl;        //                                              
}

int main()
{
    int budget = 0;
    if (!read_giftstore(store) || !read_wishlist(store, wishlist, budget))
    {
        cout << "ERROR: program failure. Terminating" << endl;
        return -1;
    }

    gifts(attempt, best, wishlist, 0, budget);
    show_vector(best);
    return 0;
}

/*         

                                                

                     
                                               
                                                 
                  

                    
                                  
                                     
                                               
                  

                    
                                               
                                             
                                 
                  

                      
                                         
                                          
                                      
                                         
                  

                      
                                                           
                                                              
                                                 
                                    
                                                                                 
                                                                                    
                   

                        
                                              
                                                 
                                                    
                                     
                   
*/

