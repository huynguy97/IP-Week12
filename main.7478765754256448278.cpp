/*
        
                        
                      
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cassert>

using namespace std;

struct Gift {string name; int value;}; //                     

int size(vector<Gift>& gifts)
{
    return static_cast<int>(gifts.size());
}

int size(vector<string>& name)
{
    return static_cast<int>(name.size());
}

bool open_file(ifstream& file, string filename)
{
    //    
    assert(true);
    //     
    //                                                                 
    file.open(filename.c_str());
    if(file)    return true;
    else        return false;
}
int get_value(string name, vector<Gift>& giftstore)
{
    //    
    assert(true);
    //     
    //                                                                         

    for(int i = 0; i < size(giftstore); i++)
    {
        if(name == giftstore[i].name)
            return giftstore[i].value;
    }
    return -1;

}
int get_wish(vector<Gift>& wishes, vector<Gift>& giftstore, string filename)
{
    //    
    assert(true);
    //     
    //                                                                                                 
    //                                                          
    ifstream file;
    if(!open_file(file, filename))
    {
        cout << "Can't open file " << filename << endl;
        return -1;
    }
    int budget;
    file >> budget;
    string line;
    getline(file, line);
    while(file)
    {
        Gift gift;
        if(getline(file, line))
        {
            gift.name = line;
            gift.value = get_value(line, giftstore);
            wishes.push_back(gift);
        }

    }
    return budget;
}

int get_giftstore(vector<Gift>& gifts)
{
    //    
    assert(true);
    //     
    //                                                                                                                                                  
    ifstream file;
    if(!open_file(file, "giftstore.txt"))
    {
        cout << "Can't open file " << "giftstore.txt" << endl;
        return -1;
    }
    string line;
    int c = 0;
    while(file)
    {
        Gift gift;
        file >> gift.value;
        file.get();
        getline(file, line);
        gift.name = line;
        gifts.push_back(gift);
        c++;
    }
    return c;
}

int spent(vector<Gift>& gift, int from)
{
    //    
    assert(from >= 0);
    //     
    //                                                                              
    int total = 0;
    for(int i = from; i < size(gift); i++)
        total += gift[i].value;
    return total;
}

void improve(vector<Gift>& attempt, vector<Gift>& best)
{
     //    
    assert(true);
    //     
    //                                                               
    if(spent(attempt,0) > spent(best,0))
        best = attempt;

    else if( spent(attempt,0) == spent(best,0) && size(attempt) > size(best) )
        best = attempt;
}

int gifts(vector<Gift>& wish, vector<Gift>& gift, vector<Gift>& best, int g, int budget)
{
    //    
    assert(true);
    //     
    //                                                                                            
    if (g >= size(wish))
    {
        if(budget >= 0)
            improve(gift,best);
        return 0;
    }

    else if (budget < 0)
        return 0;

    else if (budget == 0)
    {
        best = gift;
        return 1;
    }

    else if(spent(gift,0) + spent(wish,g) < spent(best,0))
        return 0;

    else
    {
        gift.push_back(wish[g]);
        int with_g = gifts(wish, gift, best, g+1, budget - wish[g].value);
        gift.pop_back();
        int without_g = gifts(wish, gift, best, g+1, budget);

        return with_g + without_g;
    }
}

int main()
{

    vector<string> names = {"Andrew", "Belle", "Chris", "Desiree", "Edward", "Fabienne"};

    vector<Gift> giftstore;
    get_giftstore(giftstore);

    vector<vector<Gift>> wishes;
    vector<int> budgets;
    for(int i = 0; i < size(names); i++)
    {
        vector<Gift> gift;
        budgets.push_back(get_wish(gift, giftstore, names[i]+".txt"));
        wishes.push_back(gift);
    }

    vector<Gift> wishes_andrew = wishes[0];
    int budget_andrew = budgets[0];

    vector<Gift> attempt;
    vector<Gift> best;

    for(int i = 0; i< size(names); i++)
    {
        gifts(wishes[i], attempt, best, 0, budgets[i]);

        cout << names[i] << endl;
        for(int j = 0; j < size(best); j++)
            cout << best[j].name << "\t\t" << best[j].value << endl;
        cout << "Spent " << spent(best,0) << " of " << budget_andrew << endl << endl;

        best.clear();
        attempt.clear();
    }

    return 0;
}

