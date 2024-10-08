#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// declare the functions
string getKey(string);
bool validateKey(string);
string getPlaintext(void);
void encipher(string, string, char array[]);
void printCiphertext(char array[]);

int main(int argc, string argv[])
{
    /* get key (accept only single command-line argument) */
    if (argc != 2)
    {
        printf("Use a single command-line argument without any spacing\n");
        printf("Usage: ./substituion key\n");
        return 1;
    }
    string key = getKey(argv[1]);

    /* validate key */
    bool isValid = validateKey(key);
    // return 1 to signify error if it isn't a valid key
    if (isValid == false)
    {
        return 1;
    }

    /* get plaintext */
    string plaintext = getPlaintext();
    int plaintextLength = strlen(plaintext);

    /* encipher the plaintext */
    // one character longer than plaintext to accommodate the null terminator for strings.
    char ciphertextArr[plaintextLength + 1];
    // Null-terminate the ciphertext to avoid print garbage values
    ciphertextArr[plaintextLength] = '\0';
    encipher(plaintext, key, ciphertextArr);

    /* print ciphertext */
    printCiphertext(ciphertextArr);
}

/* define getKey function */
string getKey(string argvKey)
{
    string key = argvKey;
    return key;
}

/* define validateKey function */
bool validateKey(string key)
{
    // check key length
    if (strlen(key) != 26)
    {
        printf("\nKey must contain 26 characters.\n");
        return false;
    }

    for (int i = 0; i < 26; i++)
    {
        // check if key has non-alphabetic char
        if (!isalpha(key[i]))
        {
            printf("\nKey must contains only alpahbetical characters.\n");
            return false;
        }

        // check if key has repeated char
        for (int j = 25; j > i; j--)
        {
            if (key[i] == key[j])
            {
                printf("\nKey must not contain repeated character.\n");
                return false;
            }
        }
    }

    return true;
}

/* define getPlaintext function */
string getPlaintext()
{
    string plaintext = get_string("plaintext:  ");
    return plaintext;
}

/* define encipher function */
void encipher(string plaintext, string key, char ciphertextArr[])
{
    // for each plaintext letter
    for (int i = 0; i < strlen(plaintext); i++)
    {
        // if char is non-alphabetic leave as is
        if (!isalpha(plaintext[i]))
        {
            // push it to ciphertext array
            ciphertextArr[i] = plaintext[i];
        }
        else
        {
            // keep track of the letter case (capitalized or lowercase)
            bool isLowercase = false;
            if (islower(plaintext[i]))
            {
                isLowercase = true;
            }

            // determine which letter it maps to
            int alphabetOrder = 0;
            // get alphabetical order by subtracting 65 (ascii table)
            alphabetOrder = toupper(plaintext[i]) - 65;
            // push it to ciphertext array while preserving case
            ciphertextArr[i] = isLowercase ? tolower(key[alphabetOrder]) : toupper(key[alphabetOrder]);
        }
    }
}

/* define printCiphertext function */
void printCiphertext(char ciphertextArr[])
{
    printf("ciphertext: %s\n", ciphertextArr);
}