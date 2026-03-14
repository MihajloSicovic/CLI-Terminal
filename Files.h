#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>


// Helper class. Used to open file safely.
class FileManager {
public:

	// Helper method. Returns opened input file with the given name.
	// Throws error if the file cannot be opened.
	static std::ifstream* getInputFile(const std::string& filename) {
		std::ifstream* file = new std::ifstream(filename);
		if (!file->is_open()) {
			delete file;
			throw std::system_error(errno, std::generic_category(), filename);
		}

		return file;
	}

	// Helper method. Returns opened output file with the given name and mode.
	// Throws error if the file cannot be opened.
	static std::ofstream* getOutputFile(const std::string& filename, 
		const std::ios_base::openmode& mode = std::ios_base::out) {

		std::ofstream* file = new std::ofstream(filename, mode);
		if (!file->is_open()) {
			delete file;
			throw std::system_error(errno, std::generic_category(), filename);
		}

		return file;
	}
};
