#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

/*
                       
                            

        

       
                               
                                  

      
                  
                     
                               

      
                               
                              
                 

        
                           
                       
                                  

       
                                            
                                               
                                  
                      
                                                                 
                                                                    

         
                                
                                  
                                     
                      

*/

struct Gift{
    //         
    int price;
    string name;
};

int sum(vector<Gift>& sumVector){
    //             
    assert(true);

    //              
    //                                              

    int theSum = 0;

    for(int i = 0; i < sumVector.size(); i++){
        theSum += sumVector[i].price;
    }

    return theSum;
}

int sum_from(vector<Gift>& sumVector, int from){
    //             
    assert(from >= 0 && from < sumVector.size());

    //              
    //                                                                       

    int theSum = 0;

    for(int i = from; i < sumVector.size(); i++){
        theSum += sumVector[i].price;
    }

    return theSum;
}

void improve(vector<Gift>& a, vector<Gift>& b){
    //             
    assert(true);

    //              
    //                                     

    if(sum(a) > sum(b))
        b = a;
}

int gifts(vector<Gift>& wishlist, vector<Gift>& solution, vector<Gift>& attempt, int current, int budget){
    //             
    assert(current >= 0);

    //              
    //                                                      

    if(budget == 0){
        solution = attempt;
        return 1;
    }
    else if(budget < 0){
        return 0;
    }
    else if(current >= wishlist.size()){
        improve(attempt, solution);
        return 0;
    }
    else if(sum(attempt) + sum_from(wishlist, current) <= sum(solution)){
        return 0;
    }
    else{
        attempt.push_back(wishlist[current]);

        int with_current = gifts(wishlist, solution, attempt, current + 1, budget - wishlist[current].price);

        attempt.pop_back();
        int without_current = gifts(wishlist, solution, attempt, current + 1, budget);

        return with_current + without_current;
    }
}

void get_all_gifts(vector<Gift>& allGifts, string storeFile){
    //             
    assert(true);

    //              
    //                                                                       

    ifstream stream;

    stream.open(storeFile.c_str());

    if(!stream.is_open())
        cout << "Could not retrieve all gifts" << endl;

    while(stream){
        Gift newGift;
        stream >> newGift.price;
        stream.ignore(256, ' ');

        char a;
        stream.get(a);
        string name = "";

        while(a != '\n'){
            //                       
            //                         
            name += a;
            stream.get(a);
        }

        newGift.name = name;

        allGifts.push_back(newGift);
    }

    allGifts.pop_back();
    stream.close();
}

int get_gift_price(vector<Gift> allGifts, string name){
    //             
    assert(true);

    //              
    //                                                                             

    for(int i = 0; i < allGifts.size(); i++){
        if(allGifts[i].name == name)
            return allGifts[i].price;
    }

    return 0;
}

int get_wishlist(vector<Gift> allGifts, vector<Gift>& wishList, string listFile){
    //             
    assert(true);

    //              
    //                                                         

    ifstream stream;
    int budget;

    stream.open(listFile.c_str());

    if(!stream.is_open())
        cout << "Could not retrieve wish list" << endl;

    stream >> budget;
    stream.ignore(256, '\n');

    while(stream){
        Gift newGift;

        char a;
        stream.get(a);
        string name = "";

        while(a != '\n'){
            //                       
            //                         
            name += a;
            stream.get(a);
        }

        newGift.name = name;
        newGift.price = get_gift_price(allGifts, name);

        if(newGift.price != 0)
            wishList.push_back(newGift);
    }

    wishList.pop_back();
    stream.close();

    return budget;
}

int main()
{
    vector<Gift> allGifts;
    vector<Gift> wishlist;
    vector<Gift> solution;
    vector<Gift> attempt;

    get_all_gifts(allGifts, "giftstore.txt");

    for(int i = 0; i < allGifts.size(); i++){
        cout << (i + 1) << ": " << allGifts[i].price << " | " << allGifts[i].name << endl;
    }

    cout << endl;

    int budget;
    budget = get_wishlist(allGifts, wishlist, "Andrew.txt");

    cout << "Budget: " << budget << "\n" << endl;

    for(int i = 0; i < wishlist.size(); i++){
        cout << (i + 1) << ": " << wishlist[i].price << " | " << wishlist[i].name << endl;
    }

    gifts(wishlist, solution, attempt, 0, budget);

    cout << "\nBest gifts for this budget:" << endl;

    for(int i = 0; i < solution.size(); i++){
        cout << (i + 1) << ": " << solution[i].price << " | " << solution[i].name << endl;
    }

    return 0;
}

