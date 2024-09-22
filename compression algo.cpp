#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

vector<char> Compress(const vector<char>& data) {
    vector<char> Compressed;
    if (data.empty()) {
        return Compressed;
    }
    char Prev = data[0];
    int Count = 1;

    for (size_t i = 1; i < data.size(); i++) {
        if (data[i] == Prev) {
            Count++;
        }
        else {
            Compressed.push_back(static_cast<char>(Count));
            Compressed.push_back(Prev);
            Prev = data[i];
            Count = 1;
        }
    }

    Compressed.push_back(static_cast<char>(Count));
    Compressed.push_back(Prev);

    return Compressed;
}

vector<char> DeCompress(const vector<char>& Compressed) {
    vector<char> DeCompressed;
    for (size_t i = 0; i < Compressed.size(); i += 2) {
        if (i + 1 < Compressed.size()) {
            int Count = static_cast<unsigned char>(Compressed[i]);
            char Symbol = Compressed[i + 1];
            for (int j = 0; j < Count; j++) {
                DeCompressed.push_back(Symbol);
            }
        }
        else {
            break;
        }
    }
    return DeCompressed;
}

int main() {
    int choice;
    do {
        cout << "1: Compress File" << endl;
        cout << "2: DeCompress File" << endl;
        cout << "3: Exit" << endl;
        cin >> choice;

        if (choice == 1) {
            ifstream file("compression.docx", ios::binary);
            if (!file) {
                cerr << "Error opening input file." << endl;
                continue;
            }
            vector<char> data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
            file.close();

            vector<char> Compressed = Compress(data);

            ofstream Compressed_file("Compressed.txt", ios::binary);
            if (!Compressed_file) {
                cerr << "Error opening output file." << endl;
                continue;
            }
            Compressed_file.write(Compressed.data(), Compressed.size());
            Compressed_file.close();
        }
        else if (choice == 2) {
            ifstream Compressed_file("Compressed.txt", ios::binary);
            if (!Compressed_file) {
                cerr << "Error opening compressed file." << endl;
                continue;
            }
            vector<char> Compressed((istreambuf_iterator<char>(Compressed_file)), istreambuf_iterator<char>());
            Compressed_file.close();

            vector<char> DeCompressed = DeCompress(Compressed);

            ofstream DeCompressed_file("DeCompressed.docx", ios::binary);
            if (!DeCompressed_file) {
                cerr << "Error opening decompressed file." << endl;
                continue;
            }
            DeCompressed_file.write(DeCompressed.data(), DeCompressed.size());
            DeCompressed_file.close();
        }
        else if (choice != 3) {
            cout << "Invalid Choice" << endl;
        }

    } while (choice != 3 && !cin.fail());
    return 0;
}
