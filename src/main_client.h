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

int batchpir_main_client(int argc, char* argv[])
{
    const int client_id = 0;
    //  batch size, number of entries, size of entry
    std::vector<std::array<size_t, 3>> input_choices;
    size_t num_nodes = 0;
    for (int i = 1; i <= DatabaseConstants::TreeHeight; i++) {
        num_nodes += pow(DatabaseConstants::children, i);
    }
    input_choices.push_back({ DatabaseConstants::TreeHeight, num_nodes, 32 });

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
    BatchPirParams params(choice[0], choice[1], choice[2], encryption_params);
    size_t bucket_size = utils::load_bucket_size();
    params.set_max_bucket_size(bucket_size);

    BatchPIRClient batch_client(params);

    auto hash_map = utils::load_map();
    batch_client.set_map(hash_map);

    long unsigned int upper = 0;
    long unsigned int lower = 0;
    for (int i = 0; i <= DatabaseConstants::TreeHeight; i++) {
        int nodes = pow(DatabaseConstants::children, i);
        upper += nodes;
        if (i != DatabaseConstants::TreeHeight) {
            lower += nodes;
        }
    }
    upper = upper;
    lower = lower + 1;
    cout << "Main: Starting query generation and information retrieval for " + to_string(DatabaseConstants::num_batches) + " iterations..." << endl;
    auto start = chrono::high_resolution_clock::now();
    int fails = 0;
    for (int i = 0; i < DatabaseConstants::num_batches; i++) {
        try {
            vector<uint64_t> entry_indices = generate_batch(DatabaseConstants::TreeHeight, DatabaseConstants::children, upper, lower);
            auto queries = batch_client.create_queries(entry_indices);
            auto hashed_query = batch_client.get_cuckoo_table();
        }
        catch (std::invalid_argument const&) {
            fails++;
        }
        // auto request = return_request(buckets, hashed_query);
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration_querygen = chrono::duration_cast<chrono::milliseconds>(end - start);
    query_gen_times.push_back(duration_querygen);
    cout << "Main: Query generation complete for example." << endl;
    cout << endl;

    cout << "***********************" << endl;
    cout << "     Timings Report    " << endl;
    cout << "***********************" << endl;
    for (size_t i = 0; i < input_choices.size(); ++i)
    {
        cout << "Input Parameters: ";
        cout << "Batch Length: " << DatabaseConstants::TreeHeight << ", ";
        cout << "Number of Entries: " << input_choices[i][1] << ", ";
        cout << "Entry Size: " << input_choices[i][2] << endl;
        cout << "Average Indexing time: " << query_gen_times[i].count() / DatabaseConstants::num_batches << " milliseconds" << endl;
        cout << "Rate of failure: " << fails / DatabaseConstants::num_batches << " %" << endl;
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