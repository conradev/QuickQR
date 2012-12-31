//
//  QRCaptureController.h
//  QuickQR
//
//  Created by Conrad Kramer on 12/30/12.
//  Copyright (c) 2012 Kramer Software Productions, LLC. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>

@class QRCaptureController;
@protocol QRCaptureControllerDelegate <NSObject>
@optional
- (void)captureController:(QRCaptureController *)captureController recognizedResult:(NSString *)result;
@end

@interface QRCaptureController : NSObject

@property (assign, nonatomic) id<QRCaptureControllerDelegate> delegate;

@property (readonly, retain, nonatomic) AVCaptureVideoDataOutput *output;

@property (assign) BOOL enabled;

@end
