#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
//                                        

using namespace std;

struct Presents
{
    int price;
    string item;
};
void cross_reference(vector<Presents>& available,vector<string> wish_list) //                                                     
{
    assert(true);
    ifstream store;
    store.open("giftstore.txt"); //             
    int price;
    string item;
    string wish;
    while(store) //                            
    {
        store>> price; //                   
        store.get();//                                                                                
        getline(store,item);//                                                                
        bool no_match=true;
        for (int element=0;element<wish_list.size() && no_match; element++)
        {
            wish=wish_list[element];
            if(item==wish) //                     
            {
                available.push_back({price,item});
                no_match=false; //                                           
            }
        }
    }
    store.clear();
    store.close();
}//                                                                                                             
/*            
                                                                                                   
            */
void improve(vector<Presents>& trial,vector<Presents>& best) //                  
{
    assert(trial[trial.size()-1].price>=0&&best[best.size()-1].price>=0);//                                           
    if (trial[trial.size()-1].price<best[best.size()-1].price) //                                                                                                                                                     
        best=trial;
}//                                                                    
void solutions(vector<Presents>& trial, vector<Presents>& best, vector<Presents> wish_list, int c, int budget)//                                                            
{
    assert(true);//                             
    //                                                                                                              
    if (budget==0)
    {
        best=trial;
    }
    else if (budget<0); //                                             
    else if (c>=wish_list.size())
    {
        improve(trial,best);
    }
    else
    {
        int with_c_budget=budget-wish_list[c].price;
        trial.push_back({with_c_budget,wish_list[c].item});
        solutions(trial, best, wish_list, c+1, with_c_budget);
        trial.pop_back();
        solutions(trial,best,wish_list,c+1,budget);
    }
}//                                                                                                                                                                                                                                                                                                        

void gifts(vector<string> wish_list, int budget)
{
    assert(budget>=0);//                                                                                                  
    vector<Presents> available={};//                                                                   
    cross_reference(available,wish_list);//                                  
    int c=0;
    vector<Presents> trial{{budget,"Phantom"}};//                                                                                                                                 
    vector<Presents> best={{budget,"de roe"}};//                                                                                  
    solutions(trial, best,available,c,budget);//                         
    for (int item=1; item<best.size();item++) //                                                       
        cout<<best[item].item<<"\n";
}//                                                                                
/*
                                                                                                                                                                                                                     
*/
void acquire_person_data(vector<string>& wish_list,int& budget,string personfile)//                                                          
{
    assert(true);
    ifstream person;
    person.open(personfile);//                                      
    person>>budget;//                               
    string next_item;//                                                                                                             
    while(person)//                          
    {
        getline(person,next_item);//             
        wish_list.push_back(next_item);//                     
    }
    person.clear();
    person.close();
}//                                                                                                                                          
int main()
{
    vector<string> wish_list;
    int budget;
    acquire_person_data(wish_list,budget,"Fabienne.txt");
    gifts(wish_list,budget);
    return 0;
    //                                                                              
    //                                                                                    
    //                                                                                                             
    //                                                                                                              
    //                                                                                                                                                                                                                                                                                  
    //                                                                                                                                      
}

