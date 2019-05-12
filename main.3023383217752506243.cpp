//                                                 
//                                            

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
using namespace std;

typedef struct Gifts;
typedef string Wish;

struct Gifts
{
	int price;           //                                      
	string article;      //                                                   
};

void read_wishlist_and_budget(ifstream& infile1, vector<Wish>& wishlist, int& budget)
{
    //            
    assert(true);
    //             
    //                                                                                                
    //                                                          

    string wishl;
    cout << "Please enter the file name of your wish list: ";
    cin >> wishl;
    infile1.open(wishl.c_str());

    if (infile1.is_open())
        cout << "Wish list opened" << endl;
    else
    {
        cout << "Failed" << endl;
        return;
    }

    int money;
    infile1 >> money;
    budget = money;

    string object;
    string object2;
    while(!infile1.eof())
    {
        getline(infile1, object);
        object2 = object + "\n";
        wishlist.push_back(object2);        //                                                  
    }

//                         
//                                             
//                                           
}

//                                                                               
ostream& operator<< (ostream& out, const Gifts gift)
{
    //            
    assert (true) ;
    //             
    //                                    

    out << gift.price   << endl;
    out << gift.article << endl;
    return out ;
}

void read_giftshop(ifstream& infile2, vector<Gifts>& gift)
{
    //            
    assert(true);
    //             
    //                                                                     

    infile2.open("giftstore.txt");

    if (infile2.is_open())
        cout << "Gift shop opened" << endl;

    if (!infile2.is_open())
    {
        cout << "Failed" << endl;
        return;
    }

    while (!infile2.eof())
    {
        Gifts present;
        infile2 >> present.price;
        infile2.get();
        getline(infile2, present.article);
        if (infile2)
            gift.push_back(present);
    }

//                         
//                                         
//                                       
}

int size(vector<Gifts>& gift)
{
    //            
    assert(true);
    //             
    //                                                                     

    return static_cast<int>(gift.size());
}

void show(vector<Gifts>& gift)
{
    //            
    assert(true);
    //             
    //                                                                    

	const int NUMBER_ELEMENTS = size(gift);
	if (NUMBER_ELEMENTS > 0)
	{
		for(int i = 0; i < NUMBER_ELEMENTS-1; i++)
			cout << gift[i].article << ",";
		cout << gift[NUMBER_ELEMENTS-1].article;
	}
}

int sum(vector<Gifts>& gift, int from)
{
    //            
    assert(from >= 0 && from <= size(gift));
    //             
    //                                                                                                   

    int sum = 0;
    for(int i = from; i < size(gift); i++)
        sum = sum + gift[i].price;
    return sum;
}

int sum(vector<Gifts>& gift)
{
    //            
    assert(true);
    //             
    //                                                    

    return sum (gift,0);
}

void improve(vector<Gifts>& current, vector<Gifts>& best)
{
    //            
    assert(true);
    //             
    //                                                                

    if (sum(current) > sum(best))
        best = current;
}

int minimum (vector<Gifts>& gift, int from)
{
    //            
    assert (from >= 0 && from <= size(gift));
    //             
    //                                                                                                                   
    if (from == size(gift))
        return 0;
    int m = gift[from].price;
    for (int i = from+1; i < size(gift); i++)
        if (gift[i].price < m)
            m = gift[i].price;
    return m;
}

int number_of_gifts(vector<Gifts>& attempt, vector<Gifts>& best, vector<Gifts>& gift, vector<Wish>& wishlist, int current_gift, int budget)
{
    //            
    assert(current_gift >= 0 && budget >= 0);
    //             
    //                                                                

    int w = current_gift;

    if (budget == 0)
    {
        best = attempt;
        return budget;
    }
    else if (budget < minimum(gift, 0))
    {
        best = attempt;
        return budget;
    }
    else if (budget < 0)
    {
        return 0;
    }
    else if (current_gift >= size(gift))
    {
        improve(attempt, best);
        return 0;
    }
    else if (sum(attempt) + sum(gift, current_gift) <= sum(best))
    {
        return 0;
    }
    else if (sum(gift, current_gift) < budget)
    {
        return 0;
    }
    else if (minimum(gift, current_gift) > budget)
    {
        return 0;
    }
    else
    {
        for (int i = 0; i < size(gift); i++)
        {
            if (wishlist[w] == gift[i].article && w < wishlist.size())
            {
                w++;
                attempt.push_back(gift[i]);
                int with_current_gift = number_of_gifts(attempt, best, gift, wishlist, current_gift+1, budget - gift[i].price);
                attempt.pop_back();
                int without_current_gift = number_of_gifts(attempt, best, gift, wishlist, current_gift+1, budget);
                return with_current_gift, without_current_gift;
            }
            else if (i == size(gift))
                w++;
        }
    }
    return 0;
}

int main()
{
//                                                                                                                              
//                                    

//                     
//                     
//                                                        
//                                                                                   
//                          
//                       
//               
//
//                                                        
//                                 
//
//                                                              
//               
//
//                 
//
//             

    cout << "Reading wish list" << endl;
    vector<Wish> wishlistt;
    int budget;
    ifstream infile1;
    read_wishlist_and_budget(infile1, wishlistt, budget);
    cout << endl;

    cout << "Reading gift shop" << endl;
    vector<Gifts> giftt;
    ifstream infile2;
    read_giftshop(infile2, giftt);
    cout << endl;

    cout << "Test vector" << endl;
    vector<Gifts> gift = {{20, "article1"}, {10, "article2"}, {25, "article3"}, {10, "article 4"}};
    vector<Gifts> attempt;
    vector<Gifts> best;
    vector<Wish> wishlist = {"article1", "article2", "article3", "article 4"};
    number_of_gifts(attempt, best, gift, wishlist, 0, 40);
    show(best);
    cout << endl;

    return 0;
}

