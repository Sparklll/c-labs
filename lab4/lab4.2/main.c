#include <stdio.h>
#include "text_analyzer.h"


int main() {
    /* Only english texts */
    FILE *text_file = fopen("../text.txt", "r");
    if (text_file == NULL) {
        puts("Unable to open file.");
        return 1;
    }
    text_properties tp;
    analyze_text(&tp, text_file);

    printf("Total number of characters : %d\n", tp.total_number_of_characters);
    printf("Total number of letters : %d\n", tp.total_number_of_letters);
    printf("Total number of words : %d\n", tp.total_number_of_words);
    printf("Total number of sentences : %d\n", tp.total_number_of_sentences);
    printf("Average number of letters in a word : %0.2f\n", tp.avn_letters_in_word);
    printf("Average number of words in sentence : %0.2f\n", tp.avn_words_in_sentence);
    printf("The longest word in the text : %s\n", tp.longest_word);
    printf("The longest sentence in the text : %s\n", tp.longest_sentence);

    fclose(text_file);
    return 0;
}
