#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct store_item {
    int price;
    string gift_name;
};

struct whishlist {
    int budget = 0;
    vector<string> gift_names;
};

vector<store_item> giftstore;

int size (vector<store_item>& store_item)
{
    return static_cast<int> (store_item.size());
}

bool in_store (string& gifts)
{
//                
    assert ( true);
//                 
//                                           

    for (int x = 0; x < giftstore.size(); x++)
        if (giftstore[x].gift_name == gifts)
            return true;
    return false;
}

void add_gift (whishlist& a, string& giftname)
{
//                
    assert ( true);
//                 
//                                   

    a.gift_names.push_back(giftname);
    for (int x = 0; x < giftstore.size(); x++)
        if (giftstore[x].gift_name == giftname)
            a.budget += giftstore[x].price;
}

whishlist improve (whishlist& a, whishlist& b)
{
//                
    assert ( true);
//                 
//                                              

    if (a.budget >= b.budget)
        return a;
    else
        return b;
}

whishlist gifts (whishlist& whish, int index, whishlist& giftlist)
{
//                
    assert ( index <= whish.gift_names.size() && index >= 0);
//                 
//                                                               

    if (giftlist.budget > whish.budget)
        return {};
    if (index == whish.gift_names.size())
        return giftlist;

    string giftname = whish.gift_names[index];

    if (!in_store(giftname))
        return gifts(whish, index + 1, giftlist);

    whishlist without_gift = gifts(whish, index + 1, giftlist);

    whishlist new_list = giftlist;

    add_gift(new_list, giftname);

    whishlist with_gift = gifts(whish, index + 1, new_list);

    return improve(with_gift, without_gift);
}

void read_store (ifstream& infile)
{
//                
    assert ( infile.is_open());
//                 
//                                               

    string giftname, gift;
    int price;
    store_item present;

    while (infile)
    {
        infile >> price;
        infile.get();
        getline(infile, giftname);

        present.price = price;
        present.gift_name = giftname;

        giftstore.push_back(present);
    }

    return;
}

void read_list (ifstream& infile, whishlist& whish)
{
//                 
    assert ( infile.is_open());
//                 
//                                        

    string giftname, lists;
    int budget;

    getline(infile, lists);
    budget = static_cast<int>(stoi(lists));
    whish.budget = budget;

    while (infile)
    {
        getline(infile, lists);
        if (!infile)
            return;
        whish.gift_names.push_back(lists);
    }

    return;
}

void print (whishlist& whish)
{
    cout << "\nBudget: " << whish.budget << endl;
    cout << "Gifts: ";

    for (int x = 0; x < whish.gift_names.size(); x++)
        cout << whish.gift_names[x] << "\n       ";
}

int main()
{
    whishlist whish, giftlist, result;
    ifstream gift_store, whish_list;
    gift_store.open("giftstore.txt");
    whish_list.open("Edward.txt");
    read_store(gift_store);
    read_list(whish_list, whish);
    result = gifts(whish, 0, giftlist);

    cout << "\nThere are " << result.gift_names.size() << " gifts on the resulting list." << endl;

    print(result);

    gift_store.close();
    whish_list.close();

    if (whish_list || gift_store)
    {
        cout << "The file wasn't closed correctly." << endl;
        return 0;
    }

    return 0;
}

/*                
                                          

       
                                        

            
                               
                                 

      
                                        

            
                  
                     
                               

      
                                        

            
                               
                             
                 

        
                                        

            
                         
                          
                      
                         

       
                                        

             
                                           
                                              
                                 
                    
                                                                 
                                                                    

         
                                        

             
                              
                                 
                                    
                     
*/

