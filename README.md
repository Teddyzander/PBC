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

Once the build process is complete, parameters can be changed in database_constants.h. The following command to execute the Vectorized Batch PIR:

```
./build/bin/vectorized_batch_pir
```

This will run the Vectorized Batch PIR for the three input scenarios mentioned below:

- tree depth = h
- number of children = q
- number of nodes = $\sum\limits_{i=1}^{h} q^i$
- batch size = h
- number of requests = n


## Expected Output

Upon processing the inputs, the terminal should display a similar output:

![Terminal Output](https://github.com/mhmughees/vectorized_batchpir/assets/6435443/5112f7e3-2087-4223-88f1-4abf2037357d)

## Contributors
 - [Muhammad Haris Mughees(Lead)](https://mhmughees.github.io)
 - [Ling Ren](https://sites.google.com/view/renling)
 - [Edward Small](https://www.linkedin.com/in/edward-small-4a6084a4/)

*Acknowledgment: Sun I (is16@illinois.edu) for helping with testing the code*

## ⚠️ Important Warning

This implementation is intended for research purposes only. The code has NOT been vetted by security experts. Therefore, no part of this code should be used in any real-world or production setting.
