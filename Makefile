TARGET = iphone:clang:latest:5.0

SUBPROJECTS = Tweak

include theos/makefiles/common.mk
include $(THEOS_MAKE_PATH)/aggregate.mk
