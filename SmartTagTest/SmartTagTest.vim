" This script tests the SmartTags script.  Load a test file and run the script.
" Test files should have "#blah" with the # above any identifier whose tag
" should be tested.  Then the line before the correct tag destination should
" have "// blah:".  "blah" can be any identifier to label the tag.

" Use the following to choose whether to find all errors, or stop at the first
" one.  In either case, the cursor is left on the first erroneous tag.
let stopOnFirstError = 0

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
    call SmartTag("goto")
    normal k
    let line = getline(".")
    if (match(line, '\<' . escape(id, '~') . ':') < 0)
	echomsg 'Error: id "' . id . '", line ' . lineNum . ' col ' . col
	if (numErrors == 0)
	    let endPos = pos
	endif
	let numErrors += 1
    endif
    quit
    call setpos(".", oldPos)
endwhile
call setpos(".", endPos)
normal zz
"if (numErrors > 0)
    echomsg numErrors . " Errors"
"endif
