#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<string> wishlist;
vector<string> attempt;

bool readfile(ifstream& file)
{
    file.open("giftstore.txt");

    return file.is_open();
}
bool dermo()
{   ifstream infile;
    readfile(infile);
    string h;
    int f;
    while(infile)
    {
    infile >> f;
    getline(infile,h);
    wishlist.push_back(f);
    }
    cout<<wishlist[0]<<wishlist[5];
    return true;

}

vector<string> gifts (vector<string>& giftstore, vector<string>attempt, vector<string>wishlist, int budget, )
{
    if(budget < 0)
    {
        return 0;
    }
    else if(budget = 0)
    {
        return 1;
    }
    else if(gift >= wishlist.size() )
    {
        return 0
    }
    else
    {
        vector<string> with_gf = gifts (giftstore, budget - wishlist[price]wishlist,gift, price );
        vector<string> without_gf = gifts (giftstore, budget,wishlist,gift, price);
        return
    }
}

int main()
{

dermo();
    return 0;
}

