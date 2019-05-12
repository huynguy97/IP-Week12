#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <cmath>

using namespace std;

//                                                                             
//                                                                             
//                                                                              
//                                                                             
//                                                                             

struct Giftstore{
    int price;
    string gift;
};

istream& operator>>(istream&in, Giftstore& item){
    string str;
    in >> item.price;
    in.ignore();
    getline(in, str);
    item.gift=str;
}

void readlist(ifstream& wish_list, vector<string>& list, int& budget){

    string str;
    getline(wish_list, str);
    budget=stoi(str);

    while(!wish_list.eof())
    {
        getline(wish_list,str);
        if(str!=""){
            list.push_back(str);
        }
    }

}

int minimum (int a, int b)
{//               
    assert (true) ;
//                                                        
    if (a <= b && a>=0)
        return a ;
    else if(b>=0)
        return b ;
}

int sum (vector<Giftstore>& gift,int from)
{//               
//                 
//                                                                                                            
    int sum = 0 ;
    for (int i = 0; i < gift.size() ; i++)
        sum += gift[i].price ;
    return sum ;
}

int sum (vector<Giftstore>& coins)
{
    return sum (coins,0) ;
}

void improve (vector<Giftstore>& current, vector<Giftstore>& best)
{//               
    assert (true) ;
//                 
//                                                                 
    if (sum (current) > sum (best))
        best = current ;
}

int gifts ( vector<Giftstore> filtered, vector<Giftstore>& current, vector<Giftstore>& best, int c, int budget){

    if ( budget == 0 )           { best = current ; return 1 ; }
else if ( budget < 0 )       { return 0; }
else if ( c == filtered.size() ) { improve (current, best) ; return 0; }
else {
    int WITH_C_=0;
        current.push_back ( filtered[c]) ;
        const int WITH_C    = gifts ( filtered, current, best, c+1, budget - current[c].price ) ;
        current.pop_back () ;

        const int WITHOUT_C = gifts ( filtered, current, best, c+1, budget) ;
        return WITH_C + WITHOUT_C;
    }
}

void filter(vector<Giftstore>& gift_instore, vector<string>& list, vector<Giftstore>& filtered){

    for (int k = 0; k < gift_instore.size(); ++k) {
        for (int j = 0; j < list.size(); ++j) {
            if(gift_instore[k].gift==list[j]){
                filtered.push_back(gift_instore[k]);
            }
        }
    }

}
int main()
{
    vector<Giftstore> gifts_price;
    vector<Giftstore> best;
    vector<Giftstore> filtered;
    vector<Giftstore> current;
    vector<string> list;
    Giftstore gift_instore;
    ifstream store;
    ifstream person;
    int budget;
    int i=0;
    store.open("giftstore.txt");
    person.open("Andrew.txt");
    while(!store.eof()) {
        store >> gift_instore;
        if(gift_instore.gift!=""){
            gifts_price.push_back(gift_instore);
        }
    }
    readlist(person, list, budget);

filter(gifts_price, list, filtered);

gifts(filtered, current, best, i, budget);

    for (int j = 0; j < best.size(); ++j) {
        cout <<best[j].gift<<endl;
    }
}
