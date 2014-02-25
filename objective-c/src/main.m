#import <Foundation/NSString.h>

#import "hangman.h"

/*
 * NOTE: the current version of hangman in Objective-C manages memory manually, and
 * in a horrible manager as I plan to change memory management in the program to use Arc
 * as soon as compilling the nessesary dependencies on Arch Linux becomes less of a 
 * headache.
 */

int main (int argc, const char * argv[])
{
    NSString* wordListPath;

    if(argc == 2) {
        wordListPath = [[NSString alloc] 
            initWithCString: argv[1] encoding: [NSString defaultCStringEncoding]];
    }
    else {
        wordListPath = [[NSString alloc] initWithString: @"../data/wordlist"];
    }
    Hangman *hangman = [[Hangman alloc] initWithWordListPath: wordListPath];
    [hangman startGame];

    [hangman release];
    [wordListPath release];
    return 0;
}
