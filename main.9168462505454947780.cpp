#include <iostream>
#include <cassert>
#include <string>
#include <vector>
using namespace std;
//                                                    

struct Gift
{
    string name;
    int price;
};

vector<Gift>& make_gift_list(vector<Gift>& shop, vector<string>& wish_list_names)
{
    vector<Gift> wish_list;
    for(int i=0; i<wish_list_names.size();i++)
        for(int j=0;j<shop.size();j++)
            if(wish_list_names[i]==shop[j].name)
                wish_list.push_back(shop[j]);
    return wish_list;
}

void show(vector<Gift> vec)
{
    for(int i=0;i<vec.size();i++)
        cout<<vec[i].name<<" ";
}
int sum(vector<Gift> gifts)
{
    int sum=0;
    for(int i =0; i<gifts.size();i++)
        sum+=gifts[i].price;
    return sum;
}

void gifts (vector<Gift>& wish_list, vector<Gift>& presents, int c, int budget, vector<Gift>& best_presents)
{
    if(budget==0)
    {
        best_presents=presents;
    }
    else if(budget<0)
        return;
    else if(c>wish_list.size()-1)
        if(sum(presents)>sum(best_presents))
            best_presents=presents;
    else
    {
        presents.push_back(wish_list[c]);
        gifts(wish_list, presents, c+1, budget-wish_list[c].price, best_presents);
        presents.pop_back();
        gifts(wish_list, presents, c+1, budget, best_presents);
    }
}

void show_gifts(vector<Gift>& wish_list, vector<Gift>& presents, int c, int budget)
{
    vector<Gift> best_presents;
    gifts(wish_list, presents, c, budget, best_presents);
    show(best_presents);
}

int main()
{

//                                                                                 

vector<Gift> test_vector={{"B", 200},{"C",100},{"D",500},{"E",250},{"F",350},{"H",50}};
vector<Gift> presents;
show_gifts(test_vector,presents,0, 180);

    cout << "Hello world!" << endl;
    return 0;
}

