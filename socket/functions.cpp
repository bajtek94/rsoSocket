int changeEndian(int old) {
	int changed;
	unsigned char *afterChange = (unsigned char*)&changed;
	unsigned char *beforeChange = (unsigned char*)&old;
	int length = (int)(sizeof(char*));
	for (int i = 0; i < length; i++) {
		afterChange[i] = beforeChange[length - 1 - i];
	}
	return changed;
}
double changeEndian(double old) {
	double changed;
	unsigned char *afterChange = (unsigned char*)&changed;
	unsigned char *beforeChange = (unsigned char*)&old;
	int length = (int)(sizeof(char*));
	for (int i = 0; i < length; i++) {
		afterChange[i] = beforeChange[length - 1 - i];
	}
	return changed;
}
time_t changeEndian(time_t old) {
	time_t changed;
	unsigned char *afterChange = (unsigned char*)&changed;
	unsigned char *beforeChange = (unsigned char*)&old;
	int length = (int)(sizeof(char*));
	for (int i = 0; i < length; i++) {
		afterChange[i] = beforeChange[length - 1 - i];
	}
	return changed;
}

bool isLittleEndian() {
	int a = 1;
	char* b = (char*)&a;
	if (*b == '0') {
		return false;
	}
	else {
		return true;
	}
}
