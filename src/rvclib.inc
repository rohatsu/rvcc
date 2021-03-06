void s_clib() {
__s("/* rvcc C compiler - barebones clib implementation */\n");
__s("\n");
__s("#define NULL 0\n");
__s("\n");
__s("#ifdef __RISCV\n");
__s("#define __syscall_exit 93\n");
__s("#define __syscall_read 63\n");
__s("#define __syscall_write 64\n");
__s("#define __syscall_close 57\n");
__s("#define __syscall_open 1024\n");
__s("#define __syscall_brk 214\n");
__s("#endif\n");
__s("\n");
__s("#ifdef __ARM\n");
__s("#define __syscall_exit 1\n");
__s("#define __syscall_read 3\n");
__s("#define __syscall_write 4\n");
__s("#define __syscall_close 6\n");
__s("#define __syscall_open 5\n");
__s("#define __syscall_brk 45\n");
__s("#endif\n");
__s("\n");
__s("typedef int FILE;\n");
__s("\n");
__s("void abort();\n");
__s("\n");
__s("int strlen(char *str)\n");
__s("{\n");
__s("	int i = 0;\n");
__s("\n");
__s("	while (str[i] != 0)\n");
__s("		i++;\n");
__s("\n");
__s("	return i;\n");
__s("}\n");
__s("\n");
__s("int strcmp(char *s1, char *s2)\n");
__s("{\n");
__s("	int i = 0;\n");
__s("\n");
__s("	while (s1[i] != 0 && s2[i] != 0) {\n");
__s("		if (s1[i] < s2[i])\n");
__s("			return -1;\n");
__s("		else if (s1[i] > s2[i])\n");
__s("			return 1;\n");
__s("		i++;\n");
__s("	}\n");
__s("	return s2[i] - s1[i];\n");
__s("}\n");
__s("\n");
__s("int strncmp(char *s1, char *s2, int len)\n");
__s("{\n");
__s("	int i = 0;\n");
__s("	while (i < len) {\n");
__s("		if (s1[i] < s2[i])\n");
__s("			return -1;\n");
__s("		else if (s1[i] > s2[i])\n");
__s("			return 1;\n");
__s("		i++;\n");
__s("	}\n");
__s("	return 0;\n");
__s("}\n");
__s("\n");
__s("char *strcpy(char *dest, char *src)\n");
__s("{\n");
__s("	int i = 0;\n");
__s("	while (src[i] != 0) {\n");
__s("		dest[i] = src[i];\n");
__s("		i++;\n");
__s("	}\n");
__s("	dest[i] = 0;\n");
__s("	return dest;\n");
__s("}\n");
__s("\n");
__s("char *strncpy(char *dest, char *src, int len)\n");
__s("{\n");
__s("	int i = 0;\n");
__s("	int beyond = 0;\n");
__s("\n");
__s("	while (i < len) {\n");
__s("		if (beyond == 0) {\n");
__s("			dest[i] = src[i];\n");
__s("			if (src[i] == 0) {\n");
__s("				beyond = 1;\n");
__s("			}\n");
__s("		} else {\n");
__s("			dest[i] = 0;\n");
__s("		}\n");
__s("		i++;\n");
__s("	}\n");
__s("	return dest;\n");
__s("}\n");
__s("\n");
__s("/* set 10 digits (32bit) without div */\n");
__s("void __render10(char *pb, int val)\n");
__s("{\n");
__s("	int neg = 0;\n");
__s("\n");
__s("	if (val < 0) {\n");
__s("		neg = 1;\n");
__s("		val = -val;\n");
__s("	}\n");
__s("\n");
__s("	while (val >= 1000000000) {\n");
__s("		val -= 1000000000;\n");
__s("		pb[0]++;\n");
__s("	}\n");
__s("	while (val >= 100000000) {\n");
__s("		val -= 100000000;\n");
__s("		pb[1]++;\n");
__s("	}\n");
__s("	while (val >= 10000000) {\n");
__s("		val -= 10000000;\n");
__s("		pb[2]++;\n");
__s("	}\n");
__s("	while (val >= 1000000) {\n");
__s("		val -= 1000000;\n");
__s("		pb[3]++;\n");
__s("	}\n");
__s("	while (val >= 100000) {\n");
__s("		val -= 100000;\n");
__s("		pb[4]++;\n");
__s("	}\n");
__s("	while (val >= 10000) {\n");
__s("		val -= 10000;\n");
__s("		pb[5]++;\n");
__s("	}\n");
__s("	while (val >= 1000) {\n");
__s("		val -= 1000;\n");
__s("		pb[6]++;\n");
__s("	}\n");
__s("	while (val >= 100) {\n");
__s("		val -= 100;\n");
__s("		pb[7]++;\n");
__s("	}\n");
__s("	while (val >= 10) {\n");
__s("		val -= 10;\n");
__s("		pb[8]++;\n");
__s("	}\n");
__s("	while (val >= 1) {\n");
__s("		val -= 1;\n");
__s("		pb[9]++;\n");
__s("	}\n");
__s("\n");
__s("	if (neg == 1) {\n");
__s("		int c = 0;\n");
__s("		while (pb[c] == '0')\n");
__s("			c++;\n");
__s("		if (c > 0)\n");
__s("			pb[c - 1] = '-';\n");
__s("	}\n");
__s("}\n");
__s("\n");
__s("void __render16(char *pb, int val)\n");
__s("{\n");
__s("	int c = 9;\n");
__s("	while (c > 0) {\n");
__s("		int v = val & 0xf;\n");
__s("		if (v < 10)\n");
__s("			pb[c] = '0' + v;\n");
__s("		else if (v < 16)\n");
__s("			pb[c] = 'a' + v - 10;\n");
__s("		else\n");
__s("			abort();\n");
__s("		val = val >> 4;\n");
__s("		c--;\n");
__s("	}\n");
__s("}\n");
__s("\n");
__s("int __format(char *buffer, int val, int width, int zeropad, int base, int hexprefix)\n");
__s("{\n");
__s("	int bi = 0;\n");
__s("	char pb[10];\n");
__s("	int pbi = 0;\n");
__s("\n");
__s("	if (hexprefix == 1) {\n");
__s("		buffer[0] = '0';\n");
__s("		buffer[1] = 'x';\n");
__s("		bi = 2;\n");
__s("		if (width > 2)\n");
__s("			width -= 2;\n");
__s("		else\n");
__s("			width = 0;\n");
__s("	}\n");
__s("\n");
__s("	/* set to zeroes */\n");
__s("	while (pbi < 10) {\n");
__s("		pb[pbi] = '0';\n");
__s("		pbi++;\n");
__s("	}\n");
__s("\n");
__s("	if (base == 10)\n");
__s("		__render10(pb, val);\n");
__s("	else if (base == 16)\n");
__s("		__render16(pb, val);\n");
__s("	else\n");
__s("		abort();\n");
__s("\n");
__s("	while (width > 10) {\n");
__s("		/* need to add extra padding */\n");
__s("		if (zeropad == 1)\n");
__s("			buffer[bi] = '0';\n");
__s("		else\n");
__s("			buffer[bi] = ' ';\n");
__s("		bi++;\n");
__s("		width--;\n");
__s("	}\n");
__s("\n");
__s("	/* no padding */\n");
__s("	if (width == 0) {\n");
__s("		int c = 0;\n");
__s("		int started = 0;\n");
__s("\n");
__s("		/* output from first digit */\n");
__s("		while (c < 10) {\n");
__s("			if (pb[c] != '0')\n");
__s("				started = 1;\n");
__s("			if (started) {\n");
__s("				buffer[bi] = pb[c];\n");
__s("				bi++;\n");
__s("			}\n");
__s("			c++;\n");
__s("		}\n");
__s("		/* special case - zero */\n");
__s("		if (started == 0) {\n");
__s("			buffer[bi] = '0';\n");
__s("			bi++;\n");
__s("		}\n");
__s("	} else {\n");
__s("		/* padding */\n");
__s("		int c = 10 - width;\n");
__s("		int started = 0;\n");
__s("		while (c < 10) {\n");
__s("			if (pb[c] != '0')\n");
__s("				started = 1;\n");
__s("			if (started)\n");
__s("				buffer[bi] = pb[c];\n");
__s("			else if (zeropad == 1)\n");
__s("				buffer[bi] = '0';\n");
__s("			else\n");
__s("				buffer[bi] = ' ';\n");
__s("			bi++;\n");
__s("			c++;\n");
__s("		}\n");
__s("	}\n");
__s("	return bi;\n");
__s("}\n");
__s("\n");
__s("void printf(char *str, ...)\n");
__s("{\n");
__s("	int *var_args = &str - 4;\n");
__s("	char buffer[200];\n");
__s("	int si = 0, bi = 0, pi = 0;\n");
__s("\n");
__s("	while (str[si] != 0) {\n");
__s("		if (str[si] != '%') {\n");
__s("			buffer[bi] = str[si];\n");
__s("			bi++;\n");
__s("			si++;\n");
__s("		} else {\n");
__s("			int w = 0, zp = 0, pp = 0;\n");
__s("\n");
__s("			si++;\n");
__s("			if (str[si] == '#') {\n");
__s("				pp = 1;\n");
__s("				si++;\n");
__s("			}\n");
__s("			if (str[si] == '0') {\n");
__s("				zp = 1;\n");
__s("				si++;\n");
__s("			}\n");
__s("			if (str[si] >= '1' && str[si] <= '9') {\n");
__s("				w = str[si] - '0';\n");
__s("				si++;\n");
__s("				if (str[si] >= '0' && str[si] <= '9') {\n");
__s("					w = w * 10;\n");
__s("					w += str[si] - '0';\n");
__s("					si++;\n");
__s("				}\n");
__s("			}\n");
__s("			if (str[si] == 's') {\n");
__s("				/* append param pi as string */\n");
__s("				int l = strlen(var_args[pi]);\n");
__s("				strcpy(buffer + bi, var_args[pi]);\n");
__s("				bi += l;\n");
__s("			} else if (str[si] == 'd') {\n");
__s("				/* append param as decimal */\n");
__s("				int v = var_args[pi];\n");
__s("				bi += __format(buffer + bi, v, w, zp, 10, 0);\n");
__s("			} else if (str[si] == 'x') {\n");
__s("				/* append param as hex */\n");
__s("				int v = var_args[pi];\n");
__s("				bi += __format(buffer + bi, v, w, zp, 16, pp);\n");
__s("			}\n");
__s("			pi--;\n");
__s("			si++;\n");
__s("		}\n");
__s("	}\n");
__s("	buffer[bi] = 0;\n");
__s("	__syscall(__syscall_write, 0, buffer, bi);\n");
__s("}\n");
__s("\n");
__s("char *memcpy(char *dest, char *src, int count)\n");
__s("{\n");
__s("	if (count > 0)\n");
__s("		do {\n");
__s("			count--;\n");
__s("			dest[count] = src[count];\n");
__s("		} while (count > 0);\n");
__s("	return dest;\n");
__s("}\n");
__s("\n");
__s("void exit(int exit_code)\n");
__s("{\n");
__s("	__syscall(__syscall_exit, exit_code);\n");
__s("}\n");
__s("\n");
__s("void abort()\n");
__s("{\n");
__s("	printf(\"Abnormal program termination\n\");\n");
__s("	/* trigger SEGV - must be a better way */\n");
__s("	int *z = 0;\n");
__s("	z[0] = 0;\n");
__s("	exit(-1);\n");
__s("}\n");
__s("\n");
__s("FILE *fopen(char *filename, char *mode)\n");
__s("{\n");
__s("	if (strcmp(mode, \"wb\") == 0)\n");
__s("		return __syscall(__syscall_open, filename, 65, 0x1c0);\n");
__s("	else if (strcmp(mode, \"rb\") == 0)\n");
__s("		return __syscall(__syscall_open, filename, 0, 0);\n");
__s("	abort();\n");
__s("}\n");
__s("\n");
__s("int fclose(FILE *stream)\n");
__s("{\n");
__s("	__syscall(__syscall_close, stream);\n");
__s("	return 0;\n");
__s("}\n");
__s("\n");
__s("int fgetc(FILE *stream)\n");
__s("{\n");
__s("	char buf;\n");
__s("	int r = __syscall(__syscall_read, stream, &buf, 1);\n");
__s("	if (r <= 0)\n");
__s("		return -1;\n");
__s("	return buf;\n");
__s("}\n");
__s("\n");
__s("char *fgets(char *str, int n, FILE *stream)\n");
__s("{\n");
__s("	int i = 0;\n");
__s("	char c;\n");
__s("	do {\n");
__s("		c = fgetc(stream);\n");
__s("		if (c == -1 || c == 255) {\n");
__s("			if (i == 0)\n");
__s("				/* EOF on first char */\n");
__s("				return NULL;\n");
__s("			else\n");
__s("				/* EOF in the middle */\n");
__s("				str[i] = 0;\n");
__s("			return str;\n");
__s("		}\n");
__s("		str[i] = c;\n");
__s("		i++;\n");
__s("	} while (str[i - 1] != '\n');\n");
__s("	str[i] = 0;\n");
__s("	return str;\n");
__s("}\n");
__s("\n");
__s("int fputc(int c, FILE *stream)\n");
__s("{\n");
__s("	char buf[1];\n");
__s("	buf[0] = c;\n");
__s("	__syscall(__syscall_write, stream, &buf, 1);\n");
__s("	return 0;\n");
__s("}\n");
__s("\n");
__s("int fputs(char *str, FILE *stream)\n");
__s("{\n");
__s("	int i = 0;\n");
__s("	while (str[i] != 0) {\n");
__s("		fputc(str[i], stream);\n");
__s("		i++;\n");
__s("	}\n");
__s("	return i;\n");
__s("}\n");
__s("\n");
__s("void *malloc(int size)\n");
__s("{\n");
__s("	int brk = __syscall(__syscall_brk, 0); /* read current break */\n");
__s("	__syscall(__syscall_brk, brk + size); /* increment */\n");
__s("	return brk; /* return previous location, now extended by size */\n");
__s("}\n");
}
