#include <crtdbg.h>

#ifdef _DEBUG
	#define DEBUG_newtnew( _CLIENT_BLOCK, __FILE__, __LINE__)
	#define newtDEBUG_NEW
#endif // _DEBUG