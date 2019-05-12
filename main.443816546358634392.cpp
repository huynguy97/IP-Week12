//                       

#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>

using namespace std;

struct giftList
{
    int price;
    string name;
};

struct gift
{
    string name;
};

istream& operator>> (istream& in, gift& gift)
{
    getline(in, gift.name);
    return in;
}

istream& operator>> (istream& in, giftList& giftlist)
{
    in >> giftlist.price;
    getline(in, giftlist.name);
    return in;
}

void readGiftList (vector<giftList>& giftlist)
{//              
    assert (true);
/*                
                                                                       
*/
    cout << "Please type the name of the file with the possible presents and prices: " << endl;
    string fileName;
    getline(cin, fileName);
    ifstream giftlistFile (fileName.c_str());
    if (!giftlistFile.is_open())
    {
        cout << "Something went wrong, could not open file." << endl;
    }
    else
    {
        int i = 0;
        giftList currentGift;
        while (giftlistFile)
        {
            cin >> currentGift;
            giftlist[i] = currentGift;
            i++;
        }
        giftlistFile.close();
    }
}

void readWishList (int& budget, vector<gift>& wishList)
{//              
    assert (true);
/*                
                                                                    
*/
    cout << "Please type the name of the file with the wish list: " << endl;
    string fileName;
    getline(cin, fileName);
    ifstream wislistFile (fileName.c_str());
    if (!wislistFile.is_open())
    {
        cout << "Something went wrong, could not open file." << endl;
    }
    else
    {
        cin >> budget;
        int i = 0;
        gift currentGift;
        while (wislistFile)
        {
            cin >> currentGift;
            wishList[i] = currentGift;
            i++;
        }
        wislistFile.close();
    }
}

int size (vector<giftList>& giftstore)
{//              
    assert (true);
/*                
                                          
*/
    return static_cast<int>(giftstore.size());
}

bool inWishlist (string gift, vector<gift>& wishList)
{//              
    assert (true);
/*                
                                                                           
*/
    for (int i=0; i<wishList.size(); i++)
    {
        if (gift == wishList[i].name)
            return true;
    }
    return false;
}

bool inChecked (string gift, vector<giftList>& checkedGifts)
{//              
    assert (true);
/*                
                                                                                       
*/
    for (int i=0; i<checkedGifts.size(); i++)
    {
        if (gift == checkedGifts[i].name)
            return true;
    }
    return false;
}

void addPrices (vector<gift>& wishList, vector<giftList>& giftstorage, vector<giftList>& checkedGifts)
{//              
    assert (true);
/*                
                                                                                    
*/
    for (int i=0; i<giftstorage.size(); i++)
    {
        if (inWishlist(giftstorage[i].name, wishList) && !inChecked(giftstorage[i].name, checkedGifts))
            checkedGifts.push_back(giftstorage[i]);
    }
}

void show(vector<giftList> attempt )
{
    for(int i=0;i<attempt.size();i++)
    {
        cout<<attempt[i].name<<" "<<attempt[i].price<<endl;
    }
}

int totalPrice (vector<giftList>& giftPrices)
{//              
    assert (true);
/*                
                                                          
*/
    int total = 0;
    for (int i=0; i<giftPrices.size(); i++)
    {
        total = total + giftPrices[i].price;
    }
    return total;
}

void improve (vector<giftList>& attempt, vector<giftList>& best)
{//              
    assert (true);
/*                
                                                       
*/
    if (totalPrice(attempt) > totalPrice(best))
    {
        best = attempt;
    }
}

int gifts (vector<gift>& wishList, vector<giftList>& attempt, vector<giftList>& best, vector<giftList>& checkedGifts,  int c, int budget)
{//              
    assert(true);
/*                
                                                                                          
*/
    if (budget == 0)
    {
        best = attempt;
        return 1;
    } else if (budget < 0) {
        return 0;
    } else if (c == wishList.size()) {
        improve(attempt, best);
        return 0;
    } else
    {
        attempt.push_back(checkedGifts[c]);
        int withC = gifts(wishList, attempt, best, checkedGifts, c+1, budget-checkedGifts[c].price);
        attempt.pop_back();
        int withoutC = gifts(wishList, attempt, best, checkedGifts, c+1, budget);
        return withoutC + withC;
    }
}

int main()
{
    int c = 0;
    vector<giftList> checkedGifts={};
    vector<giftList> attempt={};
    vector<giftList> best={};
    vector<giftList> giftstorage = {};
    vector <gift>  wishList = {};
    int budget = 0;
    readGiftList(giftstorage);
    readWishList(budget, wishList);
    addPrices(wishList, giftstorage, checkedGifts);
    gifts(wishList, attempt, best, checkedGifts, c, budget);
    show(best);
    return 0;
}

