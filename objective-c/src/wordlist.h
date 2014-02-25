#import <unistd.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSString.h>

@interface WordList : NSObject
    - (NSString*)getRandomWord;
    - (id)initWithWordListPath: (NSString*) listPath;
@end
