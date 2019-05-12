#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

//                              
//                              

//                                                                                                                                      

//                 

//                                     

/*
                                                     
 
                    
                 
                     

          
 */

/*                                                         
 
                    
                 
                     
                
                
                      
 

                                                     

                                                    

            
                    
                                 
                   
                                      

*/

typedef int List;
struct Slice {
    int from;
    int to;
};
int size(vector<List>& wish_list) {
    return wish_list.size();
}

int sum(vector<List>& money, int from, int to)
{
    int x = 0;
    for(int i = from; i < to; i++)
        x = x + money[i];
    return x;
}

void cout_vector(vector<List>& m)
{
    for(int i = 0; i < m.size(); i++)
        cout << m[i] << "\t";
}

int gifts(vector<List>& m, vector<List>& solution, vector<List>& best, int i, int budget) {
    cout_vector(solution);
    cout << endl;
    if (sum(best,0,best.size()) < sum(solution,0,solution.size()))
        best = solution;
    if (budget == 0)
        return 1;
    else if (budget < 0)
        return 0;
    else if (i >= m.size())
        return 0;
    else if (budget - m[i] < 0)
        return 1;
    else {
        int with_i = gifts(m, solution, best, i + 1, budget - m[i]);
        if (with_i == 1)
            solution.push_back(m[i]);
        int without_i = gifts(m, solution, best, i + 1, budget);
        return with_i + without_i;
    }
}

void read_list(vector<List>& m, int& budget)
{
    ifstream infile ("Belle.txt");
    ifstream store ("giftstore.txt");
    string line;
    vector<string> items;
    vector<string> stock;
    getline(infile,line);
    string b = line;
    budget = stoi(b);
    while (getline(infile, line))
    {
        items.push_back(line);
    }
    while (getline(store, line))
    {
        stock.push_back(line);
    }
    int q = 0;
    int i = 0;
    int teller = 0;
    vector<int>index;
    while (teller < items.size())
    {
        cout<< line<< "\t";
        line = stock[q];
        int start = 0;
        i = 0;
        while (start == 0 && i < line.size()) {
            if (int(line[i]) > 58 || int(line[i]) < 47)
                start = i + 1;
            i++;
        }
        cout << start << " ";
        cout << line.compare(start,line.size()-1, items[teller])<< endl;
        if (line.compare(start,line.size()-1, items[teller]) == 0) {
            //                  
            teller++;
        }
        q++;
        if (q >= stock.size())
            q = 0;
    }
    for (int k = 0; k < index.size(); k++)
        cout << index[k] << "piet";

}

int main() {
    int budget;
    vector<List> wish_list = {10,23,34,5,34};
    vector<List> solution;
    vector<List> best;
    //                                                        
    //                      

    cout<< endl;
    cout_vector(best);
    vector<List> m;
    read_list(m, budget);

    return 0;
}
