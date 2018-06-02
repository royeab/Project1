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
		INVOKE drd_imageLoadFile, OFFSET goombaloc, OFFSET goomba1.Right
		INVOKE drd_imageLoadFile, OFFSET goombaloc, OFFSET goomba2.Right
		INVOKE drd_imageLoadFile, OFFSET goombaloc, OFFSET goomba3.Right
		INVOKE drd_imageLoadFile, OFFSET goombaloc, OFFSET goomba4.Right
		INVOKE drd_imageLoadFile, OFFSET goombaloc, OFFSET goomba5.Right
		INVOKE drd_imageLoadFile, OFFSET goombaloc, OFFSET goomba6.Right
		INVOKE drd_imageLoadFile, OFFSET winloc, OFFSET win.Right
		INVOKE drd_imageLoadFile, OFFSET gameoverloc, OFFSET gameover.Right
		invoke getXgoombas,offset goomba1,offset goomba2,offset goomba3,offset goomba4,offset goomba5,offset goomba6
		INVOKE drd_imageSetTransparent, OFFSET mario.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET goomba1.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET goomba2.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET goomba3.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET goomba4.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET goomba5.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET goomba6.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET gameover.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET win.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET mario.Left,0ffffffh
		RET
	init ENDP

	update PROC
		
		INVOKE drd_processMessages
		INVOKE drd_pixelsClear, 1
		INVOKE checkWin,offset score,offset playing
		cmp playing,0
		jle no
		
		INVOKE getkeysmar, offset mario
		INVOKE moveobj, offset mario
		INVOKE getkeyback, offset back1
		INVOKE getkeyback, offset back2
		invoke changepic, offset back1
		mov isright,ecx
		INVOKE moveback, offset back1
		INVOKE moveback, offset back2
		
		invoke handleGoombas, offset goomba1, offset mario, offset score,offset playing
		invoke handleGoombas, offset goomba2, offset mario, offset score,offset playing
		invoke handleGoombas, offset goomba3, offset mario, offset score,offset playing
		invoke handleGoombas, offset goomba4, offset mario, offset score,offset playing
		invoke handleGoombas, offset goomba5, offset mario, offset score,offset playing
		invoke handleGoombas, offset goomba6, offset mario, offset score,offset playing
		invoke dwtoa, score, offset textBuffer
		invoke drd_setWindowTitle, offset textBuffer
		invoke Sleep,10
		ret
		no:
		invoke replay, offset playing,offset mario, offset goomba1,offset goomba2,offset goomba3,offset goomba4,offset goomba5,offset goomba6, offset back1,offset back2,offset score
		ret
	update ENDP

	draw PROC
		
		INVOKE drd_imageDraw, OFFSET back1.Right, back1.pos.x, back1.pos.y
		INVOKE drd_imageDraw, OFFSET back2.Right, back2.pos.x, back2.pos.y

		cmp playing,1
		je normal
		cmp playing,-1
		je winner
		INVOKE drd_imageDraw, OFFSET gameover.Right, gameover.pos.x, gameover.pos.y
		jmp normal
		winner:
		INVOKE drd_imageDraw, OFFSET win.Right, win.pos.x, win.pos.y
		normal:
		invoke drawGoombas,offset goomba1,offset goomba2,offset goomba3,offset goomba4,offset goomba5,offset goomba6
		
		cmp isright,1
		je left
		INVOKE drd_imageDraw, OFFSET mario.Right, mario.pos.x, mario.pos.y
		jmp flip
		left:
		INVOKE drd_imageDraw, OFFSET mario.Left, mario.pos.x, mario.pos.y
		flip:
		invoke drd_flip
		RET
	draw ENDP
	
	