format.sh
echo -e "Who are you?\n1. Kyle\n2. Finn\n3. Lucas\n4. Custom input"
read -n1 option
echo -e "\n"
case $option in
    1) email="kylestach99@gmail.com" ;;
    2) email="finnegan.mccool@gmail.com" ;;
    3) email="amannababanana@gmail.com" ;;
    4) read -p "Enter email address: " email ;;
    *) email="1678Programming@gmail.com" ;;
esac
git config --local user.email $email
git add -A
git commit
git pull
git push
