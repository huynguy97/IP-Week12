#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

//                                              
//                                          

//         
//      
//                        
//                          
//    

//     
//        
//           
//                        
//    

//     
//                        
//                                    
//    

//       
//                            
//                            
//                                    
//                       
//                  
//                   
//               
//                                    
//    

//      
//             
//                        
//                          
//             
//     

//        
//                             
//                                           
//                                          
//              
//                       
//                    
//     

bool open_giftstore(vector<string>& gifts_in, vector<int>& values)
{
    assert(true);
    //                                                                
    int i = 0;
    int value;
    string name;
    ifstream opened ("giftstore.txt");
    while(opened)
    {
        opened >> value;
        values.push_back(value);
        opened.ignore(1);
        getline(opened,name);
        gifts_in.push_back(name);
    }
    values.pop_back();
    gifts_in.pop_back();
    opened.close();
}

bool gift_in_store(vector<string>& gifts_in, string present)
{
    assert(true);
    //                                                                            
    for(int i = 0; i < gifts_in.size(); i++)
    {
        if (present ==  gifts_in[i])
        {
            return true;
        }
    }
    return false;
}

int open_wishlist (vector<string>& gifts_wanted, string wish_name, vector<string>& gifts_in)
{
    assert(true);
    //                                                                                        
    string present;
    ifstream person;
    person.open(wish_name+".txt");
    int budget;
    person >> budget;
    person.ignore(80, '\n');
    while(person)
    {
        getline(person,present);
        if(gift_in_store(gifts_in,present))
        {
            gifts_wanted.push_back(present);
        }
    }
    person.close();
    return budget;
}
int values_at (vector<string> gifts_wanted, vector<string> gifts_in, int place, vector<int> values)
{
    assert(true);
    //                                                                                   
    for(int i = 0; i < gifts_in.size(); i++)
    {
        if(gifts_wanted[place] == gifts_in[i])
        {
            return (values[i]);
        }
    }
}

bool gifts(vector<string>& best_gifts , vector<string>& gifts_wanted,vector<int>& values, vector<string>& gifts_in, int& budget,int& multi_values,int& best_sum,int& index,int& start_index)
{
    assert(budget >= 0);
    //                
    //                                                                                                                                    
    //                                                                 
    //                                                                                                                 
    //                                                                                             
    //                                                                       
	int temp_sum=0;
	int temp_start = start_index;
    for(temp_start ; temp_start<multi_values; temp_start++)
    {
    	temp_sum+=values_at(gifts_wanted,gifts_in, start_index, values);
	}
	temp_sum+=values_at(gifts_wanted,gifts_in, index, values);
	if(temp_sum<=budget&&temp_sum>best_sum){
		best_sum=temp_sum;
		best_gifts.clear();
		int temp_start = start_index;
		 for(temp_start ; temp_start<multi_values; temp_start++)
    		{
    			best_gifts.push_back(gifts_wanted[temp_start]);
			}
		best_gifts.push_back(gifts_wanted[index]);
		index++;
		if(index==gifts_wanted.size())
		{
			start_index++;
			index=multi_values;
			gifts(best_gifts , gifts_wanted,values, gifts_in, budget, multi_values, best_sum, index,start_index);

		}
		gifts(best_gifts , gifts_wanted,values, gifts_in, budget, multi_values, best_sum, index,start_index);
	}

	if(multi_values==gifts_wanted.size()-1){
		return false;
	}
	index++;

	if(start_index ==gifts_wanted.size())
	{
		start_index=0;
		multi_values++;
		index=multi_values;
		gifts(best_gifts , gifts_wanted,values, gifts_in, budget, multi_values, best_sum, index,start_index);
	}

	if(index==gifts_wanted.size()){
		start_index++;
		index=multi_values;
		gifts(best_gifts , gifts_wanted,values, gifts_in, budget, multi_values, best_sum, index,start_index);
	}

	gifts(best_gifts , gifts_wanted,values, gifts_in, budget, multi_values, best_sum, index,start_index);

}

int main()
{
    string wish_name;
    int index =1,start_index=0;
    int multi_values=1,best_sum=0;
    vector<string> best_gifts;
    vector<string> gifts_wanted;
    vector<string> gifts_in;
    vector<int> values;
    open_giftstore(gifts_in,values);
    cout << "Please enter the name of the person" <<endl;
    cin >> wish_name;
    int budget = open_wishlist(gifts_wanted,wish_name,gifts_in);
   gifts(best_gifts ,gifts_wanted,values,gifts_in,  budget, multi_values, best_sum, index,start_index);
    for(int i = 0; i <best_gifts.size(); i++)
    {
        cout << best_gifts[i]<<endl;
    }
cout << best_sum;
    return 0;
}

