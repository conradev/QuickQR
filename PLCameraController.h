#import <AVFoundation/AVFoundation.h>

typedef enum{
    PLCameraModePhoto = 0,
    PLCameraModeVideo = 1,
    PLCameraModePanorama = 2
} PLCameraMode;

typedef enum{
    PLCameraDeviceBack = 0,
    PLCameraDeviceFront = 1
} PLCameraDevice;

@class PLCameraController;
@protocol PLCameraControllerDelegate <NSObject>
@optional
- (void)cameraControllerTorchAvailabilityChanged:(PLCameraController *)cameraController;
- (void)cameraController:(PLCameraController *)cameraController faceMetadataDidChange:(id)faceMetadata;
- (void)cameraControllerFocusDidEnd:(PLCameraController *)cameraController;
- (void)cameraControllerFocusDidStart:(PLCameraController *)cameraController;
- (void)cameraControllerWillStartAutofocus:(PLCameraController *)cameraController;
- (void)cameraControllerVideoCaptureDidStop:(PLCameraController *)cameraController withReason:(int)reason userInfo:(id)userInfo;
- (void)cameraControllerDidStopVideoCapture:(PLCameraController *)cameraController;
- (void)cameraControllerVideoCaptureDidStart:(PLCameraController *)cameraController;
- (void)cameraController:(PLCameraController *)cameraController capturedPanorama:(id)panorama error:(NSError *)error;
- (void)cameraControllerPanoramaDidStopProcessing:(PLCameraController *)cameraController;
- (void)cameraControllerPanoramaWillStartProcessing:(PLCameraController *)cameraController;
- (void)cameraControllerWillStopPanoramaCapture:(PLCameraController *)cameraController;
- (void)cameraControllerDidStartPanoramaCapture:(PLCameraController *)cameraController;
- (void)cameraController:(PLCameraController *)cameraController didReceivePanoramaIssue:(int)issue;
- (void)cameraController:(PLCameraController *)cameraController didUpdatePanoramaPreview:(id)preview;
- (void)cameraController:(PLCameraController *)cameraController didChangeCaptureAbility:(BOOL)able;
- (void)cameraController:(PLCameraController *)cameraController capturedPhoto:(id)photo error:(NSError *)error;
- (void)cameraControllerDidTakePhoto:(PLCameraController *)cameraController;
- (void)cameraControllerWillTakePhoto:(PLCameraController *)cameraController;
- (void)cameraControllerModeDidChange:(PLCameraController *)cameraController;
- (void)cameraControllerModeWillChange:(PLCameraController *)cameraController;
- (void)cameraController:(PLCameraController *)cameraController cleanApertureDidChange:(CGRect)aperture;
- (void)cameraControllerServerDied:(PLCameraController *)cameraController;
- (void)cameraControllerSessionInterruptionEnded:(PLCameraController *)cameraController;
- (void)cameraControllerSessionWasInterrupted:(PLCameraController *)cameraController;
- (void)cameraControllerSessionDidStop:(PLCameraController *)cameraController;
- (void)cameraControllerWillStopSession:(PLCameraController *)cameraController;
- (void)cameraControllerDidStopSession:(PLCameraController *)cameraController;
- (void)cameraControllerSessionDidStart:(PLCameraController *)cameraController;
- (void)cameraControllerPreviewDidStart:(PLCameraController *)cameraController;
- (void)cameraControllerWillStartPreview:(PLCameraController *)cameraController;
- (void)cameraControllerDidStartSession:(PLCameraController *)cameraController;
@end

@interface PLCameraController : NSObject <AVCaptureFileOutputRecordingDelegate, AVCaptureVideoDataOutputSampleBufferDelegate>

@property (assign, nonatomic) id<PLCameraControllerDelegate> delegate;

@property (readonly, retain, nonatomic) AVCaptureVideoPreviewLayer *previewLayer;
@property (readonly, retain, nonatomic) AVCaptureStillImageOutput *imageOutput;
@property (readonly, retain, nonatomic) AVCaptureSession *currentSession;
@property (retain, nonatomic) AVCaptureOutput *currentOutput;
@property (retain, nonatomic) AVCaptureDeviceInput *currentInput;
@property (retain, nonatomic) AVCaptureDevice *currentDevice;
@property (nonatomic) BOOL convertSampleBufferToJPEG;

@property (nonatomic) PLCameraMode cameraMode;
@property (nonatomic) PLCameraDevice cameraDevice;

@property (readonly, nonatomic) int cameraOrientation;
@property (nonatomic) int previewOrientation;

@property (readonly, nonatomic) BOOL supportsHDR;
@property (nonatomic, getter=isHDREnabled) BOOL HDREnabled;
@property (nonatomic) int flashMode;

@property (nonatomic) BOOL isCameraApp;

+ (instancetype)sharedInstance;

- (BOOL)isTorchDisabled;
- (BOOL)isTorchOn;
- (BOOL)flashWillFire;
- (BOOL)hasFlash;

- (void)setFaceDetectionEnabled:(BOOL)enabled;
- (CGRect)faceRectangle;
- (BOOL)isFocusingOnFace;

- (BOOL)isExposing;
- (void)setFocusDisabled:(BOOL)disabled;
- (BOOL)isFocusing;
- (void)lockFocusForRecording;
- (void)lockFocusAndExposureForPano;
- (void)userInitiatedLockFocus;
- (BOOL)isExposureLockSupported;
- (BOOL)isFocusLockSupported;
- (BOOL)canLockFocus;
- (void)performAutofocusAfterCapture;
- (void)autofocus;
- (void)restartAutoFocus;
- (int)currentFocusMode;
- (void)focusAtAdjustedPoint:(CGPoint)point;
- (BOOL)canFocusAtPoint;
- (BOOL)isFocusAllowed;

- (void)setPanoramaCaptureDirection:(int)direction;
- (void)stopPanoramaCapture;
- (void)startPanoramaCapture;
- (void)setPanoramaImageQueueLayer:(id)layer;
- (BOOL)isCapturingPanorama;
- (BOOL)canCapturePanorama;
- (BOOL)supportsPanorama;

- (void)setVideoCaptureMaximumDuration:(double)duration;
- (void)setVideoCaptureQuality:(int)quality;
- (id)videoCapturePath;
- (void)stopVideoCapture;
- (BOOL)supportsVideoCapture;
- (double)minimumVideoCaptureDuration;
- (void)startVideoCapture;
- (BOOL)canCaptureVideo;
- (BOOL)isCapturingVideo;

- (void)capturePhoto;
- (BOOL)imageWriterQueueIsAvailable;
- (BOOL)canCapturePhotoDuringRecording;
- (BOOL)canCapturePhoto;

- (void)startPreview;
- (void)startPreview:(id)arg1;
- (void)stopPreview;
- (BOOL)isPreviewMirrored;

- (BOOL)supportsZoom;
- (float)maximumZoomFactor;
- (float)minimumZoomFactor;

- (BOOL)hasFrontCamera;
- (BOOL)isChangingModes;
- (void)executeBlockOnMainQueue:(id)arg1;
- (void)enqueueBlockOnMainQueue:(id)arg1;
- (void)enqueueBlockInCaptureSessionQueue:(id)arg1;
- (BOOL)isReady;
- (void)releaseIOSurface;
- (void)captureIOSurface;
- (BOOL)hasInheritedForegroundState;
- (BOOL)inCall;

@end
