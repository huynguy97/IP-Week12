/*                                                 
                         
                                    
                                                  
                                                 */

#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>

using namespace std;

typedef string gift;

struct Gift {
    int price;
    gift name;
};

int store_ls_length = 0;
int wish_list_length = 0;
int gifted_list_length = 0;
int budget;

istream& operator>> (istream& input_file, Gift& gift)
{
    /*                 */
    assert (input_file);
    /*                 
                                                          */
    input_file >> gift.price;
    getline(input_file, gift.name);
    gift.name.erase(0,1);
    return input_file;
}

void get_store_list(ifstream& input_file, vector<Gift> store_ls)
{
    /*                 */
    assert(input_file.is_open());
    /*                 
                                                         */
    Gift g;
    input_file >> g;
    while (input_file)
    {
        input_file >> g;
        if (input_file)
        {
            store_ls_length++;
            store_ls.push_back(g);
        }
    }
    input_file.close();
}

void get_wish_list(ifstream& input_file, vector<gift>& wish_list, int& budget)
{
    /*                 */
    assert(input_file.is_open());
    /*                 
                                                                                                
                                                                   */
    input_file >> budget;
    gift g;
    getline(input_file, g);
    while (input_file)
    {
        getline(input_file, g);
        if (input_file)
        {
            wish_list_length++;
            wish_list.push_back(g);
        }
    }
    input_file.close();
}

int in_store(const vector<Gift>& store_ls, int store_ls_length, int i, const gift& g)
{
    /*                 */
    assert(i <= store_ls_length);
    /*                 
                                                                       
                                */
    if (i == store_ls_length)
        return -1;
    else if (store_ls[i].name == g)
        return store_ls[i].price;
    else
        return in_store(store_ls, store_ls_length, ++i, g);
}

vector<gift> gifts(const vector<Gift> &store_ls, vector<gift> wish_list, int wish_list_length, int& budget, vector<gift> gifted, int i)
{
    /*                 */
    assert(i <= wish_list_length && budget >= 0);
    /*                 
                                                         */
    if (i == wish_list_length || budget == 0)
        return gifted;
    int price = in_store(store_ls, store_ls_length, 0, wish_list[i]);
    if (price >= 0 && budget-price >= 0)
    {
        gifted.push_back (wish_list[i]);
        budget -= price;
        gifted_list_length++;
    }
    return gifts (store_ls, wish_list, wish_list_length, budget, gifted, ++i);
}

int main() {
    ifstream input_file;

    vector<Gift> store_ls;
    input_file.open("giftstore.txt");
    get_store_list(input_file, store_ls);

    string name;
    cout << "Get wish list of: ";
    cin >> name;

    vector<gift> wish_list;
    input_file.open(name + ".txt");
    get_wish_list(input_file, wish_list, budget);

    vector<gift> gifted;
    gifted = gifts(store_ls, wish_list, wish_list_length, budget, gifted, 0);

    return 0;
}
