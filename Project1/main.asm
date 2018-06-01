include \masm32\include\masm32rt.inc
include mainfuncs.inc

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