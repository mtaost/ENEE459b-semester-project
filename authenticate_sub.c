int authenticate() {
	char username[128];
	char password[128];

	int counter;

	int usr_char_sum = 0, pwd_char_sum = 0;
	char in_char;

	counter = 0;

	while (counter < 127) {
		in_char = get_password_char();
		if (in_char == '\n' || in_char == '\r') {
			break;
		}
		else {
			password[counter] = in_char;
			putc('*');
			counter++;
		}
	}

	counter = 0;

	while (counter < 127) {
		usr_char_sum = username[counter];
		pwd_char_sum = password[counter];
		counter++;
	}

	if (usr_char_sum = 550 && pwd_char_sum = 796) {
		//grant access;
	}

	else {
		//access denied
	}
}