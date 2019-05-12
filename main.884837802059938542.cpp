#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

//                                                                                 

struct gift
{
    int price;
    string name;
};

vector<gift> giftstore;
vector<gift> wishList;
int budget = 0;

int ProductPrice(string product)
{
//               
    assert (true);
/*                
                                                                                                                           
*/
    for (gift i : giftstore)
    {
        if (i.name == product)
            return i.price;
    }
    return -1;
}

vector<gift> OpenFile(string filename, bool hasPrice = true)
{
//               
    assert (!(!hasPrice && giftstore.size() == 0));
/*                
                                                                                                                                             
                                                                                                                                                   
                                                                                                                          
*/
    string line;
    gift temp;
    temp.price = 0;
    int indexTemp;
    vector<gift> store;
    ifstream file;
    file.open(filename);
    if (!file.is_open())
    {
        cout << "Oops! Something went wrong here!";
        return store;
    }
    if (!hasPrice)
    {
        getline(file, line);
        budget = stoi(line);
    }
    while (getline(file, line))
    {
        if (hasPrice)
        {
            indexTemp = line.find(" ");
            temp.price = stoi(line.substr(0, indexTemp));
            line.erase(0, indexTemp+1);
        }
        else
            temp.price = ProductPrice(line);
        temp.name = line;
        if (!(temp.price == -1))
            store.push_back(temp);
    }
    return store;
}

void Improve(vector<gift> attempt, vector<gift>& best)
{
//               
    assert (true);
/*                
                                                                                                                                                    
*/
    int counter1 = 0;
    int counter2 = 0;
    for (gift i : attempt)
        counter1 += i.price;
    for (gift j : best)
        counter2 += j.price;
    if (counter1 > counter2)
        best = attempt;
}

void Gifts(int moneyLeft, int index, vector<gift>& attempt, vector<gift>& best)
{
//               
    assert (index >= 0 && budget >= 0 && moneyLeft <= budget);
/*                
                                                                                                                            
*/
    if (moneyLeft < 0)
        return;
    else if (moneyLeft == 0)
    {
        best = attempt;
        return;
    }
    else if (index >= wishList.size())
    {
        Improve(attempt, best);
        return;
    }
    else
    {
        attempt.push_back(wishList[index]);
        Gifts(moneyLeft - wishList[index].price, index+1, attempt, best);
        attempt.pop_back();
        Gifts(moneyLeft, index+1, attempt, best);
        return;
    }
}

void PrintVector(vector<gift>& target)
{
//               
    assert (true);
/*                
                                                       
*/
    int counter = 0;
    for (gift i : target)
    {
        cout << i.name << endl;
        counter += i.price;
    }
    cout << counter << endl;

}
int main()
{
    vector<gift> attempt;
    vector<gift> best;
    giftstore = OpenFile("giftstore.txt");
    if (giftstore.size() == 0)
        return -1;
    wishList = OpenFile("Edward.txt", false);
    if (wishList.size() == 0)
        return -1;
    Gifts(budget, 0, attempt, best);
    PrintVector(best);
    return 0;
}

