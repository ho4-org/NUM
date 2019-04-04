/*
 * 番号発生プログラム
 *                      by K.Hoshi
 * usage : NUM [-s start][-r][-z][-n][-b|-o|-d|-h]|[-h] endnum
 */
#include	<stdio.h>
#include	<stdlib.h>
#include	<memory.h>
#define 	BIN		0x01
#define 	OCT		0x02
#define 	DEC		0x04
#define 	HEX		0x08
#define 	OFF		0
#define 	ON		1
#define 	NON		2

main( argc, argv )
int 	argc ;
char	*argv[] ;
{
	extern	char	*optarg ;
	extern	int 	optind ;
	extern	int 	opterr ;
	long	max ;
	long	ci ;
	long	cj ;
	long	ret ;
	long	start ;
	long	mgn ;
	long	end ;
	long	bodh ;
	short	errflg ;
	short	rflg ;
	short	zflg ;
	short	nflg ;
	short	mflg ;
	short	keta ;
	char	buffer[40] ;
	bodh = 0 ;
	rflg = 0 ;
	zflg = 0 ;
	nflg = 0 ;
	errflg = 0 ;
	keta = 0 ;
	start = 1 ;
	mgn = 1 ;
	while( ( ret = getopt( argc, argv, "bodhrzns:m:" ) ) != EOF ) {
		switch( ret ) {
		case 'b' :
			if( bodh ) {
				errflg++ ;
			} else {
				bodh |= BIN ;
			}
			break ;
		case 'o' :
			if( bodh ) {
				errflg++ ;
			} else {
				bodh |= OCT ;
			}
			break ;
		case 'd' :
			if( bodh ) {
				errflg++ ;
			} else {
				bodh |= DEC ;
			}
			break ;
		case 'h' :
			if( argc == 2 ) {
				(void)printf( "   usage : NUM [-s start][-r][-z][-n][-b|-o|-d|-h]|[-h] endnum\n" )	;
				(void)printf( "-s start : 初期値    ふつ〜  1\n" ) ;
				(void)printf( "      -r : 逆順      ふつ〜  正順\n" ) ;
				(void)printf( "      -z : 0 つける  ふつ〜  0 なし\n" ) ;
				(void)printf( "      -n : 改行あり  ふつ〜  改行なし\n" ) ;
				(void)printf( "      -m : マージン  ふつ〜  1\n" ) ;
				(void)printf( "      -b : ２進数\n" ) ;
				(void)printf( "      -o : ８進数\n" ) ;
				(void)printf( "      -d : 10進数    ふつ〜  これ\n" ) ;
				(void)printf( "      -h : 16進数\n" ) ;
				(void)printf( "      -h : このヘルプ\n" ) ;
				(void)printf( "  endnum : 最終値\n" ) ;
				(void)printf( "  番号発生プログラム  by K.Hoshi\n" ) ;
				exit( 0 ) ;
			} else {
				if( bodh ) {
					errflg++ ;
				} else {
					bodh |= HEX ;
				}
			}
			break ;
		case 'r' :
			rflg++ ;
			break ;
		case 'z' :
			zflg++ ;
			if( start < 0 ) {
				errflg++ ;
				(void)fprintf( stderr, "初期値がマイナスのときは零つけられないょ！\n" )	;
			}
			break ;
		case 'n' :
			nflg++ ;
			break ;
		case 's' :
			start = strtol( optarg, (char **)NULL, 0 ) ;
			if( start < 0 && zflg != 0 ) {
				errflg++ ;
				(void)fprintf( stderr, "初期値がマイナスのときは零つけられないょ！\n" )	;
			}
			break ;
		case 'm' :
			mgn = strtol( optarg, (char **)NULL, 0 ) ;
			if( mgn < 1 ) {
				errflg++ ;
				(void)fprintf( stderr, "マイナスのマージンはつけられないょ！\n" )	;
			}
			mflg++ ;
			break ;
		case '?' :
			errflg++ ;
			break ;
		}
	}
	if( errflg != 0 || argc != optind+1 ) {
		(void)fprintf( stderr, "usage : NUM [-s start][-r][-z][-n][-b|-o|-d|-h]|[-h] endnum\n" )	;
		exit( 0 ) ;
	}
	max = strtol( argv[optind], (char **)NULL, 0 ) ;
	if( bodh == 0 ) {
		bodh = DEC ;
	}
	if( zflg ) {
		(void)memset( &buffer[0], 0x00, 40 ) ;
		switch( bodh ) {
		case BIN :
			(void)bsprintf( &buffer[0], max ) ;
			break ;
		case OCT :
			(void)sprintf( &buffer[0], "%o\0", max ) ;
			break ;
		case DEC :
			(void)sprintf( &buffer[0], "%d\0", max ) ;
			break ;
		case HEX :
			(void)sprintf( &buffer[0], "%x\0", max ) ;
			break ;
		}
		keta = strlen( &buffer[0] ) ;
	}
	if( rflg ) {
		ci = max ;
		end = start ;
	} else {
		ci = start ;
		end = max ;
	}
	while( 1 ) {
		if( bodh & OCT ) {
			(void)printf( "0" ) ;
		} else if( bodh & HEX ) {
			(void)printf( "0x" ) ;
		}
		if( zflg ) {
			(void)memset( &buffer[0], 0x00, 40 ) ;
			switch( bodh ) {
			case BIN :
				(void)bsprintf( &buffer[0], ci ) ;
				break ;
			case OCT :
				(void)sprintf( &buffer[0], "%o\0", ci ) ;
				break ;
			case DEC :
				(void)sprintf( &buffer[0], "%d\0", ci ) ;
				break ;
			case HEX :
				(void)sprintf( &buffer[0], "%x\0", ci ) ;
				break ;
			}
			for( cj = 0 ; cj < ( keta - strlen( &buffer[0] ) ) ; cj++ ) {
				(void)printf( "0" ) ;
			}
		}
		switch( bodh ) {
		case BIN :
			(void)bfprintf( stdout, ci ) ;
			(void)printf( " " ) ;
			break ;
		case OCT :
			(void)printf( "%o ", ci ) ;
			break ;
		case DEC :
			(void)printf( "%d ", ci ) ;
			break ;
		case HEX :
			(void)printf( "%x ", ci ) ;
			break ;
		}
		if( nflg ) {
			(void)printf( "\n" ) ;
		}
		if( mflg != OFF ) {
			if( rflg ) {
				ci -= mgn ;	
			} else {
				ci += mgn ;	
			}
		} else {
			if( rflg ) {
				ci-- ;
			} else {
				ci++ ;
			}
		}
		if( ( end < ci && rflg == OFF ) || ( end > ci && rflg == ON ) ) {
			break ;
		}
	}
	exit( 0 ) ;
}

int 	bitchk( num, x )
unsigned	long	num ;
long 	x ;
{
	unsigned	long	mask = 1 ;
	mask <<= x ;
	if( num & mask ) {
		return( ON ) ;
	} else if( mask > num ) {
		return( NON ) ;
	} else {
		return( OFF ) ;
	}
}

int 	bfprintf( std, num )
FILE 	*std ;
long	num ;
{
	long	ci ;
	for( ci = 31 ; ci >= 0 ; ci-- ) {
		switch( bitchk( (unsigned long)num, ci ) ) {
		case ON :
		/*	(void)fprintf( (FILE *)std, "1" ) ;	*/
			(void)fprintf( std, "1" ) ;
			break ;
		case OFF :
			(void)fprintf( std, "0" ) ;
			break ;
		case NON :
			if( 0 == ci ) {
				(void)fprintf( std, "0" ) ;
			}
			break ;
		}
	}
	return( 0 ) ;
}

int 	bsprintf( buff, num )
char	*buff ;
long	num ;
{
	long	ci ;
	for( ci = 31 ; ci >= 0 ; ci-- ) {
		switch( bitchk( (unsigned long)num, ci ) ) {
		case ON :
			(void)strcat( buff, "1" ) ;
			break ;
		case OFF :
			(void)strcat( buff, "0" ) ;
			break ;
		case NON :
			if( 0 == ci ) {
				(void)strcat( buff, "0" ) ;
			}
			break ;
		}
	}
	return( 0 ) ;
}
