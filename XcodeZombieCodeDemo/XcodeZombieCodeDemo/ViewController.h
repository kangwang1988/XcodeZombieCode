//
//  ViewController.h
//  KWHelper-clang
//
//  Created by KyleWong on 11/10/2016.
//  Copyright © 2016 KyleWong. All rights reserved.
//

#import <UIKit/UIKit.h>

#define kNotificationViewControllerDidLoad @"kNotificationViewControllerDidLoad"
@class ViewController;

@protocol ViewControllerDelegate <NSObject>
- (void)viewController:(ViewController *)vc execFunc:(NSInteger)aFunc;
@end

@interface ViewController : UIViewController
@property(nonatomic, weak) id<ViewControllerDelegate> delegate;
+ (instancetype)sharedInstance;
- (void)noBodyInterface;
- (id)initWithRootViewControllerURL:(NSString *)url;
- (void)openURL:(NSString *)url;
@end
