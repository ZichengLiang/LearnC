#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

struct Address{
    // elements: id, set, name, email
    // what is "set"??
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};

struct Database{
    // a database is an array of addresses
    // I can use the previous structure without a instance
    struct Address rows[MAX_ROWS];
};

struct Connection{
    // FILE is a struct defined in C standard libray
    // C and Java both use the concept "stream" for FILE processing
    FILE *file;
    // a Connection struct includes a pointer to FILE and a pointer to Database
    // This implementation always use a pointer to connection
    struct Database *db;
};

void die (const char *message){
    // errno is an external varibale set when a function returns an error
    if(errno){ // in C, as `if(expression)` when expression is not 0, true 
               // C is not as strongly typed as Java
        perror(message);
        // printError what is the difference between perror and printf ??
    } else {
        printf("ERROR: %s\n", message);
        // if -> runtime error
        // else -> functional error (??)
    }

    exit(1); //(??)
}

void Address_print(struct Address *addr){
    // parameter: a pointer typed as Address
    // ------------------
    // addr -> address[0]
    //         address[1]
    //         ...
    // ------------------
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
    // print relevant information of the given address
}

void Database_load(struct Connection *conn){

/* fread(void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream);
     fread() reads nitems objects, each size bytes long, from the stream pointed by stream, storing them at the location given by ptr
    fread() returns the number of objects read.
*/ 
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    // here, fread reads 1 database, each sizeof(struct Database) long, from the stream pointed by conn->file, storing them at the location given by conn->db, it should return 1
    if (rc != 1){
        // on what occasion rc != 1?
        die("Failed to load database.");
    }
}

struct Connection *Database_open(const char *filename, char mode){
    // what does it return? a pointer to Connection?
    // const is the keyword to define a constant value that cannot be changed at runtime
    struct Connection *conn = malloc(sizeof(struct Connection));
    // the `malloc(size_t size)` function allocates size bytes of of memory
    // and returns a pointer to the allocated memory
    if (!conn){
        // if conn == 0
        die("Memory error");
    }

    conn->db = malloc(sizeof(struct Database));
    // conn->db is also a pointer typed Database
    if (!conn->db){
        die("Memory error");
    }
    
    /*
     * fopen(const char * restrict path, const char * restrict mode);
     * The fopen() function opens the file whose name is the string pointed to
     * by path and associates a stream with it
     * The argument mode points to a string beginning with of the following letters: "r": open for reading; "w" open for writing. An optional "+" opens the file for both reading and writing
     * does "write only" mode exist? What is the point using "w" and "r+" for initialisation and later usages respectively?
     */
    if(mode == 'c'){
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if(conn->file){
            Database_load(conn);
        }
    }

    if(!conn->file){
        die("Failed to open the file");
    }

    return conn;
}

void Database_close(struct Connection *conn){
    if(conn){
        if (conn->file)
            fclose(conn->file);
        if (conn->db)
            free(conn->db);
        free(conn);
        // why `free(conn)` cannot free conn->db altogether?
    }
}

void Database_write(struct Connection *conn){
    rewind(conn->file);
    // the rewind(File *stream) function sets the file position indicator for the stream pointed to by stream to the beginning of the file, it does not return a value

    int rc = fwrite(conn-> db, sizeof(struct Database), 1, conn->file);
    if (rc != 1)
        die("Failed to write database.");

    rc = fflush(conn->file);
    // fflush(FILE *stream) synchronizes the state of the given stream in light of buffered I/O. Upon successful completion 0 is returned. Otherwise, EOF is returned and the global variable errno is set to indicate the error
    if (rc == -1)
        die("Cannot flush database.");
}

void Database_create(struct Connection *conn){
    int i = 0;

    for (i = 0; i < MAX_ROWS; i++){
        // make a prototype to initialize it
        struct Address addr = {.id = i, .set = 0};
        // then just assign it
        conn->db->rows[i] = addr;
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email){
    struct Address *addr = &conn->db->rows[id];
    if(addr->set)
        die("Already set, delete it first");

    addr->set = 1;
    //WARNING: BUG, read the "How to break it" and fix this
    char *res = strncpy(addr->name, name, MAX_DATA);
    // demonstrate the strncpy bug
    if (!res)
        die("Name copy failed");

    res = strncpy(addr->email, email, MAX_DATA);
    if(!res)
        die("Email copy failed");
}

void Database_get(struct Connection *conn, int id){
    struct Address *addr = &conn->db->rows[id];

    if(addr->set){
        Address_print(addr);
    } else {
        die("ID is not set");
    }
}

void Database_delete(struct Connection *conn, int id){
    struct Address addr = {.id = id, .set = 0};
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn){
    int i = 0;
    struct Database *db = conn->db;

    for(i = 0; i < MAX_ROWS; i++){
        struct Address *cur = &db->rows[i];

        if(cur->set){
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[]){
    if (argc < 3)
        die("USAGE: ex17 <dbfile><action> [action params]");
    char *filename = argv[1];
    // *filename = db.dat
    char action = argv[2][0];
    // here we use a char instead of a string, so we must specify the 2-d array subscript
    // action = c(reate)/g(et)/s(et)/d(elete)/l(ist)
    struct Connection *conn = Database_open(filename, action);
    int id = 0;

    if (argc > 3) id = atoi(argv[3]);
    // atoi: convert ASCII string to integer
    if (id >= MAX_ROWS) die("There's not that many records.");

    switch(action){
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if(argc != 4)
                die("Need an id to get");

            Database_get(conn, id);
            break;

        case 's':
            if (argc != 6)
                die("Need id, name, email to set");

            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if(argc != 4)
                die("Need id to delete");

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;

        default:
            die("Invalid action: c = create, g = get, s = set, d = delete, l = list");
    }

    Database_close(conn);

    return 0;
}
