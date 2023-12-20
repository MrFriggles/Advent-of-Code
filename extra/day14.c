#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Puzzle input path (should be within build dir)
#define FIRST_INPUT "./input/first"

// Constants
const char EMPTY_SPACE = '.';
const char BOULDER = 'O';
const char BLOCKADE = '#';

// Global variables for later use
static size_t g_fileSize = 0;
static int g_inputWidth = -1;
static int g_inputHeight = -1;

typedef struct BoulderLinkedListNode
{
    struct BoulderLinkedListNode *parent;
    struct BoulderLinkedListNode *child;
    char type;
} BoulderLinkedListNode;

typedef struct BoulderLinkedList
{
    int size;
    BoulderLinkedListNode *start;
    BoulderLinkedListNode *end;
    BoulderLinkedListNode *cursor;
} BoulderLinkedList;


/*
 * Calulate the width of the puzzle's input\
 * by counting how many '\n' chars we see.
 * Could just use getline() ?
 */
int widthOfInput(char *PuzzleInput)
{
    if (PuzzleInput == NULL)
    {
        return -1;
    }

    int count = 0;
    char c;
    while ((c = *(PuzzleInput+count)) != '\n')
    {
        if (c == '\0')
        {
            // Unable to determine width
            return -1;
        }

        count++;
    }

    g_inputWidth = count;

    return count;
}


/*
 *
 */ 
int heightOfInput(char *PuzzleInput)
{
    if (PuzzleInput == NULL)
    {
        return -1;
    }

    int width = widthOfInput(PuzzleInput);
    if (width > 0)
    {
        // XXX Grossly assuming square file...
        g_inputHeight = (g_fileSize / width) - 1;
        return g_inputHeight;
    }
    else
    {
        return -1;
    }
}

void deinitLinkedListArray(BoulderLinkedList *LinkedList)
{
    for (int i = 0; i < g_inputWidth; ++i)
    {
        for (BoulderLinkedListNode *cursor = LinkedList[i].end->parent; cursor != NULL; cursor = cursor->parent)
        {
            free(cursor->child);
        }

        free(LinkedList[i].start);
    }
}

void initLinkedListArray(char *PuzzleInput, BoulderLinkedList *LinkedList)
{
    BoulderLinkedListNode *cursor = NULL;
    for (int i = 0; i < g_inputWidth; ++i)
    {
        LinkedList[i].start = malloc(sizeof(BoulderLinkedListNode));
        
        ++LinkedList[i].size;
        cursor = LinkedList[i].start;
        cursor->type = PuzzleInput[i];

        //// 
        // Input puzzle still contains newline characters from when we read in the file
        int newline_offset = 1;
        ////
        for (int j = i + g_inputWidth; j < (g_inputWidth * g_inputHeight); j += g_inputWidth)
        {
            cursor->child = malloc(sizeof(BoulderLinkedListNode));
            ++LinkedList[i].size;

            cursor->child->parent = cursor;
            cursor = cursor->child;
            cursor->type = PuzzleInput[j + newline_offset++];
        }

        LinkedList[i].end = cursor;
    }
}

void rollColumnUp(BoulderLinkedList *LinkedList)
{
    for (BoulderLinkedListNode *cursor = LinkedList->start; cursor != NULL; cursor = cursor->child)
    {
        if (cursor->type == BOULDER)
        {
            if (cursor == LinkedList->start)
            {
                continue;
            }

            BoulderLinkedListNode *tmp_cursor = cursor;
            while (tmp_cursor->parent != NULL && tmp_cursor->parent->type == EMPTY_SPACE)
            {
                tmp_cursor = tmp_cursor->parent;
            }

            if (tmp_cursor == cursor)
            {
                continue;
            }
            
            if (tmp_cursor->parent == NULL)
            {
                // At start
                // Pull cursor out sorting child and parent first
                cursor->parent->child = cursor->child;
                cursor->child->parent = cursor->parent;

                tmp_cursor->parent = cursor;
                cursor->child = tmp_cursor;
                cursor->parent = NULL;

                LinkedList->start = cursor;
            }
            else if (cursor->child == NULL)
            {
                // At the end
                cursor->parent->child = NULL;
                LinkedList->end = cursor->parent;

                tmp_cursor->parent->child = cursor;
                cursor->parent = tmp_cursor->parent;

                tmp_cursor->parent = cursor;
                cursor->child = tmp_cursor;
            }
            else
            {
                // Swap them as they're adjacent
                cursor->parent->child = cursor->child;
                cursor->child->parent = cursor->parent;

                tmp_cursor->parent->child = cursor;
                cursor->parent = tmp_cursor->parent;

                tmp_cursor->parent = cursor;
                cursor->child = tmp_cursor;
            }
        }
    }
}

int findColumnLoad(BoulderLinkedList *LinkedList)
{
    int column_load = 0;
    BoulderLinkedListNode *cursor = LinkedList->start;
    for (int i = g_inputWidth; i > 0; --i) // Should be 100... But should make better checks so we don't somehow null-dereference
    {
        if (cursor->type == BOULDER)
        {
            column_load += i;
        }

        cursor = cursor->child;
    }

    return column_load;
}

int findTotalLoad(char *PuzzleInput)
{
    if (PuzzleInput == NULL)
    {
        return -1;
    }

    printf("height: %d\n", heightOfInput(PuzzleInput));
    printf("width: %d\n", g_inputWidth);

    // Make array of boulder linked lists with width of input width
    BoulderLinkedList *boulder_linked_list_array = calloc(g_inputWidth, sizeof(BoulderLinkedList));
    initLinkedListArray(PuzzleInput, boulder_linked_list_array);

    int total_load = 0;
    for (int i = 0; i < g_inputWidth; ++i)
    {
        BoulderLinkedListNode *cursor = boulder_linked_list_array[i].start;
        printf("Old column %d: ", i + 1);
        while (cursor != NULL)
        {
            printf("%c", cursor->type);
            cursor = cursor->child;
        }
        printf("\n");

        rollColumnUp(&boulder_linked_list_array[i]);

        cursor = boulder_linked_list_array[i].start;
        printf("New column %d: ", i + 1);
        while (cursor != NULL)
        {
            printf("%c", cursor->type);
            cursor = cursor->child;
        }
        printf("\n\n");

        /*
         * ### PART ONE ###
         */
        total_load += findColumnLoad(&boulder_linked_list_array[i]);
    }

    deinitLinkedListArray(boulder_linked_list_array);
    free(boulder_linked_list_array);
    return total_load;
}

int main(void)
{
    FILE *fp = fopen(FIRST_INPUT, "r");
    if (fp == NULL)
    {
        return -1;
    }
    
    if (fseek(fp, 0L, SEEK_END) == 0)
    {
        g_fileSize = ftell(fp);
        rewind(fp);
    }
    else
    {
        fclose(fp);
        return -1;
    }

    char *file_contents = malloc(g_fileSize + 1);
    size_t rc = fread(file_contents, sizeof(*file_contents), g_fileSize, fp);
    if (rc != g_fileSize)
    {
        free(file_contents);
        fclose(fp);
        return -1;
    }

    file_contents[g_fileSize] = '\0';

    int total_load = findTotalLoad(file_contents);
    printf("Total load: \t%d\n", total_load);

    free(file_contents);
    fclose(fp);

    return 0;

}
