//
//  QMUIHelper.h
//  qmui
//
//  Created by QMUI Team on 14/10/25.
//  Copyright (c) 2014年 QMUI Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface QMUIHelper : NSObject

+ (instancetype _Nonnull)sharedInstance;
@end


extern NSString *const _Nonnull QMUIResourcesMainBundleName;

@interface QMUIHelper (Bundle)

// QMUI专属
+ (nullable NSBundle *)resourcesBundle;
+ (nullable UIImage *)imageWithName:(nullable NSString *)name;

+ (nullable NSBundle *)resourcesBundleWithName:(nullable NSString *)bundleName;
+ (nullable UIImage *)imageInBundle:(nullable NSBundle *)bundle withName:(nullable NSString *)name;
@end

@interface QMUIHelper (SystemVersion)
+ (NSInteger)numbericOSVersion;
+ (NSComparisonResult)compareSystemVersion:(nonnull NSString *)currentVersion toVersion:(nonnull NSString *)targetVersion;
+ (BOOL)isCurrentSystemAtLeastVersion:(nonnull NSString *)targetVersion;
+ (BOOL)isCurrentSystemLowerThanVersion:(nonnull NSString *)targetVersion;
@end

@interface QMUIHelper (DynamicType)

/// 返回当前 contentSize 的 level，这个值可以在设置里面的“字体大小”查看，辅助功能里面有个“更大字体”可以设置更大的字体，不过这里我们这个接口将更大字体都做了统一，都返回“字体大小”里面最大值。
/// Returns the level of contentSize
/// The value can be set in Settings - Display & Brightness - Text Size as well as in General - Accessibility - Larger Text
/// This method returns the value set by user or the maximum value in Text Size, whichever is smaller
+ (nonnull NSNumber *)preferredContentSizeLevel;

/// 设置当前 cell 的高度，heights 是有七个数值的数组，对于不支持的iOS版本，则选择中间的值返回。
/// Sets height of the cell; Heights consist of 7 numberic values; Returns the middle value on legacy iOS versions.
+ (CGFloat)heightForDynamicTypeCell:(nonnull NSArray *)heights;
@end


@interface QMUIHelper (Keyboard)

/**
 * 判断当前 App 里的键盘是否升起，默认为 NO
 * Returns the visibility of the keybord. Default value is NO.
 */
+ (BOOL)isKeyboardVisible;

/**
 * 记录上一次键盘显示时的高度（基于整个 App 所在的 window 的坐标系），注意使用前用 `isKeyboardVisible` 判断键盘是否显示，因为即便是键盘被隐藏的情况下，调用 `lastKeyboardHeightInApplicationWindowWhenVisible` 也会得到高度值。
 */
+ (CGFloat)lastKeyboardHeightInApplicationWindowWhenVisible;

/**
 * 获取当前键盘frame相关
 * @warning 注意iOS8以下的系统在横屏时得到的rect，宽度和高度相反了，所以不建议直接通过这个方法获取高度，而是使用<code>keyboardHeightWithNotification:inView:</code>，因为在后者的实现里会将键盘的rect转换坐标系，转换过程就会处理横竖屏旋转问题。
 */
+ (CGRect)keyboardRectWithNotification:(nullable NSNotification *)notification;

/// 获取当前键盘的高度，注意高度可能为0（例如第三方键盘会发出两次notification，其中第一次的高度就为0）
+ (CGFloat)keyboardHeightWithNotification:(nullable NSNotification *)notification;

/**
 * 获取当前键盘在屏幕上的可见高度，注意外接键盘（iPad那种）时，[QMUIHelper keyboardRectWithNotification]得到的键盘rect里有一部分是超出屏幕，不可见的，如果直接拿rect的高度来计算就会与意图相悖。
 * @param notification 接收到的键盘事件的UINotification对象
 * @param view 要得到的键盘高度是相对于哪个View的键盘高度，若为nil，则等同于调用[QMUIHelper keyboardHeightWithNotification:]
 * @warning 如果view.window为空（当前View尚不可见），则会使用App默认的UIWindow来做坐标转换，可能会导致一些计算错误
 * @return 键盘在view里的可视高度
 */
+ (CGFloat)keyboardHeightWithNotification:(nullable NSNotification *)notification inView:(nullable UIView *)view;

/// 获取键盘显示/隐藏的动画时长，注意返回值可能为0
+ (NSTimeInterval)keyboardAnimationDurationWithNotification:(nullable NSNotification *)notification;

/// 获取键盘显示/隐藏的动画时间函数
+ (UIViewAnimationCurve)keyboardAnimationCurveWithNotification:(nullable NSNotification *)notification;

/// 获取键盘显示/隐藏的动画时间函数
+ (UIViewAnimationOptions)keyboardAnimationOptionsWithNotification:(nullable NSNotification *)notification;
@end


@interface QMUIHelper (AudioSession)

/**
 *  听筒和扬声器的切换
 *
 *  @param speaker   是否转为扬声器，NO则听筒
 *  @param temporary 决定使用kAudioSessionProperty_OverrideAudioRoute还是kAudioSessionProperty_OverrideCategoryDefaultToSpeaker，两者的区别请查看本组的博客文章:http://km.oa.com/group/gyui/articles/show/235957
 */
+ (void)redirectAudioRouteWithSpeaker:(BOOL)speaker temporary:(BOOL)temporary;

/**
 *  设置category
 *
 *  @param category 使用iOS7的category，iOS6的会自动适配
 */
+ (void)setAudioSessionCategory:(nullable NSString *)category;
@end

@interface QMUIHelper (UIGraphic)

/// 获取一像素的大小
+ (CGFloat)pixelOne;

/// 判断size是否超出范围
+ (void)inspectContextSize:(CGSize)size;

/// context是否合法
+ (void)inspectContextIfInvalidatedInDebugMode:(CGContextRef _Nonnull)context;
+ (BOOL)inspectContextIfInvalidatedInReleaseMode:(CGContextRef _Nonnull)context;
@end


@interface QMUIHelper (Device)

+ (BOOL)isIPad;
+ (BOOL)isIPadPro;
+ (BOOL)isIPod;
+ (BOOL)isIPhone;
+ (BOOL)isSimulator;

+ (BOOL)is58InchScreen;
+ (BOOL)is55InchScreen;
+ (BOOL)is47InchScreen;
+ (BOOL)is40InchScreen;
+ (BOOL)is35InchScreen;

+ (CGSize)screenSizeFor58Inch;
+ (CGSize)screenSizeFor55Inch;
+ (CGSize)screenSizeFor47Inch;
+ (CGSize)screenSizeFor40Inch;
+ (CGSize)screenSizeFor35Inch;

// 用于获取 iPhoneX 安全区域的 insets
+ (UIEdgeInsets)safeAreaInsetsForIPhoneX;

/// 判断当前设备是否高性能设备，只会判断一次，以后都直接读取结果，所以没有性能问题
+ (BOOL)isHighPerformanceDevice;

@end

@interface QMUIHelper (Orientation)

/**
 *  旋转当前设备的方向到指定方向，一般用于 [UIViewController supportedInterfaceOrientations] 发生变化时主动触发界面方向的刷新
 *  @return 是否真正旋转了方向，YES 表示参数的方向和目前设备方向不一致，NO 表示一致也即不会旋转
 *  @see [QMUIConfiguration automaticallyRotateDeviceOrientation]
 */
+ (BOOL)rotateToDeviceOrientation:(UIDeviceOrientation)orientation;

/**
 *  记录手动旋转方向前的设备方向，当值不为 UIDeviceOrientationUnknown 时表示设备方向有经过了手动调整。默认值为 UIDeviceOrientationUnknown。
 *  @see [QMUIHelper rotateToDeviceOrientation]
 */
@property(nonatomic, assign) UIDeviceOrientation orientationBeforeChangingByHelper;

/// 根据指定的旋转方向计算出对应的旋转角度
+ (CGFloat)angleForTransformWithInterfaceOrientation:(UIInterfaceOrientation)orientation;

/// 根据当前设备的旋转方向计算出对应的CGAffineTransform
+ (CGAffineTransform)transformForCurrentInterfaceOrientation;

/// 根据指定的旋转方向计算出对应的CGAffineTransform
+ (CGAffineTransform)transformWithInterfaceOrientation:(UIInterfaceOrientation)orientation;
@end

@interface QMUIHelper (UIApplication)

/**
 *  更改状态栏内容颜色为深色
 *
 *  @warning 需在项目的 Info.plist 文件内设置字段 “View controller-based status bar appearance” 的值为 NO 才能生效，如果不设置，或者值为 YES，则请通过系统的 - UIViewController preferredStatusBarStyle 方法来修改
 */
+ (void)renderStatusBarStyleDark;

/**
 *  更改状态栏内容颜色为浅色
 *
 *  @warning 需在项目的 Info.plist 文件内设置字段 “View controller-based status bar appearance” 的值为 NO 才能生效，如果不设置，或者值为 YES，则请通过系统的 - UIViewController preferredStatusBarStyle 方法来修改
 */
+ (void)renderStatusBarStyleLight;

/**
 * 把App的主要window置灰，用于浮层弹出时，请注意要在适当时机调用`resetDimmedApplicationWindow`恢复到正常状态
 */
+ (void)dimmedApplicationWindow;

/**
 * 恢复对App的主要window的置灰操作，与`dimmedApplicationWindow`成对调用
 */
+ (void)resetDimmedApplicationWindow;

@end

extern NSString * __nonnull const QMUISpringAnimationKey;

@interface QMUIHelper (Animation)

+ (void)actionSpringAnimationForView:(nonnull UIView *)view;

@end
