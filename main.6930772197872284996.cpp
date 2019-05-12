#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <fstream>
#include <stdio.h>
#include <string.h>

//                                                 
/*       
                           
                                             
                                                

                          
                                             
                                            
                               

                              
                                                
                                               
                                                        
                                                     
                                                       

                            
                                                          
                                                             
                                                
                                    
                                                                               
                                                                                  

                            
                                        
                                         
                                     
                                        

                          
                                
                                   
                                             
*/

using namespace std;

struct Gift
{
    int price;                          //              
    string itemname;                    //          
};

vector<Gift> current;
vector<Gift> best;

int size (vector<Gift>& x)
{//               
    assert (true) ;
//                                                       
    return static_cast<int> (x.size()) ;
}

bool read_store (istream& infile, vector<Gift>& presents)
{
//               
    assert (true);
//                                                                                       
    while(infile)
    {
        Gift new_gift;
        infile >> new_gift.price;
        infile.ignore();
        getline(infile,new_gift.itemname);
        presents.push_back(new_gift);
    }
    presents.pop_back();
    return true;
}

bool read_wishlist (istream& infile, vector<Gift>& wishlist, vector<Gift>& presents, int& budget)
{
//               
    assert (budget >= 0);
//                                                                                        
//                                                     
    infile >> budget;
    infile.ignore();

    while(infile)
    {
        Gift new_gift;
        getline(infile, new_gift.itemname);
        for(int i = 0; i < size(presents); i++)
        {
            if(new_gift.itemname == presents[i].itemname)
            {
                new_gift.price = presents[i].price;
            }
        }
        wishlist.push_back(new_gift);
    }
    wishlist.pop_back();
    return true;
}

int sum (vector<Gift>& temp_gifts, int from)
{
//               
    assert (from >= 0 && from <= size(temp_gifts)) ;
//                 
//                                                                                                
    int sum = 0 ;
    for (int i = from ; i < size(temp_gifts) ; i++)
        sum += temp_gifts[i].price ;
    return sum ;
}

int sum (vector<Gift>& temp_gifts)
{
    return sum (temp_gifts,0) ;
}

void improve (vector<Gift>& current, vector<Gift>& best)
{
//               
    assert (true) ;
//                 
//                                                                 
    if (sum (current) > sum (best))
        best = current ;
}

int gifts ( vector<Gift>& current, vector<Gift>& best, vector<Gift>& wishlist, int c, int budget)
{
//               
    assert (true) ;
//                 
//                                                                                                                                       
    if ( budget == 0 )
    {
        best = current ;
        return 1 ;
    }
    else if ( budget < 0 )
    {
        return 0 ;
    }
    else if ( c >= size(wishlist))
    {
        improve (current, best) ;
        return 0 ;
    }
    else
    {
        current.push_back ( wishlist[c] ) ;
        const int WITH_C    = gifts( current, best, wishlist, c+1, budget - wishlist[c].price ) ;
        current.pop_back () ;
        const int WITHOUT_C = gifts( current, best, wishlist, c+1, budget ) ;
    }
}

void show_vector(vector<Gift>& wishlist)
{
//               
    assert (true) ;
//                                                   
    for(int i = 0; i < size(wishlist); i++)
    {
        cout << "Gift: "<< wishlist[i].itemname << " with price " << wishlist[i].price << endl;
    }
}

int main()
{
    vector<Gift> presents;
    vector<Gift> wishlist;

    int budget = 0;

    string filename = "giftstore.txt";
    ifstream input_file (filename.c_str());
    read_store(input_file, presents);
    input_file.clear () ;
    input_file.close () ;

    string filename2 = "Belle.txt";
    ifstream input_file2 (filename2.c_str());
    read_wishlist(input_file2, wishlist, presents, budget);

//                        
    show_vector(wishlist);
    cout << "The budget is: " << budget<< endl;

    gifts(current,best,wishlist,0,budget);
    show_vector(best);

    return 0;
}

