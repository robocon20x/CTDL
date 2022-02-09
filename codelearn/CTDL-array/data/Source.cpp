#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <string.h>
#include <cmath>
#include <vector>
#include <unordered_map>
using namespace std;

#define _1BYTE 8
#define _0xFFFF_Length 16
#define _8BITS 255
#define _12BITS 4095
#define nl '\n'

void WriteFileLzw(ofstream& ofs, vector <int> outputCode, int codewordSize) {
    int buffer = 0;
    int bufferSize = 0;

    // Ghi pháº§n header lÃ  chiá»u dÃ i cá»§a codeword
    ofs.write(reinterpret_cast<char*>(&codewordSize), 1);

    for (int i = 0; i < outputCode.size(); i++) {
        buffer = (buffer << codewordSize) | outputCode[i];
        bufferSize += codewordSize;

        while (bufferSize >= _1BYTE) {
            int tmp = (buffer >> (bufferSize - _1BYTE));
            ofs.write(reinterpret_cast<char*>(&tmp), 1);
            buffer = buffer & (0xFFFF >> (_0xFFFF_Length - bufferSize + _1BYTE));
            bufferSize -= _1BYTE;
        }
    }

    if (bufferSize > 0) {
        buffer = buffer << (_1BYTE - bufferSize);
        ofs.write(reinterpret_cast<char*>(&buffer), 1);
    }
}

void <int> ReadFileLzw(ifstream& ifs, vector<int>& inputCode, int& codewordSize) {
    unsigned char buffer1;

    // Äá»c pháº§n header lÃ  chiá»u dÃ i cá»§a codeword
    ifs.read(reinterpret_cast<char*>(&buffer1), 1);
    codewordSize = static_cast<int>(buffer1);

    int buffer2 = 0;
    int buffer2Size = 0;

    while (ifs.read(reinterpret_cast<char*>(&buffer1), 1)) {
        buffer2 = (buffer2 << _1BYTE) | static_cast<int>(buffer1);
        buffer2Size += _1BYTE;

        while (buffer2Size >= codewordSize) {
            int tmp = buffer2 >> (buffer2Size - codewordSize);
            inputCode.push_back(tmp);
            buffer2 = buffer2 & (0xFFFF >> (_0xFFFF_Length - buffer2Size + codewordSize));
            buffer2Size -= codewordSize;
        }
    }
}

vector<int> encoding(string s, vector<pair<string, int>>& dictionary, int& codewordSize) {
    unordered_map<string, int> table;
    for (int i = 0; i <= _8BITS; i++) {
        string ch = "";
        ch += char(i);
        table[ch] = i;
    }

    string p = "", c = "";
    p += s[0];
    int count = _8BITS;
    int upperBoundary = _8BITS;  // 2^8 - 1
    vector<int> outputCode;

    for (int i = 0; i < s.size(); i++) {
        if (i != s.size() - 1)
            c += s[i + 1];

        if (table.find(p + c) != table.end()) {
            p = p + c;
        }
        else {
            if (count == upperBoundary) {
                /* Khi dictionary Ä‘Ã£ Ä‘áº¡t Ä‘áº¿n giá»›i háº¡n (2^12 - 1)
                thÃ¬ quay vá» 256 xoÃ¡ tring cÅ© vÃ  thÃªm string má»›i.
                NgÆ°á»£c láº¡i thÃ¬ tÄƒng má»©c giá»›i háº¡n */
                if (upperBoundary == _12BITS) {
                    count = _8BITS + 1;
                }
                else {
                    codewordSize++;
                    upperBoundary = upperBoundary * 2 + 1;
                    count++;
                }
            }
            else
                count++;

            outputCode.push_back(table[p]);
            dictionary.push_back(make_pair(p + c, count));
            table[p + c] = count;

            p = c;
        }
        c = "";
    }

    outputCode.push_back(table[p]);

    /* Kiá»ƒm tra xem náº¿u codewordLengh = n thÃ¬ file nÃ©n cÃ³ nhá» hÆ¡n so vá»›i codewordSize = 8
    Náº¿u khÃ´ng nhá» hÆ¡n thÃ¬ cho codewordSize = 8 vÃ  nÃ©n tá»«ng char = 8 bits. */
    if (ceil((double)(outputCode.size() * codewordSize) / _1BYTE) > s.size() * 8) {
        codewordSize = 8;
        outputCode.clear();
        dictionary.clear();
        string tmp;

        for (int i = 0; i < s.size(); i++) {
            tmp = s[i];
            outputCode.push_back(table[tmp]);
        }
    }

    return outputCode;
}

string decoding(vector<int> inputCode, vector<pair<string, int>>& dictionary, int codewordSize)
{
    unordered_map<int, string> table;
    for (int i = 0; i <= _8BITS; i++) {
        string ch = "";
        ch += char(i);
        table[i] = ch;
    }

    int old = inputCode[0], n;
    string s = table[old];
    string c = "";
    string strResult = s;
    c += s[0];
    int count = _8BITS;
    int upperBoundary = _8BITS;

    if (codewordSize == 8) {
        for (int i = 1; i < inputCode.size(); i++) {
            strResult += table[inputCode[i]];
        }

        return strResult;
    }

    for (int i = 0; i < inputCode.size() - 1; i++) {
        n = inputCode[i + 1];
        if (table.find(n) == table.end()) {
            s = table[old];
            s = s + c;
        }
        else {
            s = table[n];
        }

        if (count == upperBoundary) {
            /* Khi dictionary Ä‘Ã£ Ä‘áº¡t Ä‘áº¿n giá»›i háº¡n (2^12 - 1)
            thÃ¬ quay vá» 256 xoÃ¡ tring cÅ© vÃ  thÃªm string má»›i.
            NgÆ°á»£c láº¡i thÃ¬ tÄƒng má»©c giá»›i háº¡n */
            if (upperBoundary == _12BITS) {
                count = _8BITS + 1;
            }
            else {
                upperBoundary = upperBoundary * 2 + 1;
                count++;
            }
        }
        else
            count++;

        cout << s;
        strResult += s;
        c = "";
        c += s[0];
        table[count] = table[old] + c;
        dictionary.push_back(make_pair(table[count], count));

        old = n;
    }

    return strResult;
}

void PrintDictionary(vector<pair<string, int>> dictionary) {
    for (int i = 0; i < dictionary.size(); i++) {
        cout << dictionary[i].first << ": " << dictionary[i].second << nl;
    }
}

void CalculateSize(ifstream& ifs, ofstream& ofs) {
    ifs.clear();
    ofs.clear();
    ifs.seekg(0, ios::end);
    ofs.seekp(0, ios::end);

    int inputSize = ifs.tellg() * _1BYTE;
    int outputSize = ofs.tellp() * _1BYTE;
    double spaceSaved = 1.0 - (double)outputSize / inputSize;

    cout << "Input size: " << inputSize << " bits" << nl;
    cout << "Output size: " << outputSize << " bits" << nl;
    cout << "Space Saved: " << fixed << setprecision(2) << spaceSaved << "%" << nl;

}

int main(int argc, char* argv[]) {
    ifstream ifs;
    ofstream ofs;
    vector<int> code;
    vector<pair<string, int>> dictionary;
    int codewordSize = 8;
    string s;

    if (strcmp(argv[1], "-e") == 0) {
        ifs.open(argv[2]);
        ofs.open(argv[3], ios::binary);

        ifs >> s;
        code = encoding(s, dictionary, codewordSize);
        WriteFileLzw(ofs, code, codewordSize);
    }
    else if (strcmp(argv[1], "-d") == 0) {
        ifs.open(argv[2], ios::binary);
        ofs.open(argv[3]);

        ReadFileLzw(ifs, code, codewordSize);
        s = decoding(code, dictionary, codewordSize);
        ofs << s;
    }
    else {
        cout << "Invalid Arguments";
        return 1;
    }

    if (strcmp(argv[4], "-i") == 0) {
        PrintDictionary(dictionary);
    }
    else if (strcmp(argv[4], "-d") == 0) {
        CalculateSize(ifs, ofs);
    }
    else if (strcmp(argv[4], "-ind") == 0) {
        PrintDictionary(dictionary);
        CalculateSize(ifs, ofs);
    }
    else {
        cout << "Invalid Arguments";
        return 1;
    }

    if (ifs.is_open()) ifs.close();
    if (ofs.is_open()) ofs.close();

    return 0;
}