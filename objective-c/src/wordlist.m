#include "wordlist.h"

//Could not find a header file containing the function so.....
extern uint32_t arc4random();

@implementation WordList

    /** Instance variables **/
    NSString* wordListPath;
    NSArray* linesInWordList;
    unsigned int wordListLength;

    /** Constructor **/
    - (id)initWithWordListPath: (NSString*) listPath {
        self = [super init];
        wordListPath = listPath;

        //Checks if the word list exists, and if not terminate
        if(access([listPath UTF8String], R_OK) != 0) {
            printf("ERROR: wordlist mssing, terminating\n"); 
            exit(-1);
        }

        //Reads the file into an array to find the length and extract words
        NSString *entireFileInString = [NSString stringWithContentsOfFile: listPath 
                                                 encoding: NSASCIIStringEncoding error: NULL];
        linesInWordList = [entireFileInString componentsSeparatedByString: @"\n"];
        wordListLength = [linesInWordList count];
        return self;
    }

    /** Destructor **/
    -(void) dealloc {
        [super dealloc];
        [wordListPath release];
        [linesInWordList release];
    }

    /** Public methods **/
    - (NSString*)getRandomWord {
        int randomIndex = arc4random() % wordListLength;
        return [linesInWordList objectAtIndex: randomIndex];
    }
@end
