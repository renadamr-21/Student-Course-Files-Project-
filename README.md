# Course Management System

## Author

Renad Amr

---

## Overview

This project implements a Course Management System that allows students to register, enroll in courses, and track their academic progress, while providing administrators with full control over students, courses, and enrollments.

The system uses file handling and linked lists for data storage and management, demonstrating core concepts in data structures and system design.

---

## Key Features

### Student Operations

* Register / Login / Logout

  * New students can register with a unique ID and password
  * Existing students can log in using their credentials
  * Secure session handling with logout functionality

* Browse Courses

  * View all available courses

* Enroll in Course

  * Search for a course by ID
  * Check seat availability (current_enrolment < max_seats)
  * Add enrollment record and update seat count

* View Transcript

  * Display enrolled courses
  * Show course names and grades

---

### Admin Operations

* Login / Logout

  * Secure authentication for admin users

* Manage Students and Courses (CRUD)

  * Create, read, update, and delete students and courses

* Delete Student

  * Removes student record
  * Deletes all associated enrollment records

* Update Student GPA

  * Modify GPA using student ID

* Course Report

  * View all students enrolled in a specific course

* Enrollment Statistics

  * Identify courses nearing or reaching capacity

---

## System Design

### Main Classes

* Student: id, name, gpa, password
* Course: cid, name, max_seats, current_enrolment
* Enrollment: eid, student_id, course_id, grade
* Admin: id, name, password

---

### Data Structures

* Linked lists for:

  * Students
  * Courses
  * Enrollments
  * Admins

---

### Data Storage

* Students.txt
* Courses.txt
* Enrollments.txt
* Admins.txt

---

## How It Works

1. The system loads data from files into linked lists
2. Users log in as Student or Admin
3. Operations are performed (enrollment, updates, etc.)
4. Changes are saved back to the files

---

## Technologies Used

* Programming Language: C++
* File handling
* Linked lists

---

## Highlights

* Demonstrates use of data structures (linked lists)
* Implements real-world system logic (enrollment and authentication)
* Handles data persistence using files
* Includes both user and admin functionalities

---


