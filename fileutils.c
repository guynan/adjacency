/* This compilation unit deals with general file i/o */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include "vertex.h"

#define BASE            10
#define VERTICAL_LINES  32


void writeAdjacencyList(Graph g, const char* path, uint32_t n);
uint32_t** parseFile(const char* path, size_t ls);
uint32_t* readVertices(char* line, uint32_t ls);
void writeAdjacent(Vertex v, FILE* file);
int main(int argc, char** argv);
uint32_t strtoint(char* s);


/* The path to the file and the *proposed* size of the line are passed in
 * as arguments. It then processes the file line by line and reads the 
 * integers as type `uint32_t` into a two dimensional array. It is
 * functionally a CSV parser but with many more bugs :) */
uint32_t** parseFile(const char* path, size_t ls)
{
        FILE* file = NULL;

        size_t vert = VERTICAL_LINES;

        uint32_t** adjList = malloc(vert * sizeof(uint32_t*));
        char* line = malloc(ls * sizeof(char));

        file = fopen(path, "r");

        if(!file){
                printf("No such file\n");
                exit(2);
        }

        /* This is all pretty sloppy, especially with how much memory
         * gets allocated here */
        for(uint32_t i = 1; fgets(line, ls, file); i++){
               
                /* Note that ls is decisively overkill */
                adjList[i-1] = readVertices(line, ls);

                if(i == vert - 1){
                        // reaaaalloccc and update veeert
                }
        }

        free(line); 

        return adjList;

}


uint32_t* readVertices(char* line, uint32_t ls)
{

        uint32_t* vert = malloc(ls * sizeof(uint32_t));
        char* s;

        for(uint32_t i = 0; (s = strtok(line, ",")); i++){

                /* Certainly one way to fo it looool */
                if(!*s || *s == '\n') break;

                vert[i] = strtoint(s);
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


void writeAdjacencyList(Graph g, const char* path, uint32_t n)
{


        Graph tmp = g;
        FILE *file = fopen(path, "w");

        if (!file){
                printf("Error opening file!\n");
                exit(1);
        }

        
        for(uint32_t i = 1; i <= n; i++){

                if(!tmp[i]) continue;

                writeAdjacent(tmp[i], file);

        }

        fclose(file);
        

}


void writeAdjacent(Vertex v, FILE* file)
{

        if(!v) return;

        Vertex* tmp = v->adjacent;

        for(uint32_t i = 0; i < v->count; i++){

                if(!tmp[i]) continue;

                fprintf(file, "%"PRIu32",", (tmp[i])->id);

        }
        (void) getc(file);

        fprintf(file, "\n");

        return;

}

