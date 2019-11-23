#include "mapToJson.h"
#include <iostream>


int main(int argc, char* argv[]) {
	if (argc <= 1) {
		std::cout << "Usage: " << argv[0] << " mapFile1.map ..." << std::endl << std::endl;
		return 1;
	}

	const auto numArgs = static_cast<size_t>(argc);
	for (size_t i = 1; i < numArgs; ++i) {
		std::string inputFileName{argv[i]};
		std::string outputFileName{inputFileName + ".json"};
		std::cout << "Converting " << inputFileName << " to " << outputFileName << std::endl;
		mapFileToJsonFile(inputFileName, outputFileName);
	}
	return 0;
}
