//                                                             
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;
vector<Gift>& shop;
vector<Gift>& wishes;

struct Gift{
string article;
int price;
};

typedef int Gift;

int size (vector<Gift>& wishes){
return static_cast<int> (wishes.size());
}
int gifts(vector<Gift>shop,int c, int target)
{
    if	    ( target == 0 )		    { return 1; }
	else if ( target < 0 )		    { return 0; }
	else if ( c >= size(shop) )	{ return 0; }
	else{

	}
	}
}
int main()
{

    return 0;
}

