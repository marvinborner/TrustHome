# TrustHome

TrustHome disables the password requirement for sudo/login while you’re
using your home wifi.

### DISLAIMER: I’m not responsible for any security breaches you may encounter while having this installed. This is merely a utility for my personal convenience and should never be used if you’re serious about security. You should ALWAYS use other security measures, such as full disk encryption, in addition.

## Installation

0.  Make sure that you use `iwd` and have `pam` and `sudo` configured
    correctly
    -   if you don’t use `iwd`, modifying `ishome` to fit your network
        daemon shouldn’t be too hard
1.  Modify `ishome` according to your network’s specifications
2.  Verify whether the paths in `install.sh` work for you and your OS
3.  Run `sudo ./install.sh` - you might need to install `libpam` if you
    get errors
4.  Modify your pam configuration accordingly. For example, my
    `/etc/pam.d/sudo` file looks like this:

<!-- -->

    auth        sufficient      pam_trusthome.so
    auth        sufficient      pam_fprintd.so
    auth        include         system-auth
    account     include         system-auth
    session     include         system-auth

using this configuration sudo will fall back to my fingerprint sensor if
I’m not on my home network which will then fall back to normal password
authentication if something failed. You may also want to edit files like
`/etc/pam.d/login` in a similar way.

## Ideas

You could try modifying `ishome` so that you get authenticated
automatically based on your GPS location or public IP address.
