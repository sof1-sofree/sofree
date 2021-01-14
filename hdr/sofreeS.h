// spcl.dll:  25 exports
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved);

typedef int (__stdcall * lpfn_bind)(SOCKET s,const struct sockaddr *name,int namelen);
extern "C" int __stdcall sys_bind(SOCKET s,const struct sockaddr *name,int namelen);

typedef int (__stdcall * lpfn_closesocket)(SOCKET s);
extern "C" int __stdcall sys_closesocket(SOCKET s);

typedef int (__stdcall * lpfn_connect)(SOCKET s,const struct sockaddr *name,int namelen);
extern "C" int __stdcall sys_connect(SOCKET s,const struct sockaddr *name,int namelen);

typedef int (__stdcall * lpfn_getsockname)(SOCKET s,struct sockaddr *name,int *namelen);
extern "C" int __stdcall sys_getsockname(SOCKET s,struct sockaddr *name,int *namelen);

typedef u_long (__stdcall * lpfn_htonl)(u_long hostlong);
extern "C" u_long __stdcall sys_htonl(u_long hostlong);

typedef u_short (__stdcall * lpfn_htons)(u_short hostshort);
extern "C" u_short __stdcall sys_htons(u_short hostshort);

typedef unsigned long (__stdcall * lpfn_inet_addr)(const char *cp);
extern "C" unsigned long __stdcall sys_inet_addr(const char *cp);

typedef char* (__stdcall * lpfn_inet_ntoa)(struct in_addr in);
extern "C" char* __stdcall sys_inet_ntoa(struct in_addr in);

typedef int (__stdcall * lpfn_ioctlsocket)(SOCKET s,long cmd,u_long *argp);
extern "C" int __stdcall sys_ioctlsocket(SOCKET s,long cmd,u_long *argp);

typedef u_long (__stdcall * lpfn_ntohl)(u_long netlong);
extern "C" u_long __stdcall sys_ntohl(u_long netlong);

typedef u_short (__stdcall * lpfn_ntohs)(u_short netshort);
extern "C" u_short __stdcall sys_ntohs(u_short netshort);

typedef int (__stdcall * lpfn_recv)(SOCKET s,char *buf,int len,int flags);
extern "C" int __stdcall sys_recv(SOCKET s,char *buf,int len,int flags);

typedef int (__stdcall * lpfn_recvfrom)(SOCKET s,char *buf,int len,int flags,struct sockaddr *from,int *fromlen);
extern "C" int __stdcall sys_recvfrom(SOCKET s,char *buf,int len,int flags,struct sockaddr *from,int *fromlen);

typedef int (__stdcall * lpfn_select)(int nfds,fd_set *readfds,fd_set *writefds,fd_set *exceptfds,const struct timeval *timeout);
extern "C" int __stdcall sys_select(int nfds,fd_set *readfds,fd_set *writefds,fd_set *exceptfds,const struct timeval *timeout);

typedef int (__stdcall * lpfn_send)(SOCKET s,const char *buf,int len,int flags);
extern "C" int __stdcall sys_send(SOCKET s,const char *buf,int len,int flags);

typedef int (__stdcall * lpfn_sendto)(SOCKET s,const char *buf,int len,int flags,const struct sockaddr *to,int tolen);
extern "C" int __stdcall sys_sendto(SOCKET s,const char *buf,int len,int flags,const struct sockaddr *to,int tolen);

typedef int (__stdcall * lpfn_setsockopt)(SOCKET s,int level,int optname,const char *optval,int optlen);
extern "C" int __stdcall sys_setsockopt(SOCKET s,int level,int optname,const char *optval,int optlen);

typedef int (__stdcall * lpfn_shutdown)(SOCKET s,int how);
extern "C" int __stdcall sys_shutdown(SOCKET s,int how);

typedef SOCKET (__stdcall * lpfn_socket)(int af,int type,int protocol);
extern "C" SOCKET __stdcall sys_socket(int af,int type,int protocol);

typedef struct hostent* (__stdcall * lpfn_gethostbyname)(const char *name);
extern "C" struct hostent* __stdcall sys_gethostbyname(const char *name);

typedef int (__stdcall * lpfn_gethostname)(char *name,int namelen);
extern "C" int __stdcall sys_gethostname(char *name,int namelen);

typedef int (__stdcall * lpfn_WSAGetLastError)(void);
extern "C" int __stdcall sys_WSAGetLastError(void);

typedef int (__stdcall * lpfn_WSAStartup)(WORD wVersionRequested,LPWSADATA lpWSAData);
extern "C" int __stdcall sys_WSAStartup(WORD wVersionRequested,LPWSADATA lpWSAData);

typedef int (__stdcall * lpfn_WSACleanup)(void);
extern "C" int __stdcall sys_WSACleanup(void);

typedef int (__stdcall * lpfn___WSAFDIsSet)(SOCKET fd,fd_set *set);
extern "C" int __stdcall sys___WSAFDIsSet(SOCKET fd,fd_set *set);
