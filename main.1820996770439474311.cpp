#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;
int not_there = 0;

//                                           

struct gift
{
    string name;							//             
	int price;                              //              
};
void skip_to_next_newline (istream& infile)
{//               
    assert (true) ;
/*                 
                                                                        
*/
    string remains;
    getline (infile, remains);
}
void readfile_wishlist(ifstream& infile, vector<string>& wishlist, int& budget)
{
    assert(true);
    //                
    //                                                                                                  
    string name_person;
    cout << "From who do you want to check the wishlist? (Please use a capital letter)" << endl;
    cin >> name_person;
    string filename = name_person + ".txt";
    infile.open(filename.c_str());
    infile >> budget;
    skip_to_next_newline(infile);
    do  {
        string help;
        getline(infile,help);
        wishlist.push_back(help);
    }
    while(infile && infile.is_open());
    wishlist.pop_back();
    infile.close();
}
string substring(string original, int from)
{
    assert(from >= 0 && from <= original.length());
    //               
    //                                                                                                      
    string new_string;
    new_string.append(original,from,original.length()-1);
    return new_string;
}
void readfile_store(ifstream& infile, vector<gift>& instore)
{
    assert(true);
    //                
    //                                                                                  
    infile.open("giftstore.txt");
    while(infile)
    {
        int price;
        infile >> price;
        gift help;
        string helpname,helpname2;
        getline(infile,helpname);
        if(helpname.length() > 2)
        {
            helpname2 = substring(helpname,1);
            help.name = helpname2;
            help.price = price;
            instore.push_back(help);
        }
    }
    infile.close();
}
int sum (vector<gift>& gifts, int from)
{//               
    assert (from >= 0 && from <= gifts.size()) ;
//                 
//                                                                                                             
    int sum = 0 ;
    for (int i = from ; i < gifts.size() ; i++)
        sum += gifts[i].price;
    return sum ;
}

void improve (vector<gift>& current, vector<gift>& best,const int begin_budget)
{//               
    assert (true) ;
//                 
//                                                                 
    if(sum(current,0) <= begin_budget)
    {
        if (sum (current,0) > sum (best,0))
            best = current ;
    }

}
void gifts(vector<gift>& best,vector<string>& wishlist, vector<gift> instore, vector<gift>& attempt, int budget, int giftnumber, const int begin_budget)
{
    assert(begin_budget >= 0);
    //                
    //                                                                                
    if(budget == 0)
    {
        best = attempt;
        return;
    }
    else if(giftnumber >= wishlist.size())
    {
        improve(attempt,best,begin_budget);
        return;
    }
    else if(budget < 0)
    {
        budget = budget + attempt[attempt.size()-1].price;
        attempt.pop_back();
        improve(attempt,best,begin_budget);
        gifts(best,wishlist,instore,attempt,budget,giftnumber + 1,begin_budget);
    }
    else
    {
       int i = 0;

       bool found = false;
       bool out_of_wishlist = false;
       while( i <= instore.size() && !found)
       {
           if(i == instore.size())
           {
               gifts(best,wishlist,instore,attempt,budget,giftnumber + 1,begin_budget);
               found = true;
               out_of_wishlist = true;
           }
           if(!out_of_wishlist)
           {
                if(instore[i].name == wishlist[giftnumber])
               {
                   found = true;
               }
           }
           if(!found)
                i++;
        }
        if (!out_of_wishlist)
        {
            attempt.push_back(instore[i]);
            gifts(best,wishlist,instore,attempt,budget - instore[i].price,giftnumber+1,begin_budget); //                        
            attempt.clear();
            budget = begin_budget;
            gifts(best,wishlist,instore,attempt, budget,giftnumber+1,begin_budget);//                           
            return;
        }
       return;
    }
}
int main()
{
    ifstream infile,infile2;
    int budget;
    vector<gift> instore,best,attempt;
    vector<string> wishlist;
    readfile_wishlist(infile, wishlist, budget);
    cout << "The budget of this person is: " << budget << endl;
    cout << "The wishlist of this person:  " << endl;
    for (int i = 0 ; i < wishlist.size();i++)
    {
        cout << wishlist[i] << endl;
    }
    const int begin_budget = budget;
    readfile_store(infile2,instore);
    gifts(best,wishlist,instore,attempt,budget,0,begin_budget);
    cout << "The gifts with the maximum possible value ( " << sum(best,0) << " ) St Nicholas can give this person: " << endl;
    for (int i = 0; i < best.size(); i++)
    {
       cout << best[i].name << endl;
    }
    return 0;
}
/*                 
                                  
                            
                                      
                
                        
                          
                                                          
                                                             
                                                                      
                           
                                    
                  
                                                                                    
                        
                          

      
                                  
                            
        
           
           
              
          
                        
                 
                     
     
                                                                                    
          

      
                                  
                            
             
        
     
                        
                                       
                           
                      
                                    
                                              
                                              
                                              
                                              
                                              
                                              
                            
          
                 
                                                                                    
                        
                                       
                           

        
                                  
                            
                            
                            
                                    
                       
                  
                   
               
                                    
                                     
                
               
                   
                        
                          
                  
                                                                                    
                   
                        
                          
                  

       
                                   
                            
                           
                           
                                            
                                    
                                       
                                     
                                    
                
                                 
                                       
                   
             
                        
                          
             
                                                          
                                                             
                                                                      
                                                                                     
             
                        
                          
             
                                                          

         
                                   
                            
                       
                        
                          
                         
                                  
                               
                                 
                                     
                            
                                       
                                    
                             
                  
                 
              
                       
                    
             
                                                                                     
                       
                        
                          
                             

*/

