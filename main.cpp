#include <stdio.h>
#include <stdlib.h>

// -------------------------------
// DECLARATIONS
// -------------------------------

int mod11(char *s); // this is THE GODFATHER
int strLen(char *s);
int toInt(char *s);
int numOfDash(char *s);
int numOfDigits(char *s);
char * strSplit(char *s, char *d);
int controlNumCheck(int n);
int isDigit(char *s);

// -------------------------------
// MAIN
// -------------------------------

int main(){
    char *s = "1677036253-1677036253";

    int result; 

    result = mod11(s);

    printf("\nresult: %d\n", result);
    // char *p;
    // int result, valid;
    // int len, digit, dashes;

    // dashes = numOfDash(s);
    
    // if(dashes != 0){
    //     valid = dashes;
    // }
    // else
    // {
    //     p = strSplit(s, "-");
    //     while(*p)
    //     {
    //         len = numOfDigits(p);
            
    //         if(len == 0){
    //             // check for non-digit characters
    //             digit = isDigit(p);
    //             if(digit == 0){
    //                 // check control number
    //                 result = controlNumCheck(toInt(p));
    //                 if(result > 0) valid = result;
    //             }
    //             else valid = digit;                
    //         }
    //         else valid = len;

    //         //get new substring
    //         p = strSplit(s, "-");
    //     }
    // }

    // if(valid == 0) printf("All good");
    // else if(valid == 5) printf("Wrong number of data. Too many dashes.");
    // else if(valid == 4) printf("Wrong number of digits in a single data");
    // else if(valid == 3) printf("Data contains non-digit caracters");
    // else if(valid == 2) printf("Wrong control number");
    return 0;
}

// -------------------------------
// IMPLEMENTATIONS
// -------------------------------

int mod11(char *s){
    char *p;
    int result, valid;
    int len, digit, dashes;

    dashes = numOfDash(s);
    
    if(dashes != 0){
        valid = dashes;
    }
    else
    {
        p = strSplit(s, "-");
        while(*p)
        {
            len = numOfDigits(p);
            
            if(len == 0){
                // check for non-digit characters
                digit = isDigit(p);
                if(digit == 0){
                    // check control number
                    result = controlNumCheck(toInt(p));
                    if(result > 0) valid = result;
                }
                else valid = digit;                
            }
            else valid = len;

            //get new substring
            p = strSplit(s, "-");
        }
    }

    if(valid == 0) printf("All good");
    else if(valid == 5) {printf("Wrong number of data. Too many dashes.");return valid;}
    else if(valid == 4) {printf("Wrong number of digits in a single data");return valid;}
    else if(valid == 3) {printf("Data contains non-digit caracters");return valid;}
    else if(valid == 2) {printf("Wrong control number");return valid;}
}

int strLen(char *s){
    int i = 0;
    while(s && *s++ != '\0') i++;
    return i;
}

int isDigit(char *s){
    int isDigit = 1;
    while(*s){
        if(*s >= '0' && *s <= '9') isDigit=1;
        else return 3;
        *s++;
    }

    if(isDigit == 1) return 0;
    else return 3;
}

int numOfDash(char *s){
    int i = 0;
    int delimiter = '-';
    while(s && *s++ != '\0'){
        if(*s == delimiter){
            i++;
        }
    }
    if(i >= 0 && i < 3){
        return 0;
    }
    return 5;
}

int toInt(char *s){
    int result = 0;
    int puiss = 1;

    while(('-' == (*s)) || ((*s) == '+')){
        if(*s == '-')
            puiss = puiss * -1;
        
        s++;
    }
    while((*s >= '0') && (*s <= '9')){
        result = (result * 10) + ((*s) - '0');
        s++;
    }

    return (result * puiss);
}

char * strSplit(char *s, char *d)
{
    static char buffer[100];
    static int pos =0;
    char *trav;
    int i =0;
    if(s == NULL)
    {
        return NULL;
    }
    if(pos != 0) {
        pos = pos+1;
    }
    trav = s+pos;
    while(*trav)
    {
        if(*trav != *d)
        {
            buffer[i++] = *trav++;
            pos++;
        }
        else
        {
            break;
        }
    }
    buffer[i] = '\0';
    return(&buffer[0]);
}

int numOfDigits(char *s){
    int c = strLen(s);
    if(c >= 0 && c <= 12) return 0;
    return 4;
}

int controlNumCheck(int n){
    int checkNum = n % 10;
    int controlNum = n/10;
    int mp = 2;
    int sum = 0;
    int i;

    while(controlNum!=0){
        sum += (controlNum % 10) * mp;

        mp++;
        if(mp > 7) mp = 2;

        controlNum /= 10;
    }
    
    int mod = (sum%11);

    if(mod == 0 || mod == 1) return 2;
    if(checkNum != (11-mod)) return 2;

    return 0;
}