#ifndef DATABASE_CONSTANTS_H
#define DATABASE_CONSTANTS_H

#include <limits>
#include <string>

namespace DatabaseConstants {
    // hash function definitions
    constexpr int PolyDegree = 8192;
    constexpr int PlaintextModBitss = 22;
    // number of re-insertion attempt before failure
    constexpr int MaxAttempts = 500;
    // number of hash functions used to generate database
    constexpr int NumHashFunctions = 3;
    // defines number of buckets (height of tree multiplied by cuckoo factor)
    constexpr double CuckooFactor = 1.5;
    constexpr double FirstDimension = 32;
    constexpr uint64_t DefaultVal =  std::numeric_limits<uint64_t>::max();
    // name of file we are using to generate data base
    constexpr std::string_view FileName = "C:\\Users\\edwar\\OneDrive\\Documents\\Academia\\RMIT\\Research\\Projects\\vectorized_batch_pir\\tree_data\\wholeTree_3.json";
    // get height of the tree
    constexpr int TreeHeight = 3;

}

#endif // DATABASE_CONSTANTS_H