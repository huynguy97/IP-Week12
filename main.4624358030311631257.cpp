//                         
//                            
//                                                                        

#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>

using namespace std;
const int MAX_CHAR = 100;

struct Gift
{
    int price ;
    string object ;
};

vector<Gift> store ;

string remove_space(char info[MAX_CHAR])
{//              
    assert(true) ;
//                                                                                               
    for(int i = 0; i<MAX_CHAR-1; i++)
    {
        info[i] = info[i+1];
    }
    string infostr = string(info);
    return infostr;
}

bool read_giftstore(vector<Gift>& storage, ifstream& infile)
{//              
    assert(true) ;
//                                                                                                
    string storefile;
    cout << "Please enter the name of the file wherein the gift store data is contained (including .txt):\n";
    cin >> storefile;
    infile.open(storefile.c_str());
    if(infile)
    {
        char rest[MAX_CHAR];
        Gift gift;
        while(infile)
        {
            infile >> gift.price;
            infile.getline(rest, MAX_CHAR, '\n');
            string reststr = remove_space(rest);
            gift.object = reststr;
            storage.push_back(gift);
        }
        return true;
    }
    else{
        cout << "The file was not found. Please try again.\n";
        return false;
    }
}

bool read_wishlist(vector<string>& wishlist, ifstream& infile, int& budget)
{//              
    assert(true) ;
//                                                                                                                                      
    string filename;
    cout << "Please enter the name of the text file (including .txt):\n";
    cin >> filename;
    infile.open(filename.c_str());
    if(infile)
    {
        int c = 0;
        char textline[MAX_CHAR];
        while(infile)
        {
            if(c==0)
            {
                infile >> budget;
                c++;
            }
            else{
                infile.getline(textline, MAX_CHAR, '\n');
                wishlist.push_back(textline);
            }
        }
        cout << "The file has been read.\n";
        return true;
    }
    else{
        cout << "Unable to read file. Please try again.\n";
        return false;
    }
}

void show(vector<Gift>& buy_list)
{//              
    assert (true) ;
//                                               
    for (int i = 0; i < buy_list.size() ; i++)
        cout << buy_list[i].object << ' ' << buy_list[i].price << endl ;
}

int sum (vector<Gift>& giftlist, int from)
{//              
    assert (true) ;
//                                                                                             
    int total = 0 ;
    for (int i = from ; i < giftlist.size() ; i++)
        total = total + giftlist[i].price ;
    return total ;
}

int minimum (vector<Gift>& giftlist, int from)
{//              
    assert (from >= 0 && from < giftlist.size()) ;
//                                                                                         
    int minimal = giftlist[from].price ;
    for (int i = from + 1 ; i < giftlist.size() ; i++)
    {
        if (giftlist[i].price < minimal)
            minimal = giftlist[i].price ;
    }
    return minimal ;
}

void improve (vector<Gift>& a, vector<Gift>& b)
{//              
    assert (true) ;
//                                                                                   
    if (sum(a,0) > sum(b,0))
        b = a ;
}

vector<Gift> check_store_and_convert (vector<string> wishstrings)
{//              
    assert(true) ;
//                                                                                                                    
    vector<Gift> wishlist ;
    for (int i = 0 ; i < wishstrings.size() ; i++)
    {
        for (int j = 0 ; j < store.size() ; j++)
        {
            if (wishstrings[i] == (store[j].object))
                wishlist.push_back(store[j]) ;
        }
    }
    return wishlist ;
}

int gifts (vector<Gift>& buy_list, vector<Gift>& best, vector<Gift>& wishlist, int c, int budget)
{//              
    assert(true) ;
 //                                                                                                                          
    if (budget == 0)
    {
        best = buy_list ;
        return 1 ;
    }
    else if (budget < 0)
        return 0 ;
    else if (c >= wishlist.size())
    {
        improve(buy_list, best) ;
        return 0 ;
    }
    else if (minimum(wishlist, c) > budget)
        return 0 ;
    else if (sum(buy_list, 0) + sum(wishlist, c) <= sum(best, 0))
        return 0 ;
    else
    {
        buy_list.push_back(wishlist[c]) ;
        int with_c = gifts(buy_list, best, wishlist, c+1, budget - wishlist[c].price) ;
        buy_list.pop_back() ;
        int without_c = gifts(buy_list, best, wishlist, c+1, budget) ;
        return with_c + without_c ;
    }
}

int main()
{
    int budget;
    ifstream infile;
    ifstream infile2;
    vector<string> wishstring;
    vector<Gift> best ;
    vector<Gift> buy_list ;
    read_giftstore(store, infile) ;
    read_wishlist(wishstring, infile2, budget) ;
    vector<Gift> wishlist = check_store_and_convert(wishstring) ;
    gifts(buy_list, best, wishlist, 0, budget) ;
    show(best) ;
    return 0 ;
}
/*       
                                 

      
                      

       
                                         
                                            
                               
                   
                                                              
                                                                          

        
                       
                        
                    
                       

*/

