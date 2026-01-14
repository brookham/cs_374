#include <unistd.h>

int main(void)
{
	char buf[128];
	
	ssize_t num_bytes = read(0, buf, 128);
	
	write(1, buf, num_bytes);
}
