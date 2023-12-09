# Vectorized Batch Private Information Retrieval

This repository contains an implementation of the Vectorized Batch Private Information Retrieval (PIR) Protocol published in IEEE Security and Privacy, 2023. The protocol introduces a novel approach where both communication and computation are amortized over a batch of entries, resulting in significantly lower communication overhead for small entry sizes (ranging from 32 bytes to 256 bytes). Specifically, for a batch of 256 entries and an entry size of 32 bytes, the communication overhead is 11 times less compared to previous schemes.

The paper detailing the protocol can be found [here](https://ia.cr/2022/1262).

## Dependencies

Ensure that your system has [CMake](https://cmake.org) installed, preferably a version above 3.0:

```
sudo apt install build-essential cmake clang git g++ libssl-dev libgmp3-dev
sudo apt update
sudo apt upgrade
```

This code relies on the [Microsoft SEAL Library](https://github.com/Microsoft/SEAL#citing-microsoft-seal). Make sure to install version 4.0 of this library globally:

```
git clone https://github.com/cnquang/SEAL-4.0.0.git
cd SEAL-4.0.0
cmake -S . -B build
cmake --build build
sudo cmake --install build
```

## Compilation

After installing CMake and the Microsoft SEAL Library, clone the repository and enter the directory: 

```
git clone https://github.com/Teddyzander/PBC.git
cd PBC
```

Execute the following commands to build the executable:

```
cmake -S . -B build
cmake --build build
```

## Execution

Once the build process is complete, parameters for each run can be set via command line arguments. The following command to execute the Vectorized Batch PIR:

```
./build/bin/vectorized_batch_pir <server or client> <tree depth> <number of children> <number of requests> <save_console_output>
```

The server must be run before the client, as the client relies on the data generated by the server.

### Example

Running:

```
./build/bin/vectorized_batch_pir server 3 2 100
```

will generate PBC data for the following conditions:

- tree depth = h = 3
- number of children = q = 2
- number of nodes = $\sum\limits_{i=1}^{h} q^i$ = 14
- batch size = h = 3
- number of requests = n = 100
- Output printed to console, not to file

Running:

```
./build/bin/vectorized_batch_pir client 3 2 100 True
```

Will then create 100 hashed requests for the PBC database. This information will not be printed to the console, but instead will be saved in a text file due to the final command line argument.

### Expected Output

Upon running 
```
./build/bin/vectorized_batch_pir server 3 2 100
```
we should expect to see the following to be printed to the terminal:

![image](https://github.com/Teddyzander/PBC/assets/49641102/6493f029-ded2-4988-8cc8-6382495a48de)

Upon running 
```
./build/bin/vectorized_batch_pir client 3 2 100 True
```
we should expect to see the following saved to a text file in the client_console/ folder (which can be read using the ```cat``` command):

![image](https://github.com/Teddyzander/PBC/assets/49641102/db020f5f-10a4-405c-8d86-9235508c1834)

## Classic Errors

### Unbuilt Server

Running a client prior to building the server will cause a ```nlohmann::json_abi_v3_11_2::detail::parse_error``` error code. This is because the JSON files we need access to do not exists. Check that the server has been build, and double check that the command line arguments for the client match the arguments used to generate the database.

### incorrect arguments

Attempting to execute with innsufficient command line arguments will result in a ```std::logic_error``` error code. There are no default command line arguments - the user must always assert the tree structure and batch numbers.

## Contributors
 - [Muhammad Haris Mughees(Lead)](https://mhmughees.github.io)
 - [Ling Ren](https://sites.google.com/view/renling)
 - [Edward Small](https://www.linkedin.com/in/edward-small-4a6084a4/)

*Acknowledgment: Sun I (is16@illinois.edu) for helping with testing the code*

## ⚠️ Important Warning

This implementation is intended for research purposes only. The code has NOT been vetted by security experts. Therefore, no part of this code should be used in any real-world or production setting.
