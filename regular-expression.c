//Regex
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

bool isMatch(char *s, char *p) {
    if (*p == '\0')
        return *s == '\0';
    bool match = (*s != '\0') && (*p == *s || *p == '.');  //realize the matching of '.'
    if (strlen(p) >= 2 && p[1] == '*') {  //using recursion to realize the matching of '*'
        return isMatch(s, p + 2) || (match && isMatch(s + 1, p));  //check out condition first
    }
    else
        return match && isMatch(s + 1, p + 1);
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
        bool flag = isMatch(original_str, original_regex_str);
        if (flag == true)
            printf("True\n");
        else
            printf("False\n");	
    }
}

