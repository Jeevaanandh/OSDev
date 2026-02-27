//
// Created by Jeevaanandh Ilayaraja on 27/02/26.
//


int memcmp(void *s1, void *s2, int size) {
    char *c1= (char *)s1;
    char *c2= (char *)s2;

    for (int i=0; i<size; i++) {
        if (c1[i] != c2[i]) {
            return c1[i]-c2[i];
        }
    }

    return 0;
}