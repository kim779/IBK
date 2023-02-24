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
#define	BEND	320
#define	FOR	321
#define	FUNCTION	322
#define	IF	323
#define	OR	324
#define	MOD	325
#define	NOT	326
#define	THEN	327
#define	TO	328
#define	WHILE	329
#define	CROSS	330
#define	ABOVE	331
#define	BELOW	332


extern YYSTYPE SysTradinglval;
