/*
	splash.h
	Michael Steer
	2017-11-21

	Splash file
*/

#ifndef __SPLASH__H__
#define __SPLASH__H__

#include <string>
#include "misc/wizzard.h"

#define __VERSION__MAJOR__ 0					// Game Major Version
#define __VERSION__MINOR__ 0					// Game Minor Version
#define __APPLICATION__NAME__ __N_A_M_E__		// Application Name
#define __APPLICATION__DATE__ __DATE__			// Application build date
#define __AUTHOR__FIRST__NAME__ __FS_N_A_M_E	// Author First Name
#define __AUTHOR__LAST__NAME__  __FS_L_A_S_T	// Author Last Name


/*
	String and datatype declarations of the above info
*/
inline std::string	                      __version__()	 { return std::string(__VERSION__MAJOR__) 
														 + " " 
														 + std::string(__VERSION__MINOR__); }
inline unsigned short              __version__major__()	 { return (unsigned short)__VERSION__MAJOR__; }
inline unsigned short              __version__minor__()	 { return (unsigned short)__VERSION__MAJOR__; }
inline std::string	                      __appname__()	 { return std::string(__APPLICATION__NAME__); }
inline std::string	                      __appdate__()	 { return std::string(__DATE__);				 }
inline std::string                         __author__()	 { return std::string(__AUTHOR__FIRST__NAME__) 
														 + " " 
														 + std::string(__AUTHOR__LAST__NAME__); }

inline std::string	                       getVersion()	 { return __version__(); }
inline std::string	         getApplicationAuthorName()	 { return __author__();  }
inline std::string	               getApplicationName()	 { return __appname__(); }
inline std::string	    getApplicaitonCompilationDate()  { return __appdate__(); }
inline std::string	             getApplicationAuthor()	 { return __author__();  }
inline std::string	    getApplicationAuthorFirstName()	 { return __AUTHOR__FIRST__NAME__; }
inline std::string	     getApplicationAuthorLastName()  { return __AUTHOR__LAST__NAME__; }

/*
	Splash screen for console
*/
void splash();

#endif // __SPLASH__H__
