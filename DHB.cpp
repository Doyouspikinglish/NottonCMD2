#include "DHB.h"

//DHB has 2 main values: StarterValue and EndValue

int ErrorValue = 0;

int Convert(const std::string& StarterValue) {
	try {
		int EndValue = std::stoi(StarterValue);

		std::cout << "Decimal: " << EndValue << "\n";
		std::cout << "Hex: 0x" << std::uppercase << std::hex << EndValue << "\n";
		std::cout << "Binary: " << std::bitset<32>(EndValue) << "\n";
		return EndValue;
	}
	catch (const std::exception& err) { std::cerr << "Conversion failed:" << err.what() << "\n"; }
	return ErrorValue;
}