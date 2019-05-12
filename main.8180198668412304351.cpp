#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

//                        

using namespace std;

struct Gift
{
    int price;
    string gift;
};

int totalbudget;
vector<Gift> emptyvector;
vector<Gift> database;

int findValue(string name)
{
    //               
    assert(true);
    //               
    //                                                                                                   
    for(int i=0; i < database.size(); i++)
    {
        if (database.at(i).gift == name)
            return database.at(i).price;
    }
    return 100000000; //                      
}

vector<Gift> openWishList(char* filename)
{
    //               
    assert(true);
    //               
    //                                                    
    vector<Gift> wishlist;
    ifstream infile (filename);
    if (!infile)
    {
        cout << "Was not able to open " << filename << endl;
    }
    infile >> totalbudget;
    while(!infile.eof())
    {
        Gift temp;
        getline(infile, temp.gift);
        temp.price = findValue(temp.gift);
        wishlist.push_back(temp);
    }
    infile.close();
    return wishlist;
}

istream& operator>> (istream& infile, Gift& gift)
{
    //               
    assert(true);
    //               
    //                                                 
    int price;
    string temp;
    infile >> price;
    getline(infile, temp);
    gift.price = price;
    gift.gift = temp.substr(temp.find(" ")+1,temp.size());
}

vector<Gift> giftstore()
{
    //               
    assert(true);
    //               
    //                                                              
    vector<Gift> giftstore;
    ifstream infile("giftstore.txt");
    while(!infile.eof())
    {
        Gift gift;
        infile >> gift;
        giftstore.push_back(gift);
    }
    infile.close();
    return giftstore;
}

int totalPrice(vector<Gift> giftlist)
{
    //               
    assert(true);
    //               
    //                                                      
    int price = 0;
    for(int i = 0; i < giftlist.size(); i++)
    {
        price += giftlist[i].price;
    }
    return price;
}

vector<Gift> gifts(vector<Gift>& wishlist, int budget, int gift, vector<Gift> giftlist)
{
    //               
    assert(true);
    //               
    //                                                                             
    //                                                                                    
    if      (budget == 0)
    {
        return giftlist;
    }
    else if (budget < 0)
    {
        return emptyvector;
    }
    else if (gift >= wishlist.size())
    {
        return giftlist;
    }
    else
    {
        vector<Gift> a = gifts(wishlist, budget, gift+1, giftlist);
        giftlist.push_back(wishlist[gift]);
        vector<Gift> b = gifts(wishlist, budget - wishlist[gift].price, gift+1, giftlist);
        return totalPrice(a) < totalPrice(b)  && totalbudget - totalPrice(b) >= 0 ? b : a;
    }
}

 //               
int main()
{
    database = giftstore();
    database.erase(database.end());
    vector<Gift> wishlist = openWishList("Fabienne.txt");
    vector<Gift> giftlist = gifts(wishlist, totalbudget, 0, emptyvector);
    for(int i = 0; i < giftlist.size(); i++)
    {
        cout << giftlist[i].price << " - " << giftlist[i].gift << endl;
    }
    cout << "\nBudget : " << totalbudget << endl;
    cout << "Total Price : " << totalPrice(giftlist) << endl;
    return 0;
}

/* 
       
       
                        
                                        
                           
                    
                                 
                                                                   
                                                                            
              
                   

      
                 
                    
                              
             
                  

      
                                 
                                           
                
             
                  

        
                         
                              
                                 
                         
             
                  

       
                        
                                        
                           
                    
                                 
                                                                   
                                                                            
              
                   

         
                               
                                 
                                    
                     
              
                   
*/

