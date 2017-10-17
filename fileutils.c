

/* The path to the file and the *proposed* size of the line are passed in
 * as arguments. It then processes the file line by line and reads the 
 * integers as type `uint32_t` into a two dimensional array */
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

        for(uint32_t i = 1; fgets(line, ls, file); i++){
                        
                        
                        readVertices(line, adjList[i]);

                        if(i == vert - 1){
                                // reaaaalloccc and update veeert
                        }
        }

        free(line); 

        return adjList;

}


void readVertices(char* line, 
