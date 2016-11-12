//
//  AppDelegate.m
//  KWHelper-clang
//
//  Created by KyleWong on 11/10/2016.
//  Copyright © 2016 KyleWong. All rights reserved.
//

#import "AppDelegate.h"
#import "NoUsedClass.h"
#import "ViewController.h"
@interface AppDelegate () <ViewControllerDelegate>
@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application
    didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  // Override point for customization after application launch.
  ViewController *vc = [ViewController new]; //[[ViewController alloc] init];
  [vc setDelegate:self];
  [ViewController sharedInstance];
  [self setWindow:[[UIWindow alloc]
                      initWithFrame:CGRectMake(
                                        0, 0,
                                        [UIScreen mainScreen].bounds.size.width,
                                        [UIScreen mainScreen]
                                            .bounds.size.height)]];
  [self.window setRootViewController:vc];
  [self.window makeKeyAndVisible];
  [[NSNotificationCenter defaultCenter]
      addObserver:self
         selector:@selector(onViewControllerDidLoadNotification:)
             name:kNotificationViewControllerDidLoad
           object:nil];
  [[ViewController alloc]
      initWithRootViewControllerURL:@"PREF://LoginViewController"];
  [[ViewController alloc] openURL:@"PREF://HomeViewController"];
  [[NoMethodUsedClass alloc] init];
  return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
  // Sent when the application is about to move from active to inactive state.
  // This can occur for certain types of temporary interruptions (such as an
  // incoming phone call or SMS message) or when the user quits the application
  // and it begins the transition to the background state.
  // Use this method to pause ongoing tasks, disable timers, and invalidate
  // graphics rendering callbacks. Games should use this method to pause the
  // game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
  // Use this method to release shared resources, save user data, invalidate
  // timers, and store enough application state information to restore your
  // application to its current state in case it is terminated later.
  // If your application supports background execution, this method is called
  // instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
  // Called as part of the transition from the background to the active state;
  // here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
  // Restart any tasks that were paused (or not yet started) while the
  // application was inactive. If the application was previously in the
  // background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
  // Called when the application is about to terminate. Save data if
  // appropriate. See also applicationDidEnterBackground:.
}

- (void)onViewControllerDidLoadNotification:(NSNotification *)aNotification {
}

- (void)viewController:(ViewController *)vc execFunc:(NSInteger)aFunc {
}
@end
