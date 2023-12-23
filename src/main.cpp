#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <map>
#include <array>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

map<string, string> extensions = {
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
map<string, string> comment_for_ext = {
    {".cpp", "//"},
    {".h", "//"},
    {".hpp", "//"},
    {".c", "//"},
    {".cs", "//"},
    {".java", "//"},
    {".js", "//"},
    {".ts", "//"},
    {".html", "<!-- -->"},
    {".css", "/* */"},
    {".php", "//"},
    {".sql", "--"},
    {".xml", "<!-- -->"},
    {".json", "//"},
    {".md", "<!-- -->"},
    {".txt", "//"},
    {".sh", "#"},
    {".bat", "REM"},
    {".ps1", "#"},
    {".psm1", "#"},
    {".psd1", "#"},
    {".ps1xml", "#"},
    {".psc1", "#"},
    {".pssc", "#"},
    {".psrc", "#"},
    {".py", "#"},
    //{".pyc", "#"},
    {".pyd", "#"},
    {".pyo", "#"},
    {".pyw", "#"},
    {".pyz", "#"},
    {".pyzw", "#"},
    {".rb", "#"},
    {".rhtml", "#"},
    {".rjs", "#"},
    {".rs", "//"},
    {".go", "//"},
    {".lua", "--"},
    {".swift", "//"}
}; 


bool is_comment(const string& line, const string& ext, bool multi_line_continues = false){
    return false;
}


array<int, 3> count_in_file(const fs::path& path){
    string ext = path.extension().string();
    array<int, 3> line_count = {0, 0, 0};
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Error opening file: " << path << endl;
        return line_count;
    }
    string line;
    while (getline(file, line)){
        // remove all space from the line
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (line.empty()) {
            line_count[2]++;
        }
        else if (is_comment(line, ext)) {
            line_count[1]++;
        }
        else {
            line_count[0]++;
        }

        //line_count++;
    }
    file.close();
    return line_count;
}


void process_directory(const fs::path& dir_path, array<int, 3>& total_lines, const map<string, string>& extensions_map){
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
                array<int, 3> line_count = count_in_file(entry.path());
                int code = line_count[0];
                int comment = line_count[1];
                int blank = line_count[2];
                total_lines[0] += code;
                total_lines[1] += comment;
                total_lines[2] += blank;
                cout << entry.path() << " (" << it->second << "): " << code << " lines of code, " << comment << " lines of comments, " << blank << " blank lines" << endl;                
            }
        }
    }
}


int main(int argc, char const *argv[]){
    //get the path from argv
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <path>" << endl;
        cout << "OPTIONAL: Add -i to ignore files with the following extensions: " << endl;
        cout << "OPTIONAL: Add -a to include only files with the following extensions: " << endl;
        return 1;
    }
    string path = argv[1];


    array<int, 3> total_lines = {0, 0, 0};

    try{
        process_directory(path, total_lines, extensions);
        cout << "Total: " << total_lines[0] << " lines of code, " << total_lines[1] << " lines of comments, " << total_lines[2] << " blank lines" << endl;
    } 
    catch (const exception& e){
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
