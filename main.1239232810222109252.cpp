#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

//                              
//                               

using namespace std;

struct Gift{
    int price;
    string name;
};

struct Wishlist{
    int budget;
    vector<string> names;
};

istream& operator>>(istream& in, Gift gift)
{
    char c;
    in >> gift.price;
    in >> c;
    getline(in, gift.name);
    return in;
}

ostream& operator<<(ostream& out, const Gift gift)
{
    out << gift.price << ' '<< gift.name<<endl;
}

istream operator>>(istream& in, Wishlist wishlist)
{
    in >> wishlist.budget;
    int i=0;
    while(in)
    {
        getline(in, wishlist.names[i]);
        i++;
    }
}

ostream& operator<<(ostream& out, const Wishlist wishlist)
{
    out << wishlist.budget<<endl;
    for (int i = 0; i < wishlist.names.size() ; i++) {
        out << wishlist.names[i]<<endl;

    }
}

bool open_file(string filename, ifstream& infile)
{
    //             
    assert(!infile.is_open());
    //              
    //            
    if(!infile.is_open())
    {
        infile.open(filename);
        if(infile.is_open())
            cout << "File opened successfully"<<endl;
        return true;
    }
    return false;
}

bool read_giftstore(vector<Gift>& giftstore,string filename, ifstream& infile)
{
    //             
    assert(!infile.is_open());
    //              
    //                            
    if(open_file(filename, infile))
    {
        int i = 0;
        while(infile)
        {

            infile >> giftstore[i];
            i++;

        }

        infile.close();

        return true;
    }
    return false;
}

bool read_wishlist(Wishlist wishlist, string filename, ifstream& infile)
{
    //             
    assert(!infile.is_open());
    //              
    //                   

    if(open_file(filename, infile))
    {
        infile >> wishlist;
        infile.close();
        return true;
    }

    return false;

}

Gift find_gift(vector<Gift>& giftstore, string name, int i)
{
    //             
    assert(i>=0);
    //              
    //            
    if(name == giftstore[i].name)
        return giftstore[i];
    else
        find_gift(giftstore,  name,  i+1);
}

int gifts s(vector<Gift>& giftstore,vector<Gift> attempt , vector<Gift>& solution ,int budget , Wishlist wishlist, int pointer)
{
    //             
    assert(pointer>0);
    //              
    //                                                          
    Gift current_gift = find_gift(giftstore, wishlist.names[pointer], 0);
    if(budget < 0)
        return 0;
    else if(budget == 0)
        return 1;
    else
    {
        attempt.push_back(current_gift);
        int with_pointer = gifts(giftstore, attempt, solution, budget - current_gift.price , wishlist, pointer+1);
        attempt.pop_back();
        int without_pointer = gifts(giftstore, attempt, solution, budget, wishlist, pointer+1);
        return with_pointer + without_pointer;
    }

}

int main() {
    vector<Gift> giftstore;
    Wishlist wishlist;
    ifstream infile_giftstore;
    ifstream infile_wishlist;
    read_giftstore(giftstore,"giftstore.txt" ,infile_giftstore);

    string filename;
    cout << "please enter a filename for the wishlist"<<endl;
    cin >> filename;
    read_wishlist(wishlist, filename, infile_wishlist);

    return 0;
}
