We need your help, soldier!

Your goal today is to help us obtain the access to Oscaderp Corp mainframe. 
Our intelligence has managed to install a keylogger and a formgrabber on some bad person's work laptop. You don't need his name to do your job.
Everything worked as planned, the victim visited mainframe's authentication page, https://authen.intranet/, and started to type in the password.
But when he had a couple characters left, the keylogger got busted and hard-killed by him.

Present intelligence evidence:
[*] The password that's being used is 1,048,576 characters long.
[*] According to our calculations, our keylogger managed to capture 1,048,568 password keystrokes.
[*] Formgrabber remained unnoticed, and in a few hours we've got the logs with successful mainframe authentication. 
    The only major problem: they use client-side MD5 to protect the password from being eavesdropped.
[*] We also managed to acquire the source code of the authentication mechanism

You can find all the necessary files in the archive.

YOUR GOAL: obtain the password to the mainframe, and post its SHA1 hash as the flag.
