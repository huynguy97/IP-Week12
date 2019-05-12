#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

//                      

struct gift_struct
{
    int price;
    string name;
};

struct giftwish
{
    string name;
};

struct person
{
    vector<gift_struct> wishlist;
    int budget;
};

vector<gift_struct> gift_store;

void read_file(ifstream& input)
{
    //   
    assert(input);
    //                                                           
    int price;
    string name;
    while (input)
    {
        input >> price;
        input.ignore(1, ' ');
        getline(input, name);
        gift_struct gift = {price, name};
        gift_store.push_back(gift);
    }
}

person read_wishlist(ifstream& input)
{
    //   
    assert(input);
    //     
    person list;
    int budget;
    string name;
    input >> budget;
    list.budget = budget;
    while(input)
    {
        getline(input, name);
        gift_struct gift = {0, name};
        list.wishlist.push_back(gift);
    }
    return list;
}
int item = 0;
bool instore(vector<gift_struct>& gift_store,  person a, int itemno)
{
    //   
    assert(true);
    //                                                                      
    for (int i = 0 ; i < gift_store.size() ; i++)
    {
        if (gift_store[i].name == a.wishlist[itemno].name)
        {
            item = i;
            return true;
        }
    }
    return false;
}

int gifts(vector<gift_struct>& gift_store, person& a, int i)
{
    //   
    assert(i >= 0);
    /*                                                                                                 
                                                                                            
                                                                               
                                                                                        
                               
    */
    if (instore(gift_store,a,i))
    {
        if ( a.wishlist[i].name == gift_store[item].name)
        {
            if (a.budget - gift_store[item].price > 0)
            {
                a.budget = a.budget - gift_store[item].price;
                cout << "Gift is: " << gift_store[item].name << "." << endl;
                cout << "Budget is: " << a.budget << ". " << endl;
                return (gifts(gift_store, a, i + 1));
            }
            else
            {
                return (gifts(gift_store, a, i + 1));
            }
        }
        else
        {
            return (gifts(gift_store, a, i + 1));
        }
    }
    else if (i < a.wishlist.size())
    {
        return(gifts(gift_store,a,i+1));
    }
    return (a.budget);
}

int main()
{
    cout << "Type store file name: ";
    string infile;
    cin >> infile;
    ifstream input(infile);
    read_file(input);

    cout << "Type wishlist file name: ";
    string wishfile;
    cin >> wishfile;
    ifstream inwish(wishfile);
 //                                                     
//              
person b = read_wishlist(inwish);
string test = b.wishlist[1].name;
    cout << "Remaining Budget is: "<< gifts(gift_store,b,1) << ".";

    return 0;
}

/*                                                                            
  
                                                                                                                    
                        
  
                                                                                                                        
                                                                                          
  
                                                                                                    
  
                                                                                                                                     
                        
*/

