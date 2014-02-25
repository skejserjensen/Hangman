#import "nsstringadditions.h"

@implementation NSString (NSStringAdditions)
    - (NSString*) initWithCharacter: (char) aChar length: (int) aLength {
        //A string must be of length 1 or more
        assert(aLength > 0);

        //We built a cString containing only the char and is properly terminated
        char cString[aLength+1];
        for(int index = 0; index < aLength; index++)
            cString[index] = aChar;
        cString[aLength] = '\0';

        //Finally we can create a string with only aChar aLength times
        return [NSMutableString stringWithFormat: @"%s", cString];
    }
@end
