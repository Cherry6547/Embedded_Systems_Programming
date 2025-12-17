int _write(int file,char *ptr,int len){
	uart2_write((char *)ptr, len);
	return len;
}
int _read(int file, char *ptr, int len) { return 0; }
int _lseek(int file, int ptr, int dir) { return 0; }
int _close(int file) { return -1; }
int _fstat(int file, void *st) { return 0; }
int _isatty(int file) { return 1; }
