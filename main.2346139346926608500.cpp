#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <vector>

using namespace std;

typedef string Name;

struct Product
{
    int prize;
    Name name;
};

istream& operator>> (ifstream& in, Name& name)
{//               
    assert (true) ;
/*                 
                                            
*/
    getline(in, name, '\n');
    return in ;
}

istream& operator>> (ifstream& in, Product& product)
{//               
    assert (true) ;
/*                 
                                                         
                                                                                         

*/
    char c;
    in >> product.prize;
    in.get(c);
    in >> product.name;
    return in ;
}

void print_wish_list(vector<Name>& wish_list)
{
    //         
    assert(true);
    //          
    //                                       
    for(int i=0;i<wish_list.size(); i++)
        cout << wish_list[i] << endl;
    cout << endl;
}

int location_in_store(Name gift_name, vector<Product>& gift_store)
{
    //         
    assert(true);
    //          
    //                                                                     
    //                                                                   
    int i;
    for(i=0; i<gift_store.size(); i++)
    {
        if( gift_store[i].name==gift_name )
            return i;
    }
    return i;
}

void gifts(vector<Name>& attempt, vector<Name>& best, int& smallest_budget_left, vector<Product>& gift_store,
                    vector<Name>& wish_list, int index, int budget_left)
{
    //         
    assert(budget_left>=0 && index>=0);
    //          
    //                                                                             
    //                                                      

    if(index>=wish_list.size())
    {
        if(budget_left<smallest_budget_left)
        {
            smallest_budget_left=budget_left;
            best= attempt;
        }
        return;
    }
    int location_gift = location_in_store( wish_list[index], gift_store );
    if( location_gift == gift_store.size())
    {
        gifts( attempt, best, smallest_budget_left, gift_store, wish_list, index+1, budget_left );
        return;
    }
    else if ( budget_left-gift_store[location_gift].prize <0 )
    {
        gifts( attempt, best, smallest_budget_left, gift_store, wish_list, index+1, budget_left );
        return;
    }
    else
    {
        gifts( attempt, best, smallest_budget_left, gift_store, wish_list, index+1, budget_left );
        attempt.push_back(wish_list[index]);
        gifts( attempt, best, smallest_budget_left, gift_store, wish_list, index+1, budget_left-gift_store[location_gift].prize );
        attempt.pop_back();
        return ;
    }
}

void read_gift_store(vector<Product>& gift_store)
{
    //         
    assert(true);
    //          
    //                                                                     
    //                                      

    ifstream inputfile;
    inputfile.open( "giftstore.txt");
    if(!inputfile.is_open())
    {
        cout << "Couldn't read file\n";
        return;
    }
    Product product;
    inputfile >> product;
    while(inputfile)
    {
        gift_store.push_back(product);
        inputfile >> product;
    }
    return;
}

void read_wish_list(vector<Name>& wish_list, int& budget, string filename)
{
    //         
    assert(true);
    //          
    //                                                                        
    //                                      
    ifstream inputfile;
    inputfile.open(filename);
    if(!inputfile.is_open())
    {
        cout<<"File couldn't be opened\n";
        return;
    }
    Name name;
    char c;
    inputfile >> budget;
    inputfile.get(c);
    inputfile >> name;
    while(inputfile)
    {
        wish_list.push_back(name);
        inputfile >> name;
    }
    return;
}

int main()
{
    vector<Product> gift_store;

    read_gift_store(gift_store);
//                                                                                                                                      

    vector<Name> wish_list;
    vector<Name> attempt;
    vector<Name> best;
    int budget, smallest_budget_left;
    string filename = "Desiree.txt";
    read_wish_list(wish_list, budget, filename);
//                                                                        
    smallest_budget_left = budget;
//                               

    gifts(attempt, best, smallest_budget_left, gift_store, wish_list, 0, budget);
    cout << "Best gifts for wish list in " << filename << ":\n";
    print_wish_list(best);

    return 0;
}

