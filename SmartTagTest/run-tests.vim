" for those people like me who don't know how to run this test case :-) - Marc
" source this file in Vim to run the small testsuite
" make sure you don't have additional files open!

let testFiles = [
                \   "TestTags/TestTags.cpp"
                \ , "TestTags/TestTags.h"
                \ , "wrong-type-member/file.c"
                \ , "wrong-type-member2/file.c"
                \ ]

set runtimepath=..
let g:batchRun=1
let g:resultFile="../errors.log"

exe "e " . g:resultFile
%delete
w

for fileName in testFiles
	exe "e " . fileName
	source SmartTagTest.vim
endfor

if expand("%") != g:resultFile
	echomsg 'No errors found.'
endif

" vim: ft=vim ts=4 sw=4 sts=4 sta noet
