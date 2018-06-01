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
moveback proc backAdr:dword
	mov ebx,backAdr
	mov eax,10
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
		mov eax,10
		mov [ebx+getXdir],eax
		ret

	righti:
		mov eax,-10
		mov [ebx+getXdir],eax
		ret
getkeyback endp
movegoomba proc objAdr: dword
	mov ebx,objAdr
	mov eax,[ebx+getXdir]
	add [ebx],eax
	mov eax,0
	mov [ebx+getXdir],eax
	ret
movegoomba endp
jumpon proc maradr: dword, goobadr: dword
	
	ret
jumpon endp
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
	cmp eax,1
	je left
	mov ecx,-1
	ret
	left:
	mov ecx,1
	ret
changepic endp
findCenter proc, objAdr:dword
	push ebx
	mov ebx,objAdr
	mov ecx,[ebx+getY]
	mov eax,2
	idiv ecx
	mov ecx,eax
	mov edx,[ebx]
	idiv edx
	mov edx,eax
	pop ebx
	ret
findCenter endp

findRad proc, objAdr:dword
	push ebx
	mov ebx,objAdr
	mov ecx,[ebx+getImgHeight]
	mov eax,2
	idiv ecx
	ret
findRad endp
checkCollision proc, marAdr:dword,goombaAdr:dword
	mov eax,marAdr
	mov ebx,goombaAdr
	ret
checkCollision endp