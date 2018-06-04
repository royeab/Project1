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
	marioBegin equ 200
	backTwoBegin equ 0
	backOneBegin equ -1280
.DATA	
	marioloc BYTE "mario.bmp",0
	mario2loc BYTE "mario2.bmp",0
	backloc BYTE "background.bmp",0
	goombaloc BYTE "goomba.bmp",0
	gameoverloc BYTE "gameover.bmp",0
	winloc BYTE "youwin.bmp",0
	isright dword 1
	grv dword 0
	goombaamunt dword 0
	score dword 0
	playing dword 1
	jumpCounter dword 10
	KEYS STRUCT
		Left dword ?
		Right dword ?
		Up dword ?
	KEYS ends
	CHARACTER STRUCT
		pos POINT<> ;x=0 y=4
		dir POINT<> ;x=8 y=12
		keys KEYS<> ;Left = 16 Right = 20 Up = 24			
		Right Img<> ;28-48 width:32 height:36
		Left Img<> ;48-68
		alive BYTE 1
		XOne dword ? ;69
		xTwo dword ? ;73
		UpRight Img<> ;68-88
		UpLeft Img<> ;88-108
	CHARACTER ends
	textBuffer byte 64 dup(0)
	mario CHARACTER<<marioBegin,marioGroundloc>,<0,0>,<VK_LEFT,VK_RIGHT,VK_UP>>
	back1 CHARACTER<<backTwoBegin,0>,<0,0>,<VK_LEFT,VK_RIGHT,VK_UP>>
	back2 CHARACTER<<backOneBegin,0>,<0,0>,<VK_LEFT,VK_RIGHT,VK_UP>>
	goomba1 CHARACTER<<0,GoombaY>,<0,0>,<VK_LEFT,VK_RIGHT,VK_UP>>
	goomba2 CHARACTER<<0,GoombaY>,<0,0>,<VK_LEFT,VK_RIGHT,VK_UP>>
	goomba3 CHARACTER<<0,GoombaY>,<0,0>,<VK_LEFT,VK_RIGHT,VK_UP>>
	goomba4 CHARACTER<<0,GoombaY>,<0,0>,<VK_LEFT,VK_RIGHT,VK_UP>>
	goomba5 CHARACTER<<0,GoombaY>,<0,0>,<VK_LEFT,VK_RIGHT,VK_UP>>
	goomba6 CHARACTER<<0,GoombaY>,<0,0>,<VK_LEFT,VK_RIGHT,VK_UP>>
	gameover CHARACTER<<400,150>>
	win CHARACTER<<400,150>>
	
