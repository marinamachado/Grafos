#include <stdio.h>
#include <stdlib.h>

#include "MaisQueMigos.h"


int main(int argc, const char * argv[]) {
    
    Graph *g;
    
    g = create_graph(MAX, 0, 0);
    load_database(g);
    
    printf("                                       _                      __      _                _     \n");
    printf("    _                                 (_)                    / _|    (_)              | |    \n");
    printf("  _| |_    __ _ _   _  ___   _ __ ___  _  __ _  ___  ___    | |_ _ __ _  ___ _ __   __| |___ \n");
    printf(" |_   _|  / _` | | | |/ _ | | '_ ` _  | |/ _` |/ _ |/ __|   |  _| '__| |/ _ | '_   / _` / __|\n");
    printf("   |_|   | (_| | |_| |  __/ | | | | | | | (_| | (_) )__ )_  | | | |  | |  __/ | | | (_| (__ )\n");
    printf("           __, | __,_| ___| |_| |_| |_|_| __, |(___/|___( ) |_| |_|  |_| ___|_| |_| __,_|___/\n");
    printf("             | |                          __/ |         |/                                   \n");
    printf("             |_|                         |___/                                               \n\n");
    open_social_midia(g);
    
    destroy_graph(g);

    return 0;
}