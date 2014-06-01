#import <Foundation/NSString.h>

#import "hangman.h"

int main (int argc, const char * argv[])
{
    NSString* wordListPath;

    if(argc == 2) {
        wordListPath = [[NSString alloc] 
            initWithCString: argv[1] encoding: [NSString defaultCStringEncoding]];
    }
    else {
        wordListPath = @"../data/wordlist";
    }
    Hangman *hangman = [[Hangman alloc] initWithWordListPath: wordListPath];
    [hangman startGame];

    return 0;
}
