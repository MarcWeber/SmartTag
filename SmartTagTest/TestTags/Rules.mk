sp		:= $(sp).x
dirstack_$(sp)	:= $(d)
d		:= $(dir)

LOCAL_TEST_CASES := $(d)/TestTags.cpp-test $(d)/TestTags.h-test
ALL_TEST_CASES   := $(ALL_TEST_CASES) $(LOCAL_TEST_CASES)

d		:= $(dirstack_$(sp))
sp		:= $(basename $(sp))

# vim: ft=make isfname-== noet
