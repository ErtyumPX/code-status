#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;


int count_in_file(const fs::path& path){
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << path << std::endl;
        return -1;
    }
    int line_count = 0;
    std::string line;
    while (std::getline(file, line)){
        line_count++;
    }
    file.close();
    return line_count;
}


void process_directory(const fs::path& dir_path, int& total_lines){
    for (const auto& entry : fs::directory_iterator(dir_path)){
        if (fs::is_directory(entry)){
            process_directory(entry.path(), total_lines);
        } else if (entry.path().extension() == ".py"){
            int linesInFile = count_in_file(entry.path());
            if (linesInFile >= 0){
                std::cout << "File: " << entry.path() << ", Lines: " << linesInFile << std::endl;
                total_lines += linesInFile;
            }
        }
    }
}


int main(int argc, char const *argv[]){
    //get the path from argv
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <path>" << endl;
        return 1;
    }
    string path = argv[1];

    int totalLines = 0;

    try{
        process_directory(path, totalLines);

        std::cout << "Total lines in all .py files: " << totalLines << std::endl;
    } 
    catch (const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
