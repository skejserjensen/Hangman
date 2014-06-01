#import <stdio.h>
#import <ctype.h>
#import <Foundation/NSString.h>

#import "wordlist.h"
#import "nsstringadditions.h"

@interface Hangman : NSObject
    - (bool)startGame;
    - (id)initWithWordListPath: (NSString*) listPath;
@end
