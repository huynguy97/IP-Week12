#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;

//                                                       

ifstream wish_A("Andrew.txt");
ifstream wish_B("Belle.txt");
ifstream wish_C("Chris.txt");
ifstream wish_D("Desiree.txt");
ifstream wish_E("Edward.txt");
ifstream wish_F("Fabienne.txt");
ifstream store("giftstore.txt");

struct Shop
{
    int cost;
    string object;
};

int budget = 0;

vector<string> Wish_list ;

vector<Shop> Bought ;
vector<Shop> Consider ;

vector<Shop> Gift_shop ;

istream& operator>> (istream& in, Shop& store)
{//               
    assert (true) ;
   //                                                     
    char space;
    in >> store.cost;
    in.get();
    getline(in,store.object);
    return in ;
}

void read_store (ifstream& in, vector<Shop>& gifts)
{//               
    assert (in.is_open ()) ;
//                                                            
    for(int  no_gifts = 0; no_gifts < 68; no_gifts ++)
    {
        Shop gift ;
        in >> gift;
        if (in)
        gifts.push_back(gift) ;
    }
}

void read_wish(ifstream& in, vector<string>& wish, int& budget)
{//               
    assert (in.is_open ()) ;
//                                                                                                        

in >> budget;

for(int  no_gifts = 0; no_gifts < 68; no_gifts ++)
    {
        string item;
        getline(in, item);
        if (in)
        wish.push_back(item) ;
    }
}

int sum (vector<Shop>& bought, int from)
{//              
    assert (from >= 0 && from <= static_cast<int>(bought.size())) ;
//                                                           
    int sum = 0 ;
    for (int i = from ; i < static_cast<int>(bought.size()) ; i++)
        sum += bought[i].cost ;
    return sum ;
}

void show (vector<Shop> bought)
{//              
    assert(0 <= static_cast<int>(bought.size()) );
//                                            
    for (int i = 0 ; i< static_cast<int>(bought.size()); i++)
        cout << bought[i].object << endl;
}

bool wishes_come_true(vector<string> wishes, vector<Shop> boat, vector<Shop>& consider, int& budget, int c)
{//              
    assert(c>= 0);
//                                                                                                                
//                                                                                       
    for(int i = 0; i < static_cast<int>(boat.size()); i ++)
    {
        if(wishes[c] == boat[i].object && budget >= boat[i].cost)
        {
            budget = budget - boat[i].cost;
            consider.push_back(boat[i]);
            return true;
        }
    }
    return false;
}

int gifts (vector<string> wishes, vector<Shop> boat,vector<Shop> consider, vector<Shop>& bought, int& budget, int c )
{//              
    assert (c >= 0 );
//                                                                                                                                                                                  
//                                                                                                                                                                              
    if(budget == 0)
    {
        bought = consider;
        return budget;
    }
    else if(c >= static_cast<int>(wishes.size())-1)
    {
        if (sum (consider,0) > sum (bought,0))
        bought = consider ;
        return budget;
    }
    else if(wishes_come_true(wishes, boat, consider, budget, c))
        return (gifts(wishes,boat,consider,bought,budget, c+1));
    else
        return (gifts(wishes,boat,consider,bought,budget, c+1));

    return 1;
}

void who (char person)
{//              
    assert(true);
//                                                                                                  
    switch (person)
    {
        case 'A' :
            read_wish(wish_A,Wish_list, budget);
            cout << "This was not used: " ;
            cout << gifts(Wish_list,Gift_shop,Consider,Bought,budget, 0) << endl;
            cout << "It cost in cents: "<<  sum(Bought, 0)<< endl;
            show(Bought);
            break ;
        case 'B' :
            read_wish(wish_B,Wish_list, budget);
            cout << "This was not used: " ;
            cout << gifts(Wish_list,Gift_shop,Consider,Bought,budget, 0) << endl;
            cout <<  "It cost in cents: "<< sum(Bought, 0)<< endl;
            show(Bought);
            break ;
        case 'C' :
            read_wish(wish_C,Wish_list, budget);
            cout << "This was not used: " ;
            cout << gifts(Wish_list,Gift_shop,Consider,Bought,budget, 0) << endl;
            cout <<  "It cost in cents: "<< sum(Bought, 0)<< endl;
            show(Bought);
            break ;
        case 'D' :
            read_wish(wish_D,Wish_list, budget);
            cout << "This was not used: ";
            cout << gifts(Wish_list,Gift_shop,Consider,Bought,budget, 0) << endl;
            cout <<  "It cost in cents: "<< sum(Bought, 0)<< endl;
            show(Bought);
            break ;
        case 'E' :
            read_wish(wish_E,Wish_list, budget);
            cout << "This was not used: " ;
            cout << gifts(Wish_list,Gift_shop,Consider,Bought,budget, 0) << endl;
            cout <<  "It cost in cents: "<< sum(Bought, 0)<< endl;
            show(Bought);
            break ;
        case 'F' :
            read_wish(wish_F,Wish_list, budget);
            cout << "This was not used: " ;
            cout << gifts(Wish_list,Gift_shop,Consider,Bought,budget, 0) << endl;
            cout <<  "It cost in cents: "<< sum(Bought, 0)<< endl;
            show(Bought);
            break ;
        default :
            cout << endl << "Who?" << endl ;
    }
}

int main()
{
    read_store(store, Gift_shop);

    char person ;
    cout << "Who should we bring gifts to?(type the initial)" << endl;
    cin >> person;
    who (person);

    return 0;
}

