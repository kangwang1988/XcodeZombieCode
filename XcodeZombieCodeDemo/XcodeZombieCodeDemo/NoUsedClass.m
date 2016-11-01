#import "NoUsedClass.h"
#import <Foundation/Foundation.h>

@implementation NoMethodUsedClass
- (instancetype)init {
  if (self = [super init]) {
    [self noUsedMethod];
  }
  return self;
}

- (void)noUsedMethod {
}
@end

@protocol NoUsedClassProtocol <NSObject>
- (void)doSomething;
@end

@interface NoUsedClass : NSObject
@end

@implementation NoUsedClass
- (void)noUsedClassTest {
}
@end
