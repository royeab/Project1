INCLUDE drd.inc
includelib drd.lib
include data.inc
include funcs.inc
.CODE
	init PROC	
		INVOKE drd_init, 1280,720,0
		
		INVOKE drd_imageLoadFile, OFFSET backloc, OFFSET back1.Right
		INVOKE drd_imageLoadFile, OFFSET backloc, OFFSET back2.Right
		INVOKE drd_imageLoadFile, OFFSET marioloc, OFFSET mario.Right
		INVOKE drd_imageLoadFile, OFFSET mario2loc, OFFSET mario.Left
		INVOKE drd_imageLoadFile, OFFSET goombaloc, OFFSET goomba.Right
		INVOKE drd_imageSetTransparent, OFFSET mario.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET goomba.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET mario.Left,0ffffffh
		RET
	init ENDP

	update PROC
		INVOKE drd_processMessages
		INVOKE drd_pixelsClear, 1
		INVOKE getkeysmar, offset mario
		INVOKE moveobj, offset mario
		INVOKE getkeyback, offset back1
		INVOKE getkeyback, offset back2
		invoke changepic, offset back1
		mov isright,ecx
		INVOKE moveback, offset back1
		INVOKE moveback, offset back2
		INVOKE getkeyback, offset goomba
		INVOKE movegoomba, offset goomba
		INVOKE jumpon, offset mario, offset goomba
		invoke dwtoa, 0, offset textBuffer
		invoke drd_setWindowTitle, offset textBuffer
		invoke Sleep,10
	update ENDP

	draw PROC
		INVOKE drd_imageDraw, OFFSET back1.Right, back1.pos.x, back1.pos.y
		INVOKE drd_imageDraw, OFFSET back2.Right, back2.pos.x, back2.pos.y
		INVOKE drd_imageDraw, OFFSET goomba.Right, goomba.pos.x, goomba.pos.y
		cmp isright,1
		je left
		INVOKE drd_imageDraw, OFFSET mario.Right, mario.pos.x, mario.pos.y
		INVOKE drd_flip
		ret
		left:
		INVOKE drd_imageDraw, OFFSET mario.Left, mario.pos.x, mario.pos.y
		INVOKE drd_flip
		RET
	draw ENDP
	
	