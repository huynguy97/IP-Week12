#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <iostream>

/* 
                             
                             
*/

using namespace std;

double naive_power(double base, int exponent){
    //             
    assert(exponent >= 0);
    //              
    //                         
    //                
    //                                           
    if(base == 0 || base == 1)
        return base;
    else if(exponent == 0)
        return 1;
    else
        return base * naive_power(base, exponent - 1);
}

double unlimited_power(double base, int exponent){
    //             
    assert(exponent >= 0);
    //              
    //                         
    //                 
    //                                               
    if(base == 0 || base == 1)
        return base;
    else if(exponent == 0)
        return 1;
    else {
        double result = unlimited_power(base, exponent / 2);
        result *= result;
        if(exponent & 1) //                   
            result *= base;
        return result;
    }
}

bool palindrome1(const string& str, int i, int j){
    //             
    assert(i >= 0 && j < (int)str.length());
    //              
    //                                     
    if(j <= i)
        return true;
    else
        return str[i] == str[j] && palindrome1(str, i + 1, j - 1);
}

bool palindrome2(const string& str, int i, int j){
    //             
    assert(i >= 0 && j < (int)str.length());
    //              
    //                                     
    if(j <= i)
        return true;
    else {
        char c = str[i];
        char d = str[j];
        return
            (c == d ||
            (c >= 'a' && c <= 'z' && d == c - 'a' + 'A') ||
            (c >= 'A' && c <= 'Z' && d == c - 'A' + 'a'))
            && palindrome2(str, i + 1, j - 1);
    }
}

bool palindrome3(const string& str, int i, int j){
    //             
    assert(i >= 0 && j < (int)str.length());
    //              
    //                                     
    if(j <= i)
        return true;
    else {
        while(str[i] == ' '  ||
              str[i] == '.'  ||
              str[i] == ','  ||
              str[i] == ':'  ||
              str[i] == ';'  ||
              str[i] == '\'' ||
              str[i] == '!'  ||
              str[i] == '?'  ||
              str[i] == '-')
              i++;
        while(str[j] == ' '  ||
              str[j] == '.'  ||
              str[j] == ','  ||
              str[j] == ':'  ||
              str[j] == ';'  ||
              str[j] == '\'' ||
              str[j] == '!'  ||
              str[j] == '?'  ||
              str[j] == '-')
              j--;
        char c = str[i];
        char d = str[j];
        return ( c == d ||
                (c >= 'a' && c <= 'z' && d == c - 'a' + 'A') ||
                (c >= 'A' && c <= 'Z' && d == c - 'A' + 'a') ) &&
                palindrome3(str, i + 1, j - 1);
    }
}

bool match_chars(const string& chars, int i, const string& src, int j){
    //             
    assert(true);
    //               
    //                                                                   
    if(i >= (int)chars.length())
        return true;
    else if(j >= (int)src.length())
        return false;
    else if(chars[i] == src[j])
        return match_chars(chars, i + 1, src, j + 1);
    else
        return match_chars(chars, i, src, j + 1);
}

bool match_pattern_rec(const string& pattern, int i, const string& source, int j){
    if(i >= (int)pattern.length())
        return true;
    else if(j >= (int)source.length())
        return false;
    else if(pattern[i] == '*')
        return match_pattern_rec(pattern, i + 1, source, j    )
            || match_pattern_rec(pattern, i,     source, j + 1);
    else if(pattern[i] == '.' || pattern[i] == source[j])
        return match_pattern_rec(pattern, i + 1, source, j + 1);
    else
        return false;
}

bool match_pattern(string pattern, const string& source){
    //             
    assert(true);
    //               
    //                                    

    //            
    for(int i = 0; i + 1 < (int)pattern.length(); i++){
        while(pattern[i] == '*' && pattern[i + 1] == '*'){
            for(int j = i; j + 1 < (int)pattern.length(); j++)
                pattern[j] = pattern[j + 1];
            pattern.pop_back();
        }
        if(pattern[i] == '*' && pattern[i + 1] == '.'){
            char tmp = pattern[i];
            pattern[i] = pattern[i + 1];
            pattern[i + 1] = tmp;
        }
    }
    cout << pattern << endl;
    //         
    return match_pattern_rec(pattern, 0, source, 0);
}

int main()
{
    printf("%f\n", naive_power(2, 50));
    printf("%f\n", naive_power(1, 50));
    printf("%f\n", naive_power(0, 50));
    printf("%f\n", naive_power(2, 0));
    printf("%f\n", naive_power(2, 1));
    printf("%f\n", unlimited_power(2, 50));
    printf("%f\n", unlimited_power(1, 50));
    printf("%f\n", unlimited_power(0, 50));
    printf("%f\n", unlimited_power(2, 0));
    printf("%f\n", unlimited_power(2, 1));

    putchar('\n');

    printf("%X\n", palindrome1("otto", 0, 3));
    printf("%X\n", palindrome1("Otto", 0, 3));
    printf("%X\n", palindrome1("Madam, I'm Adam.", 0, 15));

    putchar('\n');

    printf("%X\n", palindrome2("otto", 0, 3));
    printf("%X\n", palindrome2("Otto", 0, 3));
    printf("%X\n", palindrome2("Madam, I'm Adam.", 0, 15));

    putchar('\n');

    printf("%X\n", palindrome3("otto", 0, 3));
    printf("%X\n", palindrome3("Otto", 0, 3));
    printf("%X\n", palindrome3("Madam, I'm Adam.", 0, 15));

    putchar('\n');

    printf("%X\n", match_chars("abc", 0, "It is a bag of cards", 0));
    printf("%X\n", match_chars("abc", 0, "It is a bag of books", 0));
    printf("%X\n", match_chars("abc", 0, "It is a classy bag", 0));

    putchar('\n');

    printf("%X\n", match_pattern("a***b**.c", "abbc"));
    printf("%X\n", match_pattern("a***b**.c", "abc"));
    printf("%X\n", match_pattern("a***bc", "ababc"));

    return 0;
}

