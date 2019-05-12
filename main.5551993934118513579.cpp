#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <vector>

using namespace std;

//                                                      

struct Gift{
    int Price;
    string Name;
};

void operator<< (ostream& out, Gift gift){
    //                           
    assert(true);
    //                                             
    out << "Gift Price: " << gift.Price << " Gift Name: " << gift.Name << endl;
}

void PrintVector(vector<Gift> vec){
    //                           
    assert(true);
    //                       
    for (Gift gift: vec)
        cout << gift;
}

void CreateGiftStore(vector<Gift>& Giftstore){
    //                           
    assert(true);
    //                                             
    char space;
    Gift gift;
    ifstream file;
    file.open("giftstore.txt");
    cout << file.is_open() << endl;
    while (file >> gift.Price){
        file.get(space);
        getline(file, gift.Name);
        Giftstore.push_back(gift);
    }
}

void CreatePresents(vector<Gift>& WishList, string Person, int&Budget){
    //                                                      
    assert(Budget >= 0);
    //                                   
    string Present;
    Gift gift;
    ifstream file;
    file.open(Person.c_str());
    file >> Budget;
    getline(file, gift.Name);
    while (getline(file, gift.Name)) {
        gift.Price = 0;
        WishList.push_back(gift);
    }
}

void FixPresents(vector<Gift>& Wishlist, vector<Gift> Giftstore) {
    //                           
    assert(true);
    //                                                                                                              
    for (int i = 0; i < Wishlist.size(); i++)
        for (Gift Product : Giftstore)
            if (Wishlist[i].Name == Product.Name)
                Wishlist[i].Price = Product.Price;
    for (int i = 0; i < Wishlist.size(); i++)
        if (Wishlist[i].Price == 0) {
            Wishlist.erase(Wishlist.begin() + i);
        }
}

void gifts (vector<Gift> Wishlist, vector<Gift>& Solution, vector<Gift>& RealSolution, vector<Gift> Giftstore, int Budget, int& Total, int& BestTotal, int Size, int Place){
    //                                                      
    assert(Budget >= 0);
    //                                                              
    if (Total > Budget)
        return;
    if (Total > BestTotal) {
        BestTotal = Total;
        RealSolution = Solution;
    }
    for (int i = Place; i < Size; i++) {
        Solution.push_back(Wishlist[i]);
        Total += Wishlist[i].Price;
        gifts(Wishlist, Solution, RealSolution, Giftstore, Budget, Total, BestTotal, Size, i+1);
        Total -= Wishlist[i].Price;
        Solution.pop_back();
    }
}

int main() {
    int Place = 0;
    int BestTotal = 0;
    int Total = 0;
    int Budget;
    vector<Gift> Solution;
    vector<Gift> RealSolution;
    vector<Gift> Giftstore;
    vector<Gift> WishList;
    CreateGiftStore(Giftstore);
    CreatePresents(WishList, "Edward.txt", Budget);
    FixPresents(WishList, Giftstore);
    gifts(WishList, Solution, RealSolution, Giftstore, Budget, Total, BestTotal, WishList.size(), Place);
    PrintVector(RealSolution);
    return 0;
}
