/*  
                          
                 
                     
            

                                                                   
  */

#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
using namespace std;

struct Gift
{
    int price;
    string name;
};

struct Wishlist
{
    int budget;
    vector<Gift> wishes;
};

void print_list(vector<Gift>& giftlist)
{
    //             
    assert(true);
    //                                                                               
    int total=0;
    for (int i=0; i< giftlist.size(); i++)
    {
        cout << "- " << giftlist[i].price << "\t" << "\t" << giftlist[i].name << endl;
        total += giftlist[i].price;
    }
    cout << "Total cost:\t" << total << endl;
}

int gifts(int i, Wishlist& wishlist, Wishlist& current, Wishlist& best, int remainingbudget)
{
    //             
    assert(i >= 0 );
    //                                                              
    //                                                                                            

    if (i >= wishlist.wishes.size())
    {
        if ((wishlist.budget - remainingbudget) > best.budget && remainingbudget >= 0)
        {
            best.wishes = current.wishes;
            best.budget = (wishlist.budget - remainingbudget);
        }
        return 1;
    }
    else if (remainingbudget < 0)
    {
        return 0;
    }
    else if (remainingbudget == 0)
    {
        best = current;
        return 1;
    }
    else
    {
        current.wishes.push_back(wishlist.wishes[i]);
        const int with_i = gifts(i+1, wishlist, current, best, remainingbudget - wishlist.wishes[i].price);
        current.wishes.pop_back();
        const int without_i = gifts(i+1, wishlist, current, best, remainingbudget);
        return with_i + without_i;
    }
}

int read_giftstore (ifstream& infile, vector<Gift>& inventory)
{
    //             
    assert(true);
    //                                                             

    infile.open("giftstore.txt");

    if (infile.is_open())
    {
        cout << "Giftstore loaded successfully." << endl;
    }

    else{
        cerr << "Error loading file"  << endl;
        return -1;
    }

    while(infile && !infile.eof())
    {
        Gift x;
        infile >> x.price;
        infile.ignore(1);
        getline(infile, x.name);
        if(x.name == "")
        {
            break;
        }
        if(x.price > 0)
        {
            inventory.push_back(x);
        }
    }
    infile.close();
    return inventory.size();
}

int read_wishlist (ifstream& infile, Wishlist& wishlist, string filename)
{
    //             
    assert(true);
    //                                                                             

    infile.open(filename.c_str());

    if(infile.fail())
	{
		cerr << "Error with file" << endl;
		exit(1);
	}

    int i=0;
    if (infile.is_open())
    {
        cout << "You have successfully opened the file " << filename << endl;
    }
    infile >> wishlist.budget;
    infile.ignore(1);
    while (!infile.eof())
    {
        Gift z;
        getline(infile, z.name);
        wishlist.wishes.push_back(z);
        i++;
    }
    infile.close();
    wishlist.wishes.pop_back();
    return i;
}

int add_prices_to_wishlist(vector<Gift>& inventory, Wishlist& wishlist)
{
    //             
    assert(true);
    //                                                   

    int wishlist_length = wishlist.wishes.size();
    int totalinventory = inventory.size();
    int counter = 0;
    for (int i=0; i < wishlist_length; i++)
    {
        for (int j=0; j < totalinventory ; j++)
        {
            if(wishlist.wishes[i].name == inventory[j].name)
            {
                wishlist.wishes[i].price = inventory[j].price;
                counter++;
            }
        }
    }
    wishlist.wishes.pop_back();
    return counter;
}

int main()
{
    string filename;
    ifstream infile;
    cout << "Enter the filename of the wishlist you *wish* to use: (e.g. \"Andrew.txt\")\n" << endl;
    cin >> filename;

    vector<Gift> giftstore;
    Wishlist wishlist, current, best;

    read_wishlist(infile, wishlist, filename);

    read_giftstore(infile, giftstore);

    add_prices_to_wishlist(giftstore, wishlist);

    int budget = wishlist.budget;

    gifts(0, wishlist, current, best, budget);

    cout << "The best solution is:\n";
    print_list(best.wishes);

    return 0;
}

/*  
           
                                            
                                              
               
                               

          
                               
                                   
                                            
               
                               

          
                                            
                                          
                              
                
                               

           
                                       
                                   
                                              
               
                               

          
                                                        
                                                           
                                              
                                 
                                                                              
                                                                                 
               
                                

            
                                           
                                              
                                                 
                                  
               
                                

  */

