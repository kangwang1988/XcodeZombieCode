//
//  ViewController.m
//  KWHelper-clang
//
//  Created by KyleWong on 11/10/2016.
//  Copyright © 2016 KyleWong. All rights reserved.
//

#import "ViewController.h"
#include <vector>
#include <string>
using namespace std;

@interface ViewController ()

@end
ViewController *sVc;
@implementation ViewController
+ (instancetype)sharedInstance {
  static dispatch_once_t onceToken;
  dispatch_once(&onceToken, ^{
    sVc = [[self alloc] init];
  });
  return sVc;
}

- (void)viewDidLoad {
  [super viewDidLoad];
  [self.view setBackgroundColor:[UIColor redColor]];
  [[NSNotificationCenter defaultCenter]
      postNotificationName:kNotificationViewControllerDidLoad
                    object:nil];
  [[NSNotificationCenter defaultCenter]
      addObserver:self
         selector:@selector(onAppBecomeActiveNotification:)
             name:UIApplicationDidBecomeActiveNotification
           object:nil];
//  [self performSelector:@selector(func1) withObject:nil afterDelay:1];
  [self performSelector:@selector(func2) withObject:nil afterDelay:1];
  // Do any additional setup after loading the view, typically from a nib.
  dispatch_async(dispatch_get_main_queue(), ^{
    [self funcDispatchAsync];

  });
}

- (id)initWithRootViewControllerURL:(NSString *)url {
  return nil;
}

- (void)openURL:(NSString *)url {
}

- (void)didReceiveMemoryWarning {
  [super didReceiveMemoryWarning];
  dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(5 * NSEC_PER_SEC)),
                 dispatch_get_main_queue(), ^{
                   [self funcDispatchAfter];
                 });
  // Dispose of any resources that can be recreated.
}

- (void)func1 {
  NSInteger x = 100;
  if ([self.delegate respondsToSelector:@selector(viewController:execFunc:)])
    [self.delegate viewController:self execFunc:1];
}

- (void)func2 {
  NSInteger x = 100;
  if ([self.delegate respondsToSelector:@selector(viewController:execFunc:)])
    [self.delegate viewController:self execFunc:2];
}

- (void)func3 {
  NSInteger x = 100;
  if ([self.delegate respondsToSelector:@selector(viewController:execFunc:)])
    [self.delegate viewController:self execFunc:3];
}

- (void)funcDispatchAsync {
  NSInteger x = 100;
}

- (void)funcDispatchAfter {
  NSInteger x = 100;
}

- (void)onAppBecomeActiveNotification:(NSNotification *)aNotification {
  NSLog(@"");
}
@end
