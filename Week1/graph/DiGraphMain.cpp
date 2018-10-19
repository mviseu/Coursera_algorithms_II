#include "DiGraph.h"
#include <fstream>
#include <string>

int main() {
	std::ifstream file("TinyDiGraph.txt");
	DiGraph g(file);
	std::cout << std::string(g) << std::endl;
	return 0;
}