#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <math.h>
#include <tuple>
#include <cctype>
#include <locale>
#include <algorithm>

using namespace std;

//                               

typedef int list;

struct Presents
{
    int price;      //                                           
    string name;    //                                       
};

int size (vector<list>& lists)
{
    return static_cast<int> (lists.size());
}

int size (vector<string>& articles)
{
    return static_cast<int> (articles.size());
}

int size (vector<Presents>& presents)
{
    return static_cast<int> (presents.size());
}

istream& operator>> (istream& infile, Presents& presents)
{
    //               
    assert(true);
    /*                
    */
    infile >> presents.price;
    getline(infile,presents.name);
    return infile;
}

ostream& operator<< (ostream& out, const Presents presents)
{//               
    assert (true) ;
/*                 
                                                                                
*/
    out << presents.price   << "\t" ;
    out << presents.name;
    out << endl ;
    return out ;
}

static inline void ltrim(string& s)
{
    //               
    assert(s.size()>=0);
    /*                
                                                                                                                          
    */
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch){return !std::isspace(ch);}));
}

bool real_money (vector<Presents>& presents)
{//               
    assert (true) ;
//                                                                                 
    for (int i = 0 ; i < size(presents) ; i++)
    {
        if (presents[i].price <= 0)
        {
            return false ;
        }
    }
    return true ;
}

bool real_indices (vector<int>& indixes)
{
    //               
    assert(true);
    /*                
                                                                 
    */
    for (int i = 0 ; i < size(indixes) ; i++)
    {
        if (indixes[i] <= 0)
        {
            return false ;
        }
    }
    return true ;
}

void show_all_articles (vector<Presents>& giftstore, int no_of_presents)
{
    //               
    assert (real_money(giftstore) && no_of_presents>0) ;
/*                 
                                                                                          
*/
    for (int i = 0 ; i < no_of_presents; i++)
    {
        cout << i+1 << ".\t" << giftstore[i];
    }
}

void show_articles (vector<Presents>& giftstore, vector<int>& indexes)
{
    //               
    assert (real_money(giftstore) && real_indices(indexes)) ;
/*                 
                                                                           
*/
    for (int i=0; i<size(indexes); i++)
    {
        cout << giftstore[indexes[i]];
    }
}

void show_listprice (vector<list>& lists, int n)
{
    //               
    assert (n>=0) ;
/*                 
                                        
*/
    if (n==size(lists))
    {
        return;
    }
    else
    {
        cout << lists[n] << "\t";
        show_listprice(lists, n+1);
    }
}

void show_listprice (vector<list>& lists)
{
    //               
    assert (true) ;
/*                 
                                        
*/
    return show_listprice(lists, 0);
}

void show_wishinglist(vector<string>& articles, int n)
{
    //               
    assert (n>=0) ;
/*                 
                                          
*/
    if (n==size(articles))
    {
        return;
    }
    else
    {
        cout << articles[n] << endl;
        show_wishinglist(articles, n+1);
    }
}

void show_wishinglist (vector<string>& articles)
{
    //               
    assert (true) ;
/*                 
                                          
*/
    return show_wishinglist(articles, 0);
}

void show_indexes(vector<int>& indexes, int n)
{
    //               
    assert (n>=0) ;
/*                 
                                           
*/
    if (n==indexes.size())
    {
        cout << endl;
        return;
    }
    else
    {
        cout << indexes[n] << "\t";
        show_indexes(indexes, n+1);
    }
}

void show_indexes (vector<int>& indexes)
{
    //               
    assert (true) ;
/*                 
                                           
*/
    return show_indexes(indexes, 0);
}

int sum (vector<list>& lists, int from)
{
    //               
    assert (from >= 0 && from <= size(lists)) ;
    /*
                   
                                                                  
    */
    int sum = 0 ;
    for (int i = from ; i < size(lists) ; i++)
        sum += lists[i] ;
    return sum ;
}

int sum (vector<list>& lists)
{
    //               
    assert (true) ;
    /*
                   
                                                                  
    */
    return sum (lists,0) ;
}

int read_giftlist (ifstream& infile, vector<Presents>& giftstore)
{//               
    assert (infile.is_open () && real_money(giftstore)) ;
/*                 
                                                                                    
                                                                             
*/
    int no_of_read_presents=0;
    while (infile)
    {
        Presents article ;
        infile >> article ;
        ltrim(article.name);
        if (infile)
        {
            giftstore.push_back(article);
            no_of_read_presents++;
        }
    }
    return no_of_read_presents ;
}

int read_giftstore (string filename, vector<Presents>& giftstore)
{//               
    assert (giftstore.size() == 0 && real_money(giftstore)) ;
/*                 
                                                                                  
                                                                                             
                                        
*/
    ifstream articleDBS (filename.c_str());
    if (!articleDBS)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_PRESENTS = read_giftlist (articleDBS, giftstore);
	articleDBS.close();
	cout << "Read " << NO_OF_PRESENTS << " tracks." << endl;
	return NO_OF_PRESENTS;
}

int read_wishinglist (string filename, vector<string>& wishinglist)
{
    //               
    assert (wishinglist.size() == 0) ;
    /*                
                                                                                                  
                                                                 
    */
    ifstream infile (filename.c_str());
    if (!infile)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
    int budget=0;
    string whiteline;
    infile >> budget;
    getline(infile, whiteline);
    while (infile)
    {
        string article;
        getline(infile, article);
        if (infile)
        {
            wishinglist.push_back(article);
        }
    }
    infile.close();
    return budget;
}

void convert_wlist_list(vector<string>& wishinglist, vector<Presents>& giftstore, vector<list>& pricelist, vector<int>& indexes, int n)
{
    //               
    assert (real_money(giftstore) && real_indices(indexes) && n>=0) ;
    /*                
                                                                                                                               
                                                                             
    */
    if (n==size(wishinglist))
    {
        return;
    }
    else
    {
        for (int i=0; i<size(giftstore); i++)
        {
            if (wishinglist[n]== giftstore[i].name)
            {
                pricelist.push_back(giftstore[i].price);
                indexes.push_back(i);
            }
        }
        return convert_wlist_list(wishinglist, giftstore, pricelist, indexes, n+1);
    }
}

void improve (vector<list>& current, vector<list>& best, vector<int>& index_c, vector<int>& index_b)
{//               
    assert (real_indices(index_c) && real_indices(index_b)) ;
//                 
//                                                                 
    if (sum (current) > sum (best))
    {
        best = current ;
        index_b = index_c ;
    }
}

int solutions5 ( vector<list>& current, vector<list>& best, vector<list>& prizes, vector<int>& index_c, vector<int>& index_b, vector<int>& indexes, int c, int budget)
{//               
    assert (0 <= c && c <= size(prizes) && real_indices(indexes) && real_indices(index_b) && real_indices(index_c)) ;
/*                 
                                                                                                                                
                                                                                                                   
                                                                     
    */

	if ( budget == 0 )
    {
        index_b = index_c;
        best = current ;
        return 1 ;
    }
	else if ( budget < 0 )
    {
        return 0 ;
    }
	else if ( c >= size(prizes) )
    {
        improve (current, best, index_c, index_b) ;
        return 0 ;
    }
	else
    {
		current.push_back ( prizes[c] ) ;
        index_c.push_back (indexes[c]);
		const int WITH_C    = solutions5 ( current, best, prizes, index_c, index_b, indexes, c+1, budget - prizes[c] ) ;
		current.pop_back () ;
		index_c.pop_back () ;
		const int WITHOUT_C = solutions5 ( current, best, prizes, index_c, index_b, indexes, c+1, budget ) ;
		return WITH_C + WITHOUT_C ;
	}
}

void find_best_solution (vector<Presents>& giftstore,vector<list>& lists, int value, vector<int>& indexes)
{//               
    assert (real_money(giftstore) && value>=0 && real_indices(indexes)) ;
    /*
                                                                                                                    
                                                                                       
    */
    vector<list> current ;
    vector<list> best ;
    vector<int> index_c;
    vector<int> index_b;
    cout << endl << "The number of solutions to make " << value << " is: " << endl ;
    cout << solutions5 (current, best, lists, index_c, index_b, indexes, 0, value) ;
    cout << endl << "One best found solution is: " << endl ;
    show_articles(giftstore, index_b);
    cout << endl << "It has value: " << sum(best) << endl ;
    cout << endl ;
}

int main()
{
    vector<Presents> giftstore {};
    int no_of_presents=read_giftstore("giftstore.txt", giftstore);
    if (no_of_presents<0)
    {
        cout << "Reading file failed. Program terminates." << endl;
	    return no_of_presents;
    }
    cout << endl << "All the articles in the giftstore: " << endl;
    show_all_articles(giftstore, no_of_presents);
    vector<string> wishinglist{};
    int budget;
    string filename= "Fabienne.txt";
    budget=read_wishinglist(filename, wishinglist);
    filename.erase(filename.end()-4, filename.end());
    cout << endl << "The articles in the wishinglist of " << filename << ":" <<endl;
    cout << endl << "The budget for this wishinglist is: " << budget << endl;
    show_wishinglist(wishinglist);
    vector<list> pricelist {};
    vector<int> indexes {};
    convert_wlist_list(wishinglist, giftstore, pricelist, indexes, 0);
    find_best_solution(giftstore, pricelist, budget, indexes);
}

/*
           
                           
                                
                                  

                  

          
                           
                   
                      
                                

                  

          
                           
                                
                              
                  

                  

            
                           
                          
                           
                       
                          

                  

           
                           
                                            
                                               
                                  
                     
                                                                  
                                                                     

                   

             
                           
                               
                                  
                                     
                      

                   
*/

