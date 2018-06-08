.686
.code
moveobj PROC objAdr:DWORD
	mov ebx,objAdr ;ebx->offset mario
	
	mov ecx,marioGroundloc
	cmp [ebx+getY],ecx
	jae on_ground
	jumpyes:
	mov eax,[ebx+getYdir];eax=diry
	sub [ebx+getY],eax;add diry to marioy
	dec eax
	mov [ebx+getYdir],eax
	ret
	on_ground:
	mov [ebx+getY],ecx
	mov eax,[ebx+getYdir];eax=diry
	cmp eax,0
	jg jumpyes
	ret
moveobj ENDP
getkeysmar PROC objAdr:DWORD
	mov ebx,objAdr
	invoke GetAsyncKeyState, VK_UP ;up key
	cmp ax,0
	je notup
	mov eax,marioGroundloc
	cmp [ebx+getY],eax ;compare Y and and ground loc
	jne notup 
	mov ecx,20 ;add direction
	mov [ebx+getYdir],ecx
	notup:
	ret
getkeysmar endp
movebackTwo proc objAdr:dword
	mov ebx,objAdr
	mov ecx,[ebx+72] ;current x
	add ecx,[ebx+8] ;add to it dir
	mov [ebx+72],ecx ;update original x
	mov eax,[ebx+8] 
	mov ecx,10
	cmp eax,ecx ;check dir
	jne left 
	;right
	mov ecx,[ebx+72]
	mov edx,1280
	cmp ecx,edx ;check if reset
	je resetright
	jmp drawback
	left:
	mov ecx,[ebx+72]
	mov edx,0
	cmp ecx,edx
	je resetleft ;check if reset
	drawback:
	mov eax,ebx
	add eax,28 ;eax=image loc
	mov ecx,[ebx+72]
	mov edx,1280
	sub edx,ecx
	pusha
	invoke drd_imageDrawCrop,eax,0,0,ecx,0,widthb,heightb ;draw first back
	popa
	invoke drd_imageDrawCrop, eax,edx,0,0,0,widthb,heightb ;draw second back
	
	ret

	resetright:
		mov ecx,0
		mov [ebx+72],ecx ;move 0 to x
		jmp drawback
	resetleft:
		mov ecx,1270
		mov [ebx+72],ecx ;move 1270 to x
		jmp drawback
movebackTwo endp
getkeyback proc backAdr: dword
	mov ebx,backAdr
	invoke GetAsyncKeyState, VK_LEFT
	cmp ax,0
	jne lefti
	invoke GetAsyncKeyState, VK_RIGHT
	cmp ax,0
	jne righti
	ret
	lefti:
		mov eax,-10
		mov [ebx+getXdir],eax
		;jmp move
		ret
	righti:
		mov eax,10
		mov [ebx+getXdir],eax
		
	
	ret
getkeyback endp
movegoomba proc objAdr: dword
	mov ebx,objAdr
	mov ecx, [ebx+getXdir]
	sub [ebx],ecx
	mov eax,0
	mov [ebx+getXdir],eax
	ret
movegoomba endp
randx proc min : dword, max: dword
	push ecx
	push edx
	mov edx,0
	mov ecx,max
	sub ecx,min ;difference between min and max
	rdrand eax ;randomise eax between 0 and 2^32
	idiv ecx 
	add edx,min ;add min to mod eax
	mov eax,edx
	pop ecx
	pop edx
	ret
randx endp
changepic proc, back:dword,marioAdr:dword,curlocRight:dword,curlocLeft:dword,countloc:dword,isrightAdr:dword
	;The animation
	mov ebx,back
	mov eax,[ebx+8]
	mov ecx,10
	cmp eax,ecx
	je right
	mov ecx,0
	cmp eax,ecx
	je nothing
	;left:
	mov ecx,isrightAdr
	mov edx,0
	mov [ecx],edx
	mov ebx,marioAdr
	mov edx,[ebx+4]
	mov ecx,marioGroundloc
	cmp edx,ecx ;check if jumping
	jne jumpleft
	;leftnotjump
	mov edx,countloc
	mov ecx,10
	mov eax,curlocLeft
	cmp [edx],ecx ;check counter
	jne nochangeleft
	mov ecx,0
	mov [edx],ecx
	mov eax,curlocLeft
	mov ecx,440 ;move to next frame
	push ecx
	cmp [eax],ecx ;check if reset is needed
	
	mov ecx,440
	sub [eax],ecx
	je resetleft
	jmp after
	nochangeleft:
	mov ecx,1	;add to counter
	add [edx],ecx
	after:
	mov ebx,marioAdr
	add ebx,76
	invoke drd_imageDrawCrop,ebx,marioBegin,marioGroundloc,[eax],0,300,400 ;draw correct frame in the size of 300,400
	mov ebx,back
	mov edx,0
	mov [ebx+8],edx
	ret
	resetleft:
	mov ecx,2200
	mov [eax],ecx	;move location of first frame to frame
	jmp after
	
	jumpleft:
	mov ebx,marioAdr
	mov edx,[ebx+4]
	add ebx,76
	invoke drd_imageDrawCrop,ebx,marioBegin,edx,0,0,300,400	;draw correct frame in the size of 300,400
	mov ebx,back
	mov edx,0
	mov [ebx+8],edx
	ret
	right:
	mov ecx,isrightAdr
	mov edx,1
	mov [ecx],edx
	mov ebx,marioAdr
	mov edx,[ebx+4]
	mov ecx,marioGroundloc
	cmp edx,ecx ;check if jumping
	jne jumpright
	;rightnotjump
	mov edx,countloc
	mov ecx,10
	mov eax,curlocRight
	cmp [edx],ecx ;check counter
	jne nochange
	mov ecx,0
	mov [edx],ecx
	mov ecx,440
	add [eax],ecx ;move to next frame
	mov edx,2200
	cmp [eax],edx ;check if reset in needed
	je resetright
	jmp afterright
	nochange:
	mov ecx,1 ;add to counter
	add [edx],ecx
	afterright:
	mov ebx,marioAdr
	add ebx,48

	invoke drd_imageDrawCrop,ebx,marioBegin,marioGroundloc,[eax],0,280,400 ;draw correct frame
	mov ebx,back
	mov edx,0
	mov [ebx+8],edx
	ret
	jumpright:
	mov ebx,marioAdr
	mov edx,[ebx+4]
	add ebx,48
	invoke drd_imageDrawCrop,ebx,marioBegin,edx,2590,0,298,400 ;draw correct frame
	mov ebx,back
	mov edx,0
	mov [ebx+8],edx
	ret
	resetright:
	mov edx,0
	mov [eax],edx ;move to first frame
	jmp afterright
	nothing:
	mov ebx,isrightAdr
	mov eax,1
	cmp [ebx],eax ;find last direction
	je rightnothing
	;leftnothing:
	mov ebx,marioAdr
	mov ecx,[ebx+4]
	add ebx,76
	invoke drd_imageDrawCrop,ebx,marioBegin,ecx,2200,0,300,400 ;draw idle left
	ret
	rightnothing:
	mov ebx,marioAdr
	mov ecx,[ebx+4]
	add ebx,48
	invoke drd_imageDrawCrop,ebx,marioBegin,ecx,0,0,300,400 ;draw idle right
	ret
changepic endp

squareCollision proc, objOneAdr:dword,objTwoAdr:dword
	mov eax, objOneAdr
	mov edx, objTwoAdr
	mov edx,[edx]
	cmp [eax],edx ;check which x is bigger
	jg OneBigger
	;TwoBigger:
	mov eax,[eax]
	sub eax,edx
	neg eax ;get difference between bigger and larger
	mov edx,objOneAdr
	jmp FinalX

	OneBigger:
	mov eax,[eax]
	sub edx,eax
	neg edx ;get difference between bigger and larger
	mov eax,edx
	mov edx,objOneAdr
	
	FinalX:
	cmp eax,[edx+getImgWidth] ;Compare difference between x's and smaller width
	jge nocol
	;colX
	mov eax,objOneAdr
	mov eax,[eax+getY]
	mov edx,objTwoAdr
	cmp eax,[edx+getY] ;compare y's
	jg OneYBigger

	mov edx,[edx+getY]
	sub eax,edx
	neg eax ;get the difference between bigger and larger
	mov edx,objOneAdr
	jmp FinalY
	OneYBigger:
	mov edx,[edx+getY]
	sub edx,eax
	neg edx ;get the difference between bigger and larger
	mov eax,edx
	mov edx,objTwoAdr

	FinalY:	
	mov ecx,[edx+getImgHeight] 
	cmp eax,[edx+getImgHeight] ;Compare difference between y's and smaller height
	jge nocol

	;;;;;col;;;;;
	mov eax,1
	ret

	nocol:
	mov eax,0
	ret
squareCollision endp

jumpCollision proc objOne:dword,objTwo:dword
	mov eax,objOne
	mov ecx,[eax+getY]
	mov edx,[eax+getImgHeight]
	add ecx,edx ;find height of legs
	mov ebx,objTwo
	mov ebx,[ebx+getY]
	add ebx,10
	cmp ecx,ebx
	jge nothing
	mov ebx,13
	mov [eax+getYdir],ebx	;give mario the jump boost
	mov ecx,1
	ret
	nothing:
	mov ecx,0
	ret
jumpCollision endp

handleCollision proc marAdr:dword,goomAdr:dword,scoreloc:dword,playingloc:dword
	invoke squareCollision,marAdr,goomAdr ;check general collision
	cmp eax,0
	je nothing
	invoke jumpCollision,marAdr,goomAdr ;check jump collision
	cmp ecx,1
	je scoreadd ;add score if jump collision
	;there is collision but no jump collision
	mov eax,playingloc
	mov ebx,0
	mov [eax],ebx ;die
	mov ebx,goomAdr

	ret
	scoreadd:
	mov eax,scoreloc
	mov ebx,1
	add [eax],ebx ;add to score
	mov eax,goomAdr
	mov ebx,0
	mov [eax+68],ebx
	nothing:
	ret
handleCollision endp
getXgoombas proc gOne:dword,gTwo:dword,gThree:dword,gFour:dword,gFive:dword,gSix:dword
	;randomize x of all goombas
	;1
	mov ebx,gOne
	invoke randx,500,30000
	mov [ebx],eax
	;2
	mov ebx,gTwo
	invoke randx,500,30000
	mov [ebx],eax
	;3
	mov ebx,gThree
	invoke randx,500,30000
	mov [ebx],eax
	;4
	mov ebx,gFour
	invoke randx,500,30000
	mov [ebx],eax
	;5
	mov ebx,gFive
	invoke randx,500,30000
	mov [ebx],eax
	;6
	mov ebx,gSix
	invoke randx,500,30000
	mov [ebx],eax
	ret
getXgoombas endp
getCoinLocs proc c1:dword,c2:dword,c3:dword,c4:dword,c5:dword,c6:dword
	;randomize locs of all coins
	;1
	mov ebx,c1
	invoke randx,500,30000
	mov [ebx],eax
	invoke randx,30,350
	mov [ebx+4],eax
	;2
	mov ebx,c2
	invoke randx,500,30000
	mov [ebx],eax
	invoke randx,30,350
	mov [ebx+4],eax
	;3
	mov ebx,c3
	invoke randx,500,30000
	mov [ebx],eax
	invoke randx,30,350
	mov [ebx+4],eax
	;4
	mov ebx,c4
	invoke randx,500,30000
	mov [ebx],eax
	invoke randx,30,350
	mov [ebx+4],eax
	;5
	mov ebx,c5
	invoke randx,500,30000
	mov [ebx],eax
	invoke randx,30,350
	mov [ebx+4],eax
	;6
	mov ebx,c6
	invoke randx,500,30000
	mov [ebx],eax
	invoke randx,30,350
	mov [ebx+4],eax
	ret
getCoinLocs endp
replay proc playingloc:dword,marioAdr:dword,goomba1Adr:dword,goomba2Adr:dword,goomba3Adr:dword,goomba4Adr:dword,goomba5Adr:dword,goomba6Adr:dword,back1Adr:dword,scoreAdr:dword,coinAdr1:dword,coinAdr2:dword,coinAdr3:dword,coinAdr4:dword,coinAdr5:dword,coinAdr6:dword
	invoke GetAsyncKeyState,VK_SPACE
	cmp ax,0
	je nothing
	mov eax,playingloc
	mov ebx,1
	mov [eax],ebx
	mov eax,marioAdr
	mov ebx,230 ;reset mario hitbox
	mov [eax],ebx
	invoke getXgoombas,goomba1Adr,goomba2Adr,goomba3Adr,goomba4Adr,goomba5Adr,goomba6Adr
	mov eax,goomba1Adr
	mov ebx,1
	;bring back goombas
	;1
	mov [eax+68],ebx
	;2
	mov eax,goomba2Adr
	mov [eax+68],ebx
	;3
	mov eax,goomba3Adr
	mov [eax+68],ebx
	;4
	mov eax,goomba4Adr
	mov [eax+68],ebx
	;5
	mov eax,goomba5Adr
	mov [eax+68],ebx
	;6
	mov eax,goomba6Adr
	mov [eax+68],ebx
	;reset back
	mov eax,back1Adr
	mov ebx,400
	mov [eax+72],ebx
	mov eax,scoreAdr
	mov ebx,0
	mov [eax],ebx
	invoke getCoinLocs,coinAdr1,coinAdr2,coinAdr3,coinAdr4,coinAdr5,coinAdr6 ;coin locs
	mov eax,1
	mov ebx,coinAdr1
	mov [ebx+68],eax
	mov ebx,coinAdr2
	mov [ebx+68],eax
	mov ebx,coinAdr3
	mov [ebx+68],eax
	mov ebx,coinAdr4
	mov [ebx+68],eax
	mov ebx,coinAdr5
	mov [ebx+68],eax
	mov ebx,coinAdr6
	mov [ebx+68],eax
	nothing:
	ret
replay endp

checkWin proc pointsAdr:dword,playingAdr:dword
	mov eax,pointsAdr
	mov ecx,12
	cmp [eax],ecx ;check if won
	je winner
	ret
	winner:
	mov ecx,1
	neg ecx
	mov eax,playingAdr
	mov [eax],ecx ;move to win mode
	ret
checkWin endp
handleGoombas proc goombaAdr:dword,marioAdr:dword,scoreAdr:dword,playingAdr:dword
		mov eax,goombaAdr
		mov ebx,1
		cmp [eax+68],ebx ;check if alive
		jne nothing
		invoke getkeyback, eax
		mov eax,goombaAdr
		invoke movegoomba,eax ;move the goomba
		mov eax, goombaAdr
		mov ebx,marioAdr
		mov ecx,scoreAdr
		mov edx,playingAdr
		invoke handleCollision,ebx,eax,ecx,edx
		nothing:
		ret
handleGoombas endp
drawGoombas proc goombaAdr1:dword,goombaAdr2:dword,goombaAdr3:dword,goombaAdr4:dword,goombaAdr5:dword,goombaAdr6:dword
	;draw 1
	mov eax,goombaAdr1
	mov ebx,1
	cmp [eax+68],ebx
	jne doTwo
	mov ecx,eax
	add ecx,28
	mov edx,eax
	add edx,4
	mov ebx,[edx]
	INVOKE drd_imageDraw, ecx, [eax], [edx]
	;draw 2
	doTwo:
	mov eax,goombaAdr2
	mov ebx,1
	cmp [eax+68],ebx
	jne doThree
	mov ecx,eax
	add ecx,28
	mov edx,eax
	add edx,4

	INVOKE drd_imageDraw, ecx, [eax], [edx]
	;draw 3
	doThree:
	mov eax,goombaAdr3
	mov ebx,1
	cmp [eax+68],ebx
	jne doFour
	mov ecx,eax
	add ecx,28
	mov edx,eax
	add edx,4

	INVOKE drd_imageDraw, ecx, [eax], [edx]
	;draw 4
	doFour:
	mov eax,goombaAdr4
	mov ebx,1
	cmp [eax+68],ebx
	jne doFive
	mov ecx,eax
	add ecx,28
	mov edx,eax
	add edx,4

	INVOKE drd_imageDraw, ecx, [eax], [edx]
	;draw 5
	doFive:
	mov eax,goombaAdr5
	mov ebx,1
	cmp [eax+68],ebx
	jne doSix
	mov ecx,eax
	add ecx,28
	mov edx,eax
	add edx,4

	INVOKE drd_imageDraw, ecx, [eax], [edx]
	;draw 6
	doSix:
	mov eax,goombaAdr6
	mov ebx,1
	cmp [eax+68],ebx
	jne stop
	mov ecx,eax
	add ecx,28
	mov edx,eax
	add edx,4

	INVOKE drd_imageDraw, ecx, [eax], [edx]

	stop:
	ret
drawGoombas endp
handleCoins proc coinAdr:dword,marioAdr,scoreAdr
	mov ebx,coinAdr
	mov eax,1
	mov ecx,[ebx+68]
	cmp ecx,eax
	jne nothing
	push ebx
	invoke getkeyback,ebx
	pop ebx
	push ebx
	invoke movegoomba,ebx
	pop ebx
	mov ecx,marioAdr
	push ebx
	invoke squareCollision,ebx,ecx ;check if coin collides
	pop ebx
	mov edx,1
	cmp eax,edx
	jne noColl
	mov edx,0
	mov [ebx+68],edx ;kill coin
	mov ecx,scoreAdr
	mov edx,1
	add [ecx],edx ;add 1 to score
	noColl:
	nothing:
	ret
handleCoins endp

drawCoins proc c1:dword,c2:dword,c3:dword,c4:dword,c5:dword,c6:dword
	mov ebx,c1
	mov edx,[ebx+68]
	mov ecx,1
	cmp edx,ecx
	jne co2
	mov eax,ebx
	add eax,28
	mov ecx,[ebx]
	mov edx,[ebx+4]
	invoke drd_imageDraw,eax,ecx,edx
	co2:
	mov ebx,c2
	mov edx,[ebx+68]
	mov ecx,1
	cmp edx,ecx
	jne co3
	mov eax,ebx
	add eax,28
	mov ecx,[ebx]
	mov edx,[ebx+4]
	invoke drd_imageDraw,eax,ecx,edx
	co3:
	mov ebx,c3
	mov edx,[ebx+68]
	mov ecx,1
	cmp edx,ecx
	jne co4
	mov eax,ebx
	add eax,28
	mov ecx,[ebx]
	mov edx,[ebx+4]
	invoke drd_imageDraw,eax,ecx,edx
	co4:
	mov ebx,c4
	mov edx,[ebx+68]
	mov ecx,1
	cmp edx,ecx
	jne co5
	mov eax,ebx
	add eax,28
	mov ecx,[ebx]
	mov edx,[ebx+4]
	invoke drd_imageDraw,eax,ecx,edx
	co5:
	mov ebx,c5
	mov edx,[ebx+68]
	mov ecx,1
	cmp edx,ecx
	jne co6
	mov eax,ebx
	add eax,28
	mov ecx,[ebx]
	mov edx,[ebx+4]
	invoke drd_imageDraw,eax,ecx,edx
	co6:
	mov ebx,c6
	mov edx,[ebx+68]
	mov ecx,1
	cmp edx,ecx
	jne no
	mov eax,ebx
	add eax,28
	mov ecx,[ebx]
	mov edx,[ebx+4]
	invoke drd_imageDraw,eax,ecx,edx
	no:
	ret
drawCoins endp