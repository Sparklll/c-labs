#include <string.h>
#include <ctype.h>
#include "text_analyzer.h"


void analyze_text(text_properties *tp, FILE *text_file) {
    tp->avn_letters_in_word = 0;
    tp->avn_words_in_sentence = 0;

    int num_of_characters = 0;
    int num_of_letters = 0;
    int num_of_sentences = 0;
    int num_of_words = 0;
    char longest_sentence[BUFSIZ];
    char longest_word[BUFSIZ];

    int ch;
    int prev_punct_ch;
    int current_pos_on_word = FALSE;
    int prev_pos_on_punct = FALSE;
    int temp_sentence_buffer_index = 0;
    int temp_word_buffer_index = 0;
    char temp_sentence_buffer[BUFSIZ];
    char temp_word_buffer[BUFSIZ];

    /* it's strange parsing  but it works :D */
    while ((ch = fgetc(text_file)) != EOF) {
        if (isalnum(ch)) {
            if (prev_pos_on_punct) {
                prev_pos_on_punct = FALSE;
                if (prev_punct_ch == '-' || (!isupper(ch) && prev_punct_ch == '.') || prev_punct_ch == '\'') {
                    temp_word_buffer[temp_word_buffer_index] = prev_punct_ch;
                    temp_word_buffer_index++;
                } else if (prev_punct_ch == ':' ||
                           prev_punct_ch == '(' ||
                           prev_punct_ch == ')' ||
                           prev_punct_ch == '{' ||
                           prev_punct_ch == '}' ||
                           prev_punct_ch == '"' ||
                           prev_punct_ch == '<' ||
                           prev_punct_ch == '>' ||
                           prev_punct_ch == '|' ||
                           prev_punct_ch == '\\' ||
                           prev_punct_ch == '/' ||
                           prev_punct_ch == '@' ||
                           prev_punct_ch == '#' ||
                           prev_punct_ch == '$' ||
                           prev_punct_ch == '%' ||
                           prev_punct_ch == '^' ||
                           prev_punct_ch == '&' ||
                           prev_punct_ch == '*' ||
                           prev_punct_ch == '+' ||
                           prev_punct_ch == '-' ||
                           prev_punct_ch == '~'
                        ) {
                    /* stub */
                } else {
                    if (current_pos_on_word) {
                        temp_word_buffer[temp_word_buffer_index] = '\0';
                        if (strlen(temp_word_buffer) > strlen(longest_word)) {
                            memcpy(longest_word, temp_word_buffer, strlen(temp_word_buffer) + 1);
                        }
                        temp_word_buffer_index = 0;
                        num_of_words++;
                    }


                    temp_sentence_buffer_index = 0;
                    num_of_sentences++;
                }
            }

            if (!current_pos_on_word) {
                current_pos_on_word = TRUE;
            }
            temp_sentence_buffer[temp_sentence_buffer_index] = ch;
            temp_word_buffer[temp_word_buffer_index] = ch;

            temp_sentence_buffer_index++;
            temp_word_buffer_index++;
            num_of_letters++;

        } else if (ispunct(ch)) {
            prev_pos_on_punct = TRUE;
            prev_punct_ch = ch;
            temp_sentence_buffer[temp_sentence_buffer_index] = ch;
            temp_sentence_buffer_index++;
        } else if (isspace(ch)) {
            if (isblank(ch)) {
                if (prev_pos_on_punct) {
                    prev_pos_on_punct = FALSE;
                    if (prev_punct_ch == '.' ||
                        prev_punct_ch == '?' ||
                        prev_punct_ch == '!' ||
                        prev_punct_ch == ';'
                            ) {

                        temp_sentence_buffer[temp_sentence_buffer_index] = '\0';
                        if (strlen(temp_sentence_buffer) > strlen(longest_sentence)) {
                            memcpy(longest_sentence, temp_sentence_buffer, strlen(temp_sentence_buffer) + 1);
                        }
                        num_of_sentences++;
                        temp_sentence_buffer_index = 0;
                    }
                }
                if (current_pos_on_word) {
                    current_pos_on_word = FALSE;
                    temp_word_buffer[temp_word_buffer_index] = '\0';
                    if (strlen(temp_word_buffer) > strlen(longest_word)) {
                        memcpy(longest_word, temp_word_buffer, strlen(temp_word_buffer) + 1);
                    }
                    temp_word_buffer_index = 0;
                    num_of_words++;
                }

                temp_sentence_buffer[temp_sentence_buffer_index] = ch;
                temp_sentence_buffer_index++;
            }
        }
        num_of_characters++;
    }

    /* check last sentence and word after exiting the loop */
    if (prev_pos_on_punct) {
        if (prev_punct_ch == '.' ||
            prev_punct_ch == '?' ||
            prev_punct_ch == '!' ||
            prev_punct_ch == ';'
                ) {

            temp_sentence_buffer[temp_sentence_buffer_index] = '\0';
            if (strlen(temp_sentence_buffer) > strlen(longest_sentence)) {
                memcpy(longest_sentence, temp_sentence_buffer, strlen(temp_sentence_buffer) + 1);
            }
            num_of_sentences++;
        }
    }
    if (current_pos_on_word) {
        current_pos_on_word = FALSE;
        temp_word_buffer[temp_word_buffer_index] = '\0';
        if (strlen(temp_word_buffer) > strlen(longest_word)) {
            memcpy(longest_word, temp_word_buffer, strlen(temp_word_buffer) + 1);
        }
        temp_word_buffer_index = 0;
        num_of_words++;
    }



    /* fill in the structure fields */
    tp->total_number_of_characters = num_of_characters;
    tp->total_number_of_sentences = num_of_sentences;
    tp->total_number_of_words = num_of_words;
    tp->total_number_of_letters = num_of_letters;
    if (num_of_words != 0) {
        tp->avn_letters_in_word = (double) num_of_letters / num_of_words;
    }
    if (num_of_sentences != 0) {
        tp->avn_words_in_sentence = (double) num_of_words / num_of_sentences;
    }
    memcpy(tp->longest_word, longest_word, strlen(longest_word) + 1);
    memcpy(tp->longest_sentence, longest_sentence, strlen(longest_sentence) + 1);

}