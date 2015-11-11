#import "nsstringadditions.h"

@implementation NSMutableString (NSStringAdditions)
    - (NSMutableString*) initWithCharacter: (char) aChar length: (int) aLength {
        NSAssert(aLength > 0, @"initWithCharacter: length must be above zero");

        //The cString does not need to be terminated as it is copied by index
        unichar cString[aLength];
        for(int index = 0; index < aLength; index++)
            cString[index] = aChar;
        return [self initWithCharacters: cString length: aLength];
    }
@end
