format.sh
read -p "Please enter the email to use for this commit: " email
git config --local user.email $email
git add -A
git commit
git pull
git push
