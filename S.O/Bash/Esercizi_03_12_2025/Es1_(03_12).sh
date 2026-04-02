administrator(){
    echo "administrator"
}

student(){
    echo "student"
}

teacher(){
    echo "teacher"
}

stop=0

while [ $stop -eq 0 ]
do
    cat << EOF
    1: Administrator
    2: Student
    3: Teacher
EOF
echo "Please select your role (1-3): "
read role
if [[ "$role" == "1" ]]; then
    administrator
elif [[ "$role" == "2" ]]; then
    student
elif [[ "$role" == "3" ]]; then
    teacher
elif [[ "$role" == "0" ]]; then
    stop=1
else
    echo "Invalid role selected."

fi
done