
#define	MAX_axisPALETTE	256

COLORREF axisRGB[MAX_axisPALETTE] = {
	// user color
		PALETTERGB(204,   0,  51),	// 0
		PALETTERGB(255,   0,  51),
		PALETTERGB(  0,  51,  51),
		PALETTERGB( 51,  51,  51),
		PALETTERGB(102,  51,  51),
		PALETTERGB(153,  51,  51),
		PALETTERGB(204,  51,  51),
		PALETTERGB(255,  51,  51),
		PALETTERGB(  0, 102,  51),
		PALETTERGB( 51, 102,  51),

		PALETTERGB(102, 102,  51),	// 10
		PALETTERGB(153, 102,  51),
		PALETTERGB(204, 102,  51),
		PALETTERGB(255, 102,  51),
		PALETTERGB(  0, 153,  51),
		PALETTERGB( 51, 153,  51),
		PALETTERGB(102, 153,  51),
		PALETTERGB(153, 153,  51),
		PALETTERGB(204, 153,  51),
		PALETTERGB(255, 153,  51),

		PALETTERGB(  0, 204,  51),	// 20
		PALETTERGB( 51, 204,  51),
		PALETTERGB(102, 204,  51),
		PALETTERGB(153, 204,  51),
		PALETTERGB(204, 204,  51),
		PALETTERGB(255, 204,  51),
		PALETTERGB( 51, 255,  51),
		PALETTERGB(102, 255,  51),
		PALETTERGB(153, 255,  51),
		PALETTERGB(204, 255,  51),

		PALETTERGB(255, 255,  51),	// 30
		PALETTERGB(  0,   0, 102),
		PALETTERGB( 51,   0, 102),
		PALETTERGB(102,   0, 102),
		PALETTERGB(153,   0, 102),
		PALETTERGB(204,   0, 102),
		PALETTERGB(255,   0, 102),
		PALETTERGB(  0,  51, 102),
		PALETTERGB( 51,  51, 102),
		PALETTERGB(102,  51, 102),

		PALETTERGB(153,  51, 102),	// 40
		PALETTERGB(204,  51, 102),
		PALETTERGB(255,  51, 102),
		PALETTERGB(  0, 102, 102),
		PALETTERGB( 51, 102, 102),
		PALETTERGB(102, 102, 102),
		PALETTERGB(153, 102, 102),
		PALETTERGB(204, 102, 102),
		PALETTERGB(  0, 153, 102),
		PALETTERGB(108,  11,   1),

		PALETTERGB(102, 153, 102),	// 50
		PALETTERGB(153, 153, 102),
		PALETTERGB(204, 153, 102),
		PALETTERGB(255, 153, 102),
		PALETTERGB(  0, 204, 102),
		PALETTERGB( 51, 204, 102),
		PALETTERGB(153, 204, 102),
		PALETTERGB(204, 204, 102),
		PALETTERGB(255, 204, 102),
		PALETTERGB(  0, 255, 102),

		PALETTERGB( 51, 255, 102),	// 60
		PALETTERGB(153, 255, 102),
		PALETTERGB(204, 255, 102),
		PALETTERGB(255,   0, 204),
		PALETTERGB(204,   0, 255),
		PALETTERGB(  0, 153, 153),
		PALETTERGB(153,  51, 153),
		PALETTERGB(153,   0, 153),
		PALETTERGB(204,   0, 153),
		PALETTERGB(  0,   0, 153),

		PALETTERGB( 51,  51, 153),	// 70
		PALETTERGB(102,   0, 153),
		PALETTERGB(204,  51, 153),
		PALETTERGB(255,   0, 153),
		PALETTERGB(  0, 102, 153),
		PALETTERGB( 51, 102, 153),
		PALETTERGB(102,  51, 153),
		PALETTERGB(153, 102, 153),
		PALETTERGB(204, 102, 153),
		PALETTERGB(255,  51, 153),

		PALETTERGB( 51, 153, 153),	// 80
		PALETTERGB(102, 153, 153),
		PALETTERGB(153, 153, 153),
		PALETTERGB(204, 153, 153),
		PALETTERGB(255, 153, 153),
		PALETTERGB(  0, 204, 153),
		PALETTERGB( 51, 204, 153),
		PALETTERGB(102, 204, 102),
		PALETTERGB(153, 204, 153),
		PALETTERGB(204, 204, 153),

		PALETTERGB(255, 204, 153),	// 90
		PALETTERGB(  0, 255, 153),
		PALETTERGB( 51, 255, 153),
		PALETTERGB(102, 204, 153),
		PALETTERGB(153, 255, 153),
		PALETTERGB(204, 255, 153),
		PALETTERGB(255, 255, 153),
		PALETTERGB(  0,   0, 204),
		PALETTERGB( 51,   0, 153),
		PALETTERGB(102,   0, 204),

		PALETTERGB(153,   0, 204),	// 100
		PALETTERGB(204,   0, 204),
		PALETTERGB(  0,  51, 153),
		PALETTERGB( 51,  51, 204),
		PALETTERGB(102,  51, 204),
		PALETTERGB(153,  51, 204),
		PALETTERGB(204,  51, 204),
		PALETTERGB(255,  51, 204),
		PALETTERGB(  0, 102, 204),
		PALETTERGB( 51, 102, 204),

		PALETTERGB(102, 102, 153),	// 110
		PALETTERGB(153, 102, 204),
		PALETTERGB(204, 102, 204),
		PALETTERGB(255, 102, 153),
		PALETTERGB(  0, 153, 204),
		PALETTERGB( 51, 153, 204),
		PALETTERGB(102, 153, 204),
		PALETTERGB(153, 153, 204),
		PALETTERGB(204, 153, 204),
		PALETTERGB(255, 153, 204),

		PALETTERGB(  0, 204, 204),	// 120
		PALETTERGB(252, 196,   0),
		PALETTERGB(102, 204, 204),
		PALETTERGB(153, 204, 204),
		PALETTERGB(204, 204, 204),
		PALETTERGB(255, 204, 204),
		PALETTERGB(  0, 255, 204),
		PALETTERGB( 51, 255, 204),
		PALETTERGB(102, 255, 153),
		PALETTERGB(153, 255, 204),

		PALETTERGB(204, 255, 204),	// 130
		PALETTERGB(255, 255, 204),
		PALETTERGB( 51,   0, 204),
		PALETTERGB(102,   0, 255),
		PALETTERGB(153,   0, 255),
		PALETTERGB(  0,  51, 204),
		PALETTERGB( 51,  51, 255),
		PALETTERGB(102,  51, 255),
		PALETTERGB(153,  51, 255),
		PALETTERGB(204,  51, 255),

		PALETTERGB(255,  51, 255),	// 140
		PALETTERGB(  0, 102, 255),
		PALETTERGB( 51, 102, 255),
		PALETTERGB(102, 102, 204),
		PALETTERGB(153, 102, 255),
		PALETTERGB(204, 102, 255),
		PALETTERGB(255, 102, 204),
		PALETTERGB(  0, 153, 255),
		PALETTERGB( 51, 153, 255),
		PALETTERGB(102, 153, 255),

		PALETTERGB(153, 153, 255),	// 150
		PALETTERGB(204, 153, 255),
		PALETTERGB(255, 153, 255),
		PALETTERGB(  0, 204, 255),
		PALETTERGB( 51, 204, 255),
		PALETTERGB(102, 204, 255),
		PALETTERGB(153, 204, 255),
		PALETTERGB(204, 204, 255),
		PALETTERGB(255, 204, 255),
		PALETTERGB( 51, 255, 255),

		PALETTERGB(102, 255, 204),	// 160
		PALETTERGB(153, 255, 255),
		PALETTERGB(204, 255, 255),
		PALETTERGB(255, 102, 102),
		PALETTERGB(102, 255, 102),
		PALETTERGB(255, 255, 102),
		PALETTERGB(102, 102, 255),
		PALETTERGB(255, 102, 255),
		PALETTERGB(102, 255, 255),
		PALETTERGB(165,   0,  33),

		PALETTERGB( 95,  95,  95),	// 170
		PALETTERGB(119, 119, 119),
		PALETTERGB(134, 134, 134),
		PALETTERGB(150, 150, 150),
		PALETTERGB(203, 203, 203),
		PALETTERGB(178, 178, 178),
		PALETTERGB(215, 215, 215),
		PALETTERGB(221, 221, 221),
		PALETTERGB(227, 227, 227),
		PALETTERGB(234, 234, 234),

		PALETTERGB(241, 241, 241),	// 180
		PALETTERGB(248, 248, 248),
		PALETTERGB(255, 251, 240),
		PALETTERGB(160, 160, 164),
		PALETTERGB(128, 128, 128),
		PALETTERGB(255,   0,   0),
		PALETTERGB(  0, 255,   0),
		PALETTERGB(255, 255,   0),
		PALETTERGB(  0,   0, 255),
		PALETTERGB(255,   0, 255),

		PALETTERGB(  0, 255, 255),	// 190
		PALETTERGB(255, 255, 255),

	// system color
		PALETTERGB(255, 255, 255),	// 192
		PALETTERGB(255, 192, 192),
		PALETTERGB(255, 224, 192),
		PALETTERGB(255, 255, 192),
		PALETTERGB(192, 255, 192),
		PALETTERGB(192, 255, 255),
		PALETTERGB(192, 192, 255),
		PALETTERGB(255, 192, 255),
		PALETTERGB(224, 224, 224),
		PALETTERGB(255, 128, 128),
		PALETTERGB(255, 192, 128),
		PALETTERGB(255, 255, 128),
		PALETTERGB(128, 255, 128),
		PALETTERGB(128, 255, 255),
		PALETTERGB(128, 128, 255),
		PALETTERGB(255, 128, 255),

		PALETTERGB(192, 192, 192),	// 208
		PALETTERGB(255,   0,   0),
		PALETTERGB(255, 128,   0),
		PALETTERGB(255, 255,   0),
		PALETTERGB(  0, 255,   0),
		PALETTERGB(  0, 255, 255),
		PALETTERGB(  2,  1, 254),
		PALETTERGB(255,   0, 255),
		PALETTERGB(128, 128, 128),
		PALETTERGB(102,   0,   0),
		PALETTERGB(192,  64,   0),
		PALETTERGB(192, 192,   0),
		PALETTERGB(  0, 192,   0),
		PALETTERGB(  0, 192, 192),
		PALETTERGB(  0,   0, 192),
		PALETTERGB(192,   0, 192),

		PALETTERGB( 64,  64,  64),	// 224
		PALETTERGB( 91,   0,   0),
		PALETTERGB(128,  64,   0),
		PALETTERGB(128, 128,   0),
		PALETTERGB(  0, 128,   0),
		PALETTERGB(  0, 128, 128),
		PALETTERGB(  0,   0, 128),
		PALETTERGB(128,   0, 128),
		PALETTERGB(  0,   0,   0),
		PALETTERGB(  64,  0,   0),
		PALETTERGB(128,  64,  64),
		PALETTERGB( 64,  64,   0),
		PALETTERGB(  0,  64,   0),
		PALETTERGB(  0,  64,  64),
		PALETTERGB(  0,   0,  64),
		PALETTERGB( 64,   0,  64),

		PALETTERGB(255, 255, 255),	// 240
		PALETTERGB(238, 238, 238),
		PALETTERGB(221, 221, 221),
		PALETTERGB(204, 204, 204),
		PALETTERGB(187, 187, 187),
		PALETTERGB(170, 170, 170),
		PALETTERGB(153, 153, 153),
		PALETTERGB(136, 136, 136),
		PALETTERGB(119, 119, 119),
		PALETTERGB(102, 102, 102),
		PALETTERGB( 85,  85,  85),
		PALETTERGB( 68,  68,  68),
		PALETTERGB( 51,  51,  51),
		PALETTERGB( 34,  34,  34),
		PALETTERGB( 17,  17,  17),
		PALETTERGB(  0,   0,   0),	// 255
};