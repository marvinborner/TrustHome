#include <security/pam_modules.h>
#include <security/pam_ext.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *handle, int flags, int argc,
				   const char **argv)
{
	if (fork() == 0) {
		execl("/etc/security/isbypass", NULL);
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
