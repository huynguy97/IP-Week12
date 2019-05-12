#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;

//                                                                                                                                                       

struct Item {int Cost; string Name;};

int iSize (vector<Item>& v)
{
    //             
    assert(true);
    //                                                
    return static_cast<int>(v.size());
}

bool readStoreFile(vector<Item>& store, string filename)
{
    //             
    assert(filename.length() > 0);
    //                                                                                  
    ifstream file(filename.c_str());
    if (!file.is_open()){
        cout << "ERROR: Could not open file" << endl;
        return false;
    }
    string line = "";
    while (file){
        getline(file, line);
        if (line.length() >= 3){ //                                                                          
            int space = line.find(' ');
            if (space > 0 ){
                int cost = stoi(line.substr(0,space));
                string name = line.substr(space+1);
                if (name.length() > 0 && cost > 0){
                    Item newItem = {cost, name};
                    store.push_back(newItem);
                }
            }
        }
    }
    if (iSize(store) > 0){
        cout << "Succesfull file read - " << iSize(store) << " items read." << endl;
        return true;
    } else {
        cout << "ERROR: Could not read items into store." << endl;
        return false;
    }
    file.close();
}

int findCost(string s, vector<Item>& store)
{ //             
    assert(s.length()>=0);
  //                                                                                                              
    int ms = iSize(store);
    for (int i = 0; i < ms; i++){
        if (store[i].Name == s){
            return store[i].Cost;
        }
    }
    return -1;
}

bool readWishFile(vector<Item>& wishList, int& budget, string filename, vector<Item>& store)
{//             
    assert(iSize(store)>0 && filename.length()>0);
//                                                                                 
    ifstream file(filename.c_str());
    if (!file.is_open()){
        cout << "ERROR: Could not open file" << endl;
        return false;
    }
    string line = "";
    getline(file, line);
    if (line.length() > 0){
        budget = stoi(line);
        if (budget <= 0){
            cout << "Wrong budget format" << endl;
            return false;
        }
    } else {
        cout << "Empty File" << endl;
        return false;
    }

    while (file){
        getline(file, line);
        if (line.length() > 0){
            int cost = findCost(line, store);
            if (cost == -1){ //                 
                cout << "Found item which is not in store: " << line << endl;
            } else {
                Item newItem = {cost, line};
                wishList.push_back(newItem);
            }
        }
    }

    if (iSize(wishList) > 0){
        cout << "Amount of items on wishlist also in store: " << iSize(wishList) << endl;
        return true;
    } else {
        cout << "No presents in store and wishlisht" << endl;
        return false;
    }
    file.close();
}

int calcCost(vector<Item>& attempt)
{
    //             
    assert (true);
    //                                                                     
    int total = 0;
    int ms = iSize(attempt);
    for (int i = 0; i < ms; i++){
            total += attempt[i].Cost;
    }
    return total;
}

int remainingCostMaximum(int index, vector<Item>& wishList)
{//              
    assert(index >= 0 && index < iSize(wishList));
//                                                                                                    
    int total = 0;
    int ms = iSize(wishList);
    for (int i = index; i < ms; i++){
            total += wishList[i].Cost;
    }
    return total;
}

int gifts(int budget, vector<Item>& wishList, vector<Item>& currBest, vector<Item>& currAttempt, int wishListIndex)
{
    //              
    assert (iSize(wishList) > 0 && wishListIndex >= 0);
    //                                                                                                                                                                                    

    /*                  
               
                    
                     
                                                                              
                                                                                                       
                                                                              
                    
                                        
                                                
                                                                              
    */

    if (budget < 0){ //                      
        return 0; //                              
    }

    else if (budget == 0){
        currBest = currAttempt; //                                        
        return 1;
    }

    else if (wishListIndex >= iSize(wishList)){
        if (calcCost(currAttempt) > calcCost(currBest)){
            currBest = currAttempt;
        }
        return 0; //                                                                         
    }

    else if (calcCost(currAttempt) + remainingCostMaximum(wishListIndex, wishList) < calcCost(currBest)){
        return 0; //                                  
    }

    else {
        currAttempt.push_back(wishList[wishListIndex]);
        int nSolW = gifts(budget-wishList[wishListIndex].Cost, wishList, currBest, currAttempt, wishListIndex+1);
        currAttempt.pop_back();

        int nSolWO = gifts(budget, wishList, currBest, currAttempt, wishListIndex+1);

        return nSolW + nSolWO;
    }

}

void printSolution(vector<Item>& sol)
{
    //             
    assert (true);
    //                                                 
    int ms = iSize(sol);
    for (int i = 0; i < ms; i++){
            cout << sol[i].Cost << " - " << sol[i].Name << endl;
    }
}

bool giftsPerson(string fileName, vector<Item>& store)
{
    //             
    assert (fileName.length() > 0 && iSize(store)> 0);
    //                                                                                                             
    //                                                    
    int budget = -1;
    vector<Item>wishList;

    if (!readWishFile(wishList, budget, fileName, store))
    {
        cout << "File error: " << fileName << endl;
        return false;
    }

    vector<Item> currBest;
    vector<Item> currAttempt;
    cout << endl << "Amount of perfect solutions: " << gifts(budget, wishList, currBest, currAttempt, 0) << endl;
    cout << "Best solution: " << calcCost(currBest) << endl;
    printSolution(currBest);
    return true;
}

int main()
{
    vector<Item> store;
    cout << "Reading store file..." << endl;
    if(!readStoreFile(store, "giftstore.txt")){
        cout << "File problem, ending program" << endl;
        return 1;
    }

    cout << "Andrew: " << endl << "==========================================" << endl;
    giftsPerson("Andrew.txt", store);
    cout << "==========================================" << endl << endl << endl;
    cout << "Belle: " << endl << "==========================================" << endl;
    giftsPerson("Belle.txt", store);
    cout << "==========================================" << endl << endl << endl;
     cout << "Chris: " << endl << "==========================================" << endl;
    giftsPerson("Chris.txt", store);
    cout << "==========================================" << endl << endl << endl;
     cout << "Desiree: " << endl << "==========================================" << endl;
    giftsPerson("Desiree.txt", store);
    cout << "==========================================" << endl << endl << endl;
     cout << "Edward: " << endl << "==========================================" << endl;
    giftsPerson("Edward.txt", store);
    cout << "==========================================" << endl << endl << endl;
     cout << "Fabienne: " << endl << "==========================================" << endl;
    giftsPerson("Fabienne.txt", store);

    return 0;
}

/*
                     
                                     
       
                                          
                                             

                              
                   
                              
                                 
                                          

      
                                          
                                            

                              
                   
                 
                    
                              
                                          

      
                                          
                                                              
                                             

                              
                   
                              
                             
                
                                          

        
                                          
                                             

                              
                   
                         
                          
                      
                         
                                          

       
                                          
                                                                      
                                             

                              
                    
                                           
                                              
                                 
                     
                                                                
                                                                   
                                          

         
                                          
                                                           
                                                                    
                                                                 
                                                                   
                                                                       
                                                              
                                                                         
                                                                      
                                             

                              
                    
                               
                                 
                                    
                     

*/

