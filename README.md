# Installation
Install clang and llvm
```bash
sudo apt-get install clang
```
```bash
sudo apt-get install llvm
```

Install dev dependencies for clang
```bash
sudo apt-get install libc++-dev
```
```bash
sudo apt-get install libc++abi-dev
```

Install debugger tools
```bash
sudo apt-get install lldb
```

```bash
sudo apt-get install liblldb-dev
```

Download and build lldb-mi:
```bash
git clone https://github.com/lldb-tools/lldb-mi
cd lldb-mi
cmake -DLLDB_DIR=/usr/lib/llvm-14/lib/ .
make
```



# Compile and run code
Run the command:
```bash
clang++ -std=c++11 -stdlib=libc++ <filename>.cpp -o <output-file>
```
add `-v` at the end for verbose output.

Then run the output file
```bash
./<output-file>
```