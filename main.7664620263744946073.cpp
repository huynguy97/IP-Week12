//                         
//                        
#include <iostream>
#include<vector>
#include <cassert>
#include <fstream>

using namespace std;

struct Gift
{
    int price;
    string cadeau;
};

ifstream& operator>> (ifstream& infile, Gift& gift) {
    infile >> gift.price;
    char c;
    infile >> c;
    getline(infile, gift.cadeau);
    return infile;
}

ostream& operator<< (ostream& out, const Gift& gift)
{
    out << gift.price << " " << gift.cadeau << endl;
    return out;
}

void read_wish_list (ifstream& infile, vector<Gift>&wenslijst, int& budget)
{
    infile >> budget;

    while (infile)
    {
        Gift wens;
        wens.price = 0;
        getline(infile, wens.cadeau);
        wenslijst.push_back (wens);
    }
}

void read_giftstore (ifstream& giftfile, vector<Gift>& giftstore)
{
    string filename = "giftstore.txt";
    giftfile.open(filename.c_str());
    char x;

    while (giftfile)
    {
        Gift gift;
        giftfile >> gift.price;
        giftfile >> x;
        getline (giftfile, gift.cadeau);

        giftstore.push_back(gift);
    }
}

int size (vector<Gift>&(gifts))
{
    return static_cast<int>(gifts.size());
}

int initial_sum (vector<Gift>&(sum), int from)
{
    //             
    assert (from >=0 && from <= size(sum));
    //              
    //                                                                
    int j = 0;
    for (int i = from; i < size(sum); i++)
    {
        j = j + sum[i].price;
    }
    return j;
}

int sum (vector<Gift>& sum)
{
    return initial_sum (sum, 0);
}

void improve (vector<Gift>&attempt, vector<Gift>&best)
{
    //             
    assert (true);
    //              
    //                                                                  
    if (sum(attempt) > sum(best))
    {
        best = attempt;
    }
}

void show (vector<Gift>&kados)
{
    //             
    assert (true);
    //              
    //                      
    cout << "Asked gifts:" << endl;
    for (int i = 0; i < size(kados); i++)
    {
        cout << kados[i] << ", " ;
    }
    cout << "." << endl;
}

int gifts(vector<Gift>& kados, vector<Gift>& giftstore, vector<Gift>& attempt, vector<Gift>& best, int c, int budget)            //                                                                                                                                        
{
//             
    assert (true);
//              
//                                                                                                   
    vector<Gift> best_met;
    vector<Gift> best_zonder;
    if (budget == 0)
    {
        show(attempt);
    }
    else if (budget < 0)
    {
        return 0;
    }
    else if (c >= size(kados))
    {
        return 0;
    }
    else
    {
        for (int j =0; j < size(giftstore); j++)
            {
                if (giftstore[j].cadeau == kados[c].cadeau)
                    kados[c].price = giftstore[j].price;
            }

        attempt.push_back(kados[c]);           //       
        int with_c = gifts(kados, giftstore, attempt, best_met, c+1, budget-kados[c].price);
        improve(attempt, best_met);
        attempt.pop_back();                     //      

        int without_c = gifts (kados, giftstore, attempt, best_zonder, c+1, budget);
        improve(attempt, best_zonder);
        cout << with_c << " " << without_c << endl;

        improve (best_met, best_zonder);

    }
    show(best_zonder);
    return 1;
}

int main()
{
    int budget = 0;
    int c = 0;
    vector<Gift> wenslijst;
    cout << "Kies wiens lijst je wil kijken" << endl;
    ifstream infile, giftfile;
    string filename;
    cin >> filename;
    infile.open(filename.c_str());
    read_wish_list(infile, wenslijst, budget);
    cout << budget;

    vector<Gift> giftstore;
    read_giftstore (giftfile, giftstore);

    vector<Gift>(best);
    vector<Gift>(attempt);
    gifts(wenslijst, giftstore, attempt, best, c, budget);
    infile.close();
    return 0;
}

