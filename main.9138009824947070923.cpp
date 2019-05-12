#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <fstream>

//                          
//                         

using namespace std;

struct Gift  {int price; string name;};

istream& operator>> (istream& in, Gift& gift)
{
	//             
	assert(true);
	//                
	//                                                                   
	in >> gift.price;
	in.ignore(1);
	getline(in, gift.name, '\n');
	return in;
}

int string_vector_size(vector<string>& a)
{
	//              
	assert(true);
	//                
	//                                                                              
	return static_cast<int>(a.size());
}
int gift_vector_size(vector<Gift>& a)
{
    //              
	assert(true);
	//                
	//                                                                            
    return static_cast<int>(a.size());
}

bool read_giftshop(string filename, vector<Gift>& giftshop)
{
	//               
	assert(true);
	//                
	//                                                                                                            
	//                                          
	ifstream infile;
	infile.open(filename.c_str());
	if(!infile)
		return false;
	int counter = 0;
	while(infile)
	{
		giftshop.push_back({});
		infile >> giftshop[counter];
		//                                       
		counter++;
	}
	giftshop.pop_back();
	return true;
}

int read_wishlist(string filename, vector<string>& wishlist)
{
	//               
	assert(true);//              
	assert(true);
	//                
	//                                                                              
	//                
	//                                                                                                            
	cout << filename << '\n';
	ifstream infile;
	infile.open(filename.c_str());
	int budget = 0;
	infile >> budget;
	infile.ignore(1);
	string temp;
	getline(infile, temp, '\n');
	wishlist.push_back(temp);
	while(infile)
	{
		getline(infile, temp, '\n');
		wishlist.push_back(temp);
	}
	wishlist.pop_back();
	return budget;
}

int sum(vector<Gift>& attempt)
{
	//               
	assert(true);
	//                
	//                                                                         
	int vectorsize = gift_vector_size(attempt);
	int sum = 0;
	for(int i = 0; i < vectorsize; i++)
		sum += attempt[i].price;
	return sum;
}

Gift match_list(vector<Gift>& giftshop, vector<string>& wishlist, int i)
{
	//               
	assert(i >= 0);
	//                
	//                                                                                              
	//                                                         
	int giftsize = gift_vector_size(giftshop);
    for(int j = 0; j < giftsize; j++)
        if(wishlist[i] == giftshop[j].name)
            return giftshop[j];
    return {0,"NA"};
}

void show(vector<Gift>& best)
{
    //               
    assert(true);
    //                
    //                                                             
    int size = gift_vector_size(best);
    cout << "The optimal list is:\n";
    for(int i = 0; i < size; i++)
        cout << best[i].name << '\n';
    cout << "And the total price is: " << sum(best) << '\n';
}

void improve(vector<Gift>& attempt, vector<Gift>& best, int budget)
{
    //               
    assert (budget >= 0);
    //                
    //                                                                                                       
    //                                                                        
    if((budget - sum(attempt)) < (budget - sum(best)))
        best = attempt;
}

bool gifts(vector<Gift>& giftshop, vector<string>& wishlist, int budget, vector<Gift>& attempt, vector<Gift>& best, int counter)
{
    //               
    assert(string_vector_size(wishlist) <= gift_vector_size(giftshop));
    /*                
                                                                                                                                                 
                                                                                                                                       
    */
    int attempt_size = gift_vector_size(attempt);
    if(attempt_size > 0 && attempt[attempt_size-1].name == "NA")
        return false;
    if((budget - sum(attempt) == 0))
    {
        best = attempt;
        return true;
    }
    else if((budget - sum(attempt) < 0))
        return false;
    else if (counter >= string_vector_size(wishlist))
    {
        improve(attempt, best, budget);
        return false;
    }
    else
    {
        attempt.push_back(match_list(giftshop, wishlist, counter));
        bool accepted = gifts(giftshop, wishlist, budget, attempt, best, counter+1);
        attempt.pop_back();
        bool rejected = gifts(giftshop, wishlist, budget, attempt, best, counter+1);
        return accepted || rejected;
    }
}

int main()
{
    vector<string> wishlist;
    vector<Gift> giftshop;
    vector<Gift> attempt;
    vector<Gift> best;
    int counter = 0;
    if(!(read_giftshop("giftstore.txt", giftshop)))
    {
        cout << "Giftshop failed :(";
        return 1;
    }
    int budget = read_wishlist("Fabienne.txt", wishlist);
    gifts(giftshop, wishlist, budget, attempt, best, counter);
    show(best);
}

/*
        
      
                    
                        
                          
                            

      
                    
           
              
                        
                            

      
                    
                        
                      
          
                            

        
                    
                  
                   
               
                  
                            

       
                    
                                    
                                       
                          
             
                                                          
                                                             
                             

         
                    
                       
                          
                             
              
                             
*/

