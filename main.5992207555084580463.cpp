#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>

using namespace std;

//                                                               
//                                                       

int size(vector<string>& str)
{
    return static_cast<int>(str.size());
}

void display(vector<string>& str)
{
    //                
    assert(true);
    //                                                          
    for (int i = 0; i<size(str); i++)
        cout << str[i] << endl;

}

void gifts(vector<string>& wishlist, vector<string>& shop, vector<string>& gekocht, vector<int>& prijslijst, int budget, int wishindex, int shopindex, int& bestbudget, vector<string>& bestlist)
{
    //               
    assert(shopindex <= size(shop) && wishindex <= size(wishlist) && shopindex >= 0 && wishindex >= 0);
    //                                                                        
    if (budget < bestbudget)
    {
        bestbudget = budget;
        bestlist = gekocht;
    }

    if (wishindex >= size(wishlist))
        return;

    if (shopindex >= size(shop))
        {
        gifts(wishlist, shop, gekocht, prijslijst, budget,wishindex+1,0, bestbudget, bestlist);
        return;
        }

    if (wishlist[wishindex] == shop[shopindex] && (budget - prijslijst[shopindex] >= 0))
        {
        gekocht.push_back(wishlist[wishindex]);
        gifts(wishlist, shop,gekocht, prijslijst , budget - prijslijst[shopindex] ,wishindex+1, 0, bestbudget, bestlist);
        gekocht.pop_back();
        }

    gifts(wishlist, shop,gekocht,prijslijst, budget,wishindex, shopindex+1, bestbudget, bestlist);
}

void readshop (ifstream& infile, vector<string>& shop, vector<int>& prijslijst)
    {
    //                
    assert(true);
    //                                                                                                     
    string filename = "giftstore.txt";
    infile.open(filename.c_str());
    if (infile.is_open())
        cout << "giftstore.txt is opened" << endl;
    int prijs = 0;

    while (infile)
    {
        infile >> prijs;
        prijslijst.push_back(prijs);
        string item = "";
        string dummy = "";
        getline(infile, dummy, ' ');
        getline(infile, item);
        shop.push_back(item);
    }
    infile.close();
    if (!infile.is_open())
    cout << "giftstore.txt is closed" << endl << endl;
    }

int readlist (ifstream& infile, vector<string>& wishlist)
    {
    //                
    assert(true);
    //                                                                                                                     
    string filename;
    cout << "input a filename for the wishlist" << endl;
    cin >> filename;
    infile.open(filename.c_str());

    int budget = 0;
    if (infile.is_open())
        cout << "File is opened" << endl;

    infile >> budget;
    string item = "";
    string dummy = "";
    getline(infile, dummy, '\n');

    while(infile)
    {
      getline(infile, item);
      wishlist.push_back(item);
    }
    infile.close();
    infile.close();
    if (!infile.is_open())
    cout << "file is closed" << endl;
    return budget;
    }

int main()
{
vector<string> wishlist = {};
vector<string> shop = {};
vector<int> prijslijst = {};
int budget = 0;
vector<string> gekocht = {};
vector<string> bestlist = {};

ifstream inputfile;
budget = readlist(inputfile, wishlist);
int bestbudget = budget;
readshop (inputfile, shop, prijslijst);
gifts(wishlist, shop, gekocht, prijslijst, budget, 0, 0, bestbudget, bestlist);

cout << "best list:" << endl;
display(bestlist);
cout << endl << "Remaining budget:" << bestbudget;
    return 0;
}

    /*
                

              
              

          
                        
                          

                  

                                                                                                         

             
              

          
           
              
                        

                    

                                                                                                         

             
               

          
                        
                      
          

                  
                                                                                                         

              
                

          
                  
                   
               
                  

                  

                                                                                                         

              
             

                                    
                                       
                          
             
                                                          
                                                             

                  

                                                                                                         

                
             

          
                       
                          
                             
              

                    

                                                                                                         
*/

