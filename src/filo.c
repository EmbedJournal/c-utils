#include <stddef.h>
#include <string.h>

#include <utils/filo.h>
#include <utils/utils.h>


void filo_init(filo_t *pfilo, void *buffer, unsigned elem_size, unsigned max_size)
{
    pfilo->buffer = buffer;
    pfilo->elem_size = elem_size;
    pfilo->max_size = max_size;
    pfilo->top = 0;
}

void filo_reset(filo_t *pfilo)
{
    pfilo->top = 0;
}

filo_t *filo_alloc(unsigned elem_size, unsigned max_size)
{
    filo_t *pfilo = safe_malloc(sizeof(filo_t));
    void *buffer = safe_malloc(elem_size * max_size);
    filo_init(pfilo, buffer, elem_size, max_size);
    return pfilo;
}

void filo_free(filo_t *pfilo)
{
    safe_free(pfilo->buffer);
    safe_free(pfilo);
}

int filo_push(filo_t *pfilo, void *elem)
{
    if (pfilo->top >= pfilo->max_size)
        return -1;
    memcpy(pfilo->buffer + (pfilo->elem_size * pfilo->top), elem, pfilo->elem_size);
    pfilo->top++;
    return 0;
}

int filo_pop(filo_t *pfilo, void *elem, bool remove)
{
    if (pfilo->top <= 0)
        return -1;
    memcpy(elem, pfilo->buffer + (pfilo->elem_size * (pfilo->top - 1)), pfilo->elem_size);
    if (remove)
        pfilo->top--;
    return 0;
}

unsigned filo_get_count(filo_t *pfilo)
{
    return pfilo->top;
}