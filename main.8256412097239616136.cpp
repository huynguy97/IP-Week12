#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;

//                      
//                          

struct present
{
    string name ;
    int price ;
} ;

/*                                                     
 
                                  
 

                                                        
 
                 
                                     
                
 */

istream& operator>> (istream& in, present& gift)
{
    in >> gift.price ;
    in.ignore(1) ;
    getline(in, gift.name) ;
    return in ;
}

void make_list(ifstream& store_in, ifstream& wish_list, vector<present>& store_presents, vector<string>& wanted_presents, vector<present>& overlapping_presents, int& budget)
{
    //               
    assert ( true ) ;
    //                
    //                                                
    //                                                  
    //                                                                                                  
    present between ;
    while (store_in >> between)
    {
        store_presents.push_back(between) ;
    }
    wish_list >> budget ;
    while(getline(wish_list, between.name))
    {
        wanted_presents.push_back(between.name) ;
    }
    for (int i = 0 ; i < store_presents.size() ; i++)
    {
        for (int j = 0 ; j < wanted_presents.size() ; j++)
        {
            if (store_presents[i].name == wanted_presents[j])
            {
                overlapping_presents.push_back(store_presents[i]) ;
            }
        }
    }
}

void improve(vector<present>& attempt, vector<present>& best)
{
    //               
    assert ( true ) ;
    //                
    //                                                                                                  
    int attempt_total = 0 ;
    int best_total = 0 ;
    for (int i = 0 ; i < attempt.size() ; i++)
    {
        attempt_total += attempt[i].price ;
    }
    for (int i = 0 ; i < best.size() ; i++)
    {
        best_total += best[i].price ;
    }
    if (attempt_total > best_total)
    {
        best = attempt ;
    }
}

int gifts(int budget, vector<present>& attempt, vector<present>& best, vector<present> present_list, int pos)
{
    //            
    assert( pos >= 0 ) ;
    //             
    //                                                                            
    //                                                                             
    //                                                                        
    if (budget == 0)
    {
        best = attempt ;
        return 1 ;
    }
    else if (budget < 0)
    {
        return 0 ;
    }
    else if (pos >= present_list.size())
    {
        improve(attempt, best) ;
        return 0 ;
    }
    else
    {
        attempt.push_back(present_list[pos]) ;
        gifts((budget - present_list[pos].price), attempt, best, present_list, (pos + 1)) ;
        attempt.pop_back() ;
        gifts(budget, attempt, best, present_list, (pos + 1)) ;
    }
    return 1 ;
}

int used_budget(vector<present> best)
{
    //               
    assert ( true ) ;
    //                
    //                                                                     
    int total = 0 ;
    for (int i = 0 ; i < best.size() ; i++)
    {
        total += best[i].price ;
    }
    return total ;
}

int main()
{
    int budget = 0 ;
    int pos = 0 ;
    vector<present> store_presents ;
    vector<string> wanted_presents ;
    vector<present> overlapping_presents ;
    vector<present> attempt ;
    vector<present> best ;
    ifstream store_in ("giftstore.txt") ;
    ifstream wish_list ("Fabienne.txt") ;
    make_list(store_in, wish_list, store_presents, wanted_presents, overlapping_presents, budget) ;
    gifts(budget, attempt, best, overlapping_presents, pos) ;
    for (int i = 0 ; i < best.size() ; i++)
    {
        cout << best[i].name << endl ;
    }
    cout << "The used budget is: " << used_budget(best) ;
    return 0;
}

/*
       
                        
                          
                        

      
           
              
                        
                        

      
                           
                                    
          
                        

        
                  
                   
               
                  
                        

       
                                 
                                                          
                                                             
             
                          
                   
                
                         

         
                             
                          
              
                       
                         
*/

