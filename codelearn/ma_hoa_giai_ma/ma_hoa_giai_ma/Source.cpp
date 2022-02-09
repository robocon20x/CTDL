#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <bitset>
using namespace std;

#define _1BYTE 8
#define _0xFFFF_Length 24

vector<int> encoding(string s1) {
    unordered_map<string, int> table;
    for (int i = 0; i <= 255; i++) {
        string ch = "";
        ch += char(i);
        table[ch] = i;
    }

    string p = "", c = "";
    p += s1[0];
    int code = 256;
    vector<int> output_code;
    for (int i = 0; i < s1.length(); i++) {
        if (i != s1.length() - 1)
            c += s1[i + 1];
        if (table.find(p + c) != table.end()) {
            p = p + c;
        }
        else {
            // cout << p << "\t" << table[p] << "\t\t" 
            //      << p + c << "\t" << code << endl; 
            output_code.push_back(table[p]);
            table[p + c] = code;
            code++;
            p = c;
        }
        c = "";
    }
    // cout << p << "\t" << table[p] << endl; 
    // output_code.push_back(table[p]); 
    return output_code;
}

// string decoding(vector<int> op) 
// { 
//     // cout << "\nDecoding\n"; 
//     unordered_map<int, string> table; 
//     for (int i = 0; i <= 255; i++) { 
//         string ch = ""; 
//         ch += char(i); 
//         table[i] = ch; 
//     } 
//     int old = op[0], n; 
//     string s = table[old]; 
//     string c = "";
//     string strRes = s;
//     c += s[0]; 
//     // cout << s; 
//     int count = 256; 
//     for (int i = 0; i < op.size() - 1; i++) { 
//         n = op[i + 1]; 
//         if (table.find(n) == table.end()) { 
//             s = table[old]; 
//             s = s + c; 
//         } 
//         else { 
//             s = table[n]; 
//         } 
//         // cout << s;
//         strRes += s;
//         c = ""; 
//         c += s[0]; 
//         table[count] = table[old] + c; 
//         count++; 
//         old = n; 
//     } 
// } 

void WriteFile(ofstream& ofs, vector <int> output_code, int codewordLength) {
    if (codewordLength == 8) {
        for (int i = 0; i < output_code.size(); i++)
            ofs.write(reinterpret_cast<const char*>(&output_code[i]), 1);
    }
    else {
        int buffer = 0;
        int bufferSize = 0;
        for (int i = 0; i < output_code.size(); i++) {
            buffer = (buffer << codewordLength) | output_code[i];
            bufferSize += codewordLength;

            while (bufferSize >= _1BYTE) {
                int tmp = (buffer >> (bufferSize - _1BYTE));
                ofs.write(reinterpret_cast<const char*>(&tmp), 1);
                buffer = buffer & (0xFFFF >> (_0xFFFF_Length - bufferSize));
                bufferSize -= _1BYTE;
            }
        }

        if (buffer > 0) {
            buffer = buffer << (_1BYTE - bufferSize);
            ofs.write(reinterpret_cast<const char*>(&buffer), 1);
        }
    }
}

int main(int argc, char* argv[]) {
    ifstream ifs(argv[2]);
    ofstream ofs(argv[3], ios::binary);
    vector<int> output_code;
    int codewordLength = 9;
    string s;

    ifs >> s;
    output_code = encoding(s);

    WriteFile(ofs, output_code, codewordLength);

    return EXIT_SUCCESS;
}