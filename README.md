# QuickQR

This project integrates a QR code reader into Apple's Camera application. It brings the "quick" back into "quick response"!

The project uses [ZXing](http://code.google.com/p/zxing/) to read QR codes, and [Theos](https://github.com/DHowett/theos) as its build system.

## Getting Started

### Prequisites

- [Xcode 4.5](https://itunes.apple.com/us/app/xcode/id497799835), which includes the iOS 6 SDK
- A jailbroken device running iOS 5 or later

### Building

The first step to build the project is to clone the repository and initialize all of its submodules:

``` sh
git clone git://github.com/conradev/QuickQR.git
cd QuickQR
git submodule update --init
```

The next step is to build the C++ port of ZXing
``` sh
cd Tweak/zxing/cpp
xcodebuild -project ios.xcodeproj -target zxing -sdk iphoneos6.0 -configuration Release -arch armv7 -arch armv7s
cd ../../..
```

To build the project, you need only run

```
make
```

### Installing

To install this on a jailbroken device, some additional tools are needed.

The first tool is `ldid`, which is used for fakesigning binaries. Ryan Petrich has a build on his [Github mirror](https://github.com/rpetrich/ldid):

``` sh
curl -O http://cloud.github.com/downloads/rpetrich/ldid/ldid.zip
unzip ldid.zip
mv ldid theos/bin/
rm ldid.zip
```

To build a Debian package, `dpkg` is required. You can install it from [Homebrew](http://mxcl.github.com/homebrew/):

``` sh
brew install dpkg
```

To build a package in the project directory, you can run:

``` sh
make package
```

and to automatically install this package on your jailbroken device (over SSH), you can run:

``` sh
make package install THEOS_DEVICE_IP=xxx.xxx.xxx.xxx
```

## License

QuickQR is available under the MIT license. See the LICENSE file for more info.
