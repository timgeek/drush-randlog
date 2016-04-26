# drush-randlog
Drush command to login as a random active user with options to exclude and include users by roles.

# Installation
Copy any of these locations:
* Folders listed in the 'include' option (see drush topic docs-configuration).
* The system-wide Drush commands folder, e.g. /usr/share/drush/commands
* The ".drush" folder in the user's HOME folder.
* /drush and /sites/all/drush in the current Drupal installation
* All enabled modules in the current Drupal installation
* Folders and files containing other versions of Drush in their names will be *skipped* (e.g. devel.drush4.inc or drush4/devel.drush.inc). Names containing the current version of Drush (e.g. devel.drush5.inc) will be loaded.

# Usage Options:
 --browser:  Optional value denotes which browser to use (defaults to operating system default). Set to 0 to suppress opening a browser.                         
 --not-roles:  A list of roles to exclude from the the list from which the random user is chosen.                                                                  
 --path:  Optional path to redirect to after logging in.                                                                                                      
 --roles:  A list of roles to limit the the list from which the random user is chosen.  The Authenticated User is automatic and does not need to be specified.

# Aliases: rl

# Examples
drush rl --not-roles=Developer,Editor --roles=Administrator --path=admin --browser=0
