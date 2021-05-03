/***********************************************************
 *  this is where all the funtions for all the procedures 
 *  a user can do with the program 
***********************************************************/
#include "process.h"

/***********************************************************
 *  option one of the procedures
 *  find and processs the larges file 
************************************************************/
void largest(){
    char *name = makeFolderName();
    char *largest = findLargest();
    printf("\n Now processing the smallest file, named %s\n", largest);
    processCSV(largest, name);
    printf("Created directory with name %s\n", name);
    free(largest);
    free(name);
}

/***********************************************************
 *  helper function for option one of the procedures
 *  find the larges file 
 *  this function is inspired from sample code in module 3 
************************************************************/
char *findLargest(){
    char *largest = (char *)malloc(4);
    char filetype [] = ".csv";
    char *temp;
    DIR *wd = opendir("."); //opens the working directory 
    struct dirent *aDir;
    struct stat dirStat;
    long int curr = 0;
    while(aDir = readdir(wd)){ //looping though dir entries 
        if(strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0){
            temp = strstr(aDir->d_name, filetype); //check if type is .csv
            if(temp != NULL){
                stat(aDir->d_name, &dirStat);
                if(dirStat.st_size > curr){ //check for biggest 
                    curr =  dirStat.st_size;
                    largest = (char *)realloc(largest, sizeof(aDir->d_name));
                    strcpy(largest, aDir->d_name);
                }
            }
        }

    }
    closedir(wd);
    return largest;
}

/***********************************************************
 *  option two of the procedures
 *  find and processs the smallest file 
************************************************************/
void smallest(){
    char *name = makeFolderName();
    char *smallest = findSmallest();
    printf("\n Now processing the smallest file, named %s\n", smallest);
    processCSV(smallest, name);
    printf("Created directory with name %s\n", name);
    free(smallest);
    free(name);
}

/***********************************************************
 *  helper function for option two of the procedures
 *  find the smallest file 
 *  this function is inspired from sample code in module 3 
************************************************************/
char *findSmallest(){
    char *smallest = (char *)malloc(4);
    char filetype [] = ".csv";
    char *temp;
    DIR* wd = opendir(".");
    struct dirent *aDir;
    struct stat dirStat;
    long int curr = 999999;

    while((aDir = readdir(wd))){ //looping through entries 
        if(strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0){ //checking prefix
            temp = strstr(aDir->d_name, filetype);  //check for .csv
            if (temp != NULL){
                stat(aDir->d_name, &dirStat);
                if(dirStat.st_size < curr){ //want smallest one
                    curr = dirStat.st_size;
                    smallest = (char *)realloc(smallest, sizeof(aDir->d_name));
                    strcpy(smallest, aDir->d_name);
                }
            }
        }
    }
    closedir(wd);
    return smallest;
}

/***********************************************************
 *  option three of the procedures
 *  finds the users choice
************************************************************/
int userChoice(){
    char *name = makeFolderName();
    char *filename = NULL;
    size_t len = 0;
    ssize_t read;
    int exists = 0;
    printf("Enter the complete filename e.g. \"movies_sample_1.csv\": ");
    scanf("%s", filename);
    while ((read = getline(&filename, &len, stdin)) != -1) {
        if (read > 0) {
            exists = findFileName(filename);
            printf("%d", exists);
        }
        break;
    }
    printf("\n");
    if (exists == 1) {
        char *filepath = (char *)calloc(1, strlen(filename) + 1);
        strncpy(filepath, filename, strlen(filename) - 1);
        strcat(filepath, "\0");
        printf("Now processing the file named %s\n", filepath);
        processCSV(filepath, name);
        printf("Created directory with name %s\n", name);
        free(filepath);
    } 
    else  {
        printf("ERROR: File named \"%s\" was not found.\n", filename);
        exists = 0;
    }
    free(filename);
    free(name);
    return exists;
}

/***********************************************************
 *   helper function option three of the procedures
 *  trys to find the users choice to see if exist 
************************************************************/
int findFileName(char *file){
    int a = 0; // int as bool to return
    char *temp1 = (char *)calloc(1, strlen(file) + 1);
    strncpy(temp1, file, strlen(file) - 1);
    strcat(temp1, "\0");
    DIR* wd = opendir("."); // opens working directory
    struct dirent *aDir;
    while((aDir = readdir(wd))){ // loop over directory
        if(strncmp(temp1, aDir->d_name, strlen(temp1)) == 0) {
            a = 1;
        }
    }
    char filetype [] = ".csv";
    char *temp;
    if ((temp = strstr(temp1, filetype)) == NULL) {
        a = 0;
    }
    closedir(wd);
    free(temp1);
    return a;
}

/***********************************************************
 *   helper function that adds id and rand num like 
 *   specified in assignment 
************************************************************/
char *makeFolderName(){
    char onid [] = "doylalex.movies.";
    int r = rand() % 9999;
    char *numstr = (char *)(calloc(1, 5));
    sprintf(numstr, "%d", r);
    strcat(numstr, "\0");
    char *str = (char *)calloc(1, sizeof(onid) + sizeof(numstr) + 1);
    strcpy(str, onid);
    strcat(str, numstr);
    strcat(str, "\0");
    free(numstr);
    return str;
}

void processCSV(char* file , char* direct){
    char *dPath = (char *)calloc(1, strlen(direct) + 12); // turn the file into a usable path
    strcpy(dPath, "./");
    strcat(dPath, direct);
    int newdir = mkdir(direct, 0750); //create new directory
    char *year = (char *)calloc(1, strlen(direct) + strlen("/1111.txt\0") + 1);
    FILE *data = fopen(file, "r");
    char *temp;
    size_t len = 0;
    ssize_t nread;
    nread = getline(&temp, &len, data);
    while ((nread = getline(&temp, &len, data)) != -1){ //loop through
        char *duplicate = (char *)calloc(1, strlen(temp) + 1); //year line is associated with 
        strcpy(duplicate, temp);
        char *tempstr;
        char *token = strtok_r(duplicate, ",", &tempstr);
        token = strtok_r(NULL, ",", &tempstr);
        strcpy(year, direct); //make year useable path 
        strcat(year, "/");
        strcat(year, token);
        strcat(year, ".txt\0");
        FILE *f = fopen(year, "a+"); //add text to file
        token = strtok_r(temp, ",", &tempstr);
        duplicate = (char *)realloc(duplicate, strlen(token) + strlen("\n\0") + 1); //append movie title string to doc
        strcpy(duplicate, token);
        strcat(duplicate, "\n\0");
        fputs(duplicate, f);
        fclose(f); //cleaing up memory below 
        int permissions = chmod(year, 0640);
        free(duplicate);
    }
    fclose(data);
    free(temp);
    free(year);
    free(dPath);
}