#ifndef NETWORKING_ABSTRACTION_HEADER_H__
#define NETWORKING_ABSTRACTION_HEADER_H__

#include <stdlib.h>

#ifdef __cplusplus

#define EXTERN extern "c"

#else

#define EXTERN

#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)

#define ON_WINDOWS

#ifdef _MSC_VER

#pragma comment(lib, "ws2_32.lib")

#endif

#include <winsock2.h>
#include <ws2tcpip.h>

#define NET_INVALID_HANDLE WSA_INVALID_HANDLE
#define NET_NO_MEM WSA_NOT_ENOUGH_MEMORY
#define NET_INVALID_PARAM WSA_INVALID_PARAMETER
#define NET_ABORTED WSA_OPERATION_ABORTED
#define NET_INCOMPLETE_IO WSA_IO_INCOMPLETE
#define NET_LATER WSA_IO_PENDING
#define NET_INTERUPTED WSAEINTR

typedef SOCKET socket_t;
typedef struct sockaddr_in inet4_addr_t;
typedef struct sockaddr_in6 inet6_addr_t;

#if !defined(NET_IMPL)

EXTERN int init();

#else

WSADATA wsa_data;

EXTERN int init() {
	int wsa;
	if((wsa = WSAStartup(MAKEWORD(2, 2), &wsa_data)) != 0) {
		errno = WSAGetLastError();
	}

	return wsa;	
}

#endif

#else

#define ON_UNIX

#include <sys/socket.h>

typedef int socket_t;
typedef struct sockaddr_in inet4_addr_t;
typedef struct sockaddr_in6 inet6_addr_t;

#define init()

#endif

#endif
