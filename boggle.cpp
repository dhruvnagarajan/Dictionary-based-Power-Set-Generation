#include "header.h"

const int one_d = 3, two_d = 3;

vector <string> generated_words;

class Trie {

    map <char, Trie *> book;

    bool isEnd;

public:

    Trie () { isEnd = true; }

    Trie * get_index (char ch) { return book[ch]; }

    bool is_last () { return isEnd; }

    void set_index (char ch) {
        
        book[ch] = new Trie;

        isEnd = false;
    }
};

Trie * generate_dict () {

    return new Trie;
}

void update_dict (Trie * head, string key) {

    Trie * trav = head;

    FOR (i, key.length ()) {

        if (!trav -> get_index (key[i])) {

            trav -> set_index (key[i]);
        }

        trav = trav -> get_index (key[i]);
    }
}

bool is_word (Trie * head, string key) {

    Trie * trav = head;

    FOR (i, key.length ()) {

        if (!trav -> get_index (key[i])) return false;

        trav = trav -> get_index (key[i]);
    }

    // should meet condition for word completeness => reach till leaf
    return true && trav -> is_last ();
}

void update_generated_words (string str) {

    bool success = true;

    FOR (i, generated_words.size ()) {

        if (generated_words[i] == str) {

            success = false;

            break;
        }
    }

    if (success) {

        generated_words.push_back (str);
    }
}

void generate_words_util (Trie * dict, char data[][two_d], bool visited[][two_d], int i, int j, string &str) {

    visited[i][j] = true;

    // db ("Adding", data[i][j], false);

    str += data[i][j];

    if (is_word (dict, str)) update_generated_words (str);

    for (int row = i - 1; row <= i + 1 && row < one_d; row ++) {

        for (int col = j - 1; col <= j + 1 && col < two_d; col ++) {

            if (row >= 0 && col >= 0 && !visited[row][col]) {

                generate_words_util (dict, data, visited, row, col, str);
            }
        }
    }

    str.erase (str.length () - 1);

    // db ("Cleared", "", true);

    visited[i][j] = false;
}

void generate_words (Trie * dict, char data[one_d][two_d]) {

    bool visited[one_d][two_d] = {{ false }};

    string str = "";

    FOR (i, one_d) {

        FOR (j, two_d) {

            // db ("Starting with", data[i][j], true);

            generate_words_util (dict, data, visited, i, j, str);
        }
    }
}

void print_words () {

    sort (generated_words.begin (), generated_words.begin () + generated_words.size ());

    FOR (i, generated_words.size ()) {

        cout << generated_words[i] << endl;
    }
}

int main () {

    freopen ("boggle.txt", "r", stdin);

    Trie * dict = generate_dict ();

    int _;
    cin >> _;

    FOR (i, _) {

        string str;
        cin >> str;

        update_dict (dict, str);
    }

    char data[one_d][two_d];

    FOR (i, one_d) FOR (j, two_d) cin >> data[i][j];

    generate_words (dict, data);

    print_words ();

    return 0;
}