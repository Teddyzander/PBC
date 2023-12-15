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

int batchpir_main_client(int argc, const char* argv[])
{
    unsigned int tree_height = stoi(argv[2]);
    unsigned int children = stoi(argv[3]);
    unsigned int num_batches = stoi(argv[4]);
    if (argc == 6) {
        std::filesystem::create_directory("client_console");
        std::string out_name = "client_console/client_" + std::to_string(tree_height) + "_" + std::to_string(children) + ".txt";
        const char* out = out_name.c_str();
        FILE* output_file = freopen(out, "w", stdout);
    }
    const int client_id = 0;
    //  batch size, number of entries, size of entry
    std::vector<std::array<size_t, 3>> input_choices;
    size_t num_nodes = 0;
    for (int i = 1; i <= tree_height; i++) {
        num_nodes += pow(children, i);
    }
    input_choices.push_back({ tree_height, num_nodes, 32 });

    std::vector<std::chrono::milliseconds> init_times;
    std::vector<std::chrono::milliseconds> database_times;
    std::vector<std::chrono::milliseconds> query_gen_times;
    std::vector<std::chrono::milliseconds> resp_gen_times;
    std::vector<size_t> communication_list;

    std::cout << "***************************************************" << std::endl;
    std::cout << "             Starting Client " << std::endl;
    std::cout << "***************************************************" << std::endl;

    const auto& choice = input_choices[0];

    string selection = std::to_string(choice[0]) + "," + std::to_string(choice[1]) + "," + std::to_string(choice[2]);

    auto encryption_params = utils::create_encryption_parameters(selection);
    BatchPirParams params(choice[0], choice[1], choice[2], tree_height, children, encryption_params);
    size_t bucket_size = utils::load_bucket_size(tree_height, children);
    params.set_max_bucket_size(bucket_size);

    long unsigned int upper = 0;
    long unsigned int lower = 0;
    for (int i = 0; i <= tree_height; i++) {
        int nodes = pow(children, i);
        upper += nodes;
        if (i != tree_height) {
            lower += nodes;
        }
    }
    upper = upper;
    lower = lower + 1;
    cout << "Main: Starting query generation and information retrieval for " + to_string(num_batches) + " iterations..." << endl;
    int fails = 0;
    std::filesystem::create_directory("requests");
    std::ofstream myfile;
    std::string file_name = "requests/indices_" + to_string(tree_height) + "_" + to_string(children) + ".txt";
    myfile.open(file_name, std::ofstream::app);
    unsigned int num_buckets = ceil(DatabaseConstants::CuckooFactor * tree_height);
    auto hash_map = utils::load_map(tree_height, children);
    auto start = chrono::high_resolution_clock::now();
    auto end = chrono::high_resolution_clock::now();
    auto duration_querygen = chrono::duration_cast<chrono::milliseconds>(end - start);
    auto start_map = chrono::high_resolution_clock::now();
    auto end_map = chrono::high_resolution_clock::now();
    auto total_map = chrono::duration_cast<chrono::milliseconds>(end_map - start_map);
    for (int i = 0; i < num_batches; i++) {
        try {
            BatchPIRClient batch_client(tree_height, children, params);
            start_map = chrono::high_resolution_clock::now();
            batch_client.set_map(hash_map);
            end_map = chrono::high_resolution_clock::now();
            total_map += chrono::duration_cast<chrono::milliseconds>(end_map - start_map);
            vector<uint64_t> entry_indices = generate_batch(tree_height, children, upper, lower);
            start = chrono::high_resolution_clock::now();
            auto queries = batch_client.create_queries(entry_indices);
            auto hashed_query = batch_client.get_cuckoo_table();
            auto leaves = batch_client.leaves;
            end = chrono::high_resolution_clock::now();
            duration_querygen += chrono::duration_cast<chrono::milliseconds>(end - start);
            for (int v = 0; v < num_buckets; v++) {
                myfile << "PBC" + to_string(v+1) + "_" + to_string(tree_height) + "_" + to_string(children) + ".json; " +
                    "NodeID: " + to_string(leaves[v]) + "; index: " + to_string(hashed_query[v] + 1) + "\n";
            }
        }
        catch (std::invalid_argument const&) {
            fails++;
        }
        myfile << "\n";
        // auto request = return_request(buckets, hashed_query);
    }
    query_gen_times.push_back(duration_querygen);
    cout << "Main: Query generation complete for example." << endl;
    cout << endl;

    cout << "***********************" << endl;
    cout << "     Timings Report    " << endl;
    cout << "***********************" << endl;
    for (size_t i = 0; i < input_choices.size(); ++i)
    {
        cout << "Input Parameters: ";
        cout << "Batch Length: " << tree_height << ", ";
        cout << "Number of Entries: " << input_choices[i][1] << ", ";
        cout << "Entry Size: " << input_choices[i][2] << endl;
        cout << "Average Indexing time: " << query_gen_times[i].count() / num_batches << " milliseconds" << endl;
        cout << "Average Map handover time: " << total_map.count() / num_batches << " milliseconds" << endl;
        cout << "Rate of failure: " << fails / num_batches << " %" << endl;
    }

    return 0;
}

/*
int main(int argc, char* argv[])
{
    //vectorized_pir_main(argc, argv);
    batchpir_main_client(argc, argv);
    return 0;
}*/
