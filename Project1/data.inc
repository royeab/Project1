.const
	widthb equ 1280
	heightb equ 720
	keypress equ 1000h
	goomnum equ 20
	xending equ 30000
	CharacterLen equ 108
	GoombaY equ 375
	getY equ 4
	getYdir equ 12
	getXdir equ 8
	getLeftKey equ 16
	getRightKey equ 20
	getUpKey equ 24
	getImgWidth equ 32
	getImgHeight equ 36
	marioGroundloc equ 250
.DATA	
	marioloc BYTE "mario.bmp",0
	mario2loc BYTE "mario2.bmp",0
	backloc BYTE "background.bmp",0
	goombaloc BYTE "goomba.bmp",0
	isright dword 1
	grv dword 0
	goombaamunt dword 0

	KEYS STRUCT
		Left qword ?
		Right qword ?
		Up qword ?
	KEYS ends
	CHARACTER STRUCT
		pos POINT<> ;x=0 y=4
		dir POINT<> ;x=8 y=12
		keys KEYS<> ;Left = 16 Right = 20 Up = 24			
		Right Img<> ;28-48 width:32 height:36
		Left Img<> ;48-68	
		UpRight Img<> ;68-88
		UpLeft Img<> ;88-108
	CHARACTER ends
	goombas CHARACTER 100 dup(<>)
	textBuffer byte 64 dup(0)
	mario CHARACTER<<200,marioGroundloc>,<0,0>,<VK_LEFT,VK_RIGHT,VK_UP>>
	back1 CHARACTER<<-1280,0>,<1,0>,<VK_LEFT,VK_RIGHT,VK_UP>>
	back2 CHARACTER<<0,0>,<1,0>,<VK_LEFT,VK_RIGHT,VK_UP>>
	goomba CHARACTER<<500,GoombaY>,<0,0>,<VK_LEFT,VK_RIGHT,VK_UP>>