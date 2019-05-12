#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//                                                       
//                                                   

struct Store_item {
    string name;
    int price;
};

istream& operator>>(istream& in, Store_item& item)
{
    char space;
    in >> item.price;
    in.get(space);
    getline(in, item.name);
    return in;
}

int size(vector<string>& data)
{
    return static_cast<int>(data.size());
}

int size(vector<Store_item>& data)
{
    return static_cast<int>(data.size());
}

int sum_price(vector<string>& gifts, vector<Store_item>& gift_store)
{
    //             
    assert(true);
    /*              
                                               
    */

    int sum = 0;
    for (int i = 0; i < size(gifts); i++) {
        int j = 0;
        while (gift_store[j].name != gifts[i])
            j++;
        sum += gift_store[j].price;
    }

    return sum;
}

bool improve(vector<string>& attempt, vector<string>& best, vector<Store_item>& gift_store)
{
    //             
    assert(true);
    /*              
                                                                                                                            
    */
    return sum_price(attempt, gift_store) > sum_price(best, gift_store);
}

void gifts(vector<string>& attempt, vector<string>& wish_list, int wish_index, vector<Store_item>& gift_store, int budget, vector<string>& best)
{
    //             
    assert(wish_index >= 0);
    /*              
                                                                                                                                   
                                                                                                                                        
    */
    if (budget < 0)
        return;
    else if (budget == 0) {
        best = attempt;
        return;
    } else if (wish_index >= size(wish_list)) {
        if (improve(attempt, best, gift_store))
            best = attempt;
        return;
    }

    int i = 0;
    while (i < size(gift_store) && wish_list[wish_index] != gift_store[i].name)
        i++;
    if (i < size(gift_store)) {
        attempt.push_back(wish_list[wish_index]);
        gifts(attempt, wish_list, wish_index + 1, gift_store, budget - gift_store[i].price, best);
        attempt.pop_back();
    }

    gifts(attempt, wish_list, wish_index + 1, gift_store, budget, best);
}

void read_gift_store(vector<Store_item>& gift_store)
{
    //             
    assert(size(gift_store) == 0);
    /*              
                                                               
    */
    ifstream fin ("giftstore.txt");
    Store_item item;
    fin >> item;
    while (fin) {
        gift_store.push_back(item);
        fin >> item;
    }
    fin.close();
}

void skip_to_newline(istream& in)
{
    //             
    assert(true);
    /*              
                              
    */
    string remains;
    getline(in, remains);
}

void read_wish_list(string name, vector<string>& wish_list, int& budget)
{
    //             
    assert(size(wish_list) == 0);
    /*              
                                                                
    */
    name += ".txt";
    ifstream fin (name.c_str());
    string gift;
    fin >> budget;
    skip_to_newline(fin);
    getline(fin, gift);
    while (fin) {
        wish_list.push_back(gift);
        getline(fin, gift);
    }
    fin.close();
}

void show_gifts(vector<string> gifts)
{
    //             
    assert(true);
    /*              
                                                 
    */

    for (int i = 0; i < size(gifts); i++)
        cout << gifts[i] << endl;
}

int main()
{
    vector<Store_item> gift_store;
    vector<string> names = {"Andrew", "Belle", "Chris", "Desiree", "Edward", "Fabienne"};

    read_gift_store(gift_store);

    for (int i = 0; i < size(names); i++) {
        vector<string> wish_list;
        int budget;
        read_wish_list(names[i], wish_list, budget);

        vector<string> attempt;
        vector<string> best;
        int wish_index = 0;
        gifts(attempt, wish_list, wish_index, gift_store, budget, best);

        cout << names[i] << "'s gifts are:\n";
        show_gifts(best);
        cout << endl;
    }

    return 0;
}

