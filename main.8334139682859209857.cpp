#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>
#include <cmath>

//                     
//                             

/*
                                            
                                   
                                  
                                  
                                    
                                     
                                       
*/

using namespace std;

struct Gift
{
    int price;
    string name;
};

struct Wishlist
{
    int budget;
    vector<string> gifts;
};

vector<Gift> storelist;

istream& operator>> (istream& infile, Gift& storelist)
{
    //               
    assert (true);
    //                                                                                                                               
    //                                       
    infile >> storelist.price;
    infile.ignore();
    getline(infile, storelist.name);
}
int size (vector<Gift> storelist)
{
    //               
    assert (true);
    //                                                          
    return static_cast<int> (storelist.size ()) ;
}

int size2 (vector<string> storelist)
{
    //               
    assert (true);
    //                                                          
    return static_cast<int> (storelist.size ()) ;
}

int read_storelist (ifstream& infile, vector<Gift>& storelist)
{
    //               
    assert (infile.is_open());
    //                                                                                                                                                    
    int no_of_gifts = 0;
    do
    {
        Gift gifts;
        infile >> gifts;
        if (infile)
        {
            storelist.push_back(gifts);
            no_of_gifts++;
        }
    }
    while (infile);
    return no_of_gifts;
}

void printVector(vector<Gift>v){
    for (int i=0; i<size(v); i++)
        cout << v[i].name << endl;
}

void printVector2(vector<string>v){
    for (int i=0; i<size2(v); i++)
        cout << v[i] << endl;
}

Wishlist read_wishlist (ifstream& infile)
{
    //               
    assert (infile.is_open());
    //                                                                                                                                                  
    int no_of_wishes = 0;
    Wishlist w;
    infile >> w.budget;
    do
    {
        string gift;
        if (infile)
        {
            getline(infile, gift);
            w.gifts.push_back(gift);
            no_of_wishes++;
        }
    }
    while (infile);
    w.gifts.pop_back();
    return w;
}

int getPrice (vector<Gift>& storelist, string target)
{
    //               
    assert (true);
    //                                                                      
    for (int i=0; i<size(storelist); i++)
    {
        if (storelist[i].name == target)
            return storelist[i].price;
    }
    return 0;
}

int solution (vector<Gift>& storelist, Wishlist w, int j, int total)
{
    //               
    assert (0 <= size(storelist) && 0 <= j);
    //                
    if (total == w.budget)
    {
        return total;
    }
    else if (total > w.budget)
    {
        return total -= getPrice(storelist, w.gifts[j-1]);
    }
    else if (j==size2(w.gifts)-1)
    {
        return total;
    }
    else
    {
        const int with_j = solution(storelist, w, j+1, total+getPrice(storelist, w.gifts[j]));
        const int without_j = solution(storelist, w, j+1, total);
        if (with_j>without_j)
            return with_j;
        else return without_j;
    }
}

int read_giftstore (string filename)
{//               
    assert (size (storelist) == 0) ;
/*                 
                                                                              
                                                                                                
                                        
*/
    ifstream giftstore (filename.c_str());
    if (!giftstore)
    {
        cout << "Could not open '" << filename << "'." << endl;
        return -1;
    }
    cout << "Reading '" << filename << "'." << endl;
	const int NO_OF_GIFTS = read_storelist (giftstore, storelist);
	giftstore.close();
	cout << "Read " << NO_OF_GIFTS << " lines of available gifts." << endl;
	return NO_OF_GIFTS;
}

Wishlist read_wishes (string filename)
{//               
    assert (sizeof(struct Wishlist) >= 0) ;
/*                 
                                                                              
                                                                                                
                                        
*/
    ifstream wishlist (filename.c_str());
    cout << "Reading '" << filename << "'." << endl;
	Wishlist w = read_wishlist (wishlist);
	wishlist.close();
	cout << "Read " << w.gifts.size() << " lines of wishes." << endl;
	return w;
}

int main()
{
    cout << "Hello world!" << endl;
    read_giftstore("giftstore.txt");
    Wishlist w = read_wishes("Fabienne.txt");
    printVector(storelist);
    printVector2(w.gifts);
    cout << solution(storelist, w, 1, 0);
    return 0;
}

