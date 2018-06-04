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
	invoke GetAsyncKeyState, VK_UP
	cmp ax,0
	je notup
	mov eax,marioGroundloc
	cmp [ebx+getY],eax
	jne notup
	mov ecx,20
	mov [ebx+getYdir],ecx
	notup:
	ret
getkeysmar endp
movebackTwo proc objAdr:dword
	;drd_imageDrawCrop PROTO pimg:DWORD, dstX:DWORD, dstY:DWORD, srcX:DWORD, srcY:DWORD, srcWidth:DWORD, srcHeight:DWORD
	mov ebx,objAdr
	
	mov eax,ebx
	add eax,28
	mov edx,[ebx+73]
	
	sub edx,[ebx+8]
	mov [ebx+73],edx
	mov ecx,[ebx+69]
	add ecx,[ebx+8]
	mov [ebx+69],ecx
	cmp ecx,widthb
	je reset
	pusha
	invoke drd_imageDrawCrop,eax,0,0,ecx,0,widthb,heightb
	popa
	invoke drd_imageDrawCrop, eax,edx,0,0,0,widthb,heightb
	mov edx,0
	mov [ebx+8],edx
	
	ret

	reset:
		mov ecx,0
		mov [ebx+69],edx
		mov edx,widthb
		mov [ebx+73],edx
		pusha
		invoke drd_imageDrawCrop,eax,0,0,ecx,0,widthb,heightb
		popa
		invoke drd_imageDrawCrop, eax,edx,0,0,0,widthb,heightb
		ret
movebackTwo endp
moveback proc backAdr:dword
	mov eax,1
	cmp [ebx+getXdir],eax
	je left
	mov eax,-1280
	cmp [ebx],eax
	jne nothing1
	mov eax,1280
	mov [ebx],eax
	nothing1:
	jmp startingp
	left:
	mov eax,1280
	cmp [ebx],eax
	jne nothing2
	mov eax,-1280
	mov [ebx],eax
	nothing2:
	startingp:
	mov ebx,backAdr
	mov eax,[ebx+getXdir]
	add[ebx],eax
	mov eax,0
	mov [ebx+getXdir],eax
	ret
moveback endp
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
		
	;move:
	;mov ebx,backAdr
	;mov eax,[ebx+getXdir]
	;add [ebx],eax
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
	sub ecx,min
	rdrand eax
	idiv ecx
	add edx,min
	mov eax,edx
	pop ecx
	pop edx
	ret
randx endp
changepic proc, back:dword
	mov ebx,back
	mov eax,[ebx+getXdir]
	cmp eax,-10
	je left
	cmp eax,10
	je right
	mov ecx,isright
	ret
	right:
	mov ecx,-1
	ret
	left:
	mov ecx,1
	ret
changepic endp

squareCollision proc, objOneAdr:dword,objTwoAdr:dword
	mov eax, objOneAdr
	mov edx, objTwoAdr
	mov edx,[edx]
	cmp [eax],edx
	jg OneBigger
	
	mov eax,[eax]
	sub eax,edx
	neg eax
	mov edx,objOneAdr
	jmp FinalX

	OneBigger:
	mov eax,[eax]
	sub edx,eax
	neg edx
	mov eax,edx
	mov edx,objOneAdr
	
	FinalX:
	cmp eax,[edx+getImgWidth]
	jge nocol

	mov eax,objOneAdr
	mov eax,[eax+getY]
	mov edx,objTwoAdr
	cmp eax,[edx+getY]
	jg OneYBigger

	mov edx,[edx+getY]
	sub eax,edx
	neg eax
	mov edx,objOneAdr
	jmp FinalY
	OneYBigger:
	mov edx,[edx+getY]
	sub edx,eax
	neg edx
	mov eax,edx
	mov edx,objTwoAdr

	FinalY:	
	mov ecx,[edx+getImgHeight]
	cmp eax,[edx+getImgHeight]
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
	add ecx,edx
	mov ebx,objTwo
	mov ebx,[ebx+getY]
	add ebx,10
	cmp ecx,ebx
	jge nothing
	mov ebx,13
	mov [eax+getYdir],ebx
	mov ecx,1
	ret
	nothing:
	mov ecx,0
	ret
jumpCollision endp

handleCollision proc marAdr:dword,goomAdr:dword,scoreloc:dword,playingloc:dword
	invoke squareCollision,marAdr,goomAdr
	cmp eax,0
	je nothing
	invoke jumpCollision,marAdr,goomAdr
	cmp ecx,1
	je scoreadd
	mov eax,playingloc
	mov ebx,0
	mov [eax],ebx
	mov ebx,goomAdr

	ret
	scoreadd:
	mov eax,scoreloc
	mov ebx,1
	add [eax],ebx
	mov eax,goomAdr
	mov ebx,0
	mov [eax+68],ebx
	nothing:
	ret
handleCollision endp
getXgoombas proc gOne:dword,gTwo:dword,gThree:dword,gFour:dword,gFive:dword,gSix:dword
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
replay proc playingloc:dword,marioAdr:dword,goomba1Adr:dword,goomba2Adr:dword,goomba3Adr:dword,goomba4Adr:dword,goomba5Adr:dword,goomba6Adr:dword,back1Adr:dword,scoreAdr:dword
	invoke GetAsyncKeyState,VK_SPACE
	cmp ax,0
	je nothing
	mov eax,playingloc
	mov ebx,1
	mov [eax],ebx
	mov eax,marioAdr
	mov ebx,marioBegin
	mov [eax],ebx
	invoke getXgoombas,goomba1Adr,goomba2Adr,goomba3Adr,goomba4Adr,goomba5Adr,goomba6Adr
	mov eax,goomba1Adr
	mov ebx,1
	mov [eax],ebx
	mov eax,goomba2Adr
	mov [eax],ebx
	mov eax,goomba3Adr
	mov [eax],ebx
	mov eax,goomba4Adr
	mov [eax],ebx
	mov eax,goomba5Adr
	mov [eax],ebx
	mov eax,goomba6Adr
	mov [eax],ebx
	mov eax,back1Adr
	mov ebx,backOneBegin
	mov [eax],ebx
	;mov eax,back2Adr
	;mov ebx,backTwoBegin
	;mov [eax],ebx
	mov eax,scoreAdr
	mov ebx,0
	mov [eax],ebx
	nothing:
	ret
replay endp

checkWin proc pointsAdr:dword,playingAdr:dword
	mov eax,pointsAdr
	mov ecx,6
	cmp [eax],ecx
	je winner
	ret
	winner:
	mov ecx,1
	neg ecx
	mov eax,playingAdr
	mov [eax],ecx
	ret
checkWin endp
handleGoombas proc goombaAdr:dword,marioAdr:dword,scoreAdr:dword,playingAdr:dword
		mov eax,goombaAdr
		mov ebx,1
		cmp [eax+68],ebx
		jne nothing
		invoke getkeyback, eax
		mov eax,goombaAdr
		invoke movegoomba,eax
		mov eax, goombaAdr
		mov ebx,marioAdr
		mov ecx,scoreAdr
		mov edx,playingAdr
		invoke handleCollision,ebx,eax,ecx,edx
		nothing:
		ret
handleGoombas endp
drawGoombas proc goombaAdr1:dword,goombaAdr2:dword,goombaAdr3:dword,goombaAdr4:dword,goombaAdr5:dword,goombaAdr6:dword
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