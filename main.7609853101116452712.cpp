
//                                                                

#include <iostream>
#include <cassert>
#include <string>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

struct gift
{
    string price;
    string name;
};

struct Wishlist
{
    int price;
    string name;
};

ostream& operator<< (ostream& out, const gift gifts)
{
    out << gifts.price
        << "\t"
        << gifts.name;
    return out;
}

ostream& operator<< (ostream& out, const Wishlist gifts)
{
    out << gifts.price
        << "\t"
        << gifts.name;
    return out;
}

int calculate_path(vector<int>& attempt, vector<Wishlist>& wishes){
//              
    assert (true);
//                
//                                                               
//                
    int cost = 0;

    for (int i = 0; i < attempt.size(); i++)
        {
            cost = cost + wishes[attempt[i]].price;
        }
    return cost;
}

bool next(int& index, vector<int> attempt, vector<Wishlist> wishes)
{//              
    assert (true);
//                
//                                                                
//                
    int counter;
    for (int i = 0; i < attempt.size(); i++)
                if(index == attempt[i])
                {
                    if (index == wishes.size()-1)
                        counter++;
                        index = 0;
                    if (counter > 1)
                        return false;
                    index ++;
                }
    return true;
}

bool gifts(vector<Wishlist>& wishes, vector<int>& attempt, vector<int>& best_attempt, int& index, int& budget)
{//              
    assert (budget >= 0);
//                
//                                                                                                                                         
//                                                               
//                
    index = 0;
    cout << endl << endl << "SEARCH" << endl << endl;
    if (calculate_path(attempt, wishes) == budget)
    {
        cout << "TEST";

        best_attempt = attempt;
        return true;
    }
    else if(calculate_path(attempt,wishes) > calculate_path(best_attempt, wishes))
    {
        best_attempt = attempt;
        return true;
    }
    else{

        if (index < wishes.size() - 1 && next(index, attempt, wishes))
        {

            attempt.push_back(index);
            for (int i = 0; i < attempt.size(); i++)
                cout << attempt[i] << endl;
            index++;
            return gifts(wishes, attempt, best_attempt, index, budget);
        }
        attempt.pop_back();
        index++;
        return gifts(wishes, attempt, best_attempt, index, budget);
    }
}

//      
void read_giftstore(ifstream& infile_giftstore, vector<gift>& gifts)
{//              
    assert (true);
//                
//                                                                                                                
//                                                                                                                                                                                     
//                                                                                                                                                                               
//                
    gift present;
    infile_giftstore.open("giftstore.txt");
    if (infile_giftstore.is_open())
        cout << "giftstore.txt has been succesfully opened." << endl;
    string gift_price, gift_name;
    while (infile_giftstore)
    {
        getline(infile_giftstore, gift_price, ' ');
        getline(infile_giftstore, gift_name);
        present.price = gift_price;
        present.name = gift_name;
        gifts.push_back(present);
    }
    infile_giftstore.close();
}

int read_wishlist(ifstream& infile_wishlist, vector<gift>& gifts, vector<Wishlist>& wishes)
{//              
    assert (true);
//                
//                                                                                                                                                                  
//                                                                                                                    
//                                                                                                                                            
//                                                                                                                       
//                
    cout << "You can choose one of the following files: Andrew.txt, Belle.txt, Chris.txt, Desiree.txt, Edward.txt or Fabienne.txt" << endl;
    string filename;
    cin >> filename;
    infile_wishlist.open(filename);
    if (infile_wishlist.is_open())
        cout << filename <<" has been succesfully opened." << endl;
    string budget, wish_name;
    getline(infile_wishlist, budget);
    int money = stoi(budget);
    Wishlist wishlist;
    while (infile_wishlist)
    {
        getline(infile_wishlist, wish_name);
        for (int i = 0; i < gifts.size() - 1; i++)
            if (wish_name == gifts[i].name)
                {
                    wishlist.price = stoi(gifts[i].price);
                    wishlist.name = wish_name;
                    wishes.push_back(wishlist);
                }
    }
    infile_wishlist.close();
    return money;
}

int main()
{
    vector<gift> presents;
    vector<Wishlist> attempt;
    vector<Wishlist> best;
    vector<Wishlist> wishes;
    ifstream infile_giftstore;
    ifstream infile_wishlist;
    read_giftstore(infile_giftstore, presents);
    for (int i = 0; i < presents.size(); i++)
        cout << presents[i] << endl;
    int money = read_wishlist(infile_wishlist, presents, wishes);
    for (int i = 0; i < wishes.size(); i++)
        cout << wishes[i] << endl;
    int index = 0;
    int counter = 0;
    int spent = 0;
    gifts(wishes, attempt, best, index, counter, money, spent, money);
    return 0;
}

