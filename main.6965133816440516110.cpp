#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

//                        
//                           

using namespace std;

struct present
{
    int price;
    string present_name;
};

istream& operator>> (istream& in, present& present)
{
    in >> present.price;
          in.get();
          getline(in, present.present_name);
    return in;
}

ostream& operator<< (ostream& out, present& present)
{
    out << present.price
       << ' '
        << present.present_name;
    return out;
}

vector<present> store_vector;

vector<string> wishlist_vector;

vector<present> attempt;

bool open_whislist(ifstream& input_whishlist)
{   //             
    assert(true);
    //                                                                                                

    input_whishlist.open("whishlist.txt");
    if (input_whishlist.is_open())
        return true;
    else
        return false;
}

bool open_file(ifstream& inputfile)
{   //             
    assert(true);
    //                                                                                  

    inputfile.open("giftstore.txt");
    if (inputfile.is_open())
    {
        cout << "file is open" << endl;
        return true;
    }

    else
        return false;
}

bool read_whislist(vector<string>& whishlist_vector, istream& input_whishlist)
{   //             
    assert(input_whishlist.is_open());
    //                                                                                                    
    int budget;
    budget = input_whishlist;
    while (input_whishlist)
    {
        string whishlist_temp;
        input_whishlist >> whishlist_temp;
        whishlist_vector.push_back(whishlist_temp);
    }
return true;
}

bool read_store(vector<present> store_vector, istream& inputfile)
{   //             
    assert(inputfile.is_open());
    //                                                                                                        

    while (inputfile)
    {
        present present_to_be_read_in;
        inputfile >> present_to_be_read_in;
        store_vector.push_back(present_to_be_read_in);
    }

return true;
}

int gifts(vector<present>& attempt, vector<present>& best, int budget, int c, int target, vector<string>& whishlist_vector, vector<present>& store_vector)
{   //             
    assert(int budget);
    //                                                            

    if (c >= store_vector.size())
    {
        //                        
        attempt = best;

        return budget;
    }
    else
    {
        attempt[c] = whishlist_vector[c]
    }

    //                                                                             
    //                                                              
    //                                                                  

}

int main() {

    //                                                
    ifstream inputfile;

    open_file(inputfile);
    read_store(store_vector, inputfile);

    return 0;
}
