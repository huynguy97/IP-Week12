#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <fstream>
using namespace std;

//                
//                 

//       
typedef int Price ;

int size(vector<Price>& wishes) {
    //               
    assert (true) ;
//                 
//                                
    return static_cast<int> (wishes.size()) ;
}

int sum (vector<Price>& wishes, int from) {
//               
assert (from >= 0 && from <= size(wishes)) ;
//                 
//                                                                                                                
    int sum = 0 ;
    for (int i = from ; i < size(wishes) ; i++)
        sum += wishes[i] ;
    return sum ;
}

int sum (vector<Price>& wishes)
{
    return sum (wishes,0) ;
}

void improve(vector<Price>& current, vector<Price>& best){
//               
    assert (true) ;
//                 
//                                                                                              
    if (sum (current) > sum (best))
        best = current ;
}

void show ( vector<Price>& wishes )
{//               
    assert (true) ;
//                                                         
    const int NO_OF_ELEMS = size (wishes) ;
    cout << "{" ;
    if ( NO_OF_ELEMS > 0 )
    {
        for (int i = 0 ; i < NO_OF_ELEMS-1 ; i++)
            cout << wishes[i] << "," ;
        cout << wishes[NO_OF_ELEMS-1] ;
    }
    cout << "}" << endl ;
}

int gifts(vector<Price>& attempt, vector<Price>& best, vector<Price>& wishes, int budget, int p){
//               
    assert (true) ;
//                 
//                                                                                                          
    if (budget == 0) {return 1;}
    else if (budget < 0) {return 0;}
    else if (p >= size(wishes)){improve(attempt, best); return 0;}
    else if (sum(attempt) + sum(wishes,p) <= sum(best)) {return 0;}

    else{
        attempt.push_back(wishes[p]);
        int with_p = gifts(attempt, best, wishes, budget - wishes[p],p+1);
        attempt.pop_back();
        int without_p = gifts(attempt, best, wishes, budget, p+1);
        return with_p + without_p;
    }
}

void find_best_solution (vector<Price>& wishes, int budget)
{//               
    assert (true) ;
//                                                                                         
//                                                      
    vector<Price> current ;
    vector<Price> best ;
    cout << endl << "The number of solutions to make " << budget << " is: " << endl ;
    cout << gifts(current, best, wishes, budget, 0) ;
    cout << endl << "One best found solution is: " << endl ;
    show (best) ;
    cout << endl << "It has value: " << sum(best) << endl ;
    cout << endl ;
}

//       

struct Gift {
    int price;
    string type;
    string name;
};

vector<Gift>giftstore;
int b_andrew; int b_belle; int b_chris; int b_desiree; int b_edward; int b_fabienne;

istream& operator>> (istream& in, Gift& gift) {
    //              
    assert (true) ;
    int price;
    string type, name, price_string;

    getline(in, price_string, ' ');
    if(price_string[0]!=NULL) {
        price=stoi(price_string);
        gift.price=price;

        getline(in, type, ' ');
        gift.type=type;

        getline(in, name, '\n');
        gift.name=name;
    }
}

ostream& operator<< (ostream& out, Gift& gift) {
    out << gift.price << ' '
        << gift.type << ' '
        << gift.name;
    return out;
}

bool open_file(ifstream& infile, string filename) {
    //              
    assert(true);
    //               
    //                          
    infile.open(filename.c_str());
    if(!infile.is_open()) {
        return false;
    }
    return true;
}

bool get_wishlist(ifstream& infile, int& budget, vector<Gift>& wishes)
{
    //              
    assert(infile.is_open());
    //               
    //                                                             

    string budget_string, type, gift_name;
    Gift gift;
    int counter=0;

    getline(infile, budget_string, '\n');
    budget=stoi(budget_string);
    gift.price=0;

    while(infile)
    {
        getline(infile, type, ' ');
        gift.type=type;

        getline(infile, gift_name, '\n');
        gift.name=gift_name;

        wishes.push_back(gift);
        counter++;
    }
    wishes.pop_back();
}

int main() {

    return 0;
}
