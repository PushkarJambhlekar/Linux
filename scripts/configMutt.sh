set USERNAME=p***@gmail.com
set PASSWORD=********
set USER=pjambhleakr

sudo apt-get -y install openssl ca-certificates
sudo apt-get -y install msmtp
touch $HOME/.msmtprc && \
touch $HOME/.msmtp.log && \
chmod 0600 $HOME/.msmtprc


echo account default >> ~/.msmtprc 
echo host smtp.gmail.com >> ~/.msmtprc 
echo port 587 >> ~/.msmtprc 
echo from $USERNAME >> ~/.msmtprc 
echo tls on >> ~/.msmtprc 
echo tls_starttls on >> ~/.msmtprc         
echo tls_trust_file /etc/ssl/certs/ca-certificates.crt >> ~/.msmtprc 
echo auth on >> ~/.msmtprc 
echo user $USERNAME >> ~/.msmtprc     
echo password $PASSWORD >> ~/.msmtprc 
echo logfile ~/.msmtp.log >> ~/.msmtprc 


sudo apt-get -y install fetchmail

echo poll pop.gmail.com >> ~/.fetchmailrc
echo with proto POP3    >> ~/.fetchmailrc                  
echo user  $USERNAME >> ~/.fetchmailrc 
echo there with password $PASSWORD >> ~/.fetchmailrc        
echo is $USERNAME here >> ~/.fetchmailrc
echo mda "/usr/bin/procmail -d %T" >> ~/.fetchmailrc        
echo options >> ~/.fetchmailrc                     
echo no keep >> ~/.fetchmailrc                                 
echo ssl>> ~/.fetchmailrc                                  
echo sslcertck  >> ~/.fetchmailrc                          
echo sslcertpath /etc/ssl/certs >> ~/.fetchmailrc

chmod 600 ~/.fetchmailrc

sudo apt-get -y install procmail

echo MAIL=/var/spool/mail/$USER && export MAIL >> ~/.bashrc


echo PATH=/bin:/usr/bin:/usr/local/bin >>~/.procmailrc
echo VERBOSE=off                   # Turn on for verbose log >> ~/.procmailrc
echo MAILDIR=$HOME/Mail            # Where Procmail recipes deliver >> ~/.procmailrc
echo LOGFILE=$HOME/.procmaillog    # Keep a log for troubleshooting. >> ~/.procmailrc
echo # Recipes >> ~/.procmailrc
echo :0: >> ~/.procmailrc
echo * ^TOmutt-user >> ~/.procmailrc
echo mutt >> ~/.procmailrc

sudo apt-get -y install mutt

echo > ~/.muttrc
echo \#======================================================# >> ~/.muttrc
echo \# Boring details>> ~/.muttrc
echo set realname = Pushkar>> ~/.muttrc
echo set from = pushkar.iit@gmail.com>> ~/.muttrc
echo set use_from = yes>> ~/.muttrc
echo set envelope_from ="yes">> ~/.muttrc
echo set sendmail="/usr/bin/msmtp">> ~/.muttrc
echo \# If not set in environment variables:>> ~/.muttrc
echo set spoolfile = /var/spool/mail/$USER >> ~/.muttrc
echo \#======================================================#>> ~/.muttrc
echo \# Folders>> ~/.muttrc
echo set folder="~/Mail"                \# Mailboxes in here>> ~/.muttrc
echo set record="+sent"                 \# where to store sent messages>> ~/.muttrc
echo set postponed="+postponed"         \# where to store draft messages>> ~/.muttrc
echo set move=no                        \# Don't move mail from the spool.>> ~/.muttrc
echo \#======================================================#>> ~/.muttrc
echo \# Watch these mailboxes for new mail:>> ~/.muttrc
echo mailboxes ! +Fetchmail +slrn +mutt>> ~/.muttrc
echo set sort_browser=alpha    \# Sort mailboxes by alpha(bet)>> ~/.muttrc
echo \#======================================================#>> ~/.muttrc
echo \# Order of headers and what to show>> ~/.muttrc
echo hdr_order Date: From: User-Agent: X-Mailer \\>> ~/.muttrc
echo           To: Cc: Reply-To: Subject:>> ~/.muttrc
echo ignore *>> ~/.muttrc
echo unignore Date: From: User-Agent: X-Mailer  \\>> ~/.muttrc
echo          To: Cc: Reply-To: Subject:>> ~/.muttrc
echo \#======================================================#>> ~/.muttrc
echo \# which editor do you want to use? >> ~/.muttrc
echo \# vim of course!>> ~/.muttrc
echo set editor=\"vim -c 'set tw=70 et' '+/^$' \" >> ~/.muttrc
echo set edit_headers          \# See the headers when editing>> ~/.muttrc
echo \#======================================================#>> ~/.muttrc
echo \# Aliases>> ~/.muttrc
echo set sort_alias=alias     \# sort aliases in alpha order by alias name>> ~/.muttrc
echo \#======================================================#>> ~/.muttrc
echo \# Odds and ends>> ~/.muttrc
echo set markers          \# mark wrapped lines of text in the pager with a +>> ~/.muttrc
echo set smart_wrap       \# Don't wrap mid-word>> ~/.muttrc
echo set pager_context=5  \# Retain 5 lines of previous page when scrolling.>> ~/.muttrc
echo set status_on_top    \# Status bar on top.>> ~/.muttrc
echo push \<show-version\>  \# Shows mutt version at startup>> ~/.muttrc
