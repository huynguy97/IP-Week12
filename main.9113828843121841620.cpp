#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>

using namespace std;

struct Gift{
    string gift_name;
    int gift_value;
};

int sum(vector<Gift>& gifts)
{
    //              
    assert(true);
    /*                
                                                        
    */
    int total = 0;
    for(int i=0; i<gifts.size(); i++){
        total += gifts[i].gift_value;
    }
    return total;
}

void improve(vector<Gift> current, vector<Gift>& best)
{
    //              
    assert(true);
    /*                
                                                                                  
    */
    if(sum(current) > sum(best)){
        best = current ;
    }
}

void gifts(vector<Gift>& wishlist, vector<Gift>& best, vector<Gift>& current, int budget, int gift_index)
{
    //              
    assert(true);
    /*                
                                                                                                             
                                                 
    */
    //          
    if(budget == 0){
        best = current;
        return;
    } else if(budget < 0){
        return;
    } else if(gift_index >= wishlist.size()){
        improve(current, best);
        return;
    //              
    } else{
        //                                                             
        current.push_back(wishlist[gift_index]);
        gifts(wishlist, best, current, budget - wishlist[gift_index].gift_value, gift_index + 1);
        current.pop_back();
        gifts(wishlist, best, current, budget, gift_index + 1);
        return;
    }
}

bool open_file(ifstream& input_file, string filename)
{
    //             
    assert(true);
    /*               
                                                                      
                              
    */
    input_file.open(filename.c_str());
    if(input_file.is_open()){
        return true;
    } else{
        return false;
    }
}

bool input_giftstore(vector<Gift>& giftstore, string filename)
{
    //              
    assert(true);
    /*                
                                                                                                          
                                                                                                                 
    */
    ifstream input_file;
    if( !open_file(input_file, filename) ){
        return false;
    }
    Gift placeholder;
    while(input_file){
        input_file >> placeholder.gift_value;
        //                                          
        input_file.ignore(1, ' ');
        getline(input_file, placeholder.gift_name);
        giftstore.push_back(placeholder);
    }
    //           
    input_file.clear();
    input_file.close();
    if(!input_file){
        //                                      
        return false;
    } else{
        return true;
    }
}

int find_gift_value(string gift_name, vector<Gift>& giftstore){
    //              
    assert(true);
    /*                
                                                                                              
                                                 
    */
    for(int i=0; i<giftstore.size(); i++){
        if(giftstore[i].gift_name == gift_name){
            return giftstore[i].gift_value;
        }
    }
    return -1;
}

void print_gifts(vector<Gift>& gifts)
{
    //              
    assert(true);
    /*                
                                                                      
    */
    for(int i=0; i<gifts.size(); i++){
        cout << "Name: " << gifts[i].gift_name << endl;
        cout << "Price: " << gifts[i].gift_value << endl;
        cout << endl;
    }
    return;
}

bool process_wishlist(string filename, vector<Gift> giftstore)
{
    //              
    assert(true);
    /*                
                                                                                                                                              
                                                                                                                                         
                                                                                      
    */
    ifstream input_file;
    if( !open_file(input_file, filename) ){
        return false;
    }
    int budget;
    input_file >> budget;
    //                                                                          
    input_file.ignore(1, '\n');
    vector<Gift> wishlist;
    Gift placeholder;
    //                                                                                                    
    //                                                 
    while(input_file){
        getline(input_file, placeholder.gift_name);
        placeholder.gift_value = find_gift_value(placeholder.gift_name, giftstore);
        wishlist.push_back(placeholder);
        if(placeholder.gift_value < 0){
            //                                                                                         
            //                     
            wishlist.pop_back();
        }
    }
    //           
    input_file.clear();
    input_file.close();
    if(!input_file){
        //                                      
        return false;
    }
    //                                            
    vector<Gift> ideal_gifts;
    vector<Gift> placeholder_list;
    gifts(wishlist, ideal_gifts, placeholder_list, budget, 0);
    //                                                 
    cout << "Ideal gift list for wishlist in file: " << filename << endl;
    print_gifts(ideal_gifts);
    cout << "Total budget: " << budget << endl;
    cout << "Used budget: " << sum(ideal_gifts) << endl;
    cout << endl << endl;
    return true;
}

//                       

int main()
{
    vector<Gift> giftstore;
    if( !input_giftstore(giftstore, "giftstore.txt") ){
        cout << "Reading gift store failed, exiting." << endl;
        return -1;
    }
    if( !process_wishlist("Desiree.txt", giftstore) ){
        cout << "Processing wishlist failed, exiting." << endl;
        return -1;
    }
    if( !process_wishlist("Edward.txt", giftstore) ){
        cout << "Processing wishlist failed, exiting." << endl;
        return -1;
    }
    if( !process_wishlist("Fabienne.txt", giftstore) ){
        cout << "Processing wishlist failed, exiting." << endl;
        return -1;
    }
    if( !process_wishlist("Andrew.txt", giftstore) ){
        cout << "Processing wishlist failed, exiting." << endl;
        return -1;
    }
    if( !process_wishlist("Belle.txt", giftstore) ){
        cout << "Processing wishlist failed, exiting." << endl;
        return -1;
    }
    if( !process_wishlist("Chris.txt", giftstore) ){
        cout << "Processing wishlist failed, exiting." << endl;
        return -1;
    }
    /*                
                                                         
                                
                   

                                 
                   

                             
                   

                                
                   

                          
                         

                                                        
                                                  
                   

                                                     
                   

                                        
                   

                           
                    

                                                                        
                  

                                                                           
                  

                           
                          

                                                          
                                     
                    

                                        
                   

                                           
                   

                            
                   

                           
                          

                                                        
                                      
                  

                                        
                   

                          
                         

                                                       
                         
                  

                            
                  

                                      
                  

                          
                         

                                                       
                                      
                  

                                    
                   

                        
                  

                          
                         
    */
}

