#include <memory.h>
#include <stdio.h>
#include <winsock.h>

/*
//const char str[] = "GET http://2ip.ru/\r\n";
//const char str[] =
//	"GET http://www.google.ru/" "\r\n";


const char str[] =
	"GET http://localhost/" "\r\n";

//const char str[] =
//	"GET http://www.google.com/images/branding/googlelogo/1x/googlelogo_color_150x54dp.png" "\r\n";

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
	cerr((host = gethostbyname("localhost")) == NULL);

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
*/

struct test_query {
	int recv_ok;
	const char *server;
	const char *response;
	const char *query;
};




#define cerr(s) if ((s) ? (fprintf(stderr, "error: \"%s\"\n", #s),1) : 0) goto err



int do_test_query(const struct test_query *test) {
  SOCKET s;
  union {
	struct sockaddr a;
	struct sockaddr_in i;
  } addr;
  struct servent const *http;
  struct hostent const *host;
  char buf[1000];
  int i, size = 0;

	cerr((http = getservbyname("http", "tcp")) == NULL);
	cerr((host = gethostbyname(test->server)) == NULL);

	memset(&addr, 0, sizeof addr);
	addr.i.sin_family = AF_INET;
	addr.i.sin_port = http->s_port;
	addr.i.sin_addr.s_addr = *(DWORD*)host->h_addr_list[0];

	cerr((s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET);
	cerr(connect(s, &addr.a, sizeof addr.a));
	cerr(send(s, test->query, strlen(test->query), 0) != (int)strlen(test->query));
	//cerr(shutdown(s, 1));
	do {
		cerr(sizeof buf - size < 0);
		//cerr((i = recv(s, buf + size, sizeof buf - size, 0)) < 0);
		if ((i = recv(s, buf + size, sizeof buf - size, 0)) < 0) {
			cerr(test->recv_ok);
			break;
		}
		size += i;
	} while (i != 0);
	//buf[size] = '\0';
	//printf("%s", buf);

	cerr((i >= 0)  !=  test->recv_ok);

	cerr(closesocket(s));


	if (memcmp(buf, test->response, strlen(test->response)) == 0)
		return 1;
	else {
		if (!test->recv_ok) return 1;
		return 0;
	}

err:
	return 0;
}





static const char ok[] = "HTTP/1.0 200 \r\n";
static const char badquery[] = "HTTP/1.0 400 \r\n";
static const char server[] = "localhost";




static const struct test_query q_tests[] = {
	//{"www.google.ru", "HTTP/1.0 200 OK\r\n", "GET http://www.google.ru/ HTTP/1.0" "\r\n\r\n"},

	{1, server, badquery, "GET  HTTP/1.0" "\r\n\r\n"},
	{0, server, badquery, "GET HTTP/1.0" "\r\n\r\n"},

	{1, server, ok, "GET http://localhost/ HTTP/1.0" "\r\n\r\n"},
	{1, server, ok, "GET http://localhost HTTP/1.0" "\r\n\r\n"},
	{1, server, ok, "GET / HTTP/1.0" "\r\n\r\n"},

	{1, server, ok, "GET http://localhost/" "\r\n"},
	{1, server, ok, "GET http://localhost" "\r\n"},
	{1, server, ok, "GET /" "\r\n"},
	{1, server, badquery, "GET " "\r\n"},
	{1, server, badquery, "GET" "\r\n"},
};

#define asizeof(array) (sizeof(array) / sizeof(*(array)))


int main() {
  WSADATA wd;
  size_t i;
	cerr(WSAStartup(MAKEWORD(1, 1), &wd));
	fprintf(stderr, "test_query\n");
	for (i = 0; i < asizeof(q_tests); ++i) {
		if (!do_test_query(&q_tests[i])) {
			fprintf(stderr, "#%lu FAILED (%s)\n", i, q_tests[i].query);
		}
	}
	cerr(WSACleanup());
	return 0;
err:
	fprintf(stderr, "winsock failed");
	return 1;
}

