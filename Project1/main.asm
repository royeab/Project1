include \masm32\include\masm32rt.inc
include mainfuncs.inc
;This is the main file. This is where masm will start reading the code. The code invokes the init function and then loops between update and draw
.CODE
	main PROC
		INVOKE init
		loopi:
			INVOKE update
			INVOKE draw
		JMP loopi

		RET
	main ENDP
END main