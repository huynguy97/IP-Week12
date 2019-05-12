/*                                                                             
                                                                               
                                                           */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

struct Gift
{
	int price;
	string type;
	string name;
};

vector<Gift> giftstore;
vector<Gift> list_andrew;
vector<Gift> list_belle;
vector<Gift> list_chris;
vector<Gift> list_desiree;
vector<Gift> list_edward;
vector<Gift> list_fabienne;
int budget_andrew, budget_belle, budget_chris, budget_desiree, budget_edward, budget_fabienne;

ostream& operator<< (ostream& out, Gift& gift)
{//              
    assert(true);
/*                                                        
*/
    out << gift.price << ' '
        << gift.type << ' '
        << gift.name;
    return out;
}

istream& operator>> (istream& in, Gift& gift)
{//              
    assert(true);
/*                                                            
*/
    int price;
    string type, name, pricestr;

    getline(in, pricestr, ' ');
    if(pricestr[0]!=NULL)
    {
        price=stoi(pricestr);
        gift.price=price;

        getline(in, type, ' ');
        gift.type=type;

        getline(in, name, '\n');
        gift.name=name;
    }
}

bool operator== (const Gift& a, const Gift& b)
{//             
    assert(true);
/*                                                                                 
*/
    if(a.name==b.name && a.price==b.price && a.type==b.type)
        return 1;
    else
        return 0;
}

void show(vector<Gift>vect)
{//              
    assert(true);
/*                                                        
*/
    int c=0;
    while(c<vect.size())
    {
        cout << vect[c] << endl;
        c++;
    }
}

int sum(vector<Gift>sum, int c)
{//                                                          
    assert(c>=0 && c<=sum.size());
/*                                                                                                                        
*/
    int csum=0, counter=c;
    while(counter<sum.size())
    {
        csum=csum+sum[counter].price;
        counter++;
    }
    return csum;
}

int minimum(vector<Gift>minimum, int c)
{//                                                          
    assert(c>=0 && c<minimum.size());
/*                                                                                                                   
*/
    int minim=999999999, counter=c;
    while(counter<minimum.size())
    {
        if(minimum[counter].price<minim)
            minim=minimum[counter].price;
        counter++;
    }
    return minim;
}

void clearvector(vector<Gift>&clvector)
{//              
    assert(true);
/*                                                           
*/
    while(clvector.size()>0)
    {
        clvector.pop_back();
    }
}

void improve(vector<Gift>&a, vector<Gift>&b)
{//              
    assert(true);
/*                                                                                  
*/
    vector<Gift>help;
    int counter=0;
    if(sum(b,0)<sum(a,0))
    {
        clearvector(b);
        while(counter<a.size())
        {
            b.push_back(a[counter]);
            counter++;
        }
    }
}

bool load_giftstore()
{//              
    assert(true);
/*                                                                                                                                                  
                            
*/
    ifstream infile;

    cout << "Loading in giftstore..." << endl;
    cout << "Opening file 'giftstore.txt'...";
    infile.open("giftstore.txt");
    if(!infile.is_open())
    {
        cout << " Unsuccessful." << endl << "Aborting" << endl;
        return false;
    }
    cout << " Successful." << endl;
    Gift gift;
    int counter=0;

    while(infile)
    {
        infile >> gift;
        giftstore.push_back(gift);
    }
    giftstore.pop_back();
    infile.close();
    if(giftstore.size()>0)
    {
        cout << "Giftstore successfully loaded in, loaded in " << giftstore.size() << " entries." << endl;
        return 1;
    }
    else
        return 0;

}
bool open_file(ifstream& infile, string fname)
{//                                                                 
    assert(!infile.is_open());
/*                                                                                                           
*/
    infile.open(fname.c_str());
    if(!infile.is_open())
        return false;
    return true;
}

bool load_list(ifstream& infile, int& budget, vector<Gift>& wishes)
{//                                            
    assert(infile.is_open());
/*                                                                                                                 
                                                                                   
*/
    string budgetstr, type, giftname;
    Gift gift;
    int counter=0;

    getline(infile, budgetstr, '\n');
    budget=stoi(budgetstr);
    gift.price=0;

    while(infile)
    {
        getline(infile, type, ' ');
        gift.type=type;

        getline(infile, giftname, '\n');
        gift.name=giftname;

        wishes.push_back(gift);
        counter++;
    }
    wishes.pop_back();
    if(wishes.size()>0)
        return true;
    else
        return false;
}

void delfromlist(vector<Gift>& dellist, int pos)
{//                                                         
    assert(pos>=0 && pos<dellist.size());
/*                                                             
*/
    int counter=pos;
    while(counter<dellist.size()-1)
    {
        dellist[counter]=dellist[counter+1];
        counter++;
    }
    dellist.pop_back();
}

void find_prices(vector<Gift>& wishes)
{//              
    assert(true);
/*                                                                                                                                       
                                           
*/
    int counterwishes=0, countergiftstore=0, value=0;
    bool found=false;

    while(counterwishes<wishes.size())
    {
        while(countergiftstore<giftstore.size())
        {
            if(wishes[counterwishes].type==giftstore[countergiftstore].type && wishes[counterwishes].name==giftstore[countergiftstore].name)
            {
                wishes[counterwishes].price=giftstore[countergiftstore].price;
                found=true;
                value=giftstore[countergiftstore].price;
            }
            if(found)
                countergiftstore=giftstore.size();
            countergiftstore++;
        }
        if(found)
            counterwishes++;
        else
            delfromlist(wishes, counterwishes);
        found=false;
        countergiftstore=0;
    }
}

bool load_wishlists()
{//                                          
    assert(load_giftstore());
/*                                                                                       
                                                                                
*/
    ifstream infile;

    cout << "Loading in wishlists..." << endl;

    open_file(infile, "Andrew.txt");
    load_list(infile, budget_andrew, list_andrew);
    find_prices(list_andrew);
    infile.close();

    open_file(infile, "Belle.txt");
    load_list(infile, budget_belle, list_belle);
    find_prices(list_belle);
    infile.close();

    open_file(infile, "Chris.txt");
    load_list(infile, budget_chris, list_chris);
    find_prices(list_chris);
    infile.close();

    open_file(infile, "Desiree.txt");
    load_list(infile, budget_desiree, list_desiree);
    find_prices(list_desiree);
    infile.close();

    open_file(infile, "Edward.txt");
    load_list(infile, budget_edward, list_edward);
    find_prices(list_edward);
    infile.close();

    open_file(infile, "Fabienne.txt");
    load_list(infile, budget_fabienne, list_fabienne);
    find_prices(list_fabienne);
    infile.close();

    if(list_andrew.size()>0 && list_belle.size()>0 && list_chris.size()>0 && list_desiree.size()>0 && list_edward.size()>0 && list_fabienne.size()>0)
    {
        cout << "Successfully loaded in wishlists." << endl << endl;
        return true;
    }
    else
    {
        cout << "Something went wrong... not all wishlists could be loaded in." << endl << endl;
        return false;
    }
}

bool check_if_selection(vector<Gift>& selection, vector<Gift>& total)
{//              
    assert(true);
/*                                                                                                        
*/
    int counterselection=0, countertotal=0;
    bool found=false;

    while(counterselection<selection.size())
    {
        while(countertotal<total.size())
        {
            if(selection[counterselection]==total[countertotal])
                found=true;
            countertotal++;
        }
        if(!found)
            return false;
        else
            counterselection++;
    }
    return true;
}

bool check_values(vector<Gift> items)
{//              
    assert(true);
/*                                                                                                                                 
*/
    int counter=0;
    while(counter<items.size())
    {
        if(items[counter].price==0)
            return false;
        counter++;
    }
    return true;
}
int gifts(vector<Gift>& attempt, vector<Gift>& best, vector<Gift> items, int c, int target)
{//                                                                                                                 
    assert(check_if_selection(attempt, items) && check_values(items));
/*                                                                                                                          
*/
    if(target == 0)
    {
        best=attempt;
        return 1;
    }
    else if(target<0){
        return 0;}
    else if(c>=items.size())
    {
        improve(attempt, best);
        return 0;
    }
    else if(minimum(items, c)>target){
        return 0;}
    else if(sum(attempt, 0) + sum(items, c) <= sum(best, 0)){
        return 0;}
    else
    {
        attempt.push_back(items[c]);
        int with_c = gifts(attempt, best, items, c+1, target-items[c].price);
        attempt.pop_back();
        int without_c=gifts(attempt, best, items, c+1, target);
        return with_c + without_c;
    }
}

int main()
{
    vector<Gift> attempt;
    vector<Gift> best;
    int solutions=0;

    if(!load_wishlists())
        return 0;
    else
    {
        solutions=gifts(attempt, best, list_andrew, 0, 5000);
        cout << "Found " << solutions << " perfect options for andrew, best is:" << endl;
        show(best);

        solutions=gifts(attempt, best, list_belle, 0, budget_belle);
        cout << endl << "Found " << solutions << " perfect options for belle, best is:" << endl;
        show(best);

        solutions=gifts(attempt, best, list_chris, 0, budget_chris);
        cout << endl << "Found " << solutions << " perfect options for chris, best is:" << endl;
        show(best);

        solutions=gifts(attempt, best, list_desiree, 0, budget_desiree);
        cout << endl << "Found " << solutions << " perfect options for desiree, best is:" << endl;
        show(best);

        solutions=gifts(attempt, best, list_edward, 0, budget_edward);
        cout << endl << "Found " << solutions << " perfect options for edward, best is:" << endl;
        show(best);

        solutions=gifts(attempt, best, list_fabienne, 0, budget_fabienne);
        cout << endl << "Found " << solutions << " perfect options for fabienne, best is:" << endl;
        show(best);
    }
    return 0;
}

