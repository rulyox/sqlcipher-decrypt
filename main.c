#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sqlite3.h>

int does_file_exist(char* file) {

    if(access(file, F_OK) == 0) return 1;
    else return 0;

}

int sqlite_callback(void *v, int argc, char **argv, char **az_col_name) {

    for(int i = 0; i < argc; i++) {

        printf("  - %s = %s\n", az_col_name[i], argv[i] ? argv[i] : "NULL");

    }

    return 0;

}

int main(int argc, char** argv) {

    if(argc != 3) {
        printf("2 arguments are needed\n");
        printf("sqlcipher-decrypt [SQLite file] [SQLCipher password]\n");
        return 0;
    }

    char* input_file = argv[1];
    char* password = argv[2];
    char* output_file = malloc(sizeof(char) * (strlen(input_file) + 15));
    strcpy(output_file, input_file);
    strcat(output_file, "-decrypted.db");

    printf("SQLite version %s\n", sqlite3_libversion());

    if(does_file_exist(input_file)) {

        if(!does_file_exist(output_file)) {

            sqlite3 *db;
            char sql[100];

            // Open DB
            printf("  Open DB...\n");
            sqlite3_open(input_file, &db);

            // Use password
            printf("  Use password...\n");
            sprintf(sql, "PRAGMA key = '%s';", password);
            sqlite3_exec(db, sql, sqlite_callback, NULL, NULL);

            // Create new plaintext DB
            printf("  Create new plaintext DB...\n");
            sprintf(sql, "ATTACH DATABASE '%s' AS plaintext KEY '';", output_file);
            sqlite3_exec(db, sql, sqlite_callback, NULL, NULL);

            // Write data to plaintext DB
            printf("  Write data to plaintext DB...\n");
            sqlite3_exec(db, "SELECT sqlcipher_export('plaintext');", sqlite_callback, NULL, NULL);

            // Detach from plaintext DB
            printf("  Detach from plaintext DB...\n");
            sqlite3_exec(db, "DETACH DATABASE plaintext;", sqlite_callback, NULL, NULL);

            printf("Decrypted SQLite file saved to '%s'\n", output_file);

            sqlite3_close(db);

        } else {

            printf("'%s' already exists\n", output_file);

        }

    } else {

        printf("File does not exist\n");

    }
    
    free(output_file);

    return 0;

}
