#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


double frequency(char c){
    switch (c){
        case('a' | 'A'): return 0.08167;
        case('b' | 'B'): return 0.01492;
        case('c' | 'C'): return 0.02782;
        case('d' | 'D'): return 0.04253;
        case('e' | 'E'): return 0.12702;
        case('f' | 'F'): return 0.02228;
        case('g' | 'G'): return 0.02015;
        case('h' | 'H'): return 0.06094;
        case('i' | 'I'): return 0.06966;
        case('j' | 'J'): return 0.00153;
        case('k' | 'K'): return 0.00772;
        case('l' | 'L'): return 0.04025;
        case('m' | 'M'): return 0.02406;
        case('n' | 'N'): return 0.06749;
        case('o' | 'O'): return 0.07507;
        case('p' | 'P'): return 0.01929;
        case('q' | 'Q'): return 0.00095;
        case('r' | 'R'): return 0.05987;
        case('s' | 'S'): return 0.06327;
        case('t' | 'T'): return 0.09056;
        case('u' | 'U'): return 0.02758;
        case('v' | 'V'): return 0.00978;
        case('w' | 'W'): return 0.02360;
        case('x' | 'X'): return 0.00150;
        case('y' | 'Y'): return 0.01974;
        case('z' | 'Z'): return 0.00074;
    }
    return 0;
}

double entropy(string text, int char_len){
    int letter_cnt = 0;
    int char_count[26];

    for(int i=0; i<26; i++){
        char_count[i]=0;
    }
    for(int i=0; text[i]!='\0'; i++){            //count poses fores emfanizetai o ka8e xarakthras
        switch (text[i]){
            case 'a': case 'A': char_count[0]++; break;
            case 'b': case 'B': char_count[1]++; break;
            case 'c': case 'C': char_count[2]++; break;
            case 'd': case 'D': char_count[3]++; break;
            case 'e': case 'E': char_count[4]++; break;
            case 'f': case 'F': char_count[5]++; break;
            case 'g': case 'G': char_count[6]++; break;
            case 'h': case 'H': char_count[7]++; break;
            case 'i': case 'I': char_count[8]++; break;
            case 'j': case 'J': char_count[9]++; break;
            case 'k': case 'K': char_count[10]++; break;
            case 'l': case 'L': char_count[11]++; break;
            case 'm': case 'M': char_count[12]++; break;
            case 'n': case 'N': char_count[13]++; break;
            case 'o': case 'O': char_count[14]++; break;
            case 'p': case 'P': char_count[15]++; break;
            case 'q': case 'Q': char_count[16]++; break;
            case 'r': case 'R': char_count[17]++; break;
            case 's': case 'S': char_count[18]++; break;
            case 't': case 'T': char_count[19]++; break;
            case 'u': case 'U': char_count[20]++; break;
            case 'v': case 'V': char_count[21]++; break;
            case 'w': case 'W': char_count[22]++; break;
            case 'x': case 'X': char_count[23]++; break;
            case 'y': case 'Y': char_count[24]++; break;
            case 'z': case 'Z': char_count[25]++; break;
        }
    }

    for(int i=0; i<=25; i++){
        letter_cnt += char_count[i];
    }
    double char_frequency_cnt[26];
    for(int i=0; i<=25; i++){
        char_frequency_cnt[i] = double(char_count[i]) / letter_cnt ;
    }

    double entropy = 0.0;
    for(int i=0; i<=25; i++){
        entropy -= char_frequency_cnt[i] * log(frequency(i+'a'));
    }
    return entropy;
}

void decode(string decar[26], string a, int fsize, int i){
    decar[i] = "";
    for(int j=0 ; j < fsize ; j++){
        if(a[j] >= 'A' and a[j] <='Z'){                     //diavasma gia kefalaia
            if(a[j]+i>'Z') decar[i] += a[j] + i-26;
            else decar[i] += a[j]+i;
        }
        else if(a[j] >= 'a' and a[j] <= 'z'){               //diavasma gia mikra
            if(a[j] + i >'z') decar[i] += a[j] + i-26;
            else decar[i] += a[j]+i;
        }
        else decar[i] += a[j];
    }
    return;
}

int main(int argc, char* argv[]){
    string filename = argv[1];
    ifstream text(filename);
    stringstream buffer;
    buffer << text.rdbuf();
    string a = buffer.str();

    double entropy_array[26];
    string decar[26];

    for(int i=0;i<26;i++){
        int fsize = a.length();
        decode(decar, a, fsize, i);
        entropy_array[i] = entropy(decar[i],fsize);
    }
    double min_entropy = entropy_array[0];
    int min_i = 0;
    for(int i = 0; i <= 25; i++) {
        if(entropy_array[i] < min_entropy){
            min_entropy = entropy_array[i];
            min_i = i;
        }
    }
    cout << decar[min_i] << endl;
}
