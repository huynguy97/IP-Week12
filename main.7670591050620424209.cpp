#include <iostream>
#include <cassert>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

//                          
//                               

int best = 0;

void gifts (vector<int>&gift_list, int counter, int maximal, int budget)
{
    //              
    assert(counter >= 0 && maximal >= 0 && budget >= 0);
    //               
    //                                                                                                        

    if (maximal == budget)
    {
        best = maximal;
        return;
    }
    if (maximal > budget)
        return;
    if (counter == gift_list.size())
        return;
    if (best < maximal)
        best = maximal;

    if (maximal <= budget)
    {
        gifts(gift_list, counter + 1, maximal + gift_list[counter], budget);
        gifts(gift_list, counter + 1, maximal, budget);
        return;
    }
}

void read_gift_store (vector<int>&price_list, vector<string>&gift_name)
{
    //              
    assert(true);
    //               
    //                                                                                                                                                                                                      

    ifstream file;
    file.open("giftstore.txt");
    while(file)
    {
        int p;
        file >> p;
        //           
        price_list.push_back(p);
        //                       
        string c;
        getline(file, c);
        if (c.size() != 0)
        {
            c.erase(0,1);
            //          
            gift_name.push_back(c);
            //                                                 
            //                                                   
        }
    }
}

void vergelijk_wishlist(vector<int>&price_list, vector<string>&gift_name, string name, int& budget, vector<int>&gift_list)
{
    //              
    assert(true);
    //               
    //                                                                                      

    ifstream file;
    file.open(name);
    file >> budget;
    file.ignore();
    while(file)
    {
        string c;
        getline(file, c);
        //                   
        //                        
        for (int i = 0; i < gift_name.size(); i++)
        {
            //                   
            if (c == gift_name[i])
            {
                //                        
                gift_list.push_back(price_list[i]);
            }
        }
    }
}

int main()
{
    int maximal = 0;
    int counter = 0;
    int budget;
    vector<int>price_list;
    vector<int>gift_list;
    vector<string>gift_name;

    read_gift_store(price_list, gift_name);
    vergelijk_wishlist(price_list, gift_name, "Edward.txt", budget, gift_list);
    gifts(gift_list, counter, maximal, budget);
    cout << budget << endl;
    cout << best;

    /*
                                            
     
                                   
     

                   
                                                 
                                               
                 
    */

    return 0;
}

/*
                                         
                                        
                                        
                                          
                                          
                                            
*/

