#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;
//                       
struct Products
{
    int cost;
	string product;
};

istream& operator>> (istream& in, Products& products )
{//               
    assert (true) ;
/*                 
                                                                                     
                                   
*/
    char line[999];
    int cost;
    in >> cost;
    products.cost = cost;
    in.getline(line, 999, ' ');
    in.getline(line, 999, '\n');
    products.product = line;
    return in ;
}

int size (vector<Products>& wishlist)
{//               
    assert (true) ;
/*                 
                                                                  
*/
    return static_cast<int> (wishlist.size()) ;
}

int sum (vector<Products>& wishlist, int from)
{//               
    assert (from >= 0 && from <= size(wishlist)) ;
/*                 
                                                                        
*/
    int sum = 0 ;
    for (int i = from ; i < size(wishlist) ; i++)
        sum += wishlist[i].cost ;
    return sum ;
}

void improve (vector<Products>& current, vector<Products>& best)
{//               
    assert (true) ;
/*                 
                                                                                                  
*/
    if (sum (current, 0) > sum (best, 0))
        best = current ;
}

int gifts (vector<Products>& current, vector<Products>& best, vector <Products>& wishlist, int number, int budget)
{//               
    assert(number >= 0);
/*                
                                                                                
                                                                                       
*/
    if ( budget == 0 )
    {
        best = current ;
        return 1 ;
    }
	else if ( budget < 0 )
    {
        return 0 ;
    }
	else if (number >= wishlist.size())
    {
        improve (current, best);
        return 0;
    }
	else if (sum (current,0) + sum (wishlist, number) <= sum (best,0))
    {
        return 0 ;
    }
	else
    {
		current.push_back (wishlist[number]) ;
		const int wn    = gifts ( current, best, wishlist, number+1, budget - wishlist[number].cost) ;
		current.pop_back () ;
		const int won = gifts ( current, best, wishlist, number+1, budget) ;
		return wn + won ;
	}

}

void readstore (ifstream& inputfile, vector<Products>& products)
{//               
    assert(inputfile);
/*                
                                                                          
*/
    inputfile.open("giftstore.txt");
    int counter = 0;
    while(inputfile)
    {
        inputfile >> products[counter];
        counter++;
    }
    inputfile.close();
}

void readwishlist(vector<string>& wishlist, vector<string>& files, int& budget, ifstream& inputfile, int i)
{//               
    assert(inputfile);
/*                
                                                                              
                             
*/
    inputfile.open(files[i]);
    inputfile >> budget;
    char line[999];
    inputfile.getline(line, 999, '\n');
    int counter = 0;
    while(inputfile)
    {
        inputfile.getline(line, 999, '\n');
        wishlist.push_back(line);
        counter++;
    }
}

void add_costs(vector<string>& wishlist, vector<Products>& store, vector<Products>& wishlistcosts)
{//               
    assert(true);
/*                
                                                                                             
*/
    int endpoint = wishlist.size();
    int i =0;
    while(i < endpoint)
    {
        int j = 0;
        bool flag = true;
        while(store[j].cost && flag)
        {
            if (wishlist[i] == store[j].product && store[j].product != "") //                                                              
            {
                Products temp = {store[j].cost, store[j].product};
                wishlistcosts.push_back(temp);
                flag = false;
            }
            j++;
        }
        i++;
    }
}

void print_wishlist(vector<Products>& wishlist, string name)
{//               
    assert(true);
/*                
                                               
*/
    cout << "Optimal wishlist for " << name << ":\n";
    int i = 0;
    while(i < size(wishlist))
    {
        cout << "\t" << wishlist[i].cost<< "\t" <<wishlist[i].product << "\n";
        i++;
    }
}
int main()
{
    ifstream inputfile;
    vector<Products> store(999);
    vector<string> files = {"Andrew.txt","Belle.txt","Chris.txt","Desiree.txt","Edward.txt","Fabienne.txt"};
    vector<string> names = {"Andrew","Belle","Chris","Desiree","Edward","Fabienne"};
    readstore(inputfile, store);
    for(int i = 0; i < files.size(); i++) //                                                                   
    {
        ifstream inputfile2;
        vector<string> wishlist;
        vector<Products> wishlistcosts;
        vector<Products> current;
        vector<Products> best;
        int budget;
        readwishlist(wishlist, files, budget, inputfile2, i);
        add_costs(wishlist, store, wishlistcosts);
        gifts(current, best, wishlistcosts, 0, budget);
        print_wishlist(best, names[i]);
    }
    return 0;
}

