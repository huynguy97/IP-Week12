#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Gift {
    int price;
    string name;
};

ifstream& operator>> (ifstream& in, Gift& gift ){
    in >> gift.price;
    in.ignore();
    getline(in, gift.name);
    return in;
}

ostream& operator<< (ostream& out, Gift& gift) {
    out << gift.name << " has a price of: "<<gift.price << "\n";
    return out;

}

ifstream& operator>> (ifstream& in, string& str) {
    getline(in, str);
    return in;
}

bool read_giftshop(vector <Gift>& giftshoplist) {
    ifstream infile;
    infile.open("giftstore.txt");
    if (infile.is_open()) {
        cout << "Gift shop.txt opened succesfully" << endl;
    } else {
        cout << "Failed to open giftshop.txt" << endl;
    }

    Gift gift;
    while (infile) {
        infile >> gift;
        giftshoplist.push_back(gift);

    }

    infile.close();

}

bool read_wishlist(vector <string>& wishlist, int& budget) {
    ifstream infile;
    string wishlistname;
    cout << "Enter wishlist name.txt" << endl;
    cin >> wishlistname;
    infile.open(wishlistname);
    if (infile.is_open()) {
        cout << wishlistname <<" opened succesfully" << endl;
    } else {
        cout << "Failed to open " << wishlistname << endl;
    }
    infile >> budget;
    string str;
    while (infile) {
        infile >> str;
        wishlist.push_back(str);
    }

    infile.close();
}
void check_instore(vector<string> wishlist, vector<Gift> giftshoplist, vector<Gift>& instorelist) {
    for(int i = 0; i < giftshoplist.size(); i ++){
        for(int j = 0; j < wishlist.size(); j++) {
            if (giftshoplist[i].name == wishlist[j]) {
                instorelist.push_back(giftshoplist[i]);
            }
        }
    }
}

int gifts (vector <Gift> wishlist, int budget, int c, vector<Gift>& attempt ) {
    //                                                                                  

    if (budget == 0) {
        return 1;
    } else if(budget < 0) {
        return 0;
    } else if (c >= wishlist.size()) {
        return 0;
    } else {
        attempt.push_back(wishlist[c]);
        int with_gift = gifts(wishlist , budget - wishlist[c].price, c+1, attempt);
        attempt.pop_back();

        int without_gift = gifts(wishlist, budget, c + 1, attempt);

        return with_gift + without_gift;

    }
}

int main() {
    vector <Gift> giftshoplist;
    vector <string> wishlist;
    vector <Gift> instorelist;
    vector <Gift> attempt;
    int budget;
    read_giftshop(giftshoplist);
    read_wishlist(wishlist, budget);
    check_instore(wishlist, giftshoplist, instorelist);
    cout << budget << endl;
    cout << gifts(instorelist, budget, 0, attempt) << "" << attempt.size();
    for(int i =0; i < attempt.size(); i++){
        cout << attempt[i];
    }

}
