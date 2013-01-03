//
//  QRCaptureController.m
//  QuickQR
//
//  Created by Conrad Kramer on 12/30/12.
//  Copyright (c) 2012 Kramer Software Productions, LLC. All rights reserved.
//

#import <CoreVideo/CoreVideo.h>

#import "QRCaptureController.h"

#include "CGImageLuminanceSource.h"
#include <zxing/common/HybridBinarizer.h>
#include <zxing/BinaryBitmap.h>
#include <zxing/DecodeHints.h>
#include <zxing/common/IllegalArgumentException.h>
#include <zxing/ReaderException.h>

#include <zxing/qrcode/QRCodeReader.h>

using namespace zxing;
using namespace zxing::qrcode;

@interface QRCaptureController () <AVCaptureVideoDataOutputSampleBufferDelegate> {
    QRCodeReader *_reader;
}
@property (readwrite, retain, nonatomic) AVCaptureVideoDataOutput *output;
@end

@implementation QRCaptureController

- (id)init {
    if ((self = [super init])) {
        AVCaptureVideoDataOutput *output = [[AVCaptureVideoDataOutput alloc] init];
        output.videoSettings = @{
            (id)kCVPixelBufferPixelFormatTypeKey : @(kCVPixelFormatType_32BGRA)
        };
        
        dispatch_queue_t bufferQueue = dispatch_queue_create("org.thebigboss.quickqr.videobuffers", NULL);
        [output setSampleBufferDelegate:self queue:bufferQueue];
        dispatch_release(bufferQueue);
        
        self.output = output;
        [output release];
        
        _reader = new QRCodeReader();
        
        self.enabled = YES;
    }
        
    return self;
}

- (void)dealloc {
    self.output = nil;
    
    [super dealloc];
}

- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection {
    if (!self.enabled) return;
    
    CVImageBufferRef videoFrame = CMSampleBufferGetImageBuffer(sampleBuffer);
    
    CGImageLuminanceSource *luminance = new CGImageLuminanceSource(videoFrame);
    HybridBinarizer *binarizer = new HybridBinarizer(Ref<CGImageLuminanceSource>(luminance));
    BinaryBitmap *bitmap = new BinaryBitmap(Ref<HybridBinarizer>(binarizer));
    
    DecodeHints hints = DecodeHints(BarcodeFormat_QR_CODE);
    
    NSString *result = nil;

    try {
        Ref<Result> decoderResult = _reader->decode(Ref<BinaryBitmap>(bitmap), hints);
        
        if (decoderResult->getBarcodeFormat() == BarcodeFormat_QR_CODE) {
            result = [NSString stringWithCString:decoderResult->getText()->getText().c_str() encoding:NSUTF8StringEncoding];
        }        
    } catch (ReaderException const &exception) {
    } catch (IllegalArgumentException const &exception) { }
        
    if (result && [self.delegate respondsToSelector:@selector(captureController:recognizedResult:)]) {
        dispatch_sync(dispatch_get_main_queue(), ^{
            [self.delegate captureController:self recognizedResult:result];
        });
    }
}

@end
