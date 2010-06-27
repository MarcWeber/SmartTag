sp		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)

VIM_TEST_SCRIPT := $(dir)/SmartTagTest.vim

dir := $(d)/TestTags
include $(dir)/Rules.mk

dir := $(d)/wrong-type-member2
include $(dir)/Rules.mk

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))

# vim: ft=make isfname-== noet
