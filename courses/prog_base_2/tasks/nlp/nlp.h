#ifndef NLP_H
#define NLP_H

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

typedef struct word_s word_t;

word_t *word_create(const char *str, size_t len);
size_t word_size(word_t *word);
void word_delete(word_t *word);
void word_print(word_t *word, FILE *file);
void word_dealloc_func(void *word);

typedef struct sentence_s sentence_t;

sentence_t *sentence_create(list_t *words);
sentence_t *sentence_create_str(const char *str, size_t len);
list_t *sentence_words(sentence_t *sentence);
void sentence_print(sentence_t *sentence, FILE *file);
void sentence_delete(sentence_t *sentence);
void sentence_dealloc_func(void *sentence);

typedef struct text_s text_t;

text_t *text_create(list_t *sentences);
text_t *text_create_str(const char *str, size_t len);
list_t *text_sentences(text_t *text);
void text_sort(text_t *text);
void text_print(text_t *text, FILE *file);
void text_delete(text_t *text);

#endif // NLP_H
