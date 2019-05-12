#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>

using namespace std;

//                             

struct Gift
{
    int price;
    string name;
};

struct Wishlist
{
    int budget;
    vector<string> gifts;
};

vector<Gift> giftstore;

void import_giftstore (ifstream& infile, vector<Gift>& giftstore)
{
//               
    assert(infile.is_open());
//                                                                                                           

    Gift tempgift;
    char whitespace;
    while (infile >> tempgift.price)
    {
        infile.get(whitespace);
        getline(infile, tempgift.name);
        giftstore.push_back(tempgift);
    }
}

void import_wishlists (ifstream& infile, Wishlist& wl)
{
//               
    assert(infile.is_open());
//                                                                                                                     

    int budget;
    string name;
    infile >> budget;
    wl.budget = budget;
    while (getline(infile, name))
        wl.gifts.push_back(name);
}

int find_price (string giftname, vector<Gift>& giftstore)
{
//               
    assert(giftstore.size() > 0);
//                                                                                    

    for (int i = 0; i < giftstore.size(); i++)
        if (giftname == giftstore[i].name)
            return giftstore[i].price;
}

Wishlist gifts (Wishlist& wish_list, Wishlist& gift_list, int i)
{
//               
    assert(wish_list.budget >= 0 && wish_list.gifts.size() > 0 && i >= 0);
//                                                                                                                                                                                         

    if (i == wish_list.gifts.size())
    {
        gift_list.budget -= find_price(wish_list.gifts[i-1], giftstore);
        gift_list.gifts.pop_back();
        return gift_list;
    }
    if (gift_list.budget < wish_list.budget)
    {
        gift_list.budget += find_price(wish_list.gifts[i], giftstore);
        gift_list.gifts.push_back(wish_list.gifts[i]);
        return gifts(wish_list, gift_list, ++i);
    }
    if (gift_list.budget > wish_list.budget && i < wish_list.gifts.size())
    {
        gift_list.budget -= find_price(wish_list.gifts[i-1], giftstore);
        gift_list.gifts.pop_back();
        return gifts(wish_list, gift_list, i);
    }
    else
    {
        gift_list.budget -= find_price(wish_list.gifts[i-1], giftstore);
        gift_list.gifts.pop_back();
        return gift_list;
    }
}

int main()
{
    ifstream infile ("giftstore.txt");
    import_giftstore(infile, giftstore);
    infile.close();

    infile.open("Andrew.txt");
    Wishlist Andrew;
    import_wishlists(infile, Andrew);
    infile.close();

    infile.open("Belle.txt");
    Wishlist Belle;
    import_wishlists(infile, Belle);
    infile.close();

    infile.open("Chris.txt");
    Wishlist Chris;
    import_wishlists(infile, Chris);
    infile.close();

    infile.open("Desiree.txt");
    Wishlist Desiree;
    import_wishlists(infile, Desiree);
    infile.close();

    infile.open("Edward.txt");
    Wishlist Edward;
    import_wishlists(infile, Edward);
    infile.close();

    infile.open("Fabienne.txt");
    Wishlist Fabienne;
    import_wishlists(infile, Fabienne);
    infile.close();

    cout << "Budget: " << Andrew.budget << endl;    //                                                                       

    Wishlist result = {0, {}};
    result = gifts(Andrew, result, 0);              //                                                                  

    cout << "Receipt: " << result.budget << endl
         << "\nList of bought gifts: " << endl;

    for (int i = 0; i < result.gifts.size(); i++)
        cout << result.gifts[i] << endl;

    return 0;
}

/*
                                 

          
                      
                                                    
                                      
                                                                        
                                                                           

                     

         
                      
                      
                         
                         

                     

         
                      
                                      
                                                     
                                         
                                          

                     

           
                      
                                          
                                          
                                                  
                                     
                                
                                 

                     

          
                      
                                         
                                         
                                                          
                                                  
                                                     
                                                   
                                                  
                              
                                               
                                                     
                                 
                           
                                      
                                        
                           
                                                                        
                                                                           
                                                                                    

                      

            
                      
                                     
                                      
                                        
                                       
                                                
                                             
                                               
                                                   
                                          
                                                     
                                                  
                                           

                      
*/

