#include "main_client.h"
#include "main_server.h"

int main(int argc, char* argv[])
{
    cout << argv << std::endl;
    if (argv[1] == "server") {
        batchpir_main_server(argc, argv);
    }
    else if (argv[1] == "client") {
        batchpir_main_client(argc, argv);
    }

    else {
        std::cout << "No valid arguments given." << std::endl;
        batchpir_main_server(argc, argv);
        batchpir_main_client(argc, argv);
    }    
    return 0;
}