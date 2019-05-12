#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

//                                              
//                                                   

/*                                                                                   
                               
                   
                      
                                

                                  
                               
                                  
                                     
                       

                                
                                            
                                               
                                  
                     
                                                                  
                                                                     

                                 
                                    
                                    
                                            
                               
                           
                       
                           

                               
                            
                               
                   

                                
                                  
                                                                  
                                                                                   */

ifstream giftstore;
ifstream wish_list;

struct Giftlist {
    int     price;
    string  name;
};

struct Wishlist {
    string  name;
};

int max_price;
vector<Wishlist> listofwishes;
vector<Giftlist> listofgifts;
vector<Giftlist> finallist;
vector<Giftlist> solutions;
vector<Giftlist> current;
vector<Giftlist> best;

void open_giftstore (ifstream& giftstore, vector<Giftlist>& listofgifts){
//               
    assert( true );
/*                
                                                                                
*/
    int i = 0;
    giftstore.open("giftstore.txt");

    while(giftstore){
        Giftlist temp;
        giftstore >> temp.price;
        giftstore.get();
        getline(giftstore, temp.name);
        listofgifts.push_back(temp);
        i++;
    }
}

void show_solution (vector<Giftlist>& solutions){
//               
    assert( true );
/*                
                                
*/
    int j = solutions.size();

    for(int i = 0; i < j; i++){
        cout << solutions[i].price << " " << solutions[i].name << endl;
    }
}

void show_wishlist (vector<Wishlist>& listofwishes, int max_price){     //                                                                                           
//               
    assert( true );
/*                
                                     
*/
    int j = listofwishes.size() - 1;
    cout << max_price << endl;

    for(int i = 0; i < j; i++){
        cout << listofwishes[i].name << endl;
    }
}

void open_wishlist (ifstream& wish_list, vector<Wishlist>& listofwishes, int& max_price){
//               
    assert( true );
/*                
                                                                                                                       
*/
    Wishlist hoi;
    string listname;
    cout << "Who's list do you want to open? ";
    cin >> listname;
    listname += ".txt";

    wish_list.open(listname);

    wish_list >> max_price;
    getline(wish_list, hoi.name);

    while (wish_list){
        Wishlist temp;
        getline(wish_list, temp.name);
        listofwishes.push_back(temp);
    }
}

void list_with_prices (vector<Giftlist>& finallist, vector<Giftlist>& listofgifts, vector<Wishlist>& listofwishes){
//               
    assert( true );
/*                
                                                                                                                                                                  
                                      
*/
    int q = 0;
    int wishsize = listofwishes.size();
    int giftsize = listofgifts.size();

    for(int i = 0; i < wishsize; i++){
        for(int j = 0; j < giftsize; j++){
            if(listofwishes[i].name == listofgifts[j].name){
                finallist.push_back(listofgifts[j]);
                q++;
            }
        }
    }
}

bool is_better_solution (vector<Giftlist>& a, vector<Giftlist>& b){
//               
    assert( true );
/*                
                                                                                                                                          
*/
    int size_of_a = a.size()-1;
    int size_of_b = b.size()-1;
    int k = 0;
    int l = 0;

    for(int i = 0; i < size_of_a; i++){
        k = k + a[i].price;
        }
    for(int j = 0; j < size_of_b; j++){
        l = l + b[j].price;
    }
    return k < l;
}

void copy_solution (vector<Giftlist>& c, vector<Giftlist>& d){
//               
    assert( true );
/*                
                                                                                    
*/
    d.clear();
    int size_of_c = c.size();

    for(int i = 0; i < size_of_c; i++){
        d.push_back(c[i]);
    }
}

int sum (vector<Giftlist>& current, int from){
//                
    assert (from >= 0 && from <= current.size()) ;
/*                 
                                                                               
*/
    int sum = 0;
    for (int i = from; i < current.size(); i++)
        sum += current[i].price ;
    return sum ;
}
int gifts (vector<Giftlist>& best, vector<Giftlist>& solutions, vector<Giftlist>& finallist, int c, int target){
//               
    assert ( c >= 0 );
/*                
                                                                                                                                                  
*/
    if (target == 0) {
        copy_solution(solutions, best);
        return 1;
    }
    else if (target < 0) {
        return 0;
    }
    else if ( c >= finallist.size()) {
        if(is_better_solution(best, solutions)){
            copy_solution(solutions, best);
        }
        return 0;
    }
    else if ( sum(solutions, 0) + sum(finallist, c) <= sum(best,0)){
        return 0;
    }

    else {
        solutions.push_back(finallist[c]);
        int with_c =    gifts(best, solutions, finallist, c+1, target - finallist[c].price);
        solutions.pop_back();
        int without_c = gifts(best, solutions, finallist, c+1, target);
        return with_c + without_c;
    }
}

int main(){
//               
    assert ( true );
/*                
                                                                                                                                                                    
                                                                                                                                                        
                                          
*/
    open_giftstore(giftstore, listofgifts);
    open_wishlist(wish_list, listofwishes, max_price);
    list_with_prices(finallist, listofgifts, listofwishes);
    gifts(best, solutions, finallist, 0, max_price);
    cout << "The best giftlist is:" << endl;
    show_solution(best);
}

