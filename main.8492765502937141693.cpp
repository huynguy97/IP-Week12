#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <vector>

using namespace std;

struct Gift{
    int price;
    string name;
};

struct Solution{
    int price;
    vector<Gift> gifts;
};

void operator<< (ostream& out, Gift& gift){
    out << "Price: " << gift.price;
    out << "\tName: " << gift.name << endl;
}

void print_vector(vector<Gift>& vec){
    for(int i = 0; i < vec.size(); i++)
        cout << vec[i];
}

void create_giftStore(vector<Gift>& giftstore, string filename){
    ifstream input(filename);
//                                      
    assert(input.is_open());
//                                               

    while(!input.eof()){
        Gift gift;

        input >> gift.price;

        char temp;
        input.get(temp); //             
        getline(input, gift.name);

        giftstore.push_back(gift);
    }

    giftstore.pop_back(); //                                              
    input.close();
}

void create_wishlist(int& budget, vector<Gift>& wishlist, string filename){
    ifstream input(filename);
//                                      
    assert(input.is_open());
//                                               

    input >> budget;

    char temp;
    input.get(temp); //             

    while(!input.eof()){
        Gift gift;

        gift.price = 0; //                                       

        getline(input, gift.name);

        wishlist.push_back(gift);
    }

    wishlist.pop_back(); //                                              
    input.close();
}

void correct_wishlist(vector<Gift>& wishlist, vector<Gift>& giftstore){
//                                                  
    assert(true);
//                                                                            

    for(int i = 0; i < wishlist.size(); i++){
        bool done = false;
        int counter = 0;
        while(!done){
            if(wishlist[i].name == giftstore[counter].name){
                wishlist[i].price = giftstore[counter].price;
                done = true;
            }
            else if(counter == giftstore.size()){
                wishlist.erase(wishlist.begin() + i);
                i = i - 1;
                done = true;
            }
            else
                counter++;
        }
    }
}

Solution best(Solution a, Solution b, int budget){
//                  
    assert(budget > 0);
//                                             

    if(budget - a.price < budget - b.price)
        return a;
    else
        return b;
}

Solution gifts(Solution solution, vector<Gift>& wishlist, vector<Gift> giftstore, int gift, int budget){
//                 
    assert(gift >= 0);
//                                 

    if(budget < 0){
        Solution null = {0, {}};
        return null;
    }if(budget == 0)
        return solution;
    if(gift > wishlist.size())
        return solution;

    solution.gifts.push_back(wishlist[gift]); //         
    solution.price += wishlist[gift].price;
    Solution with_gift = gifts(solution, wishlist, giftstore, gift+1, budget - wishlist[gift].price);
    solution.gifts.pop_back(); //        
    solution.price -= wishlist[gift].price;
    Solution without_gift = gifts(solution, wishlist, giftstore, gift+1, budget);

    return best(with_gift, without_gift, budget);
}

int main()
{
    vector<Gift> giftstore;
    create_giftStore(giftstore, "giftstore.txt");
    //                        

    int budget;
    vector<Gift> wishlist;
    create_wishlist(budget, wishlist, "Edward.txt");
    cout << "Budget: " << budget << endl;
    //                       

    correct_wishlist(wishlist, giftstore);
    //                       

    Solution solution = {0, {}};

    Solution best = gifts(solution, wishlist, giftstore, 0, budget);
    cout << "Final Solution: " << best.price << endl;
    print_vector(best.gifts);

    return 0;
}

/*
                       

      
            
                    
                                              
                                                

     
            
                    
                                 
                                    
                                              

     
            
                    
                                                 
                                                          
                                

       
            
                    
                                         
                                              
                                                
                                        

      
             
                     
                                      
                                                       
                                         
                                   
                                                
                                                                                   
                                                                                            

        
             
                     
                                             
                                                
                                                   
                                    

*/

