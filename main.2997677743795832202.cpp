//                                          
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <fstream>

using namespace std;

double percentage (int a, int b)
{//               
    assert (0 <= a && a <= b && b > 0) ;
//                                                                        
    return static_cast<int>(10000 * static_cast<double> (a) / b) / 100.0;
}

int minimum (int a, int b)
{//               
    assert (true) ;
//                                                        
    if (a <= b)
        return a ;
    else
        return b ;
}

int maximum (int a, int b)
{//               
    assert (true) ;
//                                                        
    if (a >= b)
        return a ;
    else
        return b ;
}

int between (int lower, int upper, int x)
{//               
    assert (true) ;
//                                                                                                    
    if (x < lower)  return lower ;
    else if (x > upper) return upper ;
    else return x ;
}

typedef int Gift ;

int size (vector<Gift>& gifts)
{//               
    assert (true) ;
//                                                           
    return static_cast<int> (gifts.size()) ;
}

void read_store (ifstream& infile, vector<Gift>& price, vector<string>& name_store )
{
//              
    assert (infile.is_open());
//                                                                                                             
    string n_input;
    Gift p_input;
    while(infile)
    {
        infile >> p_input;
        infile.ignore();
        getline(infile, n_input);
        price.push_back(p_input);
        name_store.push_back(n_input);
    }
    price.pop_back();
    name_store.pop_back();
    for (int i=0; i <= size(price); i++)
    {
        cout << price[i] << ", " << cout << name_store[i] << endl;
    }
}

void read_wishlist(ifstream& inputfile, Gift& budget, vector<string>& Name)
{
//              
    assert (inputfile.is_open());
//                                                                                          
    inputfile >> budget;
    string n_input;
    while (inputfile)
    {
        getline(inputfile, n_input);
        Name.push_back(n_input);
    }
    cout << budget;
    for (int i=0; i <= 20; i++)
    {
        cout << Name[i] << endl;
    }
}

bool real_money (vector<Gift>& gifts)
{//               
    assert (true) ;
//                                                                                 
    for (int i = 0 ; i < size(gifts) ; i++)
        if (gifts[i] <= 0)
            return false ;
    return true ;
}

Gift minimum (vector<Gift>& gifts, int from)
{//               
    assert (from >= 0 && from <= size(gifts)) ;
//                 
//                                                                                                            
    if (from == size(gifts))
        return 0 ;
    Gift m = gifts[from] ;
    for (int i = from+1 ; i < size(gifts); i++)
        if (gifts[i] < m)
            m = gifts[i] ;
    return m ;
}

int sum (vector<Gift>& gifts, int from)
{//               
    assert (from >= 0 && from <= size(gifts)) ;
//                 
//                                                                                                            
    int sum = 0 ;
    for (int i = from ; i < size(gifts) ; i++)
        sum += gifts[i] ;
    return sum ;
}

int sum (vector<Gift>& gifts)
{
    return sum (gifts,0) ;
}

void improve (vector<Gift>& current, vector<Gift>& best)
{//               
    assert (true) ;
//                 
//                                                                 
    if (sum (current) > sum (best))
        best = current ;
}

void show ( vector<Gift>& gifts )
{//               
    assert (true) ;
//                                                                                                
	const int NO_OF_ELEMS = size (gifts) ;
	cout << "{" ;
	if ( NO_OF_ELEMS > 0 )
	{
		for (int i = 0 ; i < NO_OF_ELEMS-1 ; i++)
			cout << gifts[i] << "," ;
		cout << gifts[NO_OF_ELEMS-1] ;
	}
	cout << "}" << endl ;
}

int get_price()
{
//                                                                                        
}

int solutions ( vector<Gift>& current, vector<Gift>& best, vector<Gift>& price, int c, int target)
{//               
    assert (real_money(price) && 0 <= c && c <= size(price)) ;
//                 
//                                                                                                                              
//                                                                                                                 
	if ( target == 0 )           { best = current ; return 1 ; }
	else if ( target < 0 )       { return 0 ; }
	else if ( c >= size(price) ) { improve (current, best) ;
                                   return 0 ; }
	else {
//                                                                                                                                                                                              
		current.push_back ( price[c] ) ;
		const int WITH_C    = solutions ( current, best, price, c+1, target - price[c] ) ;
		current.pop_back () ;
		const int WITHOUT_C = solutions ( current, best, price, c+1, target ) ;
		return WITH_C + WITHOUT_C ;
	}
}

int enter_non_negative_number (string prompt)
{//               
    assert (true) ;
//                                                                            
	int n = -1 ;
	do {
        cout << prompt ;
        cin  >> n ;
	}
	while (n < 0) ;
    return n ;
}

void enter_command ()
{//               
    assert (true) ;
//                                                                                                      
    cout << "Choose one of the following commands:"               << endl ;
    cout << "5. Keep track of best solution so far"               << endl ;
    int choice ;
    cin  >> choice ;
}

void find_best_solution (vector<Gift>& gifts, int value)
{//               
    assert (real_money(gifts)) ;
//                                                                                     
//                                      
    vector<Gift> current ;
    vector<Gift> best ;
    cout << endl << "The number of solutions to make " << value << " is: " << endl ;
    cout << solutions (current, best, gifts, 0, value) ;
    cout << endl << "One best found solution is: " << endl ;
    show (best) ;
    cout << endl << "It has value: " << sum(best) << endl ;
    cout << endl ;
}

int main()
{
    vector<Gift> price;
    vector<string> name_store;
    vector<string> Name;
    Gift budget;
    ifstream infile ("giftstore.txt");
//                                          
    ifstream inputfile ("Desiree.txt");
    read_wishlist(inputfile, budget, Name);
/*	                                     
	                                                   
	                    
	                                                                        
	                           
     
                                
     
	                                                            
	                                                                                                                                     
                        
                                                 
                                       
*/
    return 0 ;
}

