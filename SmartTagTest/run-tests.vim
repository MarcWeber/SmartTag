" for those people like me who don't know how to run this test case :-) - Marc
" source this file in Vim to run the small testsuite
" make sure you don't have additional files open!

e TestTags.h
e TestTags.cpp
" sourceing SmartTagTest.vim after calling :e does not work for some reason
bufdo if expand('%:e') =~ 'h\|cpp' | echo "running test on ".expand('%')| source SmartTagTest.vim | endif
