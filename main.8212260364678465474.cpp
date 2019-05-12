/*
             
                       
              
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <cstring>
#include <cmath>

using namespace std;

struct Gift
{
    string name;
    int prize;
};

vector<Gift> store_list; //                                                                      

int size (vector<Gift>& array)
{//               
    assert (true) ;
//                                                                     
    return static_cast<int> (array.size()) ;
}

bool find(string gift_name, vector<Gift>& gift_array,int& prize)
{//               
    assert (true);
//                                                                                                                 
    for (int i = 0 ; i < size(gift_array) ; i++)
        if (gift_array[i].name == gift_name) //        
        {
            prize = gift_array[i].prize;
            return true;
        }
    return false;
}

void print_solution(vector<Gift>& solution, string owner)
{
    //             
    assert(true);
    //                                                   
    cout << "The gifts for " << owner << ':' << endl;

    for(int i = 0 ; i < size(solution) ; i++)
        cout << solution[i].name << endl;
}

int sum (vector<Gift>& gifts, int from)
{//              
    assert (from >= 0 && from <= size(gifts)) ;
//                                                           
    int sum = 0 ;
    for (int i = from ; i < size(gifts) ; i++)
        sum += gifts[i].prize ;
    return sum ;
}

void improve (vector<Gift>& current, vector<Gift>& best)
{//              
    assert (true) ;
//                                                                                
    if (sum (current,0) > sum (best,0))
        best = current ;
}

int gift ( vector<Gift>& current, vector<Gift>& best, vector<Gift>& wishlist, int index, int budget)
{//              
    assert ( index >= 0 && index <= size(wishlist) && size(current) <= size(wishlist) && size(best) <= size(wishlist) );
//                                                                                                                                                                  

	if ( budget == 0 )           { best = current ; return 1 ; } //                                                             
	else if ( budget < 0 )       { return 0 ; }
	else if ( index >= size(wishlist) ) { improve (current, best) ; return 0 ; } //                                         
	else if (sum (current,0) + sum (wishlist,index) <= sum (best,0)) { return 0 ; } //                                                                                                  

	else {
		current.push_back ( wishlist[index] ) ;
		const int with_gift    = gift ( current, best, wishlist, index+1, budget - wishlist[index].prize) ; //                                       
		current.pop_back () ;
		const int without_gift = gift ( current, best, wishlist, index+1, budget) ; //                                    
		return with_gift + without_gift ; //                                                                                                           
	}
}

string remove_first_space(string text)
{
    //             
    assert(true);
    //                                                            
    string removed;

    for(int i = 1; i < text.length(); i++)
        removed = removed + text[i];

    return removed;
}

void read_giftstore(vector<Gift>& gifts)
{
    //             
    assert(true);
    //                                                                            
    ifstream storefile ("giftstore.txt");
    string name;
    int price;

    while(storefile)
    {
        storefile >> price;
        getline(storefile,name);

        gifts.push_back({remove_first_space(name),price}); //                                                                                 

    }
}

void read_wishlist(string filename, vector<Gift>& gifts, int& budget)
{
    //             
    assert(true);
    //                                                                 
    ifstream wishfile (filename.c_str());
    string name;
    int prize;

    wishfile >> budget;
    getline(wishfile,name); //                    

    while(wishfile)
    {
        getline(wishfile,name);
        if(find(name,store_list,prize)) //                                    
        {
            gifts.push_back({name,prize});
        }
    }
}

int main()
{
    vector<string> lists = {"Andrew.txt", "Belle.txt", "Chris.txt", "Desiree.txt", "Edward.txt", "Fabienne.txt"};
    vector<string> owners = {"Andrew", "Belle", "Chris", "Desiree", "Edward", "Fabienne"};

    read_giftstore(store_list);

    for(int i = 0; i < 6 ; i++)
    {
        vector<Gift> wishes;
        vector<Gift> current;
        vector<Gift> best;
        int budget;

        read_wishlist(lists[i], wishes, budget);
        gift(current,best,wishes,0,budget);
        print_solution(best, owners[i]);
        cout << endl;
    }
    return 0;
}

/* 
                           

                     
                        
                          

                    
           
              
                        

                    
                        
                      
          

                      
                  
                   
               
                  

                     
                                    
                                       
                          
             
                                                          
                                                             

                       
                       
                          
                             
              
 */

