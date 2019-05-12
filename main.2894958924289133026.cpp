#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>

using namespace std;
//                        
struct Gift
{
    int price;
    string name;
};

ostream& operator<<(ostream& out, const Gift& gift)
{
    out << gift.price << "\t" << gift.name;
    return out;
}
vector<string> best_one;

int preparing_wishlist(string person, vector<string>& wishlist)
{
    //              
    assert(wishlist.size() == 0);
    //                                                                                                           
    int budget;
    string wish;
    string s;
    ifstream file(person.c_str());
    file >> budget;
    getline(file,s);
    while(file)
    {
        getline(file,wish);
        wishlist.push_back(wish);
        //                     
    }
    file.close();
    return budget;
}

int preparing_giftstore(vector<string>& wishlist, vector<Gift>& giftstore)
{
    //              
    assert(giftstore.size() == 0);
    //                                                                                                            
    char c;
    string s;
    ifstream store("giftstore.txt");
    Gift gift;
    while(store)
    {
    store >> gift.price;
    store.get(c);
    getline(store,gift.name);
    giftstore.push_back(gift);
    }

}

int find_gift(string gift, vector<Gift>& giftstore)
{
    //              
    assert(true);
    //                                                                                                                          
    //                           
    for(int i = 0; i < giftstore.size(); i++)
    {
        if(giftstore[i].name == gift)
            return giftstore[i].price;
    }
    return -1;
}

int gifts(vector<string>& wishlist, vector<Gift>& giftstore, vector<string>& option,int& budget, int counter, int& best_budget)
{
    //              
    assert();
    /*                                                                                                                                    
                                                                                                            
    */
    int g = 0;
    if(budget < best_budget && budget >= 0)
    {
        best_budget = budget;
        best_one = option;
    }
    if(budget == 0)
    {
        return 1;
    }
    else if(budget < 0)
        return 0;
    else if(wishlist.size() < (counter + 1))
        return 0;
    else
    {
        g = budget - find_gift(wishlist[counter],giftstore);
        if(g != -1)                              //                                         
        {
        option.push_back(wishlist[counter]);
        gifts(wishlist,giftstore,option,g,counter+1,best_budget);
        option.pop_back();
        }
        gifts(wishlist,giftstore,option,budget,counter+1,best_budget);
        return 0;
    }
}

int main()
{
    int budget;
    string person;
    vector<string> wishlist;
    vector<string> option;
    vector<Gift> giftstore;
    cout << "enter the persons name (with '.txt' after it):";
    cin >> person;
    budget = preparing_wishlist(person,wishlist);
    preparing_giftstore(wishlist,giftstore);
    gifts(wishlist,giftstore,option,budget,0,budget);
    for(int i = 0;i < best_one.size();i++)
    {
        cout << best_one[i] << "\n";
    }
    return 0;
}

/*
       

       
                                      
                        
                  

      
        
           
                        

      
                        
                      
                            
          

        
                            
                            
                  
               
                  

       
                           
                           
                                            
                                    
                                    
             
                                                          
                                                             

         
                       
                          
                         
                                  
                               
                                 
                                     
                            
                                       
                                    
                             
              

*/

