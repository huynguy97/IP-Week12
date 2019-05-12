#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <cmath>
#include <fstream>

using namespace std;

struct Gift
{
    int price;
    string name;
};

vector<Gift> giftstore;
vector<Gift> wishlist;
int budget;

//     
int total_price (vector<Gift> gift_list, int index=0)
{ //              
    assert(gift_list.size() >= 0);
/*                 
                                                        */

    if (gift_list.size() == 0)
        return 0;

    else if ( index == gift_list.size() - 1)
        return gift_list[index].price;

    else
        return gift_list[index].price + total_price(gift_list, index+1);
}

//     
void improve (vector<Gift>& a, vector<Gift>& b)
{ //              
    assert(a.size() >= 0 && b.size() >= 0);
/*                 
                                                                    */
    if ( total_price(a) > total_price(b) )
        b = a;
}

//                                                                                                                                  
int gifts (vector<Gift>& store, vector<Gift>& wishlist, int budget, vector<Gift>& solution, vector<Gift>& attempt, int storeindex=0, int wishindex=0)
{//               
    assert(budget > 0);
/*                 
                                                                           
                                                 */

    //                                    
    improve(attempt, solution);

    //                                      
    if (wishindex >= wishlist.size())
    {
        return 1;
    }

    //                                              
    else if (storeindex >= store.size())
    {
        return gifts(store, wishlist, budget, solution, attempt, 0, wishindex=wishindex+1);
    }

    else if (storeindex < store.size())
    {
        //                                    
        if (wishlist[wishindex].name == store[storeindex].name)
        {
            wishindex++;

            //                       
            if (store[storeindex].price <= budget)
            {
                attempt.push_back(store[storeindex]);
                int with = gifts(store, wishlist, budget-store[storeindex].price, solution, attempt, storeindex, wishindex);

                attempt.pop_back();
                int without = gifts(store, wishlist, budget, solution, attempt, storeindex, wishindex);

                return with + without;
            }

            //                  
            else
            {
                return gifts(store, wishlist, budget, solution, attempt, storeindex, wishindex);
            }
        }

        //                                 
        else
        {
            return gifts(store, wishlist, budget, solution, attempt, storeindex+1, wishindex);
        }
    }
}

//                                   
void load_gift_vector (string filename, vector<Gift>& gift_vector, bool read_price = true)
{//               
    assert(!filename.empty());
/*                 
                                                                                                                             */
    ifstream stream (filename.c_str());

    int price = 0;
    string name = "empty";
    gift_vector.clear();

    if (! read_price) {
        stream >> budget;
        getline(stream, name);
    }

    while (stream)
    {
        if (read_price)
            stream >> price;
        while (stream.peek() == ' ')
            stream.get();
        getline(stream, name);

        if (stream)
            gift_vector.push_back({price, name});
    }

    stream.close();
}

//                                      
ostream& operator<< (ostream& out, const vector<Gift> gift_list)
{//               
    assert(gift_list.size() > 0);
/*                 
                                 */
    for (int i=0; i < gift_list.size(); i++)
    {
        cout << "price:" << gift_list[i].price;
        cout << " name:" << gift_list[i].name << endl;
    }
}

//                                                       
int main()
{//               
    assert(true);
/*                 
                                                                                                        */

    vector<string> filenames = { "andrew.txt", "Belle.txt", "Chris.txt", "Desiree.txt", "Edward.txt", "Fabienne.txt"};
    vector<Gift> solution;
    vector<Gift> attempt;

    for (int i=0; i < filenames.size(); i++)
    {
        giftstore.clear();
        wishlist.clear();
        solution.clear();
        attempt.clear();
        budget=0;

        load_gift_vector("giftstore.txt", giftstore);
        load_gift_vector(filenames[i], wishlist, false);

        cout << "- - - - -" << endl;
        gifts(giftstore, wishlist, budget, solution, attempt);
        cout << filenames[i] << " Solution :" << endl;
        cout << solution;
        cout << "Budget:" << budget << " used Budget:" << total_price(solution) << endl;
        cout << "- - - - -" << endl << "Press any key to continue.";
        cin.get();
    }

    return 0;
}

/*
         
                     
                                          
                                                                            
                            
         
                          
         
                    
                          
                             
                                       
                            
         
                          
         
                    
                                       
                                      
                         
                            
         
                          
         
                      
                                  
                                   
                               
                                  
                            
         
                          
         
                     
                                          
                                                    
                                 
                                                       
                                    
                                          
                                                                         
                                                                            
                              
         
                          
         
                       
                                        
                                          
                                             
                              
                              
         
                          

                                                   
                          

*/

