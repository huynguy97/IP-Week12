#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <fstream>

//                                       
//                                 

using namespace std;

struct article
{
    int price;
    string name;
};

int size_s(vector<string>& vector_to_size)
{//              
    assert(true);
/*               
                                       
*/
    return static_cast<int> (vector_to_size.size());
}

int size_a(vector<article>& vector_to_size)
{//              
    assert(true);
/*               
                                        
*/
    return static_cast<int> (vector_to_size.size());
}

int sum (vector<article>& vector_to_sum)
{//              
    assert(true);
/*               
                               
*/
    int sum_of_vector = 0;
    int j = 0;
    for (int i = 0; i < size_a(vector_to_sum); i++)
    {
        sum_of_vector += vector_to_sum[i].price;
    }
    return sum_of_vector;
}

void iets (vector<article>& giftshop, vector<string>& wishlist_without, vector<article>& wishlist_with)
{//              
    assert(true);
/*               
                                                                                   
*/
    int j = 0;
    for (int i = 0; i < size_s(wishlist_without); i++)
    {
        j = 0;
        while (wishlist_without[i] != giftshop[j].name && j < size_a(giftshop))
            j++;
        if (j < size_a(giftshop))
            wishlist_with.push_back(giftshop[j]);
    }
}

bool gifts (vector<article>& wishlist, vector<article>& giftshop, vector<article>& best_gift, vector<article>& attempt, int budget, int index_wishlist, int index_giftshop)
{//              
    assert(index_wishlist >= 0);
    assert(index_wishlist <= size_a(wishlist));
    assert(index_giftshop >= 0);
    assert(index_giftshop <= size_a(giftshop));
/*               
                                                                                                                                      
*/
    if (budget == 0)
    {
        best_gift = attempt;
        return true;
    }
    else if (budget < 0 || index_giftshop == size_a(giftshop))
        return false;
    else if (index_wishlist == size_a(wishlist) && sum(attempt) > sum(best_gift))
    {
        best_gift = attempt;
        return true;
    }
    else if (index_wishlist == size_a(wishlist))
        return false;
    else
    {
        attempt.push_back(wishlist[index_wishlist]);
        bool attempt_with = gifts(wishlist, giftshop, best_gift, attempt, budget - wishlist[index_wishlist].price, index_wishlist+1, index_giftshop+1);
        attempt.pop_back();
        bool attempt_without = gifts(wishlist, giftshop, best_gift, attempt, budget, index_wishlist+1, index_giftshop+1);
        return attempt_with || attempt_without;
    }
}

void input_giftshop(vector<article>& giftshop)
{//              
    assert(true);
/*               
                                   
*/
    ifstream giftstore_text;
    giftstore_text.open("giftstore.txt");

    string gift;
    string price_str;
    article gift_article;

    while (getline(giftstore_text, gift))
    {
        price_str = gift.substr(0, gift.find(" "));
        gift_article.price = stoi(price_str);
        gift_article.name = gift.substr(gift.find(" ") + 1);
        giftshop.push_back(gift_article);
    }

    giftstore_text.close();

}

int input_wishlist(string person, vector<string>& wishlist_without)
{//              
    assert(true);
/*               
                                                  
*/
    ifstream wishlist_text;
    person += ".txt";
    wishlist_text.open(person.c_str());

    int budget;
    bool first_line = true;
    string wish;

    while (getline(wishlist_text, wish))
    {
        if (first_line)
        {
            budget = stoi(wish);
            first_line = false;
        }
        else
            wishlist_without.push_back(wish);
    }

    wishlist_text.close();

    return budget;
}

int main()
{
    string person;
    cout << "Enter name:" << endl;
    cin >> person;
    vector<string> wishlist_without;
    vector<article> giftshop;
    vector<article> wishlist;
    vector<article> best_gift;
    vector<article> attempt;
    int budget = input_wishlist(person, wishlist_without);
    input_giftshop(giftshop);
    iets(giftshop, wishlist_without, wishlist);
    if (gifts(wishlist, giftshop, best_gift, attempt, budget, 0, 0))
    {
        for (int i = 0; i < size_a(best_gift); i++)
        {
            cout << best_gift[i].name << endl;
        }
    }
    return 0;
}

