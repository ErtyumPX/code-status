#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <map>

using namespace std;
namespace fs = std::filesystem;


int count_in_file(const fs::path& path){
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Error opening file: " << path << endl;
        return -1;
    }
    int line_count = 0;
    string line;
    while (getline(file, line)){
        line_count++;
    }
    file.close();
    return line_count;
}


void process_directory(const fs::path& dir_path, int& total_lines, const map<string, string>& extensions_map){
    for (const auto& entry : fs::directory_iterator(dir_path)) {
        if (fs::is_directory(entry)) {
            // Recursive call for subdirectories
            process_directory(entry.path(), total_lines, extensions_map);
        } else {
            // Check if the file has an allowed extension
            std::string fileExtension = entry.path().extension().string();
            auto it = extensions_map.find(fileExtension);
            if (it != extensions_map.end()) {
                // Count lines in the file
                int linesInFile = count_in_file(entry.path());
                if (linesInFile >= 0) {
                    std::cout << "File: " << entry.path() << ", Language: " << it->second << ", Lines: " << linesInFile << std::endl;
                    total_lines += linesInFile;
                }
            }
        }
    }
}

map<string, string> extensions = {
    {".py", "Python"},
    {".cpp", "C++"},
    {".h", "C++"},
    {".hpp", "C++"},
    {".c", "C"},
    {".cs", "C#"},
    {".java", "Java"},
    {".js", "JavaScript"},
    {".ts", "TypeScript"},
    {".html", "HTML"},
    {".css", "CSS"},
    {".php", "PHP"},
    {".sql", "SQL"},
    {".xml", "XML"},
    {".json", "JSON"},
    {".md", "Markdown"},
    {".txt", "Text"},
    {".sh", "Shell"},
    {".bat", "Batch"},
    {".ps1", "PowerShell"},
    {".psm1", "PowerShell"},
    {".psd1", "PowerShell"},
    {".ps1xml", "PowerShell"},
    {".psc1", "PowerShell"},
    {".pssc", "PowerShell"},
    {".psrc", "PowerShell"},
    {".py", "Python"},
    //{".pyc", "Python"},
    {".pyd", "Python"},
    {".pyo", "Python"},
    {".pyw", "Python"},
    {".pyz", "Python"},
    {".pyzw", "Python"},
    {".rb", "Ruby"},
    {".rhtml", "Ruby"},
    {".rjs", "Ruby"},
    {".rs", "Rust"},
    {".go", "Go"},
    {".lua", "Lua"},
    {".swift", "Swift"}
};


int main(int argc, char const *argv[]){
    //get the path from argv
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <path>" << endl;
        return 1;
    }
    string path = argv[1];

    int total_lines = 0;

    try{
        process_directory(path, total_lines, extensions);

        cout << "Total lines in all .py files: " << total_lines << endl;
    } 
    catch (const exception& e){
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
