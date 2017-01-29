#include<stdio.h>
#include<stdlib.h>

static int const INVALID_INPUT = -1;
static int const VALID = 0;
static int const TOO_MANY_CHARACTERS = 1;
static int const WRONG_CHARACTER_AT_BEGIN_END = 2;
static int const TOO_MANY_CHARACTERS_IN_SEGMENT = 3;
static int const NON_NUMERIC_CHARACTER_IN_SEGMENT = 4;
static int const INVALID_CONTROL_NUMBER = 5;
static int const INVALID_CHECK_NUMBER = 6;

struct Segment {
    char *characters; // 12 max digits + \0 terminator
    int length;
};

typedef struct Segment segment;

struct SegmentArray {
    segment* segments;
    int length;
    int totalCharacterLength;
};

typedef struct SegmentArray segArray;

int main(int argc, char *argv[]) {
    int errorCode = VALID;

    char * input = malloc(sizeof(char) * 100);
    //char *input; // = "1677036253-1677036253";
    //provide scanf;
    printf("Provide input: \n");
    scanf("%s", input);

    if (input == NULL || *input == '\0') {
        printf("Input string invalid.");
        if(errorCode == VALID) errorCode = INVALID_INPUT;
    }

    int segArrayIx = 0;
    segArray *segmentArray = (segArray*)malloc(sizeof(segArray));
    segmentArray->segments = (segment*)malloc(sizeof(segment) * 100);
    segmentArray->segments->characters = (char*)malloc(sizeof(char) *100);
    segmentArray->segments->length = 0;
    segmentArray->length = 1;
    segmentArray->totalCharacterLength = 0;

    while (1) {
        segment *seg = segmentArray->segments + segArrayIx;
        if (*input == '\0') {
            seg->characters[seg->length] = '\0';
            break;
        }

        if (*input == '-') {
            seg->characters[seg->length] = '\0';
            segArrayIx++;
            seg = segmentArray->segments + segArrayIx;
            seg->characters = (char*)malloc(sizeof(char) * 100);
            seg->length = 0;
            segmentArray->length++;
        }
        else {
            seg->characters[seg->length] = *input;
            seg->length++; 
        }
        input++;
        segmentArray->totalCharacterLength++;
    }

    if (segmentArray->totalCharacterLength > 22) {
        if(errorCode == VALID) errorCode = TOO_MANY_CHARACTERS;
    }

    for (int i = 0; i < segmentArray->length; i++) {
        segment *seg = segmentArray->segments + i;
        if (seg->length == 0) {
            if(errorCode == VALID) errorCode = WRONG_CHARACTER_AT_BEGIN_END; // - at start or end of input
        }

        if (seg->length > 12) {
             if(errorCode == VALID)errorCode = TOO_MANY_CHARACTERS_IN_SEGMENT; // - too many characters in input
        }

        char* segmentCharacter = seg->characters;
        int segmentIntValue = 0;
        while(*segmentCharacter != '\0') {
            if (*segmentCharacter < '0' || *segmentCharacter > '9') {
                if(errorCode == VALID) errorCode = NON_NUMERIC_CHARACTER_IN_SEGMENT; // - non numeric values in segment
            }else{
                segmentIntValue = (segmentIntValue * 10) + ((*segmentCharacter) - '0');
            }

            segmentCharacter++;
        }

        int checkNum = segmentIntValue%10;
        int controlNum = segmentIntValue/10;
        int mp = 2;
        int sum = 0;

        while(controlNum != 0){
            sum += (controlNum % 10) * mp;

            mp++;

            if(mp>7) mp = 2;

            controlNum /= 10;
        }

        if((sum%11) == 0 || (sum%11)==1) if(errorCode == VALID) errorCode = INVALID_CONTROL_NUMBER; // non-valid control number
        if(checkNum != (11-(sum%11))) if(errorCode == VALID) errorCode = INVALID_CHECK_NUMBER; // non-valid check number
    }

    switch(errorCode){
        case INVALID_INPUT:
            printf("Input is invalid. Either empty or null");
            break;
        case VALID:
            printf("Valid");
            break;
        case TOO_MANY_CHARACTERS:
            printf("There are too many characters in input");
            break;
        case WRONG_CHARACTER_AT_BEGIN_END:
            printf("Input must not start with non-numeric character");
            break;
        case TOO_MANY_CHARACTERS_IN_SEGMENT:
            printf("Too many characters in segment");
            break;
        case NON_NUMERIC_CHARACTER_IN_SEGMENT:
            printf("Segment contains non-numeric character");
            break;
        case INVALID_CONTROL_NUMBER:
            printf("Invalid control number");
            break;
        case INVALID_CHECK_NUMBER:
            printf("Invalid check number");
            break;
    }

    printf("\n");

    return 0;
}