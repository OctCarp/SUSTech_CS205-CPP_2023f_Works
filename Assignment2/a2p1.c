//#define DEBUG

#ifdef DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PandoraBox {
    int item_count; // Number of items stored in the PandoraBox.
    int *item_size; // Array of item sizes in bytes.
    void *data;     // A type-agnostic pointer to store data.
} Panbox;

/*
A PandoraBox capable of storing various data types within a continuous memory space.

- item_count: Number of items stored in this box.
- item_size: An array of integers; item_size[i] represents the size (in bytes) of the i-th item in the box.
- data: A type-agnostic pointer, enabling interpretation of different data types by reading segments with varying lengths.
*/
#endif

/*=+=+=+=+=+=+=+=+=+=+=Your code starts from here=+=+=+=+=+=+=+=+=+=+=*/

void *mycpy(void *dst, const void *src, size_t size) {
    if (!dst || !src || size <= 0) { return NULL; }

    unsigned char *d = (unsigned char *) dst;
    const unsigned char *s = (const unsigned char *) src;

    while (size--) {
        *d++ = *s++;
    }

    return dst;
}

/*
Function: See memcpy in <string.h>

Notes:
- It is not a must to implement this function, but with it you can implement the following functions more easily.
*/

void *myset(void *dst, int n, size_t size) {
    if (!dst || size <= 0) { return NULL; }

    unsigned char *p = (unsigned char *) dst;
    unsigned char val = (unsigned char) n;

    while (size--) {
        *p++ = val;
    }

    return dst;
}

/*
Function: See memset in <string.h>

Notes:
- It is not a must to implement this function, but with it you can implement the following functions more easily.
*/

Panbox *create(int item_count, int item_size[]) {
    if (item_count < 0 || (item_count > 0 && !item_size)) {
        return NULL;
    }

    Panbox *pb = (Panbox *) calloc(1, sizeof(Panbox));
    if (!pb) { return NULL; }

    pb->item_count = item_count;
    if (pb->item_count == 0) {
        pb->item_size = NULL;
        pb->data = NULL;
        return pb;
    }

    int *new_item_size = (int *) calloc(1, item_count * sizeof(int));
    if (!new_item_size) {
        free(pb);
        return NULL;
    }

    mycpy(new_item_size, item_size, item_count * sizeof(int));
    pb->item_size = new_item_size;

    size_t sz = 0ULL;
    for (int i = 0; i < item_count; ++i) {
        if (item_size[i] <= 0) {
            free(pb->item_size);
            free(pb);
            return NULL;
        }
        sz += item_size[i];
    }
    void *data_ptr = (void *) calloc(1, sz);
    if (!data_ptr) {
        free(pb->item_size);
        free(pb);
        return NULL;
    }

    pb->data = data_ptr;
    myset(pb->data, 0, sz);

    return pb;
}


/*
Function: Create an empty PandoraBox with specified item counts and their respective sizes.

Parameters:
- item_count: The number of items to be stored in the PandoraBox.
- item_size: An array specifying the size (in bytes) of each item.

Returns:
A pointer to the created PandoraBox.

Note:
- You CAN create a Panbox with no initial items, i.e., item_count=0 and item_size=NULL.
- However, negative item_count is not supported, and item_size should not be NULL when item_count is non-zero.
- The size of any item should be positive.
- Make sure that the memory newly allocated is filled with 0s.
- You should return NULL immediately if any failure happens.
- Good news: GuTao guarantees that [item_size, item_size+item_count-1] is allocated in advance, unless item_size is NULL.
*/

void append(Panbox *panbox, void *value, int width) {
    if (!panbox || !value || width <= 0) { return; }

    size_t sz = 0ULL;
    for (int i = 0; i < panbox->item_count; ++i) {
        int cur_sz = panbox->item_size[i];
        if (cur_sz <= 0) { return; }
        sz += cur_sz;
    }
    void *new_data = (void *) realloc(panbox->data, sz + width);
    int *new_item_sz = (int *) realloc(panbox->item_size, (panbox->item_count + 1) * sizeof(int));

    if (!new_item_sz || !new_data) {
        return;
    }

    panbox->data = new_data;
    mycpy((unsigned char *) (panbox->data) + sz, value, width);

    panbox->item_size = new_item_sz;
    panbox->item_size[panbox->item_count++] = width;
}

/*
Function: Extend the memory of the PandoraBox to append an item.

Parameters:
- panbox: A pointer to the PandoraBox.
- value: A pointer to the data to be added to the PandoraBox.
- width: The size of the data in value (in bytes).

Note:
- You should not append this item if any failure happens.
- Good news: GuTao guarantees that [value, value+width-1] is allocated in advance, unless value is NULL.
*/

void write(Panbox *panbox, int item_id, void *value, int width) {
    if (!panbox || item_id < 0 || !value || width <= 0) { return; }
    if (!panbox->data || !panbox->item_size) { return; }
    if (item_id >= panbox->item_count) { return; }
    if (panbox->item_size[item_id] < width) { return; }

    size_t sz = 0ULL;
    for (int i = 0; i < item_id; ++i) {
        int cur_sz = panbox->item_size[i];
        if (cur_sz <= 0) { return; }
        sz += cur_sz;
    }
    unsigned char *ptr = (unsigned char *) value;
    unsigned char set_v = (ptr[width - 1] & 0x80) ? 0xff : 0;

    myset((unsigned char *) panbox->data + sz, set_v, panbox->item_size[item_id]);
    mycpy((unsigned char *) panbox->data + sz, value, width);
}

/*
Function: COPY the data stored in 'value' into the segment of the item with index item_id in the PandoraBox.

Parameters:
- panbox: A pointer to the PandoraBox.
- item_id: The index of the item in the PandoraBox where data will be written.
- value: A pointer to the data that needs to be written to the PandoraBox.
- width: The size of the data in value (in bytes).

Notes:
- If 'item_id' is out of valid bounds, the data won't be written.
- If the item size cannot hold all data in value, the data won't be written.
- If the width of value is smaller than the item size, the data will be placed in the lower address and padded with the highest bit.
- Example: inserting a 1-byte value into a 2-byte item: (0x7f -> 0x007f), (0xf7 -> 0xfff7).
- The item_size should not change in this function.
- You should not write the item if any failure happens.
- Good news: GuTao guarantees that [value, value+width-1] is allocated in advance, unless value is NULL.
*/

void *read(Panbox *panbox, int item_id) {
    if (!panbox || item_id < 0 || item_id >= panbox->item_count) { return NULL; }
    if (!panbox->data || !panbox->item_size) { return NULL; }
    if (panbox->item_size[item_id] <= 0) { return NULL; }

    size_t sz = 0ULL;
    for (int i = 0; i < item_id; ++i) {
        int cur_sz = panbox->item_size[i];
        if (cur_sz <= 0) { return NULL; }
        sz += cur_sz;
    }

    void *ret = (void *) calloc(1, panbox->item_size[item_id]);
    mycpy(ret, (unsigned char *) panbox->data + sz, panbox->item_size[item_id]);

    return ret;
}

/*
Function: COPY the item with index item_id from the PandoraBox into a newly allocated memory, and return a pointer to this memory.

Parameters:
- panbox: A pointer to the PandoraBox.
- item_id: The index of the item in the PandoraBox that should be read.

Returns:
A pointer to the newly allocated memory containing a copy of the specified item.

Notes:
- You should return NULL immediately if any failure happens.
*/

void destroy(Panbox *panbox) {
    if (!panbox) {
        return;
    }
    if (panbox->data) {
        free(panbox->data);
        panbox->data = NULL;
    }
    if (panbox->item_size) {
        free(panbox->item_size);
        panbox->item_size = NULL;
    }
    panbox->item_count = 0;
    free(panbox);
    panbox = NULL;
}

/*
Function: Deallocate the memory associated with the PandoraBox and its data.

Parameters:
- panbox: A pointer to the PandoraBox that should be destroyed.

Notes:
- This function should be used when the PandoraBox is no longer needed to prevent memory leak.
- You should check before freeing a pointer.
*/

void printc(void *value, int width) {
    if (!value || width <= 0) { return; }
    unsigned char *ptr = (unsigned char *) value;

    int hasPrint = 0;
    for (int i = 0; i < width; ++i) {
        char ch = ptr[i];
        if (32 < ch && ch < 127) {
            hasPrint = 1;
            putchar(ch);
            putchar(' ');
        } else if (ch < 0) {
            hasPrint = 1;
            putchar('-');
            putchar(' ');
        }
    }

    if (hasPrint) {
        putchar('\n');
    }
}

/*
Function: Print every 1 byte (char) in [value, value+width-1] as a character, split by a space.

Notes:
- Good news: GuTao guarantees that [value, value+width-1] is allocated in advance, unless value is NULL.
- If the value of the byte is in [0, 32] or equals to 127(Del), do not print anything(they are special characters).
- e.g., for an empty box with all 0, the destroy of this box will invoke printc(), but should not print anything.
- If the value of the byte is negative, print '-' instead.
- You should return immediately if any failure happens.
- Please print a `\n` before returning, unless you print nothing in this function.
*/

void printx(void *value, int width) {
    if (!value || width <= 0) { return; }
    unsigned char *ptr = (unsigned char *) value;

    printf("0x");
    for (int i = width - 1; i >= 0; i--) {
        printf("%02x", ptr[i]);
    }

    putchar('\n');
}

/*
Function: Print the value in [value, value+width-1] as a single hexadecimal, in format of 0x12345678.

Notes:
- Good news: GuTao guarantees that [value, value+width-1] is allocated in advance, unless value is NULL.
- You should return immediately if any failure happens.
- If the highest byte is less than 0x10, please output a leading 0, e.g., 0x0514.
- Leading zeros are OK, if *(value) = 0x000f, width = 2, then print 0x000f. (print even number of characters)
- If the item is full of 0s, please still print it. E.g., 0x0000.
- Please print a `\n` before returning.
*/
inline int char2int(char ch) {
    if ('0' <= ch && ch <= '9') { return ch - '0'; }
    if ('a' <= ch && ch <= 'f') { return ch - 'a' + 10; }
    return -1;
}

void hex2byte(void *dst, char *hex) {
    if (!dst || !hex) { return; }
    size_t len = strlen(hex);
    if (len <= 2) { return; }

    if (hex[0] != '0' || !(hex[1] == 'x' || hex[1] == 'X')) { return; }

    unsigned char *ptr = (unsigned char *) dst;
    for (size_t i = len - 1; i >= 2; i -= 2) {
        int il = 0;
        int ih = 0;
        if (i == 2) {
            il = char2int(hex[i]);
        } else {
            il = char2int(hex[i]);
            ih = char2int(hex[i - 1]);
        }
        if (il == -1 || ih == -1) { return; }

        *ptr++ = (unsigned char) (il + (ih << 4));
    }
}
/*
Function: For the given hex string "0x12345678", write 0x12345678 into dst.

Notes:
- The length of hex might be ODD, make sure to put all data into dst. For example, "0xfff"(12 bits) should be stored using 2 bytes as 0x0fff(different from write(), just add a padding 0 here).
- You should return immediately if any failure happens.
*/

/*=+=+=+=+=+=+=+=+=+=+=Your code ends here=+=+=+=+=+=+=+=+=+=+=*/
#ifdef DEBUG

void show_info(Panbox *p) {
    if (p != NULL) {
        printf("%d\n", p->item_count);
        for (int i = 0; i < p->item_count; i++) {
            printf("%d ", p->item_size[i]);
        }
        printf("\n");
    } else {
        printf("NULL\n");
    }
}

/*
Function: Display the basic information of given PandoraBox

Implemented by GuTao.
*/

Panbox *p = NULL;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        char op;
        scanf(" %c", &op);
        switch (op) {
            case 'C': {
                int item_count;
                scanf("%d", &item_count);
                int *item_size = (int *) malloc(item_count * sizeof(int));
                for (int i = 0; i < item_count; i++) {
                    scanf("%d", &item_size[i]);
                }
                p = create(item_count, item_size);
                free(item_size);
                break;
            }
            case 'D': {
                if (p != NULL) {
                    for (int i = p->item_count - 1; i >= 0; i--) {
                        void *data = read(p, i);
                        if (data != NULL) {
                            printc(data, p->item_size[i]);
                            free(data);
                        }
                    }
                }
                destroy(p);
                break;
            }
            case 'A': {
                int len;
                scanf("%d", &len);
                char *hex_str = (char *) malloc(len + 1);
                scanf("%s", hex_str);
                int num_of_byte = (strlen(hex_str) - 1) / 2;
                void *data = (void *) malloc(num_of_byte);
                hex2byte(data, hex_str);
                append(p, data, num_of_byte);
                free(hex_str);
                free(data);
                break;
            }
            case 'W': {
                int item_id;
                scanf("%d", &item_id);
                int len;
                scanf("%d", &len);
                char *hex_str = (char *) malloc(len + 1);
                scanf("%s", hex_str);
                int num_of_byte = (strlen(hex_str) - 1) / 2;
                void *data = (void *) malloc(num_of_byte);
                hex2byte(data, hex_str);
                write(p, item_id, data, num_of_byte);
                free(hex_str);
                free(data);
                break;
            }
            case 'R': {
                int item_id;
                scanf("%d", &item_id);
                int is_printc;
                scanf("%d", &is_printc);
                void *data = read(p, item_id);
                if (data != NULL) {
                    if (is_printc) {
                        printc(data, p->item_size[item_id]);
                    } else {
                        printx(data, p->item_size[item_id]);
                    }
                    free(data);
                }
                break;
            }
            case 'Q': {
                show_info(p);
                break;
            }
            default: {
                break;
            }
        }
    }
    return 0;
}

/*
Main function implemented by GuTao, you cannot rewrite one for yourself.

- Just for you to understand how the functions you implement would be invoked.
- Not exact the main function to test on OJ, this one does not check your error handling.
- You can test your functions on your PC with your own main().
- You may want to hack with your own main function, but this won't help you AC :)
*/
#endif