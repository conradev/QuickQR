//
//  PLCameraController.x
//  QuickQR
//
//  Created by Conrad Kramer on 12/30/12.
//  Copyright (c) 2012 Kramer Software Productions, LLC. All rights reserved.
//

#import "PLCameraController.h"

#import "QRCaptureController.h"

@interface PLCameraController (QuickQR) <QRCaptureControllerDelegate>
@property (strong, nonatomic, getter=__quickqr_capture_controller, setter=__quickqr_set_capture_controller:) QRCaptureController *captureController;
@end

static char captureControllerKey;

%hook PLCameraController

%new(v@:@)
- (void)__quickqr_set_capture_controller:(id)object {
    objc_setAssociatedObject(self, &captureControllerKey, object, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

%new(@@:)
- (id)__quickqr_capture_controller {
    return objc_getAssociatedObject(self, &captureControllerKey);
}

%new(v@:@@)
- (void)captureController:(QRCaptureController *)captureController recognizedResult:(NSString *)result {
    NSString *action = [NSURL URLWithString:result] ? @"Open" : @"Copy";
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle: @"QR Code" message:result delegate:nil cancelButtonTitle:@"Cancel" otherButtonTitles:action, nil];
    alert.delegate = self;
    
    [alert show];
    [alert release];

    // Five second timeout
    captureController.enabled = NO;
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 5 * NSEC_PER_SEC), dispatch_get_current_queue(), ^{
        captureController.enabled = YES;
    });
}

%new(v@:@i)
- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex {
    if (alertView.firstOtherButtonIndex == buttonIndex) {
        NSURL *url = [NSURL URLWithString:alertView.message];
        
        if (url) {
            [[UIApplication sharedApplication] openURL:url];
        } else {
            [[UIPasteboard generalPasteboard] setString:alertView.message];
        }
    }
}

- (BOOL)_setupCamera {
    BOOL orig = %orig();
    
    // Check `isCameraApp` so we don't activate in an arbitrary UIImagePickerController
    if (orig && self.isCameraApp && !self.captureController) {
        QRCaptureController *captureController = [[QRCaptureController alloc] init];
        captureController.delegate = self;

        self.captureController = captureController;
        
        [captureController release];
    }
    
    return orig;
}

- (void)_destroyCamera {
    self.captureController = nil;
    
    %orig();
}

- (void)_configureSessionWithCameraMode:(PLCameraMode)cameraMode cameraDevice:(PLCameraDevice)cameraDevice {
    %orig();
    
    AVCaptureOutput *output = self.captureController.output;
    if (!output) return;
    
    if (cameraMode == PLCameraModePhoto) {
        if ([self.currentSession canAddOutput:output]) {
            [self.currentSession addOutput:output];
        }
    } else {
        [self.currentSession removeOutput:output];
    }
}

%end
