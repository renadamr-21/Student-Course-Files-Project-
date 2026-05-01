# Author
Renad amr
# Overview
The project designs a Course management system that supports Student course registration, Browse Courses, Enrol in Course, View Transcript, and admin oversight, all using file/linked list-based data storage. 
# Student Operations 
1. Register/Login/Logout o
- If a Student is not already in the system, register them with a unique ID and password.
- Append new Student details to the file and the Student list.
- Authenticate Student using their credentials.
- Provide access to their account upon successful login. o
- Exit the Student session securely.
2. Browse Courses
- Display all courses
3. Enrol in Course
- Search for course by ID
- It checks if current_enrolment < max_seats
- If valid, it creates a new Enrolment record, adds it to the EnrolmentList, and increments the current_enrolment
4. View Transcript
- Display all records from the EnrolmentList associated with the student's ID, showing the Course Name and grade
# Admin Operations
1. Login/Logout
- Authenticate admins using their credentials.
- Grant access to admin functionalities upon successful login.
- Exit the admin session securely.
2. Manage Students/Courses
- Full CRUD (Create, Read, Update, Delete) functionality for both Student and Course
- Delete Student: Requires deleting the student AND deleting all associated Enrolment records
3. Update Student GPA
- Requires finding the student by ID and updating their GPA
4. Course Report
- Given a Course ID, list all students enrolled
5. Enrolment Statistics
- Show courses where current_enrolment is close to or at max_seats System Classes & Data Structures Main Classes  Student: id, name, gpa, password  Course: cid, name, max_seats, current_enrolment  Enrolment: eid, student_id, course_id, grade  Admin: id, name, password Data Storage  Linked lists for Student, Course, Enrolment, Admin  Files: Students.txt, Courses.txt, Enrolments.txt, Admins.txt 
