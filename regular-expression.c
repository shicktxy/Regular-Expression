//Regex
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

int RegexCheck(const char *original_regex_str){  //Check the regex santax ,return error if the regex is started with * or
    if (*original_regex_str == '*')              //has part like ** 
        return -1;
    for (int i = 0; i < strlen(original_regex_str); i++) {
        if (original_regex_str[i] == '*'&&original_regex_str[i - 1] == '*')
        return -1;
    }
    return 0;
}

char* RegexStringRevise(const char *original_regex_str) {  //Delete the repeated part like a*a or a*a* in the regex
    int regex_str_len = strlen(original_regex_str);  
    char *temp = (char*)malloc((regex_str_len + 1) * sizeof(char));
    int i=0,j=0;
    while (original_regex_str[i]!='\0') {
        if (original_regex_str[i] == '*') {
            temp[j] = original_regex_str[i];
            j++;
            i++;
            while (original_regex_str[i] == '*' || original_regex_str[i] == temp[j - 2]) {
                i++;
            }
        }
        else {
        temp[j] = original_regex_str[i];
        i++;
        j++;
        }
    }
    temp[j] = '\0';
    return temp;
}

int GetAllowed(char *regex_str, char *allowed) { //get possible char to compare of every bit of the regex
    int k = 0;                                   
    char *temp = regex_str;
    if (*(temp + 1) != '*')
        allowed[k] = *temp;
    else if (*(temp + 1) == '*') {
        while (*temp != '\0' && *(temp + 1) == '*') {
            allowed[k] = *temp;
            k++;
            temp += 2;
        }
        allowed[k] = *temp;
    }
    return k+1;
}

bool BitCompare(char **original_str,char **regex_str, char *allowed, int n) { //compare every bit of the original string with the regex
    int k;																	  //use pointer to pointer to change the value of pointer
    if (n == 1) {
        if (**original_str == allowed[0]) {
            (*original_str)++;
            (*regex_str)++;
            return true;
        }
        else if (allowed[0] == '.') {
            (*original_str)++;
            (*regex_str)++;
            return true;
        }
    }
    else {
        for (k = 0; k < n; k++) {  //firstly check a to z
            if (allowed[k] != '.' && **original_str == allowed[k]) {
                if (k != n - 1) {
                    (*original_str)++;
                    (*regex_str) += k * 2;
                return true;
                }
                else {
                    (*regex_str) += k * 2;  //exit the * algorithm
                    return true;
                }
            }
        }
        for (k = 0; k < n; k++) {  //check .
            if (allowed[k] == '.') {
                if (k != n - 1) {
                    (*original_str)++;
                    (*regex_str) += k * 2;
                    return true;
                }
                else {
                    (*regex_str) += k * 2;  //exit the * algorithm
                    return true;
                }
            }		
        }
    }
    return false;  //fail to compare ,return 0
}

bool RegexCompare(const char *original_str, const char *original_regex_str) {  //compare the original string with the regex
    if (RegexCheck(original_regex_str))
        return false;  //regex santax error
    char *regex_str;
    regex_str = RegexStringRevise(original_regex_str);  //revise the regex
    char allowed[50]; 
    int count;
    char *point_regex = regex_str;  //generate the pointer to every bit of the string
    char *point_original = original_str;

    while (*point_regex != '\0' || *point_original != '\0') {  //compare bit by bit 
        count = GetAllowed(point_regex, allowed);
        if (BitCompare(&point_original, &point_regex, allowed, count) == false) {
            break;
        }
    }
    if (*point_original == '\0'&&*point_regex == '\0') {  //success
        free(regex_str);
        return true;
    }
    else {  //fail
        free(regex_str);
        return false;
    }
}


void main()
{
    char original_str[50];
    char original_regex_str[50];
    while (1) {
        printf("Please input the orginal string. Input Q to quit\n");
        if (strcmp(gets_s(original_str, 50), "Q") == 0)
            break;
        printf("Please input the regex string. Input Q to quit\n");
        if (strcmp(gets_s(original_regex_str, 50), "Q") == 0)
            break;
        bool flag = RegexCompare(original_str, original_regex_str);
        if (flag == true)
            printf("True\n");
        else
            printf("False\n");	
    }
}

