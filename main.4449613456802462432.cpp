//                                      
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <fstream>

using namespace std;

//                                                                                                                            
struct Gift
{
    int price;
    string name;
};

void open_file (ifstream& input_file, string s )
{
//               
    assert (true);
//                
//                                          

    input_file.open (s.c_str());
}

void read_store (ifstream& input_file, vector<Gift>& store)
{
//                
    assert (true);
//                 
//                                                                               

    open_file (input_file, "giftstore.txt");
    if (input_file)
    {

            while (input_file)
            {
                Gift gift;
                input_file >> gift.price;
                input_file.ignore();
                getline (input_file, gift.name);
                store.push_back(gift);
            }
    }
    else
        cout << "The giftstore file could not be opened." << endl;
}

void read_wishlist (ifstream& input_file, int& budget, string name_child, vector<string>& wishlist)
{
//               
    assert (true);
//                
//                                                                                                

    open_file(input_file, name_child.c_str() );

    if (input_file)
    {
        input_file >> budget;
        string present;
        while (input_file)
        {
            getline (input_file, present);
            wishlist.push_back(present);
        }
    }
    else
        cout << "The file of the wishlist could not be opened." << endl;
}

//                                                                                                                               

int price_present (vector<Gift>& store, string targetname)
{
    for( int i = 0; i < store.size() ; i++)
    {
         if (store[i].name == targetname)
            return store[i].price;
    }
    return 1000000;

}

//                                                                                                    

//          

//                                        
//                                     
//                              
//                                                                                        

//                
//                   
//                      
//                                                
//                                             

int solution (vector<string>& wishlist, vector<string>& best, vector<string>& current, int budget, int c, vector<Gift>& store)
{
//               
//             
//                                                                                                                                                     

    int total_price;

    if (total_price == budget)
    {
       return total_price;
    }
    if (total_price > budget)
    {
        return total_price - price_present(store, wishlist[c]);
    }
    else if (c == wishlist.size() )
    {
        return total_price;
    }

    else
    {
        current.push_back( wishlist[c] );
        const int WITH_C = solution ( wishlist, best, current, budget - price_present(store, wishlist[c]) , c+1, store);
        current.pop_back () ;
		const int WITHOUT_C = solution ( wishlist, best, current, budget, c+1, store);
        if (WITH_C >= WITHOUT_C)
        {
                best.push_back[c];
                return WITH_C;
        }
        else
            return WITHOUT_C;

    }
}

void show_solution (vector<string>& best)
{
    cout << "The best solution is:" << endl;
    for (int i = 0; i < best.size(); i++)
        cout.putline << best[i] << endl;
}

int main ()
{
    return 0;
}

