#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define SUCESS 0
#define FAILURE 1
#define true 1
#define false 0

int min(int a, int b) {
    return (a < b)? a : b;
}

int minPal(char* pal){
    int n = strlen(pal);
    int ispal[n][n];
    int partitions[n][n];
    int i, j, k, subLenght;
    for (i=0; i<n; i++){
        ispal[i][i] = true;
        partitions[i][i] = 0;
    }
    for (subLenght=2; subLenght<=n; subLenght++){
        // For substring of length L, set different possible starting indexes
        for (i=0; i<n-subLenght+1; i++){
            j = i+subLenght-1; // Set ending index

            // If L is 2, then we just need to compare two characters. Else
            // need to check two corner characters and value of P[i+1][j-1]
            if (subLenght == 2)
                ispal[i][j] = (pal[i] == pal[j]);
            else
                ispal[i][j] = (pal[i] == pal[j]) && ispal[i+1][j-1];

            // IF pal[i..j] is palindrome, then C[i][j] is 0
            if (ispal[i][j] == true)
                partitions[i][j] = 0;
            else{
                // Make a cut at every possible location starting from i to j,
                // and get the minimum cost cut.
                partitions[i][j] = INT_MAX;
                for (k=i; k<=j-1; k++)
                    partitions[i][j] = min (partitions[i][j], partitions[i][k] + partitions[k+1][j]+1);
            }
        }
    }

    // Return the min cut value for complete paling. i.e., pal[0..n-1]
    return partitions[0][n-1];
}

int isPalindrome(char* pal,int start,int end){
        int i;
        for(i=start;i<end;i++){
            if(pal[i] != pal[end]){
                return FAILURE;
            }
            end--;
        }
        return SUCESS;
}

int main(){
    char* palindrome;
    scanf("%ms",&palindrome);
    printf("%s", palindrome);
    int npartition = minPal(palindrome);
    printf("%d\n", npartition);
    free(palindrome);
return 0;
}
