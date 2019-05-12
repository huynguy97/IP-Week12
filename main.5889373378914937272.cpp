//              
//                            

#include <iostream>
#include <fstream>
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

struct Gift
{
   int prize;
   string name;
};

struct WishList
{
    int budget;
    vector<string> wishes;
};

vector<Gift> giftShop;

istream& operator>> (istream& infile, Gift& gift)
{//               
    assert (true) ;
/*                 
                                
*/
    infile >> gift.prize;
    char c;
    infile.get(c);
    getline(infile, gift.name);
    return infile ;
}

ostream& operator<< (ostream& out, const Gift gift)
{//               
    assert (true) ;
/*                 
                                       
*/
    out << gift.prize << " | " << gift.name;
	return out ;
}

int readShop(vector<Gift>& shop, string filename)
{//               
    assert (true) ;
/*                 
                                                        
                                      
*/
    int amountOfGifts = 0;
    Gift a;
    ifstream shopDesc (filename.c_str());
    if(!shopDesc.is_open()) cout << "File could not be found!" << endl;

    while(shopDesc)
    {
        shopDesc >> a;
        shop.push_back(a);
        amountOfGifts++;
    }
    shopDesc.close();
    if(amountOfGifts > 1) shop.pop_back();
    return amountOfGifts-1;
}

void showGiftList(vector<Gift>& shop)
{//               
    assert (true) ;
/*                 
                                          
*/
    for(int i = 0; i < shop.size(); i++)
        cout << shop[i] << endl;
}

int readWishList(WishList& wl, string filename)
{//               
    assert (true) ;
/*                 
                                                    
                                       
*/
    int amountOfWishes = 0;
    string wish;
    ifstream wishListDesc (filename.c_str());
    if(!wishListDesc.is_open()) cout << "File could not be found!" << endl;

    wishListDesc >> wl.budget;
    getline(wishListDesc, wish);
    while(wishListDesc)
    {
        getline(wishListDesc, wish);
        wl.wishes.push_back(wish);
        amountOfWishes++;
    }
    if(amountOfWishes > 1) wl.wishes.pop_back();
    return amountOfWishes-1;
}

void showWishList(WishList wl)
{//               
    assert (true) ;
/*                 
                                       
*/
    cout << "Wishlist is shown:" << endl;
    cout << "Budget: " << wl.budget << endl;

    for(int i = 0; i < wl.wishes.size(); i++)
        cout << wl.wishes[i] << endl;

}

bool available(const vector<Gift>& shop, const string wish, Gift& foundGift)
{//               
    assert (true) ;
/*                 
                                                                            
                                                                 
*/
    for(int i = 0; i < shop.size(); i++)
        if(wish == shop[i].name)
        {
            foundGift = shop[i];
            return true;
        }
    return false;
}

int gifts(const vector<Gift>& shop, const vector<string>& wishes, int g, int budget, vector<Gift>& attempt)
{
    //               
    assert (true) ;
/*                 
                                                                                                                        
                                                                                        
*/
    Gift current;
    while(!available(shop, wishes[g], current) && g < wishes.size())
        g++;

    if(budget < 0) return 2147483647;
    if(g >= wishes.size()) return budget;

    vector<Gift> attemptWithCurrent;
    vector<Gift> attemptWithoutCurrent;
    int withCurrent = gifts(shop, wishes, g+1, (budget - current.prize), attemptWithCurrent);
    int withoutCurrent = gifts(shop, wishes, g+1, budget, attemptWithoutCurrent);

    if(withCurrent < withoutCurrent)
    {
        attempt = attemptWithCurrent;
        attempt.push_back(current);
        return withCurrent;
    }
    else
    {
        attempt = attemptWithoutCurrent;
        return withoutCurrent;
    }

}

int main()
{
    readShop(giftShop, "giftstore.txt");
    //                       
    WishList wl1;
    readWishList(wl1, "Fabienne.txt");
    //                  
    vector<Gift> solution;
    int i = gifts(giftShop, wl1.wishes, 0, wl1.budget, solution);
    cout << (wl1.budget - i) << " ct of " << wl1.budget << " ct are used for the following gifts:"<< endl;
    showGiftList(solution);
    return 0;
}
/*
                                

       
                                                    
                                 
                              

      
                                                    
                              
                    
                 

      
                                                    
                
                                           
                                 

        
                                                    
                         
                                 
                              
                         

       
                                                      
                                                                            
                                                                   
                                 
                    
                           
                                        
                        

         
                                                      
                     
                                    
                                 
                               

*/

