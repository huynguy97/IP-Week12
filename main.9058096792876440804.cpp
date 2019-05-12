#include <iostream>
#include <cassert>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

//                                                                                          
//                                                                                          

/*
      
                                                          

                                                
                                                                            
                                                                               
      
        
       
         
*/

typedef int money;

struct Present{
    money cost;
    string item;};

string enter_filename(string& filename)
{
    assert(true);
    //                                                                
    cout<<"Please enter filename"<<endl;
    cin>>filename;
    return filename;
}

bool read_wishlist(ifstream& wishfile, money& budget, vector<string>& inter_wish)
{
    assert(wishfile.is_open());
    //                                                         
    string wish;
    wishfile>>budget;
    cout<<budget<<endl;
    while(getline(wishfile,wish)){
        inter_wish.push_back(wish);
    }
    if(inter_wish.size()>0){
        return true;}
    else{
        cout<<"Something went wrong";
        return false;}
}

bool check_wishlist(vector<Present>& giftstore, vector<Present>& wishlist, vector<string>& inter_wish, money budget)
{
    assert(inter_wish.size()>0&&giftstore.size()>0);
    //                                                                                                                                                   
    int k=0;
    for(int i=0;i<inter_wish.size();i++){
        for(int j=0;j<giftstore.size();j++){
            string b= giftstore[j].item;
            string c = " " + inter_wish[i];
            if(c == b&&giftstore[j].cost<=budget){
                const Present p=giftstore[j];
                wishlist.push_back(p);
                cout<<wishlist[k].item<<endl;
                k++;}
        }
    }
    if(k>0)
        return true;
    else{
        cout<<"Error";
        return false;}
}

bool read_giftstore(ifstream& storefile, vector<Present>& giftstore)
{
    assert(true);
    //                                                         
    string a;
    int c;
    int i=0;
    storefile.open("Giftstore.txt");
    while(storefile){
          storefile>>c;
          getline(storefile,a);
          const Present p={c,a};
          giftstore.push_back(p);
          i++;}
    if(i>0)
        return true;
    else return false;
}

int total_price(vector<Present>& wishlist)
{
    assert(wishlist.size()>0);
    //                                                                           
    money price=0;
    for(int i=0;i<wishlist.size();i++){
       price+=wishlist[i].cost;
    }
    return price;
}

int cheapest_present(vector<Present>& wishlist)
{
    assert(wishlist.size()>0);
    //                                                                                 
    vector<int> wishprice;
    for(int i=0;i<wishlist.size();i++){
        const int a=wishlist[i].cost;
        wishprice.push_back(a);}
    make_heap(wishprice.begin(),wishprice.end());
    pop_heap(wishprice.begin(),wishprice.end());
    push_heap(wishprice.begin(),wishprice.end());
    sort_heap(wishprice.begin(),wishprice.end());
    cout<<wishprice[0];
    return wishprice[0];
}

bool remove_gift(vector<Present>& giftlist, int& a, int& i)
{
    assert(giftlist.size()>0);
    //                                                             
    money cost=giftlist[i].cost;
    if(cost==a){
        giftlist.erase(giftlist.begin()+i);
        a-=cost;
        i=0;
        return true;}
    else if(cost>a){
        giftlist.erase(giftlist.begin()+i);
        a-=cost;
        i=0;
        return true;}
    else if(cost<a){
        giftlist.erase(giftlist.begin()+i);
        a-=cost;
        i++;
        remove_gift(giftlist,a,i);}
}

bool add_gift(vector<Present>& giftlist, vector<Present>& wishlist, int& a, int& i)
{
    assert(wishlist.size()>0);
    //                                                        
    a= -a;
    money cost=wishlist[i].cost;
    if(cost==a){
        Present p=wishlist[i];
        giftlist.push_back(p);
        a-=cost;
        i=0;
        return true;}
    else if(cost<a){
        Present p=wishlist[i];
        giftlist.push_back(p);
        a+=-cost;
        i=0;
        return true;}
    else if(cost>a){
        Present p=wishlist[i];
        giftlist.push_back(p);
        a+=-cost;
        i++;
        add_gift(giftlist,wishlist,a,i);}
}

bool find_gift(vector<Present>& giftlist, vector<Present>& wishlist, int& a)
{
    assert(wishlist.size()>0);
    //                                                                                                                                                       
    int i=0;
    if(a<cheapest_present(wishlist)&&a>=0){
        return true;}
    else if(a>0){
        if(remove_gift(giftlist,a,i)){
            cout<<a<<endl;
            find_gift(giftlist,wishlist,a);}
    }
    else if(a<0){
        if(add_gift(giftlist,wishlist,a,i)){
            cout<<a<<endl;
            find_gift(giftlist,wishlist,a);}
    }
}

int main()
{
    vector<Present> giftstore;
    vector<string> inter_wish;
    vector<Present> wishlist;
    vector<Present> giftlist=wishlist;
    ifstream storefile;
    ifstream wishfile;
    string filename;
    money budget=0;
    enter_filename(filename);
    if(read_giftstore(storefile,giftstore)){
        wishfile.open(filename);
        if(read_wishlist(wishfile,budget,inter_wish)){
            if(check_wishlist(giftstore,wishlist,inter_wish,budget)){
                int a=total_price(wishlist)-budget;
                if(find_gift(giftlist,wishlist,a)){
                    for(int i=0;i<giftlist.size();i++){
                        cout<<giftlist[i].item<<endl;}
                }
            }
        }
    }
return 0;
}

