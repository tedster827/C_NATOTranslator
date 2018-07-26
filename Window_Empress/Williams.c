/*
  Teddy Williams
  November 7, 2016
  CS 351 NATO Translator.
  Due: November 28, 2016
*/
// Including C's Standard Librarys
#include <stdio.h>
#include <ctype.h>
// Including C's Standard Input Output Library
// #include <cstdio>
// Includeing C String Library
#include <string.h>
// Including error code Library
#include <errno.h>


// Declairing a typedef for characters' pointers for easlier readability
typedef char* charPtr;
typedef FILE* filePtr;

/*
  isNato  (is this NATO Text?)
  Purpose: To recieve a pointer pointing the memory address of the
  file's input and then see if the file starts with NATO text.
  Input: File Pointer holding the address of the File (words.txt).
  Output: 1 for NATO; 0 for English
*/
int isNATO (filePtr inputFile) {
  // Creating a database for comparison of NATO words
  const char* NATO[26] = {"Alfa", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf", "Hotel", "India", "Juliett", "Kilo", "Lima", "Mike", "November", "Oscar", "Papa", "Quebec", "Romeo", "Sierra", "Tango", "Uniform", "Victor", "Whiskey", "X-ray", "Yankee", "Zulu"};
  // Exracting first character of the file.
  char c = fgetc(inputFile);
  int i;
  // Finding the NATO word that corresponds with the first character of the file.
  for (i = 0; i < 26; i++) {
    if (c == NATO[i][0]) {
      // Finding the length of the NATO string
      unsigned long natoLength = strlen(NATO[i]);
      // Setting the size of the check based on the length of the NATO string
      char inputCheck[natoLength];
      // Setting the file point back to the start of the file.
      rewind(inputFile);
      // Taking the same amount of characters as the size of the NATO string.
      int j;
      for (j = 0; j < natoLength; j++) {
        c = fgetc(inputFile);
        inputCheck[j] = c;
      }
      // loop counter
      int k;
      // Valid flag used to keep track of the comparison
      int valid = 1;
      // looping to compare each character
      for (k = 0; k < natoLength; k++) {
        // Changing flag value if a comparison is invaild
        if(inputCheck[k] != NATO[i][k]) {
          valid = 0;
        }
      }
      // If the valid flag was triggered return true
      if (valid) {
        return 1;
      }
    }
  }
  // Returning 0 (False first word was not NATO)
  return 0;
}
void NATOtoEng(filePtr inputFile) {
  printf("%s\n", "Translating into English");
  // Obtaining original file size for reading
  // Traversing through till the end of the file
  fseek(inputFile, 0, SEEK_END);
  // Obtaing offset number and setting size to it
  int size = ftell(inputFile);
  // Setting pointer back to the start of the file
  rewind(inputFile);
  // Creating a file pointer for appending
  filePtr appendPtr = fopen("words.txt", "a+");
  // Appending the marking before writing the translation
  fputs("\nEnglish Translation --->\n", appendPtr);
  // Placeholder variable for file input
  char c;
  // loop counter
  int i;
  // Going through the whole file
  for (i = 0; i < size; i++) {
    c = fgetc(inputFile);
    // Only write into the file when a uppercase letter is found or a space
    if ((c >= 'A' && c <= 'Z')|| c == ' ') {
      fputc(c, appendPtr);
    }
  }
  // Displaying result to console.
  // Setting file pointer to the start of the file
  rewind(appendPtr);
  // Traversing through whole file
  fseek(appendPtr, 0, SEEK_END);
  // Finding the offset and setting it to size
  size = ftell(appendPtr);
  // Setting pointer back to the beginning of the file to display
  rewind(appendPtr);
  // Roaming through till reaching size limit
  for (i = 0; i != size; i++) {
    printf("%c", fgetc(appendPtr));
  }
  // End of file marker
  printf("%s\n", "\n\n<End of File> ");
  // Returning control to main
  return;
}
/*
  engToNATO (English to NATO)
  Purpose: To recieve a pointer pointing the memory address of the
  file's input in an array. Write the NATO translation into the
  same input file.
  Input: Character Pointer (Input Array Address)
  Output: None (Void Function)
*/
void engToNATO (filePtr inputFile) {
  printf("%s\n", "Translating into NATO");
  // Making NATO key for translation
  const char* NATO[26] = {"Alfa", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf", "Hotel", "India", "Juliett", "Kilo", "Lima", "Mike", "November", "Oscar", "Papa", "Quebec", "Romeo", "Sierra", "Tango", "Uniform", "Victor", "Whiskey", "X-ray", "Yankee", "Zulu"};
  // Obtaining original file size for reading
  // Traversing through till the end of the file
  fseek(inputFile, 0, SEEK_END);
  // Obtaing offset number and setting size to it
  int size = ftell(inputFile);
  // Setting pointer back to the start of the file
  rewind(inputFile);
  // Opening the file with the append flag so that this funciton can append and read but not overwrite
  filePtr appendPtr = fopen("words.txt", "a+");
  // Appending the marking before writing the translation
  fputs("\nNATO Translation --->\n", appendPtr);
  // Creating a char array (string) to store the input
  char fileInput[size];
  // Iterating through entire file
  // loop counter
  int i;
  for (i = 0; i != size; i++) {
    // Obtaining characters to uppercase for easier matching with NATO
    fileInput[i] = toupper(fgetc(inputFile));
    // Appending a space when there is one for better readability
    if (fileInput[i] == ' ') {
      fputc(' ', appendPtr);
    }
    // loop counter
    int j;
    // Testing character obtained against the NATO key
    for (j = 0; j < 26; j++) {
      // Once there is a match it will write to the file
      if (NATO[j][0] == fileInput[i]) {
        fputs(NATO[j], appendPtr);
      }
    }
  }
  // Displaying result to console.
  // Setting file pointer to the start of the file
  rewind(appendPtr);
  // Traversing through whole file
  fseek(appendPtr, 0, SEEK_END);
  // Finding the offset and setting it to size
  size = ftell(appendPtr);
  // Setting pointer back to the beginning of the file to display
  rewind(appendPtr);
  // Roaming through till reaching size limit
  for (i = 0; i != size; i++) {
    printf("%c", fgetc(appendPtr));
  }
  // End of file marker
  printf("%s\n", "\n\n<End of File> ");
  // Returning control to main
  return;
}
/*
  Main Driver Program
  Purpose: To recieve input from user and to call needed functions.
  Input: None
  Output: 0 (Exit Call)
*/
int main(int argc, char const *argv[]) {
  // Creating a file stream to write to the file
  filePtr iFile;
  // Opeing the file in write mode.
  printf("%s\n", "Trying to Open words.txt.");
  // Only run if the file words.txt is found
  iFile = fopen("words.txt", "r");
  if (iFile != NULL) {
    printf("%s\n", "words.txt Found!");
    // Checking to see if the file starts with NATO text or English
    if (isNATO(iFile) == 1) {
      printf("%s\n", "NATO text found!");
      // Calling NATO to English funciton because isNATO found NATO text.
      NATOtoEng(iFile);
    }
    else {
      printf("%s\n", "English text found!");
      // Calling English to NATO funciton because isNATO did not find NATO text.
      engToNATO(iFile);
    }
  }
  else {
    // Display error message when words.txt is not within the directory. strerror find the error message number and displays it
    printf("[Warning] Please save a copy of words.txt to this directory and try again, %s\n", strerror(errno));
  }
  // (Exit Program)
  return 0;
}
