/*                                                       
                                   
                                   
                                                        */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <cmath>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

typedef string Gift;

struct GiftPrice
{
    Gift name;
    int price;
};

vector<Gift> wishlist;
vector<GiftPrice> giftstore;
vector<GiftPrice> available;
vector<GiftPrice> attempt;
vector<GiftPrice> result;
vector<GiftPrice> vec;

//                     

void available_gifts (vector<GiftPrice>& giftstore, vector<Gift>& wishlist, vector<GiftPrice>& available)
{
    /*               */ assert (true);
    /*                                                                                                 */
    for (int i = 0; i < wishlist.size(); i++)
        for (int x = 0; x < giftstore.size(); x++)
            if (wishlist[i] == giftstore[x].name)
                available.push_back(giftstore[x]);
    cout << "\nAvailable vector contains:" << endl;
    for (int j = 0; j < available.size(); j++)
        cout << available[j].name << " for " << available[j].price << " cents." << endl;
    cout << endl;
}

int minimum (vector<GiftPrice>& available)
{
    /*               */ assert (true);
    /*                                                                                                                                                       */
    int minimum = 500000;
    for (int i = 0; i < available.size(); i++)
    {
        if (available[i].price < available[i+1].price && minimum > available[i].price)
            {
                minimum = available[i].price;
                cout << "Minimum: " << minimum << endl;
            }
    }
    return minimum;
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
//     
//                   
// 

void improve (vector<GiftPrice>& attempt, vector<GiftPrice>& result)
{
    /*               */ assert (true);
    /*                                                                */
    result = attempt;
    for (int i = 0; i < result.size(); i++)
      {
          cout <<" Result vector \ngift: " << result[i].name << " with a price of " << result[i].price << " cents" << endl;
      }
}

int sum (vector<GiftPrice> vec)
{
    /*               */ assert (true);
    /*                                                               */
    int total_value = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        total_value = total_value+ vec[i].price;
    }
    return total_value;
}

int gifts (vector<GiftPrice>& available, int budget, vector<GiftPrice>& attempt, vector<GiftPrice>& result, int present) //                                                                                  
{
    /*               */ assert (true);
    /*                                                                                
                                                                                           
                                     */
      if (budget < 0)
        return 0;
      if (present >= available.size())
      {
          cout << "Base case accepted." << endl;
          if (sum(attempt) > sum(result))
            improve(attempt, result);
          cout << "Leftover budget " << budget << endl;
          return budget;
      }
      else
      {
            cout <<"Starting budget: " << budget << endl;
            cout << "present name " << available[present].name << " price " << available[present].price << endl;
            attempt.push_back(available[present]);
            int with_gift_x;
            if (!(budget - available[present].price == 0))
                with_gift_x = gifts(available, budget - available[present].price , attempt, result, present+1);
            attempt.pop_back();
            cout << "\nNu without gift x proberen. " << endl;
            int without_gift_x = gifts(available, budget, attempt, result, present+1);
            cout << "\nwith gift: " << with_gift_x << "and without " << without_gift_x << endl;
            if (with_gift_x > without_gift_x)
                return with_gift_x;
            else
                return without_gift_x;
      }
}

istream& operator>> (ifstream& infile, GiftPrice& giftstore)
{
    /*               */ assert(true);
    /*               
                                                                                                 
                               
    */
    char space;
    infile >> giftstore.price;
    infile.get(space);
    getline(infile,giftstore.name);
    return infile;
}

int read_giftstore (ifstream& infile, vector<GiftPrice>& giftstore)
{
    /*               */ assert (infile.is_open());
    /*                                                                                                         
                                                                            */
    int no_of_read_gifts = 0;
    do
    {
        GiftPrice gift;
        infile >> gift;
        //                                                                             
        if(infile)
        {
            giftstore.push_back(gift);
            no_of_read_gifts++;
        }
    }
    while (infile);
    return no_of_read_gifts;
}

int read_wishlist (ifstream& infile, vector<Gift>& wishlist, int& budget)
{
    /*               */ assert(infile.is_open());
    /*                                                                                                        
                                                                             */
    int no_of_read_wishes = 0;
    Gift gift;
    infile >> budget;
    cout << "\nBudget: " << budget << " cents." << endl;
    do
    {
        getline(infile, gift);
        cout << "Found wish: " << gift << endl;
        if(infile)
        {
            wishlist.push_back(gift);
            no_of_read_wishes++;
        }
    }
    while (infile);
    return no_of_read_wishes;
}

int read_file_giftstore (string filename)
{
    /*               */ assert(true);
    /*                                                                                                    */
    ifstream infile (filename.c_str());
    if(!infile)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
    const int NO_OF_GIFTS = read_giftstore(infile, giftstore);
    infile.close();
    //                                                                      
    return NO_OF_GIFTS;
}

int read_file_wishlist (string filename, int& budget)
{
    /*               */ assert(true);
    /*                                                                                                     */
    ifstream infile (filename.c_str());
    if(!infile)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
    const int NO_OF_WISHES = read_wishlist(infile, wishlist, budget);
    infile.close();
    //                                                                        
    return NO_OF_WISHES;
}

int main()
{
    int budget = 0;
    int present = 0;
    const int NO_OF_GIFTS = read_file_giftstore("giftstore.txt");
    cout << '\n';
    const int NO_OF_WISHES = read_file_wishlist("Desiree.txt", budget);
    available_gifts(giftstore, wishlist, available);
    gifts(available, budget, attempt, result, present);

    return 0;
}

