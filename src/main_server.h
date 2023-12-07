#include <iostream>
#include <map>
#include <cstdlib>
#include <cassert>
#include <chrono>
#include <functional>
#include "pirparams.h"
#include "client.h"
#include "batchpirparams.h"
#include "batchpirserver.h"
#include "batchpirclient.h"
#include "database_constants.h"
#include "utils.h"

using namespace std;
using namespace chrono;

int batchpir_main_server(int argc, const char* argv[])
{
    unsigned int tree_height = stoi(argv[2]);
    unsigned int children = stoi(argv[3]);
    unsigned int num_batches = stoi(argv[4]);
    const int client_id = 0;
    //  batch size, number of entries, size of entry
    std::vector<std::array<size_t, 3>> input_choices;
    size_t num_nodes = 0;
    for (int i = 1; i <= tree_height; i++) {
        num_nodes += pow(DatabaseConstants::children, i);
    }
    input_choices.push_back({ tree_height, num_nodes, 32 });

    std::vector<std::chrono::milliseconds> init_times;
    std::vector<std::chrono::milliseconds> database_times;
    std::vector<std::chrono::milliseconds> query_gen_times;
    std::vector<std::chrono::milliseconds> resp_gen_times;
    std::vector<size_t> communication_list;

    std::cout << "***************************************************" << std::endl;
    std::cout << "             Starting Server " << std::endl;
    std::cout << "***************************************************" << std::endl;

    const auto& choice = input_choices[0];

    string selection = std::to_string(choice[0]) + "," + std::to_string(choice[1]) + "," + std::to_string(choice[2]);

    cout << "Generating Tree..." << endl;
    auto start = chrono::high_resolution_clock::now();
    utils::create_tree_file(tree_height, DatabaseConstants::children);
    auto end = chrono::high_resolution_clock::now();
    auto duration_init = chrono::duration_cast<chrono::milliseconds>(end - start);
    init_times.push_back(duration_init);
    cout << "Number of Leaves: " << std::to_string(int(pow(DatabaseConstants::children, tree_height))) <<
        " (height: " << std::to_string(tree_height) << ", children: " <<
        std::to_string(DatabaseConstants::children) << ") generated." << endl;

    auto encryption_params = utils::create_encryption_parameters(selection);
    BatchPirParams params(choice[0], choice[1], choice[2], tree_height, encryption_params);

    BatchPIRServer batch_server(tree_height, params);
    database_times.push_back(batch_server.timer);

    params.save_params();
    
    auto hash_map = batch_server.get_hash_map();
    size_t max_bucket_size = params.get_max_bucket_size();
    utils::save_bucket_size(max_bucket_size, tree_height);
    utils::save_map(hash_map, tree_height);
    unsigned long cap = sizeof(hash_map);
    cout << "Calculating Map Size..." << endl;
    for (std::unordered_map<std::string, uint64_t>::const_iterator it = hash_map.begin(); it != hash_map.end(); ++it) {
        cap += it->first.capacity();
        cap += 32;
    }

    cout << "***********************" << endl;
    cout << "     Timings Report    " << endl;
    cout << "***********************" << endl;
    for (size_t i = 0; i < input_choices.size(); ++i)
    {
        cout << "Input Parameters: ";
        cout << "Batch Size: " << input_choices[i][0] << ", ";
        cout << "Number of Entries: " << input_choices[i][1] << ", ";
        cout << "Entry Size: " << input_choices[i][2] << endl;

        cout << "Tree Initialization time: " << init_times[i].count() << " milliseconds" << endl;
        cout << "PBC database Hashing time: " << database_times[i].count() << " milliseconds" << endl;
        cout << "Database Size: " << batch_server.database_size << " bytes" << endl;
        cout << "Map Size: " << cap << " bytes" << endl;
        float ratio = (float)cap / (float)batch_server.database_size;
        cout << "Approximate Ratio: " << ratio << endl;
    }

    return 0;
}

/*
int main(int argc, char* argv[])
{
    //vectorized_pir_main(argc, argv);
    batchpir_main_server(argc, argv);
    return 0;
}*/