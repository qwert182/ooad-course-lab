#include <memory.h>
#include <stdio.h>
#include <winsock.h>


//const char str[] = "GET http://2ip.ru/\r\n";
//const char str[] =
//	"GET http://www.google.ru/" "\r\n";


//const char str[] =
//	"GET http://localhost/" "\r\n";

const char str[] =
	"GET http://www.google.com/images/branding/googlelogo/1x/googlelogo_color_150x54dp.png" "\r\n";

#define cerr(s) if ((s) ? (fprintf(stderr, "error: \"%s\"\n", #s),1) : 0) goto err



int main() {
  WSADATA wd;
  SOCKET s;
  union {
	struct sockaddr a;
	struct sockaddr_in i;
  } addr;
  char buf[1000];
  struct servent const *http;
  struct hostent const *host;
  int i;

	cerr(freopen("C:\\Documents and Settings\\Люда\\Рабочий стол\\out.htm", "wb", stdout) == NULL);

	cerr(WSAStartup(MAKEWORD(1, 1), &wd));
	cerr((http = getservbyname("http", "tcp")) == NULL);
	cerr((host = gethostbyname("google.com")) == NULL);

	memset(&addr, 0, sizeof addr);
	addr.i.sin_family = AF_INET;
	addr.i.sin_port = http->s_port;
	addr.i.sin_addr.s_addr = *(DWORD*)host->h_addr_list[0];

	cerr((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET);
	cerr(connect(s, &addr.a, sizeof addr.a));
	cerr(send(s, str, sizeof str - 1, 0) != sizeof str - 1);
	//cerr(shutdown(s, 1));
	do {
		cerr((i = recv(s, buf, sizeof buf, 0)) < 0);
		//buf[i] = '\0';
		//printf("%s", buf);
		cerr(fwrite(buf, i, 1, stdout) != 1);
	} while (i != 0);

	cerr(closesocket(s));
	cerr(WSACleanup());

	return 0;

err:
	return 1;
}


