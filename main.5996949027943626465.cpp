//                       
//                      

#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct gift_list {
    int price;
    string gift;
};

int size(vector<gift_list>& presents){
    return static_cast<int> (presents.size());
}

void skip_line(ifstream& wish_list){
    //             
    assert(true);

    /*                
                                                                           */

    //               
    string remains;
    getline(wish_list, remains);
}

void skip_space(ifstream& store){
    //             
    assert(true);

    /*                
                                                                         */

    //               
    string remains;
    getline(store, remains, ' ');
}

int load_wish_list(ifstream& wish_list, int& budget, vector<string>& wishes){
    //             
    assert(wish_list);

    /*                
                                                                                  
                      */

    //               
    wish_list >> budget;
    string gift;
    skip_line(wish_list);
    while(wish_list){
        getline(wish_list, gift);
        wishes.push_back(gift);
    }
    return budget;
}

istream& operator>> (ifstream& store, gift_list& list){
    //             
    assert(true);

     /*                
                                                                */

    //               
    store >> list.price;
    skip_space(store);
    getline(store, list.gift);
    return store;
}

ostream& operator<< (ostream& out, const gift_list list)
{
    out << list.price << ' ';
    out << list.gift ;
}

void load_gift_store(ifstream& store, gift_list& list, vector<gift_list>& pakjes){
    //             
    assert(true);

    /*                */

    //               

    while (store)
    {
        store >> list;
        pakjes.push_back(list);
    }

}

void show(vector<gift_list>& pakjes){
    //            
    assert(true);

    /*               
                                                         
                                  */

    //               
    const int NO_OF_ELEMS = size(pakjes);
    cout << "{";
    if(NO_OF_ELEMS >0){
        for(int i = 0; i<NO_OF_ELEMS-1; i++)
            cout << pakjes[i].gift << ",";
        cout << pakjes[NO_OF_ELEMS-1].gift;
    }
    cout << "}" << endl;
}

int gifts(vector<gift_list>& pakjes,
          vector<gift_list>& attempt, vector<string>& wishes, int wish, int budget){
            //   

            //               
            if (budget == 0){
                show(attempt);
                return 1;
            }
            else if(budget < 0){
                return 0;
            }
            else if (wish >= size(pakjes)){
            return 0;
            }
            else {

                for(int i =0; i<= wishes.size(); i++){
                for(int j = 0; j <= size(pakjes); i++){
                if (wishes[i] == pakjes[j].gift){
                attempt.push_back(pakjes[wish]);
                int with_wish = gifts(pakjes, attempt,wishes, wish+1, budget - pakjes[wish].price);
                attempt.pop_back();
                int without_wish = gifts(pakjes, attempt, wishes, wish+1, budget);
                cout << without_wish << endl;
                cout << with_wish << endl;
                return without_wish + with_wish;
            }
            }
            }
            }
          }

/*
                                                                                       
                   
                                              

                    

                     
                  
                    
              
  
                     
              
  
                               
                 
      
          
                                         
                                                                                     

                            
                                                                     
                                     
  
 
*/
int main() {
    cout << "Which child you want to check, my lord?" << endl;
    string filename;
    vector<string> wishes;
    vector<gift_list> pakjes;
    vector<gift_list> attempt;
    int money =0;
    cin >> filename;
    ifstream wish_list(filename);
    ifstream store("giftstore.txt");
    load_wish_list(wish_list,money, wishes);
    gift_list list;
    load_gift_store(store, list, pakjes);
    cout << pakjes.size()<< endl;
    cout << gifts(pakjes, attempt, wishes, 0, load_wish_list(wish_list, money, wishes)) << endl;

    return 0;
}

