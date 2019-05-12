#include <iostream>
#include <fstream>
#include <assert.h>
#include <vector>

//                                                    

using namespace std;

struct Gift {
    int price   ;
    string name;
    };

istream& operator>> (istream& in, Gift& present)
{
    in >> present.price;
    getline(in, present.name);
}

ostream& operator<< (ostream& out, Gift& present)
{
    out << present.price;
    out << present.name;
}

void read_giftlist(vector<Gift>& giftlist, ifstream& input){
//               
    assert(input.is_open());
/*                
                                                     
*/
    Gift product;
    while(input >> product)
        giftlist.push_back(product);

}

void read_wishlist(vector<string>& wishlist, ifstream& input, int& Budget){
//               
    assert(input.is_open()); //                                                                                                                                               
/*                
                                                                            
*/
    input >> Budget;
    string name;

    while(getline(input, name))
        wishlist.push_back(name);

}
void conv_wishlist(vector<Gift> giftlist, vector<string> wishlist, vector<Gift>& price_wishlist){
//               
    assert (giftlist.size() > 0 && wishlist.size() > 0);
/*                
                                                                      
*/
    for (int i = 0; i < giftlist.size() ; i++)
    {
        for(int j = 0; j < wishlist.size(); j++){
        if(giftlist[i].name == wishlist[j])
            price_wishlist.push_back(giftlist[i]);
        }
    }
}
int sum (vector<Gift>& wish, int from)
{
//               
    assert (from >= 0 && from <= wish.size()) ;
/*                
                                                    
*/

    int sum = 0 ;
    for (int i = from ; i < wish.size() ; i++)
        sum = sum + wish[i].price ;
    return sum ;
}

void improve(vector<Gift>& current, vector<Gift> best)
{
 //               
    assert(true);
/*               
                                  
*/
    if(sum(current,0) > sum (best,0))
        best = current;
}
int gifts ( vector<Gift>& current, vector<Gift>& best, vector<Gift>& price_wishlist, int c, int budget)
{
    //               
      assert (price_wishlist.size() > 0);
/*                
                                     
*/
	if ( budget == 0 )           { best = current ; return 1 ; }
	else if ( budget < 0 )       { return 0 ; }
	else if ( c >= price_wishlist.size() ) { improve (current, best) ; return 0 ; }
	else if (sum (current,0) + sum (price_wishlist,c) <= sum (best,0))
                                 { return 0 ; }
	else {
		current.push_back(price_wishlist[c]) ;
		const int WITH_C    = gifts ( current, best, price_wishlist, c+1, budget - price_wishlist[c].price ) ;
		current.pop_back () ;
		const int WITHOUT_C = gifts ( current, best, price_wishlist, c+1, budget) ;
	}
}

void show ( vector<Gift>& wish )
{//               
    assert (true) ;
//                                                                   
	const int NO_OF_ELEMS = wish.size() ;
	cout << "{" ;
	if ( NO_OF_ELEMS > 0 )
	{
		for (int i = 0 ; i < NO_OF_ELEMS-1 ; i++)
			cout << wish[i] << "," ;
		cout << wish[NO_OF_ELEMS-1] ;
	}
	cout << "}" << endl ;
}

int main()

{
    vector<Gift> giftlist;
    vector<string> wishlist;
    vector<Gift> price_wishlist;
    vector<Gift> best;
    vector<Gift> current;
    int Budget;

    ifstream input_wishlist;
    input_wishlist.open("Belle.txt");
    read_wishlist(wishlist, input_wishlist, Budget);
    input_wishlist.close();

    ifstream input_giftlist;
    input_giftlist.open("giftstore.txt");
    read_giftlist(giftlist, input_giftlist);
    input_giftlist.close();

    read_wishlist(wishlist, input_wishlist, Budget);
    input_wishlist.close();

    conv_wishlist(giftlist, wishlist, price_wishlist);
    gifts(current, best, price_wishlist, 0 , Budget);

    show (price_wishlist);

    return 0;
}

