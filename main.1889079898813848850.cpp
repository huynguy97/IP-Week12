#include <cstdlib>
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

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

typedef int Coin ;

int size (vector<Coin>& coins)
{//               
    assert (true) ;
//                                                           
    return static_cast<int> (coins.size()) ;
}

bool real_money (vector<Coin>& coins)
{//               
    assert (true) ;
//                                                                                 
    for (int i = 0 ; i < size(coins) ; i++)
        if (coins[i] <= 0)
            return false ;
    return true ;
}

Coin minimum (vector<Coin>& coins, int from)
{//               
    assert (from >= 0 && from <= size(coins)) ;
//                 
//                                                                                                            
    if (from == size(coins))
        return 0 ;
    Coin m = coins[from] ;
    for (int i = from+1 ; i < size(coins); i++)
        if (coins[i] < m)
            m = coins[i] ;
    return m ;
}

int sum (vector<Coin>& coins, int from)
{//               
    assert (from >= 0 && from <= size(coins)) ;
//                 
//                                                                                                            
    int sum = 0 ;
    for (int i = from ; i < size(coins) ; i++)
        sum += coins[i] ;
    return sum ;
}

int sum (vector<Coin>& coins)
{
    return sum (coins,0) ;
}

void improve (vector<Coin>& current, vector<Coin>& best)
{//               
    assert (true) ;
//                 
//                                                                 
    if (sum (current) > sum (best))
        best = current ;
}

void show ( vector<Coin>& coins )
{//               
    assert (true) ;
//                                                                                                
	const int NO_OF_ELEMS = size (coins) ;
	cout << "{" ;
	if ( NO_OF_ELEMS > 0 )
	{
		for (int i = 0 ; i < NO_OF_ELEMS-1 ; i++)
			cout << coins[i] << "," ;
		cout << coins[NO_OF_ELEMS-1] ;
	}
	cout << "}" << endl ;
}

void swap (vector<Coin>& coins, int i, int j)
{//               
    assert (0 <= i && i < size (coins) && 0 <= j && j < size (coins)) ;
//                                                                                    
    const Coin HELP = coins[i] ;
    coins[i] = coins[j] ;
    coins[j] = HELP ;
}

bool occurs (Coin x, vector<Coin>& coins, int c, int& position)
{//               
    assert (0 <= c && c < size(coins)) ;
//                                                                                                                    
//                                                                                               
    for (int i = 0 ; i <= c ; i++)
        if (coins[i] == x)
        {
            position = i ;
            return true ;
        }
    return false ;
}

bool check_selection (vector<Coin>& a, vector<Coin>& b, int c)
{//               
    assert (0 <= c && c < size (b)) ;
//                                                                                               
//                                                                                                          
//                           
    if (size (a) == 0) { return true ; }     //                                                            
    else if (c == 0)   { return false ; }    //                                                                    
    int index_of_last_in_b ;
    int last_of_a = size(a) - 1 ;
    bool does_occur = occurs ( a[last_of_a], b, c, index_of_last_in_b ) ;
    if (!does_occur)   { return false ; }    //                                                
    else
    {
        swap (b, index_of_last_in_b, c) ;    //                                 
        a.pop_back () ;                      //                                 
        return check_selection (a, b, c-1) ; //                                      
    }
}

bool is_selection (vector<Coin>& a, vector<Coin>& b, int c)
{//               
    assert (0 <= c && c <= size(b)) ;
//                                                                                               
//                                                      
    if (c == 0)
        return size(a) == 0 ;   //                                                                 
    else
    {
        vector<Coin> x = a ;    //                                          
        vector<Coin> y = b ;    //                                          
        return check_selection (x, y, c) ;
    }
}

int solutions1 ( vector<Coin>& money, int c, int target )
{//               
    assert (real_money(money) && 0 <= c && c <= size(money)) ;
//                 
//                                                                                                            
	if	    ( target == 0 )		    { return 1; }
	else if ( target < 0 )		    { return 0; }
	else if ( c >= size(money) )	{ return 0; }
	else {
		const int WITH_C    = solutions1 ( money, c+1, target-money[c] );
		const int WITHOUT_C = solutions1 ( money, c+1, target );
		return WITH_C + WITHOUT_C;
	}
}

int solutions2 ( vector<Coin>& attempt, vector<Coin>& money, int c, int target )
{//               
    assert (real_money(money) && 0 <= c && c <= size(money) && is_selection (attempt, money, between (0, maximum(0,size(money)-1), c))) ;
//                 
//                                                                                                                                
//                                             
	if	    ( target == 0 )		    { show (attempt) ; return 1; }
	else if ( target < 0 )	    	{ return 0;	}
	else if ( c >= size(money) )	{ return 0;	}
	else {
		attempt.push_back ( money[c] ) ;
		const int WITH_C    = solutions2 ( attempt, money, c+1, target - money[c] ) ;
		attempt.pop_back () ;
		const int WITHOUT_C = solutions2 ( attempt, money, c+1, target ) ;
		return WITH_C + WITHOUT_C ;
	}
}

int solutions3 ( vector<Coin>& attempt, vector<Coin>& money, int c, int target, int& no_of_fails )
{//               
    assert (real_money(money) && 0 <= c && c <= size(money) && is_selection (attempt, money, between (0, maximum(0,size(money)-1), c)) && no_of_fails >= 0) ;
//                 
//                                                                                                                              
//                                         
//                                                               
	if	    ( target == 0 )		    { show (attempt) ; return 1; }
	else if ( target < 0 )		    { no_of_fails++;            return 0; }
	else if ( c >= size(money) )	{ no_of_fails++;            return 0; }
	else {
		attempt.push_back ( money[c] ) ;
		const int WITH_C    = solutions3 ( attempt, money, c+1, target - money[c], no_of_fails ) ;
		attempt.pop_back () ;
		const int WITHOUT_C = solutions3 ( attempt, money, c+1, target,            no_of_fails ) ;
		return WITH_C + WITHOUT_C ;
	}
}

int solutions4 ( vector<Coin>& attempt, vector<Coin>& money, int c, int target, int& no_of_fails, int& no_of_prunes )
{//               
    assert (real_money(money) && 0 <= c && c <= size(money) && is_selection (attempt, money, between (0, maximum(0,size(money)-1), c)) && no_of_fails >= 0 && no_of_prunes >= 0) ;
//                 
//                                                                                                                              
//                                         
//                                                               
	if	    ( target == 0 )		         { show (attempt) ;  return 1 ; }
	else if ( target <  0 )	    	     { no_of_fails++ ;            return 0 ; }
	else if ( c >= size(money) )	     { no_of_fails++ ;            return 0 ; }
	else if (sum (money,c) < target)     { no_of_prunes++ ;           return 0 ; }
	else if (minimum(money, c) > target) { no_of_prunes++ ;           return 0 ; }
	else {
		attempt.push_back ( money[c] ) ;
		const int WITH_C    = solutions4 ( attempt, money, c+1, target - money[c], no_of_fails, no_of_prunes ) ;
		attempt.pop_back () ;
		const int WITHOUT_C = solutions4 ( attempt, money, c+1, target,            no_of_fails, no_of_prunes ) ;
		return WITH_C + WITHOUT_C ;
	}
}

int solutions5 ( vector<Coin>& current, vector<Coin>& best, vector<Coin>& money, int c, int target)
{//               
    assert (real_money(money) && 0 <= c && c <= size(money) && is_selection (current, money, between (0, maximum(0,size(money)-1), c)) && is_selection (best, money, maximum(0,size(money)-1))) ;
//                 
//                                                                                                                              
//                                                                                                                 
	if ( target == 0 )           { best = current ; return 1 ; }
	else if ( target < 0 )       { return 0 ; }
	else if ( c >= size(money) ) { improve (current, best) ;
                                   return 0 ; }
	else {
		current.push_back ( money[c] ) ;
		const int WITH_C    = solutions5 ( current, best, money, c+1, target - money[c] ) ;
		current.pop_back () ;
		const int WITHOUT_C = solutions5 ( current, best, money, c+1, target ) ;
		return WITH_C + WITHOUT_C ;
	}
}

int solutions6 ( vector<Coin>& current, vector<Coin>& best, vector<Coin>& money, int c, int target, int& no_of_prunes)
{//               
    assert (real_money(money) && 0 <= c && c <= size(money) && is_selection (current, money, between (0, maximum(0,size(money)-1), c)) && is_selection (best, money, maximum(0,size(money)-1)) && no_of_prunes >= 0) ;
//                 
//                                                                                                                              
//                                                                                                                 
	if ( target == 0 )           { best = current ; return 1 ; }
	else if ( target < 0 )       { return 0 ; }
	else if ( c >= size(money) ) { improve (current, best) ; return 0 ; }
	else if (sum (current) + sum (money,c) <= sum (best))
                                 { no_of_prunes++ ; return 0 ; }
	else {
		current.push_back ( money[c] ) ;
		const int WITH_C    = solutions6 ( current, best, money, c+1, target - money[c], no_of_prunes ) ;
		current.pop_back () ;
		const int WITHOUT_C = solutions6 ( current, best, money, c+1, target, no_of_prunes ) ;
		return WITH_C + WITHOUT_C ;
	}
}

void make_money (int no_of_coins, vector<Coin>& coins)
{//               
    assert (no_of_coins >= 0) ;
//                                                                     
	for (int i = 0 ; i < no_of_coins; i++)
		coins.push_back ( (1 + ((i+1) % 17) / (1 + (i % 3))) * 2 ) ;
}

void show_money (vector<Coin>& coins)
{//               
    assert (true) ;
//                                                         
	for (int i = 0 ; i < size(coins); i++)
		cout << coins[i] << " " ;
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

enum Choice {CountOnly=1,CountAndShow,CountAndShowFails,CountAndShowPrunes,BestSolution,PruneBestSolution,Huh};

Choice enter_command ()
{//               
    assert (true) ;
//                                                                                                      
    cout << "Choose one of the following commands:"               << endl ;
    cout << "1. Count all possible combinations"                  << endl ;
    cout << "2. As 1. and show all possible combinations"         << endl ;
    cout << "3. As 2. and count all failed attempts"              << endl ;
    cout << "4. As 3. and count all prematurely aborted attempts" << endl ;
    cout << "5. Keep track of best solution so far"               << endl ;
    cout << "6. Use best solution so far to stop earlier"         << endl ;
    int choice ;
    cin  >> choice ;
    if (choice >= CountOnly && choice < Huh)
        return static_cast<Choice>(choice) ;
    else
        return Huh ;
}

void show_percentage (int a, int no_of_coins)
{//               
    assert (a >= 0 && a <= pow (2,no_of_coins)) ;
//                                                                                       
    cout << " (this is " << percentage (a, pow(2,no_of_coins)) << "% of all combinations)" ;
}

void count_solutions (vector<Coin>& coins, int value)
{//               
    assert (real_money(coins)) ;
//                                                                                               
    cout << endl << "The number of solutions to make " << value << " is: " << endl ;
    int no = solutions1 (coins, 0, value) ;
    cout << no ;
    show_percentage (no, size(coins)) ;
    cout << endl ;
}

void count_and_show_solutions (vector<Coin>& coins, int value)
{//               
    assert (real_money(coins)) ;
//                                                                                         
//                                       
    vector<Coin> solution ;
    cout << endl << "The solutions to make " << value << " are: " << endl ;
    int no = solutions2 (solution, coins, 0, value) ;
    cout << endl << "These are " << no << " solutions" ;
    show_percentage (no, size(coins)) ;
    cout << endl ;
}

void count_and_show_fails (vector<Coin>& coins, int value)
{//               
    assert (real_money(coins)) ;
//                                                                                         
//                                                                                 
    int no_of_fails = 0 ;
    vector<Coin> solution ;
    cout << endl << "The solutions to make " << value << " are: " << endl ;
    int no = solutions3 (solution, coins, 0, value, no_of_fails) ;
    cout << endl << "These are " << no << " solutions " ;
    show_percentage (no, size(coins)) ;
    cout << endl << no_of_fails << " attempts have failed" ;
    show_percentage (no_of_fails, size(coins)) ;
    cout << endl ;
}

void count_and_show_prunes (vector<Coin>& coins, int value)
{//               
    assert (real_money(coins)) ;
//                                                                                         
//                                                                                     
//                           
    int no_of_fails  = 0 ;
    int no_of_prunes = 0 ;
    vector<Coin> solution ;
    cout << endl << "The solutions to make " << value << " are: " << endl ;
    int no = solutions4 (solution, coins, 0, value, no_of_fails, no_of_prunes) ;
    cout << endl << "These are " << no << " solutions" ;
    show_percentage (no, size(coins)) ;
    cout << endl << no_of_fails << " attempts have failed" ;
    show_percentage (no_of_fails, size(coins)) ;
    cout << endl << no_of_prunes << " attempts have been pruned." ;
    show_percentage (no_of_prunes, size(coins)) ;
    cout << endl ;
}

void find_best_solution (vector<Coin>& coins, int value)
{//               
    assert (real_money(coins)) ;
//                                                                                     
//                                      
    vector<Coin> current ;
    vector<Coin> best ;
    cout << endl << "The number of solutions to make " << value << " is: " << endl ;
    cout << solutions5 (current, best, coins, 0, value) ;
    cout << endl << "One best found solution is: " << endl ;
    show (best) ;
    cout << endl << "It has value: " << sum(best) << endl ;
    cout << endl ;
}

void find_best_solution_by_pruning (vector<Coin>& coins, int value)
{//               
    assert (real_money(coins)) ;
//                                                                                     
//                                      
    vector<Coin> current ;
    vector<Coin> best ;
    int no_of_prunes = 0 ;
    cout << endl << "The number of solutions to make " << value << " is: " << endl ;
    cout << solutions6 (current, best, coins, 0, value, no_of_prunes) ;
    cout << endl << "One best found solution is: " << endl ;
    show (best) ;
    cout << endl << "It has value: " << sum(best) << endl ;
    cout << "Number of early failing attempts detected is: " << no_of_prunes ;
    show_percentage (no_of_prunes, size(coins)) ;
    cout << endl ;
}

int main()
{
	const int NO_OF_COINS = enter_non_negative_number ("Enter number of coins (0 or more): ") ;
	const int NO_OF_COMBINATIONS = pow(2,NO_OF_COINS) ;

	vector<Coin> coins ;
	make_money (NO_OF_COINS, coins) ;
	cout << "The collection of coins is: " << endl << endl ;
	show_money (coins) ;
	cout << endl << endl << "Their total value is: " << sum (coins) ;
	cout << endl << endl << "There are at most 2^" << NO_OF_COINS << " = " << NO_OF_COMBINATIONS << " combinations to explore." << endl ;

    cout << endl << "Enter value: " ;
    int value = 0 ;
    cin  >> value ;

    const Choice CHOICE = enter_command () ;
    switch (CHOICE)
    {
        case CountOnly :
            count_solutions (coins, value) ;
            break ;
        case CountAndShow :
            count_and_show_solutions (coins, value) ;
            break ;
        case CountAndShowFails :
            count_and_show_fails (coins, value) ;
            break ;
        case CountAndShowPrunes :
            count_and_show_prunes (coins, value) ;
            break ;
        case BestSolution :
            find_best_solution (coins, value) ;
            break ;
        case PruneBestSolution :
            find_best_solution_by_pruning (coins, value) ;
            break ;
        default :
            cout << endl << "Unknown command" << endl ;
    }
    return 0 ;
}

