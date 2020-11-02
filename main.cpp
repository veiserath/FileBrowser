#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

enum controls {
    one = 1, two = 2, three = 3, four = 4
};

struct Reader {

    string path;

    Reader() {
    }

    vector<char> data;

    void readFile() {
        ifstream input(path);
        while (input) {
            data.push_back(input.get());
        }
        input.close();
    }

    void showFile() {
        readFile();
        for (int i = 0; i < data.size(); i++) {
            cout << data[i];
        }
        cout << endl;
    }

};

class PathControler {
public:
    string path;
    fs::path *filePath = new fs::path(path);

    PathControler(const string &path) : path(path) {
    }

    void listFiles() {
        cout << "Folder: " + path + " contains: \n\n";
        for (fs::directory_entry plik : fs::directory_iterator(path)) {
            cout << plik.path().filename() << endl;
        }
    }
};

void mainMenu() {
    cout << "(1) List all files in the current directory: " << endl;
    cout << "(2) Move to another directory: " << endl;
    cout << "(3) Show file content: " << endl;
    cout << "(4) End program: " << endl;
}

void subMenu() {
    cout << "(1) Go to a specific directory (absolute path): " << endl;
    cout << "(2) Move one directory up: " << endl;
    cout << "(3) Go to a specific folder in this directory: " << endl;
}

void subCase(PathControler *pathControler, int input);

void mainCase(PathControler *pathControler, Reader reader, int input) {

    switch (input) {
        case one:
            pathControler->listFiles();
            break;
        case two:
            subMenu();
            cin >> input;
            subCase(pathControler, input);
            break;
        case three:
            cout << "File to read: " << endl;
            string fileName = pathControler->path;
            string file;
            cin >> file;
            reader.path.append(fileName.append("/").append(file));
            reader.showFile();
            break;

    }
}

void subCase(PathControler *pathControler, int input) {

    switch (input) {
        case one:
            cout << "Specify absolute path and list its content: ";
            cin >> pathControler->path;
            pathControler->listFiles();
            break;
        case two:
            pathControler->path = pathControler->filePath->parent_path();
            pathControler->filePath = new fs::path(pathControler->path);
            pathControler->listFiles();
            break;
        case three:
            string folder;
            cout << "Specify a folder you want to jump to: ";
            cin >> folder;
            if (fs::is_directory(pathControler->path + "/" + folder)) {
                pathControler->path = pathControler->path + "/" + folder;
                pathControler->listFiles();
            } else if (!fs::is_directory(pathControler->path + "/" + folder)) {
                cout << "This is not a valid directory!" << endl;
            }
            break;
    }
}

int main() {

    PathControler *pathControler = new PathControler("/Users/User/Desktop");
    Reader reader;

    int input = 0;
    do {
        mainMenu();
        cin >> input;
        mainCase(pathControler, reader, input);
    } while (input != four);
}

