#include <iostream>
#include <cassert>
#include <cstring>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

string GIFT_STORE_FILE = "giftstore.txt";

enum People { Andrew, Belle, Chris, Desiree, Edward, Fabienne, NoOfPeople};
string Names [] = { "Andrew", "Belle", "Chris", "Desiree", "Edward", "Fabienne" };

struct Gift{
    int price;
    string name;
};

vector<Gift> gift_store;

int size(vector<Gift>& gifts)
{
    return static_cast<int> (gifts.size());
}

istream& operator>> (istream& in, Gift& gift)
{
    in >> gift.price;
    in.ignore(1); //                  
    getline(in, gift.name);
    return in;
}

ostream& operator<< (ostream& out, const Gift gift)
{
    out << gift.price << '\t' << gift.name;
    return out;
}

void show_gifts(vector<Gift> gifts)
{
    //                              
    for(int i = 0; i < size(gifts); i++)
        cout << gifts[i] << endl;
}

void read_gifts_file(ifstream& inputfile, vector<Gift>& gifts)
{
    assert(inputfile.is_open());
    while(inputfile)
    {
        Gift gift;
        inputfile >> gift ;
        if (inputfile)
        {
           gifts.push_back(gift);
           //                     
        }
    };
}

void read_wish_list(ifstream& input, vector<string>& wish_list)
{
    assert(input.is_open());

    while(input)
    {
        string item;
        getline(input, item);
        //                     
        if(input)
            wish_list.push_back(item);
    }
}

int in_store(string gift, vector<Gift>& gifts)
{
    for(int i = 0; i < size(gifts) ;i ++)
    {
        //                                              
        if(gifts[i].name == gift)
            return i;
    }
    return -1;
}

vector<Gift> gifts(vector<Gift>& store, vector<string>& wish_list, int c, int budget, vector<Gift> current)
{
    //          
    if(budget == 0)
        return current;
    if(c == wish_list.size())
        return current;

    int gift_store_index = in_store(wish_list[c], store);
    if(gift_store_index >= 0)
    {
        if(store[gift_store_index].price <= budget)
        {
            current.push_back(store[gift_store_index]);
            current = gifts(store, wish_list, c+1, budget - store[gift_store_index].price, current);
            //                                                        
        }
    }
    return current;
}

int cost(const vector<Gift>& gifts)
{
    int current_cost = 0;
    for(int i = 0; i < gifts.size(); i++)
    {
        current_cost += gifts[i].price;
    }
    return current_cost;
}

//                                                    
//                                                    

int main()
{
    ifstream gifts_input (GIFT_STORE_FILE.c_str());
    if(!gifts_input)
    {
        cout << "Failed to open gifts store file." << endl;
        return -1;
    }

    const string WISH_LIST_PERSON = "Andrew.txt";
    read_gifts_file(gifts_input, gift_store);

    ifstream wish_list_file(WISH_LIST_PERSON.c_str());
    int budget;
    wish_list_file >> budget;
    string endline;
    getline(wish_list_file, endline);
    vector<string> wish_list;
    read_wish_list(wish_list_file, wish_list);

    vector<Gift> optimal_basket;
    //                                 
    for(int i = 0; i < wish_list.size(); i++)
    {
        vector<Gift> current;
        vector<Gift> new_basket = gifts(gift_store, wish_list, i, budget, current);
        //       
        //                                                                 
        if(cost(new_basket) > cost(optimal_basket))
            optimal_basket = new_basket;
    }

    show_gifts(optimal_basket);
    cout << cost(optimal_basket) << endl;

    return 0;
}

