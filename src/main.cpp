#include "main_client.h"
#include "main_server.h"

int main(int argc, char* argv[])
{
    cout << argv << std::endl;
    for (int i = 0; i < argc; i++) {
        cout << argv[i] << std::endl;
    }
    std::string call = argv[2];
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