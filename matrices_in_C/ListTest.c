#include <stdio.h>
#include <string.h>
#include "List.h"

void test_newList()
{
    List L = newList();
    if (L != NULL && length(L) == 0)
    {
        printf("test_newList passed\n");
    }
    else
    {
        printf("test_newList failed\n");
    }
}

void test_append()
{
    List L = newList();
    int data = 5;     // Example data, replace with your generic pointer data
    append(L, &data); // Use address of data
    if (*(int *)back(L) == 5 && length(L) == 1)
    { // Cast back(L) to int* before dereferencing
        printf("test_append passed\n");
    }
    else
    {
        printf("test_append failed\n");
    }
}

void test_prepend()
{
    List L = newList();
    int data = 5;      // Example data, replace with your generic pointer data
    prepend(L, &data); // Use address of data
    if (*(int *)front(L) == 5 && length(L) == 1)
    { // Cast front(L) to int* before dereferencing
        printf("test_prepend passed\n");
    }
    else
    {
        printf("test_prepend failed\n");
    }
}

void test_insertAfter()
{
    List L = newList();
    int data = 10;    // Example data, replace with your generic pointer data
    append(L, &data); // Use address of data
    moveFront(L);
    int newData = 20;         // Example data, replace with your generic pointer data
    insertAfter(L, &newData); // Use address of newData
    moveNext(L);
    if (*(int *)get(L) == 20)
    { // Cast get(L) to int* before dereferencing
        printf("test_insertAfter passed\n");
    }
    else
    {
        printf("test_insertAfter failed\n");
    }
}

void wordTest()
{
    char *words[35] = {"apple (سیب)",
                       "banana (موز)",
                       "orange (پرتقال)",
                       "pear (گلابی)",
                       "grape (انگور)",
                       "pineapple (آناناس)",
                       "strawberry (توت فرنگی)",
                       "blueberry (بلوبری)",
                       "raspberry (تمشک)",
                       "blackberry (بلک‌بری)",
                       "watermelon (هندوانه)",
                       "cantaloupe (خربزه)",
                       "honeydew (کنتالوپ)",
                       "peach (هلو)",
                       "plum (آلو)",
                       "apricot (زردآلو)",
                       "cherry (گیلاس)",
                       "lemon (لیمو)",
                       "lime (لیمو ترش)",
                       "coconut (نارگیل)",
                       "fig (انجیر)",
                       "nectarine (شفتالو)",
                       "olive (زیتون)",
                       "pomegranate (انار)",
                       "tangerine (نارنگی)",
                       "tomato (گوجه فرنگی)",
                       "avocado (آووکادو)",
                       "persimmon (خرمالو)",
                       "quince (به)",
                       "zucchini (کدو سبز)",
                       "eggplant (بادمجان)",
                       "cucumber (خیار)",
                       "squash (کدو)",
                       "pumpkin (کدو تنبل)",
                       "melon (طالبی)"};

    int numberOfWords = sizeof(words) / sizeof(char *);
    List L = newList();

    for (int i = 0; i < numberOfWords; i++)
    {
        // grab the first item and if index -1 OR if strcmp < 0 then insertBefore
        //      else moveNext
        moveFront(L);
        // printf("Findex: %d. Size of list: %d\n", findex(L), length(L));
        do
        {
            int index = findex(L);
            // int* myIndexPointer = malloc(sizeof(int));
            // *myIndexPointer = i;

            if (index == -1)
            {
                // printf("Appending word #%d: %s at end of list\n", i, words[i]);
                // append(L, myIndexPointer);
                append(L, words[i]);
                break;
            }
            char *listWord = (char *)get(L);

            // printf(
            //     // "Inside do loop for: %s. List word: %s. Findex: %d. (char "
            //     // "*)get(L): %s. get(L): %p.\n",
            //     words[i], listWord, findex(L), (char*)get(L), get(L));

            if (strcmp(words[i], listWord) < 0)
            {
                //printf("Inserting word #%d: %s before %s\n", i, words[i], listWord);

                // insertBefore(L, myIndexPointer);
                insertBefore(L, words[i]);
                break;
            }
            moveNext(L);
        } while (1);

        // printf("\n");
    }
    printf("Sorted Words:\n");

    for (moveFront(L); findex(L) >= 0; moveNext(L))
    {
        char *indexPtr = (char *)get(L);
        printf("%s\n", indexPtr);
    }
}

int main()
{
    test_newList();
    test_append();
    test_prepend();
    test_insertAfter();

    wordTest();

    return 0;
}
