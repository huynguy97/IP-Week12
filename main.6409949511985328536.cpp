#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <cmath>

/*                                           

                                                
                                               

                                            */

using namespace std;

/*                                                                         
                                                                           
                                                                           
                                                                           
                                                                         */

string ask_for_name()
{
    //              
    assert (true);
    //                                                 
    string name;
    cout << "what person do you want to see with .txt?" << endl;
    cin >> name;
    cout << name << '\t';
    return name;
}

bool open_file (ifstream& gift, ifstream& person)
{
    //              
    assert(!gift.is_open()&&!person.is_open());
    //                                                                                                                                                                               
    string name = ask_for_name();
    gift.open("giftstore.txt");
    person.open(name.c_str());
    if (gift.is_open() && person.is_open())
        return true;
    else
        cout << "One or more files could not be opened";
    return false;
}

/*                                                                         
                                                                           
                                                                           
                                                                           
                                                                         */

struct Inventory
{
    string item;
    int price;
};

int size (vector<Inventory>& inventory)
{//               
    assert (true) ;
//                                                               
    return static_cast<int> (inventory.size()) ;
}

int size (vector<string>& wishlist)
{//               
    assert (true) ;
//                                                              
    return static_cast<int> (wishlist.size()) ;
}

/*                          */
istream& operator>> (istream& in, Inventory& inventory)
{
    //              
    assert(true);
    //                                                                                                               
    in >> inventory.price;
    getline(in, inventory.item);
    return in;
}

ostream& operator<< (ostream& out, Inventory& inventory)
{
    //             
    assert(true);
    //                                                           
    out << inventory.item << "                 " << inventory.price;
    return out;
}

void show(vector<Inventory>& inventory)
{
    //             
    assert (true);
    //                                                                                                         
    const int NO_OF_ELEMS = size (inventory) ;
	cout << "{" ;
	if ( NO_OF_ELEMS > 0 )
	{
		for (int i = 0 ; i < NO_OF_ELEMS-1 ; i++)
			cout << inventory[i].item << "," ;
		cout << inventory[NO_OF_ELEMS-1].item ;
	}
	cout << "}" << endl ;
}

void read_giftfile(ifstream& invfile, vector<Inventory>& inventory)
{
    //              
    assert(invfile.is_open());
    //              
    //                                                                      

    while (invfile)
    {
        Inventory item;
        invfile >> item;
        if (invfile)
        {
            inventory.push_back(item);
        }
    }
}

void read_personfile(ifstream& person, vector<string>& personlist, int& budget)
{
    //             
    assert(person.is_open());
    //                                                                                                                            
    string number;
    getline(person, number);
    budget = atoi(number.c_str());
    while(person)
    {
        string gift;
        getline(person, gift);
        personlist.push_back(gift);
    }
}

bool match(string chars, int i, string source, int j)
{
    //              
    assert(i >= 0 && j >= 0);
    //                                                                                                                                      
    //                                                                                                 
    if (i == chars.length())
        return true;
    else if (j == source.length())
    {
        return false;
    }
    else if (chars[i] == source[j])
    {
        return match(chars, ++i, source, ++j);
    }
    else if (chars[i] != source[j])
    {
        return match(chars, i, source, ++j);
    }
}

bool price_of(string gift, int& price_item, vector<Inventory>& giftstore)
{
    //              
    assert(true);
    //                                                                                                                     
    //                                                                   
    for (int i = 0; i < size(giftstore); i++)
        {
            if (match(gift, 0, giftstore[i].item, 1))
            {
                price_item = giftstore[i].price;
                return true;
            }
        }
    return false;
}

void make_wishlist_with_price(vector<string>& personlist, vector<Inventory>& giftstore, vector<Inventory>& wishlist)
{
    //              
    assert(true);
    //                                                                                                                                                           
    for(int i = 0; i < size(personlist) - 1; i++)
    {
        int price = 0;
        if(price_of(personlist[i], price, giftstore))
        {
            Inventory item;
            item.item = personlist[i];
            item.price = price;
            wishlist.push_back(item);
        }
    }
}

/*                                                                   

                                          

                                                                    */

int sum (vector<Inventory> best)
{
    //              
    assert(true);
    //                                                                                         
    int sum = 0 ;
    for (int i = 0 ; i < size(best); i++)
        {
        sum += best[i].price;
        }
    return sum ;
}

void improve(vector<Inventory>& current, vector<Inventory>& best)
{
    //              
    assert(true);
    //                                                                               
    if (sum(current) > sum(best))
        {
            best = current;}

}

int gifts(vector<Inventory>& attempt, vector<Inventory>& best, vector<Inventory>& wishlist, int budget, int g)
{
    //              
    assert(g >= 0);
    //                                                                                                                                         

 if(budget == 0) {best = attempt; return 1;}
 else if(budget < 0) {return 0;}
 else if(g >= size(wishlist)) {improve(attempt, best); return 0;}
 else
 {
    attempt.push_back(wishlist[g]);
    int with_g = gifts(attempt, best, wishlist, budget - wishlist[g].price, g+1);
    attempt.pop_back();
    int without_g = gifts(attempt, best, wishlist, budget, g+1);
    return with_g+without_g;
}
}

int main()
{   //              
    assert(true);
    //                                                                                                                                      
    vector <string> personlist;
    vector <Inventory> inventory, attempt, best, wishlist;
    int budget = 0;
    ifstream giftfile, personfile;
    if (open_file(giftfile, personfile))
        {
        read_giftfile(giftfile, inventory);
        read_personfile(personfile, personlist, budget);
        make_wishlist_with_price(personlist, inventory, wishlist);
        }
    else
    return -1;
    gifts(attempt, best, wishlist, budget, 0);
    show(best);
    return 0;
}

/*                                     
                                                                     
                                                                     
                                                                            
                                                                                           
                                                                                                                                                                                                                                                                
                                                                                                                 
                                     */

