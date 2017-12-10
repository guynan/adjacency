/* This compilation unit deals with general file i/o */


#include "fileutils.h"


/* The path to the file and the *proposed* size of the line are passed in
 * as arguments. It then processes the file line by line and reads the 
 * integers as type `uint32_t` into a two dimensional array. It is
 * functionally a CSV parser but with many more bugs :) */
uint32_t** parseFile(const char* path, size_t ls)
{
        FILE* file = NULL;
        size_t vert = VERTICAL_LINES;

        uint32_t** adjList = calloc(vert, sizeof(uint32_t*));

        for(uint32_t i = 0; i < vert; i++){
                adjList[i] = NULL;
        }

        char* line = calloc(ls, sizeof(char));

        file = fopen(path, "r");

        if(!file){
                printf("No such file\n");
                exit(2);
        }

        /* This is all pretty sloppy, especially with how much memory
         * gets allocated here */
        for(uint32_t i = 0; fgets(line, ls, file); i++){
               
                /* Note that ls is decisively overkill */
                adjList[i] = readVertices(line, ls);

                if(i == vert - 1){
                        vert *= 2;
                        uint32_t** tmp;
                        tmp = realloc(adjList, vert * sizeof(uint32_t*));
                        if(tmp){
                                adjList = tmp;
                        } else {
                                printf("Cannot reallocate memory\n");
                                free(tmp);
                                exit(2);
                        }

                }

        }

        free(line); 
//        fclose(file);
//        file = NULL;

        return adjList;

}


uint32_t* readVertices(char* line, uint32_t ls)
{

        uint32_t* vert = calloc(ls, sizeof(uint32_t));
        char* s;

        for(uint32_t i = 0; (s = strtok(line, ",")); i++){
                vert[i] = strtoint(s);

                /* This hack is explained in `initVertex`. This is so that 
                 * we can iterate over a zero value and not stop our program.
                 * Yes, its a bit edgy casting a negative number into uint */
                if(vert[i] == 0){
                        vert[i] = -1;
                }

                line = NULL;
                 
        }

        return vert;

}


uint32_t strtoint(char* s)
{
        uint32_t dec = 0;

        for( ; *s && *s != '\n'; dec = dec * BASE + (*s++ - '0'))
                ;

        return dec;


}


void writeAdjacencyList(Graph g, const char* path)
{
        Vertex* tmp = g->vertices;

        FILE *file = fopen(path, "w");

        if (!file){
                printf("Error opening file!\n");
                exit(1);
        }

        
        for(uint32_t i = 0; i < g->order; i++){

                if(!tmp[i]) continue;

                writeAdjacent(tmp[i], file);

        }

        fclose(file);
        

}


void writeAdjacent(Vertex v, FILE* file)
{

        if(!v) return;

        Vertex* tmp = v->adjacent;

        uint32_t f = 0;
        for(uint32_t i = 0; i < v->count; i++){

                if(!tmp[i]) continue;

                if(!f){
                        /* Hack to remove trailing commas */
                        fprintf(file, "%"PRIu32, (tmp[i])->id);
                        f++;
                        continue;
                }

                fprintf(file, ",%"PRIu32, (tmp[i])->id);

        }

        fprintf(file, "\n");

        return;

}


void writeDFS(Vertex** tmp, const char* path, uint32_t n)
{
        FILE *file = fopen(path, "w");

        if (!file){
                printf("Error writing file!\n");
                exit(1);
        }

        Vertex** dfs = tmp;

        if(!dfs) return;

        uint32_t c = 0;

        for(uint32_t i = 0; i < n; i++){

                if(!dfs[i]) continue;

                Vertex* k = dfs[i];

                for(uint32_t j  = 0; j < n; j++){
                        Vertex v = k[j];
                        if(!v) continue;
                        fprintf(file, "%"PRIu32",%"PRIu32"\n", c++, v->id);

                }

                fprintf(file, "\n");
                 
        }

        fclose(file);

        return;

}

