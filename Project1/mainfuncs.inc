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
		INVOKE drd_imageLoadFile, OFFSET mariosheet1loc, OFFSET mario.sheet1
		INVOKE drd_imageLoadFile, OFFSET mariosheet2loc, OFFSET mario.sheet2
		INVOKE drd_imageLoadFile, OFFSET goombaloc, OFFSET goomba1.Right
		INVOKE drd_imageLoadFile, OFFSET goombaloc, OFFSET goomba2.Right
		INVOKE drd_imageLoadFile, OFFSET goombaloc, OFFSET goomba3.Right
		INVOKE drd_imageLoadFile, OFFSET goombaloc, OFFSET goomba4.Right
		INVOKE drd_imageLoadFile, OFFSET goombaloc, OFFSET goomba5.Right
		INVOKE drd_imageLoadFile, OFFSET goombaloc, OFFSET goomba6.Right
		INVOKE drd_imageLoadFile, OFFSET winloc, OFFSET win.Right
		INVOKE drd_imageLoadFile, OFFSET logoloc, OFFSET logo.Right
		INVOKE drd_imageLoadFile, OFFSET startloc, OFFSET start.Right
		INVOKE drd_imageLoadFile, OFFSET gameoverloc, OFFSET gameover.Right
		INVOKE drd_imageLoadFile, OFFSET coinloc, OFFSET coin1.Right
		INVOKE drd_imageLoadFile, OFFSET coinloc, OFFSET coin2.Right
		INVOKE drd_imageLoadFile, OFFSET coinloc, OFFSET coin3.Right
		INVOKE drd_imageLoadFile, OFFSET coinloc, OFFSET coin4.Right
		INVOKE drd_imageLoadFile, OFFSET coinloc, OFFSET coin5.Right
		INVOKE drd_imageLoadFile, OFFSET coinloc, OFFSET coin6.Right
		invoke getXgoombas,offset goomba1,offset goomba2,offset goomba3,offset goomba4,offset goomba5,offset goomba6
		invoke getCoinLocs,offset coin1,offset coin2,offset coin3,offset coin4,offset coin5,offset coin6
		INVOKE drd_imageSetTransparent, OFFSET mario.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET goomba1.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET goomba2.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET goomba3.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET goomba4.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET goomba5.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET goomba6.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET gameover.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET start.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET win.Right,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET mario.sheet1,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET mario.sheet2,0ffffffh
		INVOKE drd_imageSetTransparent, OFFSET coin1.Right,07f7f7fh
		INVOKE drd_imageSetTransparent, OFFSET coin2.Right,07f7f7fh
		INVOKE drd_imageSetTransparent, OFFSET coin3.Right,07f7f7fh
		INVOKE drd_imageSetTransparent, OFFSET coin4.Right,07f7f7fh
		INVOKE drd_imageSetTransparent, OFFSET coin5.Right,07f7f7fh
		INVOKE drd_imageSetTransparent, OFFSET coin6.Right,07f7f7fh
		mov playing,-2
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
		;INVOKE getkeyback, offset back2
		
		;INVOKE moveback, offset back1
		;INVOKE moveback, offset back2

		invoke handleGoombas, offset goomba1, offset mario, offset score,offset playing
		invoke handleGoombas, offset goomba2, offset mario, offset score,offset playing
		invoke handleGoombas, offset goomba3, offset mario, offset score,offset playing
		invoke handleGoombas, offset goomba4, offset mario, offset score,offset playing
		invoke handleGoombas, offset goomba5, offset mario, offset score,offset playing
		invoke handleGoombas, offset goomba6, offset mario, offset score,offset playing
		invoke handleCoins,offset coin1,offset mario,offset score
		invoke handleCoins,offset coin2,offset mario,offset score
		invoke handleCoins,offset coin3,offset mario,offset score
		invoke handleCoins,offset coin4,offset mario,offset score
		invoke handleCoins,offset coin5,offset mario,offset score
		invoke handleCoins,offset coin6,offset mario,offset score
		invoke dwtoa, score, offset textBuffer
		invoke drd_setWindowTitle, offset textBuffer
		invoke Sleep,10
		ret
		no:
		invoke replay, offset playing,offset mario, offset goomba1,offset goomba2,offset goomba3,offset goomba4,offset goomba5,offset goomba6, offset back1,offset score,offset coin1,offset coin2,offset coin3,offset coin4,offset coin5,offset coin6
		ret
	update ENDP

	draw PROC
		
		;INVOKE drd_imageDraw, OFFSET back1.Right, back1.pos.x, back1.pos.y
		;INVOKE drd_imageDraw, OFFSET back2.Right, back2.pos.x, back2.pos.y
		invoke movebackTwo,offset back1
		cmp playing,1
		je normal
		cmp playing,-1
		je winner
		cmp playing,0
		jne gamenotover
		INVOKE drd_imageDraw, OFFSET gameover.Right, gameover.pos.x, gameover.pos.y
		gamenotover:
		jmp normal
		winner:
		INVOKE drd_imageDraw, OFFSET win.Right, win.pos.x, win.pos.y
		jmp normal
		menu:
		INVOKE drd_imageDraw, OFFSET logo.Right, logo.pos.x, logo.pos.y
		INVOKE drd_imageDraw, OFFSET start.Right, start.pos.x, start.pos.y
		jmp after
		normal:
		
		invoke drawGoombas,offset goomba1,offset goomba2,offset goomba3,offset goomba4,offset goomba5,offset goomba6
		invoke drawCoins,offset coin1,offset coin2,offset coin3,offset coin4,offset coin5,offset coin6
		cmp playing,-2
		je menu
		after:
		invoke changepic, offset back1,offset mario,offset curRight,offset curLeft,offset animationCounter,offset isright
		flip:
		invoke drd_flip
		RET
	draw ENDP
	
	