# Vectorized Batch Private Information Retrieval

This repository contains an implementation of the Vectorized Batch Private Information Retrieval (PIR) Protocol published in IEEE Security and Privacy, 2023. The protocol introduces a novel approach where both communication and computation are amortized over a batch of entries, resulting in significantly lower communication overhead for small entry sizes (ranging from 32 bytes to 256 bytes). Specifically, for a batch of 256 entries and an entry size of 32 bytes, the communication overhead is 11 times less compared to previous schemes.

The paper detailing the protocol can be found [here](https://ia.cr/2022/1262).

## Dependencies

This code relies on the [Microsoft SEAL Library](https://github.com/Microsoft/SEAL#citing-microsoft-seal). Make sure to install version 4.1 of this library globally.

## Compilation

Before proceeding with the compilation, ensure that your system has [CMake](https://cmake.org) installed, preferably a version above 3.0.

After installing CMake and the Microsoft SEAL Library, navigate to the root directory of the project and execute the following commands:

```
cmake -S . -B build
cmake --build build
```

Once the build process is complete, parameters can be changed in database_constants.h. The only parameter that requires changing before testing is *FileName* - please change to the location you wish to save the tree JSON files. The following command to execute the Vectorized Batch PIR:

```
./build/bin/vectorized_batch_pir
```

This will run the Vectorized Batch PIR for the three input scenarios mentioned below:

- tree depth = h = 3
- number of children = q = 2
- number of nodes = $\sum\limits_{i=1}^{h} q^i$ = 14
- batch size = h = 3
- number of requests = n = 100


## Expected Output

Upon processing the inputs, the terminal should display a similar output:

![image](https://github.com/Teddyzander/PBC/assets/49641102/582cb2f9-5774-4806-b3b0-e5631ef469cd)

## Contributors
 - [Muhammad Haris Mughees(Lead)](https://mhmughees.github.io)
 - [Ling Ren](https://sites.google.com/view/renling)
 - [Edward Small](https://www.linkedin.com/in/edward-small-4a6084a4/)

*Acknowledgment: Sun I (is16@illinois.edu) for helping with testing the code*

## ⚠️ Important Warning

This implementation is intended for research purposes only. The code has NOT been vetted by security experts. Therefore, no part of this code should be used in any real-world or production setting.
