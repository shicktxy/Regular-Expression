//Regex
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

int RegexCheck(const char *original_regex_str){  //check if the first char of regex is '*' or if the expression has part like "**"
	if (*original_regex_str == '*')
		return -1;
	for (int i = 0; i < strlen(original_regex_str); i++) {
		if (original_regex_str[i] == '*'&&original_regex_str[i - 1] == '*')
			return -1;
	}
	return 0;
}

char* RegexStringRevise(const char *original_regex_str) {  //delete the iterative part such as "a*a" and "a*a*" in the regular expression and the error part like "a**"
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

bool RegexCompare(const char *original_str, const char *original_regex_str) {
	if (RegexCheck(original_regex_str))
		return false;  //input regex santax error
	char *regex_str;
	regex_str = RegexStringRevise(original_regex_str);

	char *point_regex = regex_str;
	char *point_original = original_str;

	if (*point_regex == '\0' && *point_original == '\0') {  //deal with expression with empty string
		free(regex_str);
		return true;
	}
	else if (*point_regex == '\0' && *point_original != '\0') {
		free(regex_str);
		return false;
	}
	else if (*point_regex != '\0' && *point_original == '\0') {
		while (*point_regex != '\0') {
			if (*(point_regex + 1) == '*')
				point_regex += 2;
			else {
				free(regex_str);
				return false;
			}
		}
		free(regex_str);
		return true;
	}

	while (*point_regex != '\0' && *point_original != '\0') {
		if ((*point_regex <= 'z' && *point_regex >= 'a') || *point_regex == '.') {
			if (*(point_regex + 1) != '*') {
				if (*point_regex != '.') {
					if (*point_original == *point_regex) {
						point_original++;
						point_regex++;
					}
					else {
						break;  //compare failed
					}
				}
				else if (*point_regex == '.') {
					point_original++;
					point_regex++;
				}
			}
			if (*(point_regex + 1) == '*') {
				if (*point_regex != '.'&&*(point_regex + 2) != '.') {
					if (*point_original == *(point_regex + 2)) {
						point_regex += 2;
					}
					else if (*point_original == *point_regex) {
						point_original++;
						if (*point_original == '\0')
							point_regex += 2;
					}
					else
						break;
				}
				if (*point_regex != '.'&&*(point_regex + 2) == '.')
				{
					if (*point_original == *point_regex) {
						point_original++;
						if (*point_original == '\0')
							point_regex += 2;
					}
					else {
						point_regex += 2;
					}
				}
				if (*point_regex == '.'&& *(point_regex + 2) != '.') {
					if (*point_original == *(point_regex + 2)) {
						point_regex += 2;
					}
					else {
						point_original++;
						if (*point_original == '\0')
							point_regex += 2;
					}
				}
			}
		}
		else
			break;
	}

	if (*point_original == '\0'&&*point_regex == '\0') {
		free(regex_str);
		return true;
	}
	else {
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

