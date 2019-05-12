//                                      
//                                       

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

struct Gifts
{
    int value ;
    string name ;
};

vector<Gifts> giftlist;

void read_giftstore (vector<Gifts>& giftlist)
{
    //              
    assert(true);
    /*
                   
                                                                                        
    */
    Gifts element;
    char space;

    ifstream fin("giftstore.txt");

    while(fin)
    {
        fin>>element.value;
        fin.get(space);
        getline(fin, element.name);
        giftlist.push_back(element);
    }

    fin.close();
}

void read_wishlist (vector<string>& wishlist, int& budget)
{
    //            
    assert(budget == 0);
    /*
                   
                                                                                               
                                   
    */
    string filename, name;

    cout<<"Please enter a filename for wishlist: "; cin>>filename;

    ifstream fin(filename.c_str());

    if(!fin.is_open())
        cout<<"Could not open the file.";

    fin>>budget;
    getline(fin, name);
    while(fin)
    {
        getline(fin, name);

        wishlist.push_back(name);
    }

    fin.close();
}

int size (vector<Gifts>& giftlist)
{
    //            
    assert(true);
    /*
                  
                                                                 
    */
    return static_cast<int> (giftlist.size ()) ;
}

int size_string (vector<string>& wishlist)
{
     //            
    assert(true);
    /*
                  
                                                                 
    */
    return static_cast<int> (wishlist.size ()) ;
}

bool check_values(vector<Gifts>& giftlist)
{
     //            
    assert(true);
    /*
                  
                                                                        
    */
    for(int i=0; i<size(giftlist); i++)
        if(giftlist[i].value <= 0)
            return false;
    return true;
}

int sum (vector<Gifts>& wishlist)
{//               
    assert (true) ;
//                 
//                                             
    int sum = 0 ;
    for (int i = 0 ; i < size(wishlist) ; i++)
        sum += wishlist[i].value ;
    return sum ;
}

void improve (vector<Gifts>& current, vector<Gifts>& best)
{//               
    assert (true) ;
//                 
//                                                                 
    if (sum (current) > sum (best))
        best = current ;
}

bool search_element (vector<string> wishlist, string name)
{
     //            
    assert(true);
    /*
                  
                                                   
    */
    for (int i = 0; i < size_string(wishlist); i++)
        if (wishlist[i] == name)
            return true;
    return false;
}

void gifts (vector<Gifts>& attempt, vector<Gifts>& best, vector<Gifts>& giftlist,
               vector<string>& wishlist, int c, int budget)
{
    //             
    assert(check_values(giftlist) && 0 <= c && c <= size(giftlist));
    /*
                 
                                                                     
    */
    if      (budget == 0)       best = attempt ;
    else if (budget  < 0)       return ;
    else if (c >= size (giftlist)) improve (attempt, best) ;
    else {
                bool ok = search_element (wishlist, giftlist[c].name) ;

                if (ok)
                    {
                        attempt.push_back(giftlist[c]) ;
                        gifts (attempt, best, giftlist, wishlist, c + 1, budget - giftlist[c].value ) ;
                        attempt.pop_back() ;
                        gifts (attempt, best, giftlist, wishlist, c + 1, budget) ;
                    }
                else
                    gifts (attempt, best, giftlist, wishlist, c + 1, budget) ;
         }
}

int main()
{
    vector<Gifts> attempt;
    vector<Gifts> best;
    vector<string> wishlist;
    int budget = 0;

    read_giftstore(giftlist);
    read_wishlist(wishlist, budget);

    gifts(attempt, best, giftlist, wishlist, 0, budget);

    for(int i = 0; i < size(best); i++)
        cout<<best[i].name<<"\n";

    return 0;
}

//      
/*
           
                        
                          

          
           
              
                        

          
                           
                                    
          

            
                  
                   
               
                  

           
                                 
                                                          
                                                             
             
                          
                   
                

             
                             
                          
              
                       
*/

