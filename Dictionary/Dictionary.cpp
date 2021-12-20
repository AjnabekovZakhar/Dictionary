#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
#include<vector>
#include<set>
#include <algorithm>
using namespace std;

vector<char> letters ={ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                      'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                      's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

vector<char> removable = {'.',
                                    ',',
                                    '!',
                                    '?',
                                    '\"',
                                    '\'',
                                    ';',
                                    ':',
                                    '(',
                                    ')',
                                    '1','2','3','4','5','6','7','8','9','0'
                                    };


vector<string> checker(string checked_str, set<string>& dictionary) {
    vector<string> variants;
    string temp_str;
    for (int i = 0; i < checked_str.size();++i) {//extra char
        temp_str = checked_str;
        temp_str.erase(temp_str.begin() + i);
        if (dictionary.find(temp_str) != dictionary.end())
            variants.push_back(temp_str);
    }
    for (int i = 0; i < checked_str.size(); ++i) {
        for (auto l : letters) {
            temp_str = checked_str;
            temp_str.insert(i,1,l);
            if (dictionary.find(temp_str) != dictionary.end())
                variants.push_back(temp_str);
        }
    }
    for (int i = 0; i < checked_str.size(); ++i) {
        for (auto l : letters) {
            temp_str = checked_str;
            temp_str[i]=l;
            if (dictionary.find(temp_str) != dictionary.end())
                variants.push_back(temp_str);
        }
    }
    return variants;
}

int main()
{
    set<string> dictionary;
    string input_str,temp_str,output_str;
    vector<string> output_text,temp_variants;

    char input_char;
    int input_int;

    try {
        ifstream dictionary_file("dictionary.txt");

        if (!dictionary_file.is_open()) {
            throw runtime_error("Couldn't open dictionary file");
        }

        while (getline(dictionary_file, input_str)) {
            transform(input_str.begin(), input_str.end(), input_str.begin(),
                [](unsigned char c) { return tolower(c); });
            dictionary.insert(input_str);
        }

        ifstream text_file("text.txt");

        if (!text_file.is_open()) {
            throw runtime_error("Couldn't open text file");
        }
        
        while (getline(text_file, input_str)) {

            std::stringstream ss;

            ss.str(input_str);
            output_str.clear();
            while (getline(ss, temp_str, ' ')) {
                for (auto f : removable)
                    temp_str.erase(remove(temp_str.begin(), temp_str.end(), f), temp_str.end());
                transform(temp_str.begin(), temp_str.end(), temp_str.begin(),
                    [](unsigned char c) { return tolower(c); });
                if (dictionary.find(temp_str) == dictionary.end()) {
                    cout << "The word " << temp_str << " is not in the dictionary" << endl;
                    cout << "Press s to save word in dictionary" << endl;
                    temp_variants = checker(temp_str, dictionary);
                    for (int i = 0; i < temp_variants.size(); ++i)
                        cout << "Press " << i << " to replace with " << temp_variants[i] << endl;
                    cout << "Press another char to go to the next word" << endl;
                    cin >> input_char;
                    if (input_char == 's')
                        dictionary.insert(temp_str);
                    else if (input_char - '0' >= 0 && input_char - '0' < temp_variants.size())
                        temp_str = temp_variants[input_char - '0'];
                    
                }
                output_str += (temp_str+' ');
            }
            output_text.push_back(output_str);
        }
    }
    catch(runtime_error e){
        cout << e.what() << endl;
    }
    cout << "correct text" << endl;
    for (auto s : output_text) cout << s << endl;
    cout<< "dictionary" << endl;
    for (auto f : dictionary) cout << f << endl;


    return 0;
}

