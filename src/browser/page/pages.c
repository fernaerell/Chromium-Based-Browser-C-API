#include "cbbapi/browser/page/pages.h"
#include <stdlib.h>

Pages* pages_create()
{
    Pages* pages = malloc(sizeof(Pages));
    if(!pages) return NULL;
    pages->capacity = 0;
    pages->length = 0;
    pages->data = NULL;
    return pages;
}

int pages_add(Pages* pages, Page* page)
{
    if(!pages || !page) return 0;
    if(pages->length >= pages->capacity)
    {
        size_t new_capacity = (pages->capacity == 0) ? 2 : pages->capacity * 2;
        Page** data_temp = realloc(pages->data, new_capacity * sizeof(Page*));
        if(!data_temp) return 0;
        pages->data = data_temp;
        pages->capacity = new_capacity;
    }
    pages->data[pages->length++] = page;
    return 1;
}

size_t pages_get_length(Pages* pages)
{
    if(!pages) return 0;
    return pages->length;
}

Page* pages_get_page(Pages* pages, size_t index)
{
    if(!pages || index >= pages->length) return NULL;
    return pages->data[index];
}

void pages_free(Pages* pages)
{
    if(!pages) return;
    if(pages->data)
    {
        for(size_t i = 0; i < pages->length; i++) page_free(pages->data[0]);
        free(pages->data);
    }
    free(pages);
}

int pages_shrink(Pages* pages)
{
    if(!pages) return 0;
    if(pages->length == 0)
    {
        pages_free(pages);
        return 1;
    }
    Page** data_temp = realloc(pages->data, pages->length * sizeof(Page*));
    if(!data_temp) return 0;
    pages->data = data_temp;
    pages->capacity = pages->length;
    return 1;
}