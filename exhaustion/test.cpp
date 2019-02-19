/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年02月19日 星期二 13时56分14秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include<iostream>
using namespace std;

typedef struct tagCharItem
{
    char c;
    int value;
    bool leading;
}CHAR_ITEM;


CHAR_ITEM charItem[] = { {'W', -1, true}, {'D', -1, true}, {'O', -1, false},
                        {'T', -1, false}, {'G', -1, true}, {'L', -1, false},
                        {'E', -1, false}, {'C', -1, false}, {'M', -1, false}};

typedef struct tagCharValue
{
    bool used;
    int value;
}CHAR_VALUE;

CHAR_VALUE charValue[10];

const int max_char_count = 9;
const int max_number_count = 10;

typedef void(*CharListReadyFuncPtr)(CHAR_ITEM ci[]);

int IsValueValid(CHAR_ITEM ci, CHAR_VALUE cv)
{
    if (ci.leading == true && cv.value == 0)
        return 0;
    
    if (cv.used == true)
        return 0;

     return 1;

}


void SearchingResult(CHAR_ITEM ci[], CHAR_VALUE cv[], int index, CharListReadyFuncPtr callback)
{
    //std::cout << "index "<< index << endl;
    if (index == max_char_count)
    {
        callback(ci);
        return;
    }

    for (int i = 0; i <  max_number_count; ++i)
    {
        if (IsValueValid(ci[index], cv[i]))
        {
   //         std::cout << "alpha "<< ci[index].c << " value " <<cv[i].value << endl;
            cv[i].used = true;
            ci[index].value = cv[i].value;
            SearchingResult(ci, cv, index + 1 , callback);
            cv[i].used = false;
        }
    }
}


int MakeIntegerValue(CHAR_ITEM ci[], char *string)
{
    int ret = 0;
    char *p = string;

//    std::cout << string <<endl << "ret ";
    while(*p!= '\0')
    {
        ret *= 10;
        for (int i = 0; i < max_char_count; i++)
        {
            if (*p == ci[i].c)
            {
               ret += ci[i].value; 
  //              std::cout << *p << " ret "<<ret;
               
               break;
            }
        }

        p++;
    }

    return ret;
    
}

void onCharListReady(CHAR_ITEM ci[])
{
    char *minuend  = "WWWDOT";
    char *subtrahend = "GOOGLE";
    char *diff = "DOTCOM";

    int m = MakeIntegerValue(ci, minuend);
    int s = MakeIntegerValue(ci, subtrahend);
    int d = MakeIntegerValue(ci, diff);

//      std::cout <<"m = "<<  m << " s = " << s << " d =" << d << std::endl;

    if ( (m-s) == d)
    {
        std::cout << m << "-" << s << "=" << d << std::endl;
    }
}


int main(int argc, char **argv)
{
    //init cv
    for (int i = 0 ;i < max_number_count; i++)
    {
      charValue[i].used = false;
      charValue[i].value = i;   
    }

    SearchingResult(charItem, charValue, 0, onCharListReady);
}

