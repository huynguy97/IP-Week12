//                          
//                    

#include <iostream>
#include <vector>
#include <fstream>
#include <assert.h>

using namespace std;

//                                                               
struct giftstruct
{
    string name;
    int price;
};

//                                          
int size(vector<giftstruct>& gifts)
{
    //               
    assert(true);
    //               
    //                         
    return static_cast<int> (gifts.size());
}

//                                                     
int total(vector<giftstruct> gifts)
{
    //               
    assert(true);
    //               
    //                                   
    int i = 0;
    for (int j = 0; j < size(gifts); j++)
    {
        i += gifts[j].price;
    }
    return i;
}

//                                                                     
vector<giftstruct> improve (vector<giftstruct>& attempt, vector<giftstruct>& best)
{
    //               
    assert(attempt.size() >= 0 && best.size() >= 0);
    //               
    //                               
        if (total(attempt) > total(best))
        {
            best = attempt;
        }
        return best;
}

//                                 
void show(vector<giftstruct>& wishlist)
{
    //               
    assert(true);
    //               
    //                                             
    for (int i = 0; i < wishlist.size(); i++)
    {
        cout << wishlist[i].name << endl;
        cout << wishlist[i].price << endl;
    }
}

//                                                      
int gifts(vector<giftstruct>& wishlist, vector<giftstruct>& attempt, vector<giftstruct>& best, int g, int budget)
{
    //               
    assert(wishlist.size() >= 0 && g >= 0);
    //               
    //                                                                                                        
    //                              
    if (budget == 0)
    {
        best = attempt;
        return 1;
    }
    else if (budget < 0)
    {
        return 0;
    }
    else if (g >= wishlist.size())
    {
        best = improve(attempt, best);
        return 0;
    }
    else
    {
        attempt.push_back(wishlist[g]);
        int with_g = gifts(wishlist, attempt, best, g + 1, budget - wishlist[g].price);
        attempt.pop_back();
        int without_g = gifts(wishlist, attempt, best, g + 1, budget);
        return with_g + without_g;
    }

}

//          
//                                                    
//                                        
//                                                                                                                                             
//                                                       

vector<giftstruct> read_giftstore(ifstream& myfile, vector<giftstruct>& giftstore)
{
    //               

    //               
    //                                                         
    if (myfile.is_open())
    {
        string line;
        cout << "file opened succesfully" << endl;
        while (getline(myfile, line))
        {
            //                                                                                                
            int price;
            string name;

        }
        myfile.close();
    }
    else
    {
        cout << "file could not be opened" << endl;
    }
    return giftstore;
}

int main()
{
    //                                            
    vector<giftstruct> wishlist = {{"book", 750}, {"racecar", 2000}, {"playing cards", 300}, {"monitor", 20000}};
    vector<giftstruct> attempt;
    vector<giftstruct> best;
    int g = 0;
    int budget = 22000;

    //                                 
    gifts(wishlist, attempt, best, g, budget);
    show(best);

    //                                
    vector<giftstruct> giftstore; //                                                          
    ifstream myfile ("giftstore.txt");
    read_giftstore(myfile, giftstore);

    return -1;
}

