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
    // name of folderwhere trees are stored
    constexpr std::string_view FileName = "..\\..\\tree_data\\";
    // set height of the tree
    constexpr unsigned int TreeHeight = 3;
    // set number of children per node
    constexpr unsigned int children = 2;
    // number of batches to request
    constexpr unsigned int num_batches = 100;

}

#endif // DATABASE_CONSTANTS_H