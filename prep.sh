#!/bin/bash
php main.php -o prepare -n df_bigvarchar -e myisam -s 1000000 
php main.php -o prepare -n df_bigvarcharaux -e myisam -s 1000000 
php main.php -o prepare -n df_text -e myisam -s 1000000 
php main.php -o prepare -n df_textaux -e myisam -s 1000000 
