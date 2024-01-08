/*///////////////////////////////////////////////////////////////////
//MCEClientAuth.h
/////////////////////////////////////////////////////////////////////
//	Written by Jeffrey Counts 20th April 2006
//	Motion Control Engineering, inc.
//	11380 White Rock Rd.
//	Rancho Cordova, CA 95742
//	1-800-444-7442
//	www.mceinc.com
//
//  Version: 0.0.2
//  Modified 9/07/06 : 11:46 AM
//	Copyright (c) 2006 Motion Control Engineering
///////////////////////////////////////////////////////////////////*/

#ifndef MCE_CLIENT_AUTHENTICATION_H
#define MCE_CLIENT_AUTHENTICATION_H

#ifdef __cplusplus
extern "C"
{
#endif		/* __cplusplus */


	/*///////////////////////////////////////////////////////////////
	//initializeEncryption
	/////////////////////////////////////////////////////////////////
	//Used to initialize encryption tables
	// to an iController.

	//Arguments:
	// none
	*/

	void initEncryption(void);


	/*///////////////////////////////////////////////////////////////
	//encryptLogonAuth
	/////////////////////////////////////////////////////////////////
	//Used to encrypt the data sent to authenticate the client
	// to an iController.

	//Arguments:
	// sessionID:	32 bit integer obtained at run time from
	//				controller by sending the Logon command.
	// vendorID:	32 bit integer obtained pre build time from
	//				MCE for the Client's Company
	// productID:	32 bit integer obtained pre build time from
	//				MCE for the Client's Application
	// bigEndian    32 bit for changeing byte order from little
	//				endian  to big endian.  Set to 0 if connecting
	//				to a PC iCue or 1 if connecting to controller
	//				(simplex, dispatcher running on IMP board).
	// outBuff:		char* pointer to a 16 byte buffer that
	//				will be over written with the encrypted data.

	//Returns int: 1 if successfull, 0 if unsuccessfull
	*/

	int encryptLogonAuth(	unsigned int sessionID,
							unsigned int vendorID,
							unsigned int productID,
							unsigned int bigEndian,
							char* outBuff);


	/*///////////////////////////////////////////////////////////////
	//encryptPassword
	/////////////////////////////////////////////////////////////////
	//Used to encrypt the data sent to authenticate the client
	// to an iController.

	//Arguments:
	// sessionID:	32 bit integer obtained at run time from
	//				controller by sending the Logon command.
	// vendorID:	32 bit integer obtained pre build time from
	//				MCE for the Client's Company
	// productID:	32 bit integer obtained pre build time from
	//				MCE for the Client's Application
	// bigEndian    32 bit for changeing byte order from little
	//				endian  to big endian.  Set to 0 if connecting
	//				to a PC iCue or 1 if connecting to controller
	//				(simplex, dispatcher running on IMP board).
	// password:	char* pointer to a 16 byte Ascii char array.
	//              important, this is not necessarily a null
	//              terminated string.  The password "pswd" must be
	//				padded with nulls to look like:
	//				{'p','s','w','d','\0','\0','\0','\0',
	//				'\0','\0','\0','\0','\0','\0','\0','\0'}

	//Returns int:	1 if successfull, 0 if unsuccessfull

	//Side Effect:	password buffer is overwritten with 16 bytes of
	//				encrypted data
	*/

	int encryptPassword(	unsigned int sessionID,
							unsigned int vendorID,
							unsigned int productID,
							unsigned int bigEndian,
							char* password);

	/*///////////////////////////////////////////////////////////////
	//encryptSetPasswordData
	/////////////////////////////////////////////////////////////////
	//Used before sending a new security password to iControl
	//This method will take in a 16 char password along with
	// the client's information and fill a 128 byte buffer with
	// the encrypted data to be sent to the iControl.

	//Arguments:
	// sessionID:	32 bit integer obtained at run time from
	//				controller by sending the xxx command.
	// vendorID:	32 bit integer obtained pre build time from
	//				MCE for the Client's Company
	// productID:	32 bit integer obtained pre build time from
	//				MCE for the Client's Application
	// securityAccount: 32 bit integer Technician = 0, Manager = 1
	// bigEndian    32 bit for changeing byte order from little
	//				endian  to big endian.  Set to 0 if connecting
	//				to a PC iCue or 1 if connecting to controller
	//				(simplex, dispatcher running on IMP board).
	// password:	char* pointer to a 16 byte Ascii char array.
	//              important, this is not necessarily a null
	//              terminated string.  The password "pswd" must be
	//				padded with nulls to look like:
	//				{'p','s','w','d','\0','\0','\0','\0',
	//				'\0','\0','\0','\0','\0','\0','\0','\0'}
	// outBuff:		char* pointer to a 32 byte buffer that
	//				will be over written with the encrypted data.

	//Returns int: 1 if successfull, 0 if unsuccessfull

	//Side Effect:	outBuff buffer is overwritten with 32 bytes of
	//				encrypted data
	*/

	int encryptSetPassword(	unsigned int sessionID,
							unsigned int vendorID,
							unsigned int productID,
							unsigned int securityAccount,
							unsigned int bigEndian,
							char* password,
							char* outBuff);

#ifdef __cplusplus
}
#endif		/* __cplusplus */


#endif		/* MCE_CLIENT_AUTHENTICATION_H */