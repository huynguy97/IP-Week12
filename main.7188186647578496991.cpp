//                    
//             

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <stdio.h>

using namespace std;

struct Gift{
    int prices;
    string name;
};

struct Wishlist{
    int budgets;
    vector<string> wishes;
};

vector<Wishlist>  attempt;
vector<Gift> gifts;
vector<Wishlist> best;

int size(vector<Gift>&  gifts)
{return static_cast<int> (gifts.size());}

/*                                           
                  
                                              
                   
                                                                                                              
                           
                  
                          
                                              
                        
                         
              
 

                                      
                  
                                              
                   
                                                                                                              
                 
                                             
                        
                
 

                            
 
                         
 

                                                        
                  
                   
                   
                                                                   
                                   
                        
 
*/

int solutions(vector<Wishlist>&  attempt, vector<Gift>& gifts, vector<Wishlist>& best, int price,int budget)
{   /*                                                             
                                          
                                                                          
                                                   
                                                        
                                                                           

          
                                        
                                                                                           

                           
                                                                               

                                           */

    assert (attempt.size() == 0);

    int i = 0;
    if (budget == 0) {cout << budget << "  " << price << endl; return 1;}
    else if (budget < 0) {return 0;}
    else if (budget > 0) {
        return solutions(attempt, gifts, best, gifts[i++].prices, budget= budget - gifts[i++].prices);
    }
    else return false;

    //                                                     
    //                          
    //                                  

    //                                                                                                 
    //                                                                                        

}

void read_pricelist(){
int price;
for (int i = 0; i < 2000; i++)
{
    ifstream input_file("giftstore.txt");
    getline(price);
    gifts.push_back(price);
    cout << c << endl;
}
}

int main()
{
    int price;
    int budget;
    solutions(attempt, gifts, best, price, budget);
}

