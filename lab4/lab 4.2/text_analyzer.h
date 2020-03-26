#ifndef TEXT_ANALYZER_H
#define TEXT_ANALYZER_H

#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct text_properties text_properties;

struct text_properties {
    int total_number_of_characters;
    int total_number_of_letters;
    int total_number_of_sentences;
    int total_number_of_words;
    double avn_letters_in_word;
    double avn_words_in_sentence;
    char longest_word[BUFSIZ];
    char longest_sentence[BUFSIZ];
};


void analyze_text(text_properties *tp, FILE *text_file);

#endif