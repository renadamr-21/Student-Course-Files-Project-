#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//                                Nodes

class studentNode {
public:
    int id=0;
    string name="";
    float gpa=0.0;
    string password="";
    studentNode* next=NULL;
};
class courseNode {
public:
    int courseid=0;
    string name="";
    int maxseats=0;
    int currentEnrollment=0;
    courseNode* next=NULL;
};
class enrolmentNode {
public:
    int enrolmentid=0;
    string grade="";
    int studentid=0;
    int courseid=0;
    enrolmentNode* next=NULL;
};
class adminNode {
public:
    int id=0;
    string name="";
    string password="";
    adminNode* next=NULL;
};

//                                Lists

class studentList {
public:
    studentNode* head = NULL;
    studentNode* tail = NULL;
    void attach(studentNode* pnn) {
        if (head == NULL) {
            head = pnn;
            tail = pnn;
        }
        else {
            tail->next = pnn;
            tail = pnn;
        }
    }
    void loadStudents() {
        ifstream file;
        file.open("Students.txt");
        string x;

        if (file.is_open()) {
            while (getline(file, x)) {
                string temp[4];
                int k = 0;
                for (int i = 0; i < x.length(); i++) {
                    if (x[i] == ',') {
                        k++;
                    }
                    else {
                        temp[k] += x[i];
                    }
                }
                studentNode*pnn=new studentNode;
                pnn->id = stoi(temp[0]);
                pnn->name = temp[1];
                pnn->gpa = stof(temp[2]);
                pnn->password = temp[3];
                pnn->next = NULL;

                attach(pnn);
            }
            file.close();
        }
    }
    int login(int Sid, string Spass, string&name) {
        studentNode*trav=head;
        while (trav != NULL) {
            if (trav->id==Sid&&trav->password==Spass) {name=trav->name;return 1;}
            trav=trav->next;
        }
        return 0;
    }
    void saveStudents() {
        studentNode* current = head;
        ofstream file("Students.txt");

        if (file.is_open()) {
            while (current != NULL) {
                file << current->id << ","
                           << current->name << ","
                           << current->gpa << ","
                           << current->password << endl;
                current = current->next;
            }
            file.close();
        }
    }
    void addStudent(int id, string name, string password){
        studentNode* pnn=new studentNode;
        pnn->id=id;
        pnn->name=name;
        pnn->gpa=0.0;
        pnn->password=password;
        pnn->next=NULL;
        attach(pnn);
        saveStudents();
    }
    int idOk(int id) {
        studentNode*trav=head;
        while (trav!=NULL) {
            if (trav->id==id) {
                return 1;
            }
            trav=trav->next;
        }
        return 0;
    }
    void GPA(int sid,float newGpa){
        studentNode*current=head;
        int flag=0;

        while(current!=NULL){
            if (current->id == sid) {
                current->gpa=newGpa;
                flag=1;
                break;
            }
            current=current->next;
        }
        if(flag==1){
            saveStudents();
            cout<<"GPA updated for student "<<current->name<<endl;
        }else{
            cout<<"Student ID not found."<<endl;
        }
    }
    int deleteStudent(int id){
        studentNode*current=head;
        studentNode* prev=NULL;
        while (current!=NULL) {
            if (current->id==id) {
                if (prev==NULL) {
                    head=current->next;
                }else{
                    prev->next=current->next;
                }
                cout<<"Student with ID "<<id<<" deleted from system."<<endl;
                saveStudents();
                return 0;
            }
            prev=current;
            current=current->next;
        }
        cout<<"Student ID not found."<<endl;
        return 0;
    }
    string getName(int id){
        studentNode*trav=head;
        while(trav!=NULL){
            if(trav->id==id)return trav->name;
            trav=trav->next;
        }
        cout<<"Not found.";
    }
};
class courseList {
public:
    courseNode* head = NULL;
    courseNode* tail = NULL;

    void attach(courseNode*pnn){
        if (head==NULL) {
            head=pnn;
            tail=pnn;
        }
        else {
            tail->next=pnn;
            tail=pnn;
        }
    }
    void loadCourse() {
        ifstream file;
        file.open("Courses.txt");
        string x;
        if(file.is_open()){
            while(getline(file,x)){
                string temp[4];
                int k=0;
                for(int i=0;i<x.length();i++){
                    if(x[i]==',')k++;
                    else temp[k]+=x[i];
                }
                courseNode*pnn=new courseNode;
                pnn->courseid=stoi(temp[0]);
                pnn->name=temp[1];
                pnn->maxseats=stoi(temp[2]);
                pnn->currentEnrollment=stoi(temp[3]);
                pnn->next=NULL;
                attach(pnn);
            }
            file.close();
        }
    }
    void saveCourses(){
        courseNode*current=head;
        ofstream file("Courses.txt");
        if(file.is_open()){
            while(current!=NULL){
                file<<current->courseid<<","
                    <<current->name<<","
                    <<current->maxseats<<","
                    <<current->currentEnrollment<<endl;
                current=current->next;
            }
            file.close();
        }
    }
    void addCourse(int id,string name,int max) {
        courseNode*pnn=new courseNode;
        pnn->courseid=id;
        pnn->name=name;
        pnn->maxseats=max;
        pnn->currentEnrollment=0;
        pnn->next=NULL;
        attach(pnn);
        saveCourses();
    }
    void enrollmentStats(){
        courseNode*current=head;
        int f=0;
        while(current!=NULL){
            if(current->currentEnrollment>=(current->maxseats-10)){
                cout<<"Course: "<<current->name
                     <<" | Enrollment: "<<current->currentEnrollment
                     << "/"<<current->maxseats;
                if(current->currentEnrollment==current->maxseats) {
                    cout<<" [FULL]";
                }
                cout<<endl;
                f=1;
            }
            current=current->next;
        }

        if(f==0)cout<<"No courses are currently near capacity."<<endl;
    }
    void updateCourse(int id,string newName,int newMax){
        courseNode*current=head;
        int f=0;
        while(current!=NULL){
            if(current->courseid==id){
                current->name=newName;
                current->maxseats=newMax;
                f=1;
                break;
            }
            current=current->next;
        }
        if(f==0){
            cout<<"Course ID not found."<<endl;
        }else{
            cout<<"Course updated."<<endl;
            saveCourses();
        }
    }
    void deleteCourse(int id){
        courseNode*current=head;
        courseNode*prev=NULL;
        while(current!=NULL){
            if(current->courseid==id){
                if(prev==NULL)head=current->next;
                else prev->next=current->next;
                cout<<"Course deleted."<<endl;
                saveCourses();
                return;
            }
            prev=current;
            current=current->next;
        }
        cout<<"Course not found."<<endl;
    }
    void displayCourses(){
        courseNode*current=head;
        if(current==NULL){
            cout<<"No courses available at this time."<<endl;
            return;
        }
        while(current!=NULL){
            cout<<"ID: "<<current->courseid
                <<" | Name: "<<current->name
                <<" | Seats: "<<current->currentEnrollment
                <<"/"<<current->maxseats<<endl;
            current=current->next;
        }
    }
    int Seat(int cid){
        courseNode*current=head;
        while(current!=NULL){
            if(current->courseid==cid){
                if(current->currentEnrollment<current->maxseats){
                    current->currentEnrollment++;
                    saveCourses();
                    return 1;
                }else return 0;
            }
            current=current->next;
        }
        return -1;
    }
    string getName(int cid){
        courseNode*trav=head;
        while (trav!=NULL) {
            if(trav->courseid==cid) return trav->name;
            trav=trav->next;
        }
        return "Unknown Course";
    }
};
class enrolmentList{
public:
    enrolmentNode*head=NULL;
    enrolmentNode*tail=NULL;
    void attach(enrolmentNode*pnn){
        if (head==NULL) {
            head=pnn;
            tail=pnn;
        }
        else{
            tail->next=pnn;
            tail=pnn;
        }
    }
    void loadEnrollment(){
        ifstream file;
        file.open("Enrolments.txt");
        string x;
        if(file.is_open()){
            while(getline(file, x)){
                string temp[4];
                int k=0;
                for(int i=0;i<x.length();i++) {
                    if(x[i]==',') k++;
                    else temp[k]+=x[i];
                }
                enrolmentNode*pnn=new enrolmentNode;
                pnn->enrolmentid=stoi(temp[0]);
                pnn->grade=temp[1];
                pnn->studentid=stoi(temp[2]);
                pnn->courseid=stoi(temp[3]);
                pnn->next=NULL;
                attach(pnn);
            }
            file.close();
        }
    }
    void deleteS(int sid){
        enrolmentNode*current=head;
        enrolmentNode* prev=NULL;
        while (current!=NULL) {
            if (current->studentid==sid) {
                enrolmentNode*delt=current;
                if (prev==NULL) {
                    head=current->next;
                    current=head;
                } else {
                    prev->next=current->next;
                    current=current->next;
                }
            } else {
                prev=current;
                current=current->next;
            }
        }
    }
    void courseReport(int cid){
        enrolmentNode*trav=head;
        int found=0;
        cout<<"Enrollment Report for Course: "<<cid;
        while(trav!=NULL){
            if(trav->courseid==cid){
                cout<<"Student ID: "<<trav->studentid<<" , Grade: "<<trav->grade<<endl;
                found=1;
            }
            trav=trav->next;
        }
        if(found==0){
            cout<<"No students are currently enrolled in this course."<<endl;
        }
    }
    void saveEnrolments(){
        enrolmentNode*current=head;
        ofstream file("Enrolments.txt");
        if(file.is_open()){
            while(current!=NULL) {
                file<<current->enrolmentid<<","
                           <<current->grade<<","
                           <<current->studentid<<","
                           <<current->courseid<<endl;
                current=current->next;
            }
            file.close();
        }
    }
    void addE(int sid,int cid){
        enrolmentNode*pnn=new enrolmentNode;
        pnn->enrolmentid=sid+cid;
        pnn->grade="";
        pnn->studentid=sid;
        pnn->courseid=cid;
        pnn->next=NULL;
        attach(pnn);
        saveEnrolments();
    }
    void viewTranscript(int sid,courseList &CList){
        enrolmentNode*current=head;
        int found=0;
        while(current!=NULL){
            if(current->studentid==sid){
                string cName=CList.getName(current->courseid);
                cout<<"Course name: "<<cName
                    <<" | Course ID: "<<current->courseid
                    <<" | Grade: "<<current->grade<<endl;
                found=1;
            }
            current=current->next;
        }
        if(found==0)cout<<"No enrollments found for this ID."<<endl;
    }
};
class adminList {
public:
    adminNode*head=NULL;
    adminNode*tail=NULL;
    void attach(adminNode*pnn){
        if(head==NULL){
            head=pnn;
            tail=pnn;
        }
        else{
            tail->next=pnn;
            tail=pnn;
        }
    }
    void loadAdmin(){
        ifstream file;
        file.open("Admins.txt");
        string x;
        if (file.is_open()) {
            while(getline(file, x)){
                string temp[3];
                int k = 0;
                for (int i=0;i<x.length();i++) {
                    if (x[i]==',') k++;
                    else temp[k] += x[i];
                }
                adminNode*pnn=new adminNode;
                pnn->id=stoi(temp[0]);
                pnn->name=temp[1];
                pnn->password=temp[2];
                pnn->next = NULL;
                attach(pnn);
            }
            file.close();
        }
    }
    int login(int Sid,string Spass,string&name){
        adminNode*trav=head;
        while(trav!=NULL){
            if(trav->id==Sid&&trav->password==Spass) {
                name=trav->name;
                return 1;
            }
            trav=trav->next;
        }
        return 0;
    }
};

//////////////////////////////////////////////////////////////////////////////////////

int main(){
    int exit=0;
    int N;
    studentList SList;
    courseList CList;
    enrolmentList EList;
    adminList AList;
    AList.loadAdmin();
    SList.loadStudents();
    CList.loadCourse();
    while(exit==0){
        cout<<"Welcome to course system!"<<endl
            <<"1- Login as a student."<<endl
            <<"2- Login as an admin."<<endl
            <<"3- Register."<<endl
            <<"4- Exit."<<endl;
        cin>>N;
        if(N==1){
            int id;
            string pass,sucname;
            cout<<"Enter student ID: ";
            cin>>id;
            cout<<"Enter Password: ";
            cin>>pass;
            if(SList.login(id,pass,sucname)){
                cout<<"Login successful! Welcome "<<sucname<<endl;
                int exit=0;
                while(exit==0){
                    int N;
                    cout<<"1- Browse courses"<<endl
                    <<"2- Enrol in course"<<endl
                    <<"3- View transcript"<<endl
                    <<"4- Exit";
                    cin>>N;
                    if(N==1)CList.displayCourses();
                    else if(N==2){
                        int targetCid;
                        cout<<"Enter Course ID to enroll: ";
                        cin>>targetCid;
                        int status=CList.Seat(targetCid);
                        if(status==1){
                            EList.addE(id,targetCid);
                            cout<<"Enrolled successfully!"<<endl;
                        }
                        else if(status==0)cout<<"Error: Course is full."<<endl;
                        else cout<<"Error: Course ID not found."<<endl;
                    }
                    else if(N==3)EList.viewTranscript(id,CList);
                    else if(N==4)exit = 1;
                }
            }
            else cout<<"Invalid ID or Password."<<endl;
        }
        else if(N==2){
            int id;
            string pass,sucname;
            cout<<"Enter admin ID: ";
            cin>>id;
            cout<<"Enter Password: ";
            cin>>pass;
            if(AList.login(id,pass,sucname)){
                cout<<"Login successful! Welcome "<<sucname<<endl;
                int exit=0;
                while(exit==0){
                    int N;
                    cout<<"1- Add new course"<<endl
                        <<"2- Update course"<<endl
                        <<"3- Delete course"<<endl
                        <<"4- Update GPA"<<endl
                        <<"5- Delete a student"<<endl
                        <<"6- Course report"<<endl
                        <<"7- Enrollment statistics"<<endl
                        <<"8- Exit";
                    cin>>N;
                    if(N==1){
                        int cid,cmax;
                        string cname;
                        cout<<"Enter Course ID: ";
                        cin>>cid;
                        cout<<"Enter Course Name: ";
                        cin.ignore();
                        getline(cin, cname);
                        cout<<"Enter Max Seats: ";cin>>cmax;
                        CList.addCourse(cid, cname, cmax);
                        cout<<"Course added successfully!"<<endl;
                    }
                    else if(N==2){
                        int cid, m;
                        string n;
                        cout<<"ID to update: ";
                        cin >> cid;
                        cin.ignore();
                        cout<<"New Name: ";
                        getline(cin, n);
                        cout<<"New Max Seats: ";
                        cin >> m;
                        CList.updateCourse(cid, n, m);
                    }
                    else if(N==3){
                        int cid;
                        cout<<"ID to delete: ";cin>>cid;
                        CList.deleteCourse(cid);
                    }
                    else if(N==4){
                        int id;
                        float gpa;
                        cout<<"Enter student ID to update GPA: ";
                        cin>>id;
                        cout<<"Enter new GPA: ";
                        cin>>gpa;
                        SList.GPA(id, gpa);
                    }
                    else if(N==5){
                        int id;
                        cout<<"Enter student ID to delete: ";
                        cin>>id;
                        SList.deleteStudent(id);
                        EList.deleteS(id);
                    }
                    else if(N==6){
                        int cid;
                        cout<<"Enter Course ID to view enrolled students: ";
                        cin>>cid;
                        EList.courseReport(cid);
                    }
                    else if(N==7)CList.enrollmentStats();
                    else if(N==8)exit=1;
                }
            }
            else cout<<"Invalid ID or Password."<<endl;
        }
        else if(N==3){
            int f=1;
            while(f==1){
                int newId;
                string name,pass;
                cout<<"Enter ID: ";
                cin>>newId;
                if(SList.idOk(newId)){
                    cout<<"ID already exists. Enter 1 to try again or enter 0 to get back to the main menu."<<endl;
                    cin>>f;
                }
                else{
                    cin.ignore();
                    cout<<"Enter Full Name: ";
                    getline(cin, name);
                    cout<<"Set Password: ";
                    cin>>pass;
                    SList.addStudent(newId,name,pass);
                    cout<<"Registration successful! You can now login."<<endl;
                    f=0;
                }
            }
        }
        else if (N==4) exit=1;
    }
    return 0;
}