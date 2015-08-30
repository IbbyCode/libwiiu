#include "loader.h"

/* Exception callback */
char ex_cb(void *context);

/* Start of our code */
void _start()
{
  /* Load a good stack */
  asm(
      "lis %r1, 0x1ab5 ;"
      "ori %r1, %r1, 0xd138 ;"
  );
 
  /* Get a handle to coreinit.rpl and nsysnet.rpl */
  unsigned int coreinit_handle, nsysnet_handle;
  OSDynLoad_Acquire("coreinit.rpl", &coreinit_handle);
  OSDynLoad_Acquire("nsysnet.rpl", &nsysnet_handle);

  /* OS Functions */
  void(*_Exit)();
  
  /* Socket functions */
  int (*socket)(int family, int type, int proto);
  int (*connect)(int fd, struct sockaddr *addr, int addrlen);

  /* Read the address of OSSetExceptionCallback() */
  OSDynLoad_FindExport(coreinit_handle, 0, "_Exit", &_Exit);

  /* Read the addresses of socket(), connect(), and send() */
  OSDynLoad_FindExport(nsysnet_handle, 0, "socket", &socket);
  OSDynLoad_FindExport(nsysnet_handle, 0, "connect", &connect);
  
  /* Set up our socket address structure */
  struct sockaddr sin;
  sin.sin_family = AF_INET;
  sin.sin_port = 12345;
  sin.sin_addr.s_addr = PC_IP;
  int i;
  for (i = 0; i < 8; i++)
  {
    sin.sin_zero[i] = 0;
  }

  /* Connect to the PC */
  int rpc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  int status = connect(rpc, &sin, 0x10);
  if (status) OSFatal("Error connecting to listener server");
  _Exit();
}
