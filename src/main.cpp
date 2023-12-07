#include "main_client.h"
#include "main_server.h"

const char* defaults[] = {"File", "client", "3" , "2", "100"};

int main(int argc, const char* argv[])
{
    //For testing
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