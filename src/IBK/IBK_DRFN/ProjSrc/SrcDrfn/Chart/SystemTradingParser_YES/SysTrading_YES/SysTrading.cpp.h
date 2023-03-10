typedef union  {
			char	name[NAME_SZ];
			int		ival;
			double	dval;
			EXPR	expr;
		} YYSTYPE;
#define	NAME	258
#define	BOOL_TYPE	259
#define	INT_NUMBER	260
#define	DBL_NUMBER	261
#define	RESERVED_VAR	262
#define	RESERVED_COND	263
#define	RESERVED_TEXT	264
#define	STRING	265
#define	ARRAY	266
#define	INPUT	267
#define	VARIABLE	268
#define	DEF_STRING	269
#define	DEF_STRING_SIMPLE	270
#define	DEF_STRING_ARRAY	271
#define	DEF_NUMERIC	272
#define	DEF_NUMERIC_SIMPLE	273
#define	DEF_NUMERIC_ARRAY	274
#define	DEF_BOOL	275
#define	DEF_BOOL_SIMPLE	276
#define	DEF_BOOL_ARRAY	277
#define	JMCODE	278
#define	CLOSE	279
#define	OPEN	280
#define	HIGH	281
#define	LOW	282
#define	VOLUME	283
#define	AMOUNT	284
#define	DATE	285
#define	TIME	286
#define	DATACNT	287
#define	CURRENTDATE	288
#define	CURRENTTIME	289
#define	CURRENTBAR	290
#define	STMT_SUFFIX	291
#define	COMMA	292
#define	EQ	293
#define	NE	294
#define	LT	295
#define	LE	296
#define	GT	297
#define	GE	298
#define	PLUS	299
#define	MINUS	300
#define	MULT	301
#define	DIVIDE	302
#define	LPAREN	303
#define	RPAREN	304
#define	LBRAC	305
#define	RBRAC	306
#define	COLON	307
#define	SEMICOLON	308
#define	STAR	309
#define	STARSTAR	310
#define	UPARROW	311
#define	AND	312
#define	BBEGIN	313
#define	BREAK	314
#define	DO	315
#define	DOWN	316
#define	DOWNTO	317
#define	ELSE	318
#define	ELSEIF	319
#define	BEND_SEMICOLON	320
#define	BEND	321
#define	FOR	322
#define	FUNCTION	323
#define	IF	324
#define	OR	325
#define	MOD	326
#define	NOT	327
#define	THEN	328
#define	TO	329
#define	WHILE	330
#define	CROSS	331
#define	ABOVE	332
#define	BELOW	333


extern YYSTYPE SysTradinglval;
