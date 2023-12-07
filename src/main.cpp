#include "main_client.h"
#include "main_server.h"

char* defaults[] = {"File", "server", "3" , "2"};

int main(int argc, char* argv[] = defaults)
{
    if (argc == 1) {
        argv = defaults;
    }

    std::string call = argv[1];
    if (call == "server") {
        batchpir_main_server(argc, argv);
    }
    else if (call == "client") {
        batchpir_main_client(argc, argv);
    }

    else {
        std::cout << "No valid arguments given." << std::endl;
    }    
    return 0;
}