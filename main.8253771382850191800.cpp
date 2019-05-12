#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <vector>

using namespace std;

/*
                                                  

                                           

                                                  

                                          
                                          

                                                  
*/

struct Gift {
    int price;
    string name;
};

int size(vector<Gift>& v)
{//              
    assert(true);
 //                
 //                                             
    return static_cast<int>(v.size());
}

ostream& operator<< (ostream& out, vector<Gift>& v)
{//               
    assert(true);
 //                
 //                                                                                                

    int v_size = size(v);
    for (int i=0; i<v_size; i++)
    {
        out << "  " << v[i].name << " (" << v[i].price << ")";
        if (i < (v_size-1))
            out << ", \n";
    }
	return out ;
}

//                                      
//                                    
//                                      

int total_price(vector<Gift>& v)
{//               
    assert(true);
 //                
 //                                                       
    int output = 0;
    for (int i=0; i<size(v); i++)
        output += v[i].price;
    return output;
}

void improve(vector<Gift>& attempt, vector<Gift>& best)
{//               
    assert(true);
 //                
 //                                                
    if (total_price(attempt) > total_price(best))
        best = attempt;
}

void gifts(vector<Gift>& attempt, vector<Gift>& best, vector<Gift>& wishlist, int g, int budget)
{//               
    assert(g >= 0);
 //                
 //                                                         
    if (budget == 0)
    {
        best = attempt;
        return;
    } else if (budget < 0)
    {
        return;
    } else if (g >= size(wishlist))
    {
        improve(attempt, best);
        return;
    } else {
        attempt.push_back(wishlist[g]); //        
        gifts(attempt, best, wishlist, g+1, budget-wishlist[g].price);
        attempt.pop_back(); //       
        gifts(attempt, best, wishlist, g+1, budget);
        return;
    }
}

//                                      
//                             
//                                      

bool load_giftstore(vector<Gift>& giftstore)
{//               
    assert(true);
 //               
 //                                                                                                                              
    ifstream infile("giftstore.txt");
	if (infile)
	{
        while (infile)
        {
            Gift g = {0, ""};

            char c;

            infile >> g.price;
            infile.get(c); //                               

            infile.get(c);
            while (c != '\n' && infile)
            {
                g.name += c;
                infile.get(c);
            }
            if (infile)
            {
                //                                                                                 
                giftstore.push_back(g);
            }
        }
		infile.close();
		return true;
	} else {
		cout << endl << "giftstore.txt could not be opened." << endl;
		return false;
	}
}

int get_price(string name, vector<Gift>& giftstore)
{//               
    assert(true);
 //               
 //                                                                                                     
    for (int i = 0; i < size(giftstore); i++)
        if (giftstore[i].name == name)
            return giftstore[i].price;

    return -1;
}

bool load_wishlist(string filename, vector<Gift>& wishlist, int& budget, vector<Gift>& giftstore)
{//               
    assert(true);
 //               
 //                                                                                                                                         
    ifstream infile(filename.c_str());
	if (infile)
	{
	    char c;
	    infile >> budget;

        while (infile)
        {
            Gift g = {0, ""};

            infile.get(c);
            while (c != '\n' && infile)
            {
                g.name += c;
                infile.get(c);
            }
            if (infile)
            {
                g.price = get_price(g.name, giftstore);
                if (g.price >= 0)
                {
                    //                                                                                 
                    wishlist.push_back(g);
                }
            }
        }
		infile.close();
		return true;
	} else {
		cout << endl << filename << " could not be opened." << endl;
		return false;
	}
}

int main()
//                                                              
{
    string filename = "Desiree.txt";
    //                                                            

    vector<Gift> giftstore;
    if (load_giftstore(giftstore))
    {
        int budget = 0;
        vector<Gift> wishlist;
        if (load_wishlist(filename, wishlist, budget, giftstore))
        {
            vector<Gift> attempt;
            vector<Gift> best;
            gifts(attempt, best, wishlist, 0, budget);
            cout << "Here is the best result for " << filename << ": " << endl;
            cout << best << endl;
            int money_spend = total_price(best);
            cout << "In total spend " << money_spend << " euro cent out of the budget of " << budget << " euro cent. (" << ((money_spend+0.0)/budget*100) << "%)" << endl;
        }
    }
    return 0;
}

//                                      
//                           
//                                      

/*
                                           
                                     
                                       
                                                                               

                                          
                        
                           
                                    
                                                                               

                                          
                                     
                                    
                      
                                                                              

                                            
                                
                                 
                             
                               
                                                                               

                                           
                                                  
                                                     
                                        
                            
                                                                       
                                                                         
                                                                                   

                                             
                                      
                                        
                                           
                           
                                                                                  
*/

