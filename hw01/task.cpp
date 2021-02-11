#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

const string FILE_IN = "input.txt";     // input file
const string FILE_OUT = "output.txt";   // output file

/**
 * The method split input string by sentences
 * and returns vector of sentences.
 * @param line - string of large text with sentences separated by dot (.)
 * @return vector<string> (set) of sentences without dot (.)
 */
vector<string> getSentences(string line) {
    stringstream ss(line);
    vector<string> ans;
    string buf;
    while (getline(ss, buf, '.')) {
        if (buf[0] == ' ')
            ans.push_back(buf.substr(1));
        else
            ans.push_back(buf);
    }
    return ans;
}

/**
 * The method convert string with lowercase letters to string
 * which contains only uppercase letters.
 * @param src - string which contain anything
 * @return string with only uppercase letters
 */
string toUpperCase(string src) {
    for (char &i : src) {
        if (i >= 'a' && i <= 'z') {
            i = i - 'a' + 'A';
        }
    }
    return src;
}

/**
 * The method gets a string and special word, which should be found
 * and highlighted by converted to uppercase.
 * @param sentence - a string which contains a special word
 * @param word - a special word
 * @return sentence with highlighted special word
 */
string getSentenceWithUpperCasedWord(string sentence, string word) {
    string ans = "", buf;
    word = toUpperCase(word);
    stringstream ss(sentence);
    while (getline(ss, buf, ' ')) {
        toUpperCase(buf) == word ? (ans += word + " ") : (ans += buf + " ");
    }
    ans.erase(ans.size()-1);
    return ans + '.';   // sentence was without dot (.)
}

int main() {
    ifstream in(FILE_IN);
    ofstream out(FILE_OUT);

    string line;
    vector<string> sentences;
    if (in.is_open()) {
        getline(in, line);
        sentences = getSentences(line);
        getline(in, line);
        int count = atoi(line.c_str());

        vector<string> ans;
        for (int i = 0; i < count; i++) {
            getline(in, line);
            line = toUpperCase(line);
            int foundSentences = 0;
            for (int j = 0; j < sentences.size(); ++j) {
                stringstream ss(sentences[j]);
                string buf;
                while (getline(ss, buf, ' ')) {
                    buf = toUpperCase(buf);
                    if (buf == line) {
                        buf = getSentenceWithUpperCasedWord(sentences[j], line);
                        ans.push_back(buf);
                        foundSentences++;
                        break;
                    }
                }
            }
            out << foundSentences << endl;
            for (int j = 0; j < foundSentences; j++) {
                out << ans[j] << endl;
            }
            ans.clear();
        }

        in.close();
        out.close();
    } else {
        cout << "Check name of the file!";
    }

    return 0;
}