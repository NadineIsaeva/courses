#include "nlp.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const char *strnchr(const char *str, char ch, size_t num) {
    for (size_t i = 0; i < num; i++)
        if (str[i] == ch)
            return str + i;
    return NULL;
}

struct word_s {
    char *str;
};

word_t *word_create(const char *str, size_t len) {
    word_t *word = malloc(sizeof(word_t));
    word->str = malloc((len + 1) * sizeof(char));
    memcpy(word->str, str, len * sizeof(char));
    word->str[len] = '\0';
    return word;
}

size_t word_size(word_t *word) {
    return strlen(word->str);
}

void word_print(word_t *word, FILE *file) {
    fprintf(file, "%s", word->str);
}

void word_delete(word_t *word) {
    free(word->str);
    free(word);
}

void word_dealloc_func(void *word) {
    word_delete(word);
}

struct sentence_s {
    list_t *words;
};

sentence_t *sentence_create(list_t *words) {
    sentence_t *sentence = malloc(sizeof(sentence));
    sentence->words = words;
    return sentence;
}

sentence_t *sentence_create_str(const char *str, size_t len) {
    list_t *words = list_create(word_dealloc_func);

    const char *it = str;
    while (1) {
        const char *endIt = strnchr(it, ' ', len - (it - str));
        endIt = endIt ? endIt : strnchr(it, '\n', len - (it - str));
        endIt = endIt ? endIt : str + len;

        word_t *newWord = word_create(it, endIt - it);
        if (word_size(newWord) > 0)
            list_push(words, newWord);

        if (((endIt + 1) - str) < len)
            it = endIt + 1;
        else
            break;
    }

    return sentence_create(words);
}

list_t *sentence_words(sentence_t *sentence) {
    return sentence->words;
}

void sentence_print(sentence_t *sentence, FILE *file) {
    for (size_t i = 0; i < list_size(sentence->words); ++i) {
        word_print(list_get(sentence->words, i), file);
        if (i != list_size(sentence->words) - 1)
            fprintf(file, ",");
    }
}

void sentence_delete(sentence_t *sentence) {
    list_delete(sentence->words);
    free(sentence);
}

void sentence_dealloc_func(void *sentence) {
    sentence_delete(sentence);
}

struct text_s {
    list_t *sentences;
};

text_t *text_create(list_t *sentences) {
    text_t *text = malloc(sizeof(text_t));
    text->sentences = sentences;
    return text;
}

text_t *text_create_str(const char *str, size_t len) {
    list_t *sentences = list_create(sentence_dealloc_func);

    const char *it = str;
    while (1) {
        const char *endIt = strnchr(it, '.', len - (it - str));
        endIt = endIt ? endIt : str + len;

        sentence_t *newSentence = sentence_create_str(it, endIt - it);
        if (list_size(newSentence->words) > 0)
            list_push(sentences, newSentence);

        if (((endIt + 1) - str) < len)
            it = endIt + 1;
        else
            break;
    }

    return text_create(sentences);
}

list_t *text_sentences(text_t *text) {
    return text->sentences;
}

void text_sort(text_t *text) {
    for (size_t i = 0; i < list_size(text->sentences); ++i) {
        for (size_t j = 0; j < list_size(((sentence_t *)list_get(text->sentences, i))->words) - 1; ++j) {
            for (size_t k = 0; k < list_size(((sentence_t *)list_get(text->sentences, i))->words) - j - 1; ++k) {
                if (word_size(list_get(((sentence_t *)list_get(text->sentences, i))->words, k)) > word_size(list_get(((sentence_t *)list_get(text->sentences, i))->words, k + 1))) {
                    word_t *word = list_get(((sentence_t *)list_get(text->sentences, i))->words, k);
                    list_put(((sentence_t *)list_get(text->sentences, i))->words, list_get(((sentence_t *)list_get(text->sentences, i))->words, k + 1), k);
                    list_put(((sentence_t *)list_get(text->sentences, i))->words, word, k + 1);
                }
            }
        }
    }
}

void text_print(text_t *text, FILE *file) {
    for (size_t i = 0; i < list_size(text->sentences); ++i) {
        sentence_print(list_get(text->sentences, i), file);
        fprintf(file, "\n");
    }
}

void text_delete(text_t *text) {
    list_delete(text->sentences);
    free(text);
}
