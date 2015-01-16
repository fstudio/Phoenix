///
///
///
#ifndef  PHOENIX_UNIVERSALCHARDET_NSCORE_H
#define PHOENIX_UNIVERSALCHARDET_NSCORE_H

#include <stdint.h>

#ifdef DEBUG
#include <assert.h>
#define MOZ_ASSERT(x) assert(x)
#else
#define MOZ_ASSERT(x)
#endif

typedef bool PRBool;
typedef int PRInt32;
typedef unsigned int PRUint32;
typedef short PRInt16;
typedef unsigned short PRUint16;
typedef signed char PRInt8;
typedef unsigned char PRUint8;

#define PR_FALSE false
#define PR_TRUE true
#define nsnull 0


enum nsresult
{
	NS_OK,
	NS_ERROR_OUT_OF_MEMORY
};


//#define ArrayLength(x) (sizeof(x)/sizeof(x[0]))


#endif
