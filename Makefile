TARGET=iphone:clang:latest:5.0

include theos/makefiles/common.mk

TWEAK_NAME = QuickQR
QuickQR_FILES = PLCameraController.x QRCaptureController.mm CGImageLuminanceSource.cpp
QuickQR_OBJ_FILES = zxing/cpp/build/Release-iphoneos/libzxing.a
QuickQR_CFLAGS = -Izxing/cpp/core/src
QuickQR_LDFLAGS = -liconv
QuickQR_FRAMEWORKS = UIKit AVFoundation CoreVideo CoreGraphics CoreMedia
QuickQR_PRIVATE_FRAMEWORKS = PhotoLibrary

include $(THEOS_MAKE_PATH)/tweak.mk
