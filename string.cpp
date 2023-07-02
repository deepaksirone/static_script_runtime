#include <stdlib.h>
#include <string.h>

#include "library.h"

// Not to put too much pressure on the heap
static char string_buffer[4096 * 5];

C_LIBRARY_EXPORT char *__str_concat(char *str1, char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int len = len1 + len2 + 1;

    char *res = (char *)malloc(len * sizeof(char));
    int j = 0; int k = 0;
    for (int i = 0; i < len - 1; i++) {
        if (i < len1)
            res[i] = str1[i];
        else 
            res[i] = str2[i - len1];
    }

    res[len] = 0;

    return res;
}

C_LIBRARY_EXPORT int __str_cmp(char *str1, char *str2) {
    
    while(*str1 && (*str1 == *str2))
    {
        str1++;
        str2++;
    }

    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

C_LIBRARY_EXPORT char ** _Z13String__matchPKc(char *str, char *regex) {
    char **res = (char **)malloc(2 * sizeof(char **));
    res[0] = str;
    res[1] = NULL;
    return res;
}

C_LIBRARY_EXPORT char *_Z15String__replaceRegExpPKc(char *src_str, char *pattern, char *targ_pattern) {
    return src_str;
}

C_LIBRARY_EXPORT char *_Z16Number__toStringv(double number) {
    int n = (int)number;
    int neg_flag = 0;
    char digits[10];

    if (n == 0) {
        char *res = (char *)malloc(2);
        res[0] = '0';
        res[1] = 0;
        return res;
    }

    int i = 0;
    if (n < 0) {
        n = -n;
        neg_flag = 1;
    }

    while (n != 0) {
        digits[i] = n % 10;
        n = n / 10;
        i++;
    }

    char *res;
    if (neg_flag) {
        res = (char *)malloc(i + 2);
        res[0] = '-';
        for(int j = 0; j < i; j++) {
            res[j + 1] = digits[j];
        }
        res[i + 1] = 0;
    } else {
        res = (char *)malloc(i + 1);
        for(int j = 0; j < i; j++) {
            res[j] = digits[j];
        }

        res[i] = 0;
    }
 
    return res;
}

C_LIBRARY_EXPORT double __str_len(char *str) {
    return strlen(str);
}

C_LIBRARY_EXPORT double __str_array_len(char **array) {
	double i = 0;
	if (array == NULL) return 0;

	for(int j = 0; array[j] != NULL; j++) {
		i++;
	}

	return i;
}
  

char* concat_array(char **array, int len) {
    int tot_len = 0;
    for (int i = 0; i < len; i++) {
        tot_len += strlen(array[i]);
    }

    char *res = (char *)malloc(tot_len);
    int j = 0;
    for(int i = 0; i < len; i++) {
        for(int k = 0; array[i][k] != 0; k++) {
            res[j] = array[i][k];
            j++;
        }
    }

    res[tot_len] = 0;

    return res;
}

C_LIBRARY_EXPORT char *_Z16ArrayT__toStringv(char **array) {
    int len = 0;
    for (; array[len] != NULL; len++);
    return concat_array(array, len);
}

C_LIBRARY_EXPORT  char *_Z14String__concatPKc(char *str1, char *str2) {
    return __str_concat(str1, str2);
}

C_LIBRARY_EXPORT double _Z15String__indexOfPKc(char *needle, char *haystack) {
    char *pos = strstr(needle, haystack);
    if (pos == NULL) 
        return -1;

    return (double)(pos - needle) ;
}
