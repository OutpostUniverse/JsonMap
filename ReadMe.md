JsonMap - Outpost 2 map file to JSON file converter

This utility converts Outpost 2 map and saved game binary files to a text readable JSON format. This is largely for viewing and inspection purposes. It may also be useful for consumption by other utilities, perhaps written in other languages, where a JSON parser is conveniently available, but reading the Outpost 2 map and saved game binary files would be difficult.

+++ Example Usage +++
```
./mapToJson eden01.map
```

+++ Compiling +++
From the project root folder run:
```
make
```

+++ Compile Dependencies +++

This project makes use of `make`, and a C++ compiler, such as `g++` or `clang++`.

This project uses NuGet for package management. Needed NuGet packages (see `packages.config`) will be automatically downloaded by the make script and cached.

To install needed dependencies on Ubuntu (18.04) run:
```
sudo apt install build-essential nuget
```
