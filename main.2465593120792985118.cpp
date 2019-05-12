#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <fstream>

/* 
            
                                                       
 */

using namespace std;

struct Gift
{
   int price ;
   string gift_name ;
} ;

void build_vector (vector<Gift>& final_list, string file)
{
    ifstream myfile (file) ;
    while (myfile)
    {
        Gift gift ;
        myfile >> gift.price ;
        myfile.get() ;
        getline(myfile, gift.gift_name) ;
        final_list.push_back(gift);
    }
}

void build_wishlist (vector<Gift>& wishlist, string file, int& budget, vector<Gift> pricelist)
{
    ifstream myfile (file) ;
    myfile >> budget ;
    myfile.get() ;
    while (myfile)
    {
        Gift gift ;
        getline(myfile,gift.gift_name);
        for (int i = 0; i < pricelist.size() ; i++)
        {
            if (gift.gift_name == pricelist[i].gift_name)
                gift.price = pricelist[i].price;
        }
        wishlist.push_back(gift) ;
    }
}

void show ( vector<Gift>& coins )
{//               
    assert (true) ;
//                                                                                                
	const int NO_OF_ELEMS = coins.size() ;
	cout << "{" ;
	if ( NO_OF_ELEMS > 0 )
	{
		for (int i = 0 ; i < NO_OF_ELEMS-1 ; i++)
			cout << coins[i].gift_name << "," ;
		cout << coins[NO_OF_ELEMS-1].gift_name ;
	}
	cout << "}" << endl ;
}

int sum (vector<Gift>& gifts)
{
    int sum = 0;
    for (int i = 0; i < gifts.size(); i++)
        sum = sum + gifts[i].price ;
    return sum ;
}

void improve (vector<Gift>& current, vector<Gift>& best)
{
    if (sum(current) > sum(best))
        best = current;
}

int gifts (vector<Gift>& current, vector<Gift>& best, vector<Gift>& wishlist, int gift, int budget )
{
    //              

    //               
    if (budget == 0)
    {
        best = current;
        return 1;
    }
    else if (budget < 0)
    {
        return 0;
    }
    else if (gift >= wishlist.size())
    {
        improve (current,best);
        return 0;
    }
    else
    {
        current.push_back (wishlist[gift]);
        const int WITH_GIFT = gifts (current, best, wishlist, gift + 1, budget - wishlist[gift].price);
        current.pop_back () ;
        const int WITHOUT_GIFT = gifts (current, best, wishlist, gift + 1, budget) ;
        return WITH_GIFT + WITHOUT_GIFT ;
    }
}

int main()
{
    vector<Gift> giftstore ;
    build_vector(giftstore, "giftstore.txt");
    vector<Gift> wishlist ;
    string filename ;
    cout << "Enter filename: \n" ;
    cin >> filename ;
    int budget;
    build_wishlist(wishlist, filename,budget,giftstore);
    cout << budget << "\n\n" ;
    for ( int i = 0 ; i < wishlist.size() ; i++ )
    {
        cout << wishlist[i].gift_name << " " << wishlist[i].price << '\n';
    }
    vector<Gift> current;
    vector<Gift> best;
    gifts (current,best,wishlist,0,budget);
    show (best);
    return 0;
}

/*                      

                                                             

                                                            

                                                                   

                                                                                    

                                                                                      
                                                                                         
                                                                                         

                                                                                                   
                                                                            

 */

