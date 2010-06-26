VIM=vim
VIM_SETTINGS=-c set\ runtimepath=.                                       \
             -c let\ g:batchRun=1                                        \
             -c let\ g:resultFile=\"errors.log\"                         \
             -c let\ g:quitAll=1

.PHONY: all
all:	SmartTag.vba

include Rules.mk

%.cpp-test:	$(VIM_TEST_SCRIPT)
%.c-test:	$(VIM_TEST_SCRIPT)
%.h-test:	$(VIM_TEST_SCRIPT)

%.cpp-test: %.cpp
	$(VIM) $(VIM_SETTINGS) -S $(VIM_TEST_SCRIPT) $<
	@touch $@

%.c-test: %.c
	$(VIM) $(VIM_SETTINGS) -S $(VIM_TEST_SCRIPT) $<
	@touch $@

%.h-test: %.h
	$(VIM) $(VIM_SETTINGS) -S $(VIM_TEST_SCRIPT) $<
	@touch $@

.PHONY: clean-error-file
clean-error-file:
	@rm -f errors.log

.PHONY: test
test: clean-error-file $(ALL_TEST_CASES)

.PHONY: testclean
testclean:
	rm -f $(ALL_TEST_CASES)

SmartTag.vba: autoload/SmartTag.vim doc/SmartTag.txt
	for dep in $^ ; do echo "$$dep" ; done        \
	| vim -c 'set runtimepath^=.'                 \
	      -c '%MkVimball! $@'                     \
	      -c 'q!' -

.PHONY: clean
clean: testclean
	rm -f SmartTag.vba

# vim: ft=make isfname-== noet
