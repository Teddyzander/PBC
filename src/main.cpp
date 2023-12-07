#include "main_client.h"
#include "main_server.h"

int main(int argc, char* argv[])
{
    batchpir_main_server(argc, argv);
    batchpir_main_client(argc, argv);
    return 0;
}