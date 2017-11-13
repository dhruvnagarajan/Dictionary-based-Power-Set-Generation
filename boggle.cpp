#include "header.h"

int data_length;
const int one_d = 3, two_d = 3;

vector <string> dict, generated_words;

bool is_word (string str) {

    FOR (i, dict.size ()) {

        if (str == dict[i]) return true;
    }

    return false;
}

void generate_words_util (char data[][two_d], bool visited[][two_d], int i, int j, string &str) {

    visited[i][j] = true;

    db ("Adding", data[i][j], false);

    str += data[i][j];

    if (is_word (str)) generated_words.push_back (str);

    for (int row = i - 1; row <= i + 1 && row < one_d; row ++) {

        for (int col = j - 1; col <= j + 1 && col < two_d; col ++) {

            if (row >= 0 && col >= 0 && !visited[row][col]) {

                generate_words_util (data, visited, row, col, str);
            }
        }
    }

    str.erase (str.length () - 1);

    db ("Cleared", "", true);

    visited[i][j] = false;
}

void generate_words (char data[one_d][two_d]) {

    bool visited[one_d][two_d] = {{ false }};

    string str = "";

    FOR (i, one_d) {

        FOR (j, two_d) {

            db ("Starting with", data[i][j], true);

            generate_words_util (data, visited, i, j, str);

            return;
        }
    }
}

void print_words () {

    FOR (i, generated_words.size ()) {

        cout << generated_words[i] << endl;
    }
}

int main () {

    extern int data_length;

    freopen ("boggle.txt", "r", stdin);

    int _;
    cin >> _;

    FOR (i, _) {

        string str;
        cin >> str;

        dict.push_back (str);
    }

    // cin >> one_d >> two_d;

    char data[one_d][two_d];

    FOR (i, one_d) FOR (j, two_d) cin >> data[i][j];

    generate_words (data);

    print_words ();

    return 0;
}