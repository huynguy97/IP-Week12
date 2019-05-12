#include <iostream>
#include <vector>
#include <fstream>
#include <assert.h>

/*
                            
                          
*/

using namespace std;
struct gift
{
    int price;
    string name;
};

vector<gift> Store (0);
vector<string> Wish (0);
vector<gift> Availabe (0);
vector<gift> Current (0);
vector<gift> Best (0);

ostream& operator<<(ostream& out, const gift& gift){
        out << gift.price << ' '
            << gift.name << endl;
}
void load_store(vector<gift>& Store)
{
    string inputfile;
    gift placeholder;
    ifstream infile("giftstore.txt");
    if(infile.is_open())
    {
        while(!infile.eof())
        {
            if(infile >> placeholder.price)
            {
            infile.ignore(1, '\n');
            getline(infile, placeholder.name);
            Store.push_back(placeholder);
            }
        }
        infile.close();
    }
}
void get_list(vector<string>& Wishes, int& budget)
{
    string inputfile;
    string placeholder;
    cout << "Input the filename of the wishlist: ";
    getline(cin, inputfile);
    ifstream infile(inputfile);
    if(infile.is_open())
    {
        infile >> budget;
        while(!infile.eof())
        {
            if(getline(infile, placeholder))
            {
                Wishes.push_back(placeholder);
            }
        }
        Wishes.erase(Wishes.begin());
    infile.close();
    }

}

void available_gifts(vector<gift>& Available, vector<gift>& Store, vector<string>& Wishes)
{
    //                                                                                                         
    for(int i = 0; i < Wishes.size(); i++)
    {
        for(int j = 0; j < Store.size(); j++)
        {
            if(Store[j].name == Wishes[i])
            {
                Available.push_back(Store[j]);
            }
        }
    }
}

int total_price(vector<gift> x){
    //                                                               
    assert(x.size() >= 0);
    int sum = 0;
    for(int i = 0; i < x.size(); i++){
        sum += x[i].price;
    }
    return sum;
}

void improve(vector<gift> current, vector<gift> best){
    assert(current.size() >= 0 && best.size() >= 0);
    //                                                                                    
    if(total_price(current) > total_price(best)){
        Best = current;
    }
}

int ding(vector<gift>& gifts, vector<gift>& current, vector<gift>& best, int place, int budget){
    //            
    //                                                                           
    //                              
    assert(gifts.size() >= 0);
    if(budget == 0)                 {Best = current; return 1;}
    else if(place >= gifts.size())  {improve(current, best); return 0;}
    else if(budget < 0)             {return 0;}
    else
    //          
    {
        current.push_back(gifts[place]);
        ding(gifts, current, best, place+1, budget - gifts[place].price);
        current.pop_back();
        ding(gifts, current, best, place+1, budget);
    }

}

int main()
{
    int budget;

    load_store(Store);
    get_list(Wish, budget);

    available_gifts(Availabe, Store, Wish);

    ding(Availabe, Current, Best, 0, budget);
    Best.pop_back();

    cout << "Sinterklaas' budget is " << budget << "\n" << endl;
    //                            
    for(int i = 0; i < Best.size(); i++){
        cout << Best[i];
    }

    cout << "\nThis selection of gifts leaves Sinterklaas with " << budget - total_price(Best) << " euro's" << endl;

    return 0;
}

