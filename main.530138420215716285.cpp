#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>

/*                                            
                                              
                                              
                                            */

using namespace std;

struct Pakjes
{
    int cost;
    string name;
};

bool operator== (const Pakjes& p1, const Pakjes& p2)
{   return p1.name == p2.name;
}

int size(vector<Pakjes>& l)
{   return static_cast<int> (l.size());
}

void show_gifts(vector<Pakjes>& result)
{
    for(int i = 0; i < size(result); i++)
    {
        cout << result[i].name << endl;
    }
}

int gifts(vector<Pakjes>& pakjes, vector<Pakjes>& wishlist, int a, int b, int& rmoney, int budget, vector<Pakjes>& result, vector<Pakjes>& current)
{//               
    assert(a >= 0 && a <= size(pakjes)-1 && b >= 0 && b <= size(wishlist)-1);
/*                 
                                                                                
                                                                               
                               
*/
    if (budget == 0)    return 1;
    else if (budget < 0) return 0;
    else if (a == size(pakjes)-1)
    {
        return gifts(pakjes, wishlist, 0, b+1, rmoney, budget, result, current);
    }
    else if (b == size(wishlist)-1)
    {
        if (budget < rmoney)
        {
            rmoney = budget;
            result = current;
        }
        return 0;
    }
    else
    {
        if (pakjes[a].name == wishlist[b].name)
        {
            current.push_back(wishlist[b]);
            int with_p = gifts(pakjes, wishlist, 0, b+1, rmoney, budget - pakjes[a].cost, result, current);
            current.pop_back();
            int without_p = gifts(pakjes, wishlist, 0, b+1, rmoney, budget, result, current);
            return with_p + without_p;
        }
        else
        {
            return gifts(pakjes, wishlist, a+1, b, rmoney, budget, result, current);
        }
    }
}

istream& operator>> (istream& in, Pakjes& pakjes)
{
    in >> pakjes.cost;
    return in;
}

void read_file(ifstream& infile, vector<Pakjes>& pakjes)
{//               
    assert (infile.is_open());
/*                 
                                                           
*/
    int a = 0;
    while (infile)
    {
        pakjes.push_back({0, " "});
        infile >> pakjes[a].cost;
        infile.ignore(1, '\n');
        getline(infile, pakjes[a].name);
        a++;
    }
}

void read_file_wl(ifstream& infile, vector<Pakjes>& wishlist, int& budget)
{//               
    assert (infile.is_open());
/*                 
                                                           
*/
    infile >> budget;
    infile.ignore(1, '\n');
    int a = 0;
    while (infile)
    {
        wishlist.push_back({0, " "});
        getline(infile, wishlist[a].name);
        a++;
    }
}

int main()
{
    vector<Pakjes> result;
    vector<Pakjes> current;
    vector<Pakjes> pakjes;
    vector<Pakjes> wishlist;
    int budget;
    ifstream myfile ("giftstore.txt");
    ifstream myfile2 ("Fabienne.txt");
    read_file(myfile, pakjes);
    read_file_wl(myfile2, wishlist, budget);
    gifts(pakjes, wishlist, 0, 0, budget, budget, result, current);
    show_gifts(result);
    myfile.close();
    myfile2.close();
    return 0;
}

/*
      

       
                        
                          

      
           
              
                        

      
                        
                      
          

        
                  
                   
               
                  

       
                                    
                                       
                          
             
                                                          
                                                             

         
                       
                          
                             
              
*/

