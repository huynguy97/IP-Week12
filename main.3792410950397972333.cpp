#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <assert.h>

using namespace std;

struct Item
{
	int price;
	string cat;
	string name;
};

struct Item2
{
	string cat;
	string name;
};

vector<Item> giftstore;
vector<Item2> item_list;

istream& operator>> (istream& infile, Item& item)
{
    infile >> item.price;
    infile >> item.cat;
    getline(infile, item.name);

    return infile ;
}

istream& operator>> (istream& infile, Item2& item)
{
    infile >> item.cat;
    getline(infile, item.name);

    return infile ;
}

bool operator== (Item& a, Item& b)
{
    if(a.price == b.price && a.cat == b.cat && a.name == b.name){
        return true;
    }
    else{
        return false;
    }
}

int size (vector<Item>& items)
{
    assert(true);
    //                                            
    return static_cast<int> (items.size ());
}

int read_items (ifstream& infile, vector<Item>& giftstore)
{
    //   
    assert(true);
    //    
    //                    
    int no_of_read_items = 0 ;
    do {
        cout << '.';
        Item item;
        infile >> item;
        if (infile){
            giftstore.push_back(item);
            no_of_read_items++;
        }
    }
    while (infile);
    return no_of_read_items;
}

int read_items_list (ifstream& infile, vector<Item2>& item_list)
{
    //   
    assert(true);
    //    
    //                    
    int no_of_read_items = 0 ;
    do {
        cout << '.';
        Item2 item;
        infile >> item;
        if (infile){
            item_list.push_back(item);
            no_of_read_items++;
        }
    }
    while (infile);
    return no_of_read_items;
}

int read_store (string filename, vector<Item>& giftstore)
{
    //   
    assert(true);
    //    
    //                               

    ifstream file (filename.c_str());
    if (!file)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }

    cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_ITEMS = read_items (file, giftstore);
	file.close();
	cout << " Read " << NO_OF_ITEMS << " items." << endl;
	return NO_OF_ITEMS;
}

int read_list(string filename, vector<Item2> item_list, int& money)
{
    //   
    assert(true);
    //    
    //                               

    ifstream file (filename.c_str());
    if (!file)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    file >> money;
    string c;
    getline(file, c);
    cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_ITEMS = read_items_list (file, item_list);
	file.close();
	cout << " Read " << NO_OF_ITEMS << " items." << endl;
	return NO_OF_ITEMS;
}

bool is_in(vector<int>& a, int b)
{
    //   
    assert(true);
    //    
    //                   

    for(int k=0; k < a.size(); k++){
        if(a[k] == b){
            return true;
        }
    }
    return false;
}

vector<Item> gifts(vector<Item>& target, vector<Item>& best, vector<int>& excluded, vector<Item>& current_amount, int current_index, int money)
{
    //   
    assert(true);
    //    
    //                                                            

    cout << "kappa" << endl;
    vector<Item> temp_amount = current_amount;
    temp_amount[0].price += target[current_index].price;
    temp_amount.push_back(target[current_index]);
    if (temp_amount[0].price > money){
        return best;
    }
    if (temp_amount[0].price > best[0].price){
        best = temp_amount;
    }
    vector<int> temp_excluded = excluded;
    temp_excluded.push_back(current_index);

    for(int i = 0; i < size(target); i++){
        if (!is_in(excluded, i)){
            gifts(target, best, temp_excluded, temp_amount, i, money);
        }
    }

    return best;
}

int main()
{

    /*
          
                            
                          
    */

    int money;
    cout << read_store("giftstore.txt", giftstore) << endl;
    cout << read_list("Andrew.txt", item_list, money) << endl;
    cout << "Items in giftstore: " << size(giftstore) << "\tItems on the list: " << item_list.size() << endl;

    vector<Item> temp;
    vector<Item> best;
    vector<Item> current_amount;
    vector<int> excluded;
    vector<Item> converted_list;

    for(int i=0; i<item_list.size(); i++){
        string cat = item_list[i].cat;
        string name = item_list[i].name;
        Item tmp = {0, cat, name};
        converted_list.push_back(tmp);
    }

    Item total = {0, "niets", "Total"};
    best.push_back(total);
    current_amount.push_back(total);

    for (int i =0; i < size(converted_list); i++){
        for(int j =0; j < size(giftstore); j++){
            if(converted_list[i].name == giftstore[j].name){
                converted_list[i].price == giftstore[j].price;
                temp.push_back(converted_list[i]);

            }
        }
    }

    cout << gifts(temp, best, excluded, current_amount, 0, money)[0].price;
    return 0;
}

