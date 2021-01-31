#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

const string FILE_IN = "input.txt";
const string FILE_OUT = "output.txt";

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

string toUpperCase(string src) {
    for (int i = 0; i < src.size(); i++) {
        if (src[i] >= 'a' && src[i] <= 'z') {
            src[i] = src[i] - 'a' + 'A';
        }
    }
    return src;
}

string getSentenceWithUpperCasedWord(string sentence, string word) {
    string ans = "";
    string buf;
    word = toUpperCase(word);
    stringstream ss(sentence);
    while (getline(ss, buf, ' ')) {
        toUpperCase(buf) == word ? (ans += word + " ") : (ans += buf + " ");
    }
    ans.erase(ans.size()-1);
    return ans + '.';
}

int main() {
    ifstream in(FILE_IN);
    ofstream out(FILE_OUT);

    string line;
    vector<string> sentences;
    if (in.is_open()) {
        getline(in, line);
        sentences = getSentences(line);

        vector<string> ans;
        getline(in, line);
        int count = atoi(line.c_str());
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