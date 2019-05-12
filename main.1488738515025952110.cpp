#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>
using namespace std;
//                         
//                    
struct Gift
{
    int price;
    string name;
};

/*
                          
                         
                     
                       
                              

                                                      
                                               
                      
                  
*/
istream& operator >> (istream& in, Gift& gift)
{
    assert(true);
    //                                                                                    
    char c;
    in >> gift.price;
    in.get(c);
    getline(in, gift.name);
    return in;
}

int size(vector<Gift>& gifts)//                  
{
    assert(true);
    //                                                                  
    return static_cast<int>(gifts.size());
}

int size(vector<string>& wishlist)//                  
{
    assert(true);
    //                                                        
    return static_cast<int>(wishlist.size());
}

void show_vector(vector<Gift>& gifts)//                  
{
    assert(true);
    //                                                            
    for(int i = 0; i<size(gifts); i++)
    {
        cout << gifts[i].price<< "\t" << gifts[i].name<< endl;
    }
}

void show_vector(vector<string>& wishes, int& budget)//                  
{
    assert(true);
    //                                                              
    cout << budget<<endl;
    for(int i = 0; i<size(wishes); i++)
    {
        cout << wishes[i]<< endl;
    }
}

void maximize_budget(vector<Gift>& best, vector<Gift>& attempts)//                                
{
    assert(true);
    //                                                                                                     
    int valueBest = 0;
    int valueAttempts = 0;
    for(int i = 0; i < size(best); i++)
    {
        valueBest = valueBest+best[i].price;
    }
    for(int i = 0; i < size(attempts); i++)
    {
        valueAttempts = valueAttempts+attempts[i].price;
    }
    if(valueAttempts>valueBest)
    {
        best=attempts;
    }
}

bool gift_on_wishlist(string name, vector<string>& wishlist)
{
    assert(true);
    //                                                                                                            
    for(int i = 0; i < size(wishlist); i++)
    {
        if(name == wishlist[i])
            return true;
    }
    return false;
}

int gifts(vector<Gift>& giftstore,vector<Gift>& attempts,vector<Gift>& best,vector<string>& wishlist , int index, int budget)
{
    assert(index>=0);
    //                                                                          
    //                                                                        
    if(budget == 0)
    {
        best = attempts;
        return 1;
    }
    if(budget < 0)
    {
        return 0;
    }
    if(index >= size(giftstore))
    {
        maximize_budget(best, attempts);
        return 0;
    }
    if(gift_on_wishlist(giftstore[index].name, wishlist))
    {
        attempts.push_back(giftstore[index]);
        int with_gift = gifts(giftstore,attempts, best,wishlist, index+1, budget-giftstore[index].price);
        attempts.pop_back();
        int without_gift = gifts(giftstore,attempts, best,wishlist, index+1, budget);
        return with_gift+without_gift;
    }
    else
    {
        gifts(giftstore, attempts, best, wishlist, index+1, budget);
    }
}

void read_wishlist(vector<string>& wishlist, ifstream& infile,int& budget)//     
{
    assert(infile.is_open());
    //                                                                     
    string gift;
    infile >> budget;
    while(infile)
    {
        getline(infile, gift);
        wishlist.push_back(gift);
    }
}

void read_giftstore(vector<Gift>& giftstore, ifstream& infile)//     
{
    assert(infile.is_open());
    //                                                                        
    Gift gift;
    while(infile)
    {
        infile >> gift;
        giftstore.push_back(gift);
    }
}

int main()
{
    int budget = 0;
    vector<Gift> giftstore;
    vector<string> wishlist;
    vector<Gift> attempts;
    vector<Gift> best;
    string child;
    //                  
    ifstream giftfile;
    giftfile.open("giftstore.txt");
    read_giftstore(giftstore, giftfile);
    giftfile.close();
    //                 
    cout << "Which child do you want to match with presents?"<<endl;
    cin >> child;
    child = child+".txt";
    //              
    ifstream wishes;
    wishes.open(child);
    read_wishlist(wishlist, wishes, budget);
    wishes.close();
    cout << gifts(giftstore, attempts, best,wishlist, 0, budget)<<endl;
    show_vector(best);
    return 0;
}
/*
                                     
                                
                                  

          
                   
                      
                                

          
                                   
                                            
                  

            
                          
                           
                       
                          

            
                                         
                                                                  
                                                                     
                     
                                  
                           
                        

              
                                     
                                  
                      
                               

*/

