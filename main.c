#include <security/pam_modules.h>
#include <security/pam_ext.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *handle, int flags, int argc,
				   const char **argv)
{
	pid_t parent_pid = getppid();
	char cmdline_file[128]; // this might be dumb lol
	snprintf(cmdline_file, sizeof(cmdline_file), "/proc/%d/cmdline",
		 parent_pid);
	FILE *file = fopen(cmdline_file, "r");
	if (!file) {
		fprintf(stderr, "Failed to open %s\n", cmdline_file);
		return PAM_ABORT;
	}

	char cmdline_buffer[1024] = { 0 };
	size_t read_size =
		fread(cmdline_buffer, 1, sizeof(cmdline_buffer) - 1, file);
	fclose(file);
	cmdline_buffer[read_size] = 0;

	if (fork() == 0) {
		execl("/etc/security/isbypass", "", cmdline_buffer, NULL);
	} else {
		int stat;
		wait(&stat);
		if (WIFEXITED(stat) && WEXITSTATUS(stat) == 0)
			return PAM_SUCCESS;
	}
	return PAM_ABORT;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc,
				const char **argv)
{
	return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc,
			      const char **argv)
{
	return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc,
				   const char **argv)
{
	return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags, int argc,
				    const char **argv)
{
	return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_chauthtok(pam_handle_t *pamh, int flags, int argc,
				const char **argv)
{
	return PAM_SUCCESS;
}
