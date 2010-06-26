" This script tests the SmartTag script.  Load a test file and run the script.
" Test files should have "#blah" with the # above any identifier whose tag
" should be tested.  Then the line before the correct tag destination should
" have "// blah:".  "blah" can be any identifier to label the tag.
" Note: This script should be run from both TestTags.cpp and TestTags.h for a
" full test.

" Use the following to choose whether to find all errors, or stop at the first
" one.  In either case, the cursor is left on the first erroneous tag.
let stopOnFirstError = 0

if !exists("g:batchRun")
    let g:batchRun=0
endif

if g:batchRun
    let fname = expand('%')
    let errorList = []
endif

let endPos = getpos(".")
let numErrors = 0
1
while (!stopOnFirstError || numErrors == 0)
    if (!search('.#.', 'eW'))
	break
    endif
    let oldPos = getpos(".")
    let id = substitute(expand("<cWORD>"), '^.*#', '', '')
    normal hj
    let pos = getpos(".")
    let lineNum = line(".")
    let col = col(".")
    split
    call SmartTag#SmartTag("goto")
    normal k
    let line = getline(".")
    if (match(line, '\<' . escape(id, '~') . ':') < 0)
	if g:batchRun
	    call add(errorList, fname . ':' . lineNum . ':' . col . ': Error: id "' . id . '"')
	else
	    echomsg 'Error: id "' . id . '", line ' . lineNum . ' col ' . col
	endif
	if (numErrors == 0)
	    let endPos = pos
	endif
	let numErrors += 1
    endif
    quit
    call setpos(".", oldPos)
endwhile

if g:batchRun
    if (numErrors > 0)
	exe "e " . g:resultFile
	call append('$', errorList)
	w
    endif
    if exists("g:quitAll") && g:quitAll != 0
	if (numErrors > 0)
	    cquit
	else
	    qa
	endif
    endif
else
    call setpos(".", endPos)
    normal zz
    "if (numErrors > 0)
    echomsg numErrors . " Errors"
    "endif
endif

" vim: ft=vim ts=8 sw=4 sts=4 sta noet
