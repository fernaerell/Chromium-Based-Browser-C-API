#ifndef PAGES_H
#define PAGES_H

#include <stddef.h>

#include "cbbapi/browser/page/page.h"

typedef struct Pages
{
    size_t length;
    size_t capacity;
    Page** data;
} Pages;

Pages* pages_create();

int pages_add(Pages* pages, Page* page);

size_t pages_get_length(Pages* pages);

Page* pages_get_page(Pages* pages, size_t index);

void pages_free(Pages* pages);

int pages_shrink(Pages* pages);

#endif